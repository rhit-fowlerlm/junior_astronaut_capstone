import pygame
from display_utils import display_fullscreen
import numpy as np
import os

class GIF_animation:
    def __init__(self, path, num_frames):
        self.__frames = []
        for i in range(num_frames):
            self.__frames.append(pygame.image.load(os.path.join(path, f"{i}.png")).convert())
        self.__i = 0
    
    def update(self, speed, tick):
        self.__i += speed * len(self.__frames) * tick
        self.__i %= len(self.__frames)
        
    def get_surf(self):
        i = round(self.__i)
        i %= len(self.__frames)
        return self.__frames[i]

class Warp:
    def __init__(self, warp_animation_folder:str, warp_sfx_file:str, travel_time:float, max_speed:float):
        self.__warp = GIF_animation(warp_animation_folder, 179)
        self.__warp_sound = pygame.mixer.Sound(warp_sfx_file)
        self.__warping = 0
        self.__t = 0
        self.__travel_time = travel_time
        self.__max_speed = max_speed
        self.__surf = None
        
    def start(self):
        if self.__warping == 0:
            self.__warp_sound.play()
            self.__t = 0
            self.__warping = 1
        
    def is_warping(self):
        return self.__warping > 0
            
    def should_switch_background(self):
        return self.__warping == 2
    
    def continue_warp(self):
        if self.__warping == 2:
            self.__warping = 3
        
    def update(self, screen:pygame.Surface, tick):
        scale = max(np.sin(np.pi * self.__t/self.__travel_time), 0)
        if self.__t > self.__travel_time:
            scale = 0
        self.__warp.update(self.__max_speed * scale + 0.1, tick)
        if self.__warping == 0:
            self.__surf = pygame.Surface((1,1))
            self.__surf.set_alpha(0)
        else:
            if self.__warping != 2:
                self.__t += tick
            self.__surf = self.__warp.get_surf()
            self.__surf.set_alpha(min(max(round(255 * scale), 0), 255))
            if self.__warping == 1:
                if self.__t > self.__travel_time/2:
                    self.__t = self.__travel_time/2
                    self.__warping = 2
            if self.__warping == 3:
                if self.__t > self.__travel_time:
                    self.__warping = 4
            if self.__warping == 4:
                if self.__t > self.__warp_sound.get_length():
                    self.__warping = 0
        
        display_fullscreen(self.__surf, screen, 0, 0, 1)