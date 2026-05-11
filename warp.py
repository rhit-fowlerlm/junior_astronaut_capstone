import pygame
from display_utils import display_fullscreen
import numpy as np
import os

class GIF_animation:
    def __init__(self, path, num_frames):
        self.frames = []
        for i in range(num_frames):
            self.frames.append(pygame.image.load(os.path.join(path, f"{i}.png")).convert())
        self.i = 0
    def update(self, speed, tick):
        self.i += speed * len(self.frames) * tick
        self.i %= len(self.frames)
        
    def get_surf(self):
        i = round(self.i)
        i %= len(self.frames)
        return self.frames[i]

class Warp:
    def __init__(self, warp_animation_folder:str, warp_sfx_file:str, travel_time:float, max_speed:float):
        self.warp = GIF_animation(warp_animation_folder, 179)
        self.warp_sound = pygame.mixer.Sound(warp_sfx_file)
        self.warping = 0
        self.t = 0
        self.travel_time = travel_time
        self.max_speed = max_speed
        self.surf = None
        
    def start(self):
        if self.warping == 0:
            self.warp_sound.play()
            self.t = 0
            self.warping = 1
        
    def is_warping(self):
        return self.warping > 0
            
    def should_switch_background(self):
        return self.warping == 2
    
    def continue_warp(self):
        if self.warping == 2:
            self.warping = 3
        
    def update(self, screen:pygame.Surface, tick):
        scale = max(np.sin(np.pi * self.t/self.travel_time), 0)
        if self.t > self.travel_time:
            scale = 0
        self.warp.update(self.max_speed * scale + 0.1, tick)
        if self.warping == 0:
            self.surf = pygame.Surface((1,1))
            self.surf.set_alpha(0)
        else:
            if self.warping != 2:
                self.t += tick
            self.surf = self.warp.get_surf()
            self.surf.set_alpha(min(max(round(255 * scale), 0), 255))
            if self.warping == 1:
                if self.t > self.travel_time/2:
                    self.t = self.travel_time/2
                    self.warping = 2
            if self.warping == 3:
                if self.t > self.travel_time:
                    self.warping = 4
            if self.warping == 4:
                if self.t > self.warp_sound.get_length():
                    self.warping = 0
        
        display_fullscreen(self.surf, screen, 0, 0, 1)