import pygame
import random
import numpy as np
from display_utils import display_fullscreen
import os

class Asteroid:
    def __init__(self, asteroid_folder_path):
        
        asteroid_files = ["Asteroid1.png"]

        self.__asteroids = []
        
        for filename in asteroid_files:
            path = os.path.join(asteroid_folder_path, filename)
            self.__asteroids.append(pygame.image.load(path).convert_alpha())

        self.angle_range_deg = 30
        self.speed_min = 0.1
        self.speed_max = 0.5
        self.scale_min = 0.05
        self.scale_max = 0.1

        self.asteroid_idx = 0
        self.x = 0
        self.y = 0
        self.vx = 0
        self.vy = 0
        self.rotation_angle = 0
        self.scale = 0.01
        self.is_moving = False

    def start(self):
        if not self.is_moving:
            self.is_moving = True
            angle = np.random.uniform(2*np.pi)
            
            self.x = np.cos(angle)
            self.y = np.sin(angle)

            speed = np.random.uniform(self.speed_min, self.speed_max)
            speed_angle = angle + np.deg2rad(np.random.uniform(-self.angle_range_deg/2, self.angle_range_deg/2))
            self.vx = -speed*np.cos(speed_angle)
            self.vy = -speed*np.sin(speed_angle)

            self.rotation_angle = speed_angle

            self.scale = np.random.uniform(self.scale_min, self.scale_max)

            self.asteroid_idx = np.random.randint(len(self.__asteroids))

            

    def update(self, screen:pygame.Surface, tick:float):
        ws, hs = screen.get_size()

        while abs(self.x) > 0.5 + self.scale and abs(self.y) > 0.5 * hs/ws + self.scale:
            self.x += self.vx * 1e-4
            self.y += self.vy * 1e-4

        self.x += self.vx * tick
        self.y += self.vy * tick

        if abs(self.x) > 0.5 and abs(self.y) > 0.5 * hs/ws and self.x * self.vx + self.y * self.vy > 0:
            self.is_moving = False

        if self.is_moving:
            asteroid = pygame.transform.rotate(self.__asteroids[self.asteroid_idx], np.rad2deg(self.rotation_angle))
            display_fullscreen(asteroid, screen, self.x, self.y, self.scale)
