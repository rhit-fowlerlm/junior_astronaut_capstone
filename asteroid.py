import pygame
import random
import numpy as np
from display_utils import display_fullscreen, GIF_animation
import os
from datetime import datetime
from inputs import AsteroidInput


class AsteroidData:
    def __init__(self):
        self.asteroid_idx = 0
        self.start_x = 0
        self.start_y = 0
        self.x = 0
        self.y = 0
        self.vx = 0
        self.vy = 0
        self.rotation_angle = 0
        self.scale = 0.01
        self.is_moving = False
        self.is_exploding = False
        self.explosion_start:datetime = datetime.now()

class Asteroid:
    def __init__(self, asteroid_folder_path, explosion_folder_path, filenames):
        
        asteroid_files = filenames

        self.__asteroids = []
        
        for filename in asteroid_files:
            path = os.path.join(asteroid_folder_path, filename)
            self.__asteroids.append(pygame.image.load(path).convert_alpha())

        self.angle_range_deg = 30
        self.speed_min = 0.1
        self.speed_max = 0.5
        self.scale_min = 0.05
        self.scale_max = 0.1

        self.__asteroid_datas:list[AsteroidData] = []
        
        self.__explosion_frames = []
        self.__num_explosion_frames = 16
        for i in range(self.__num_explosion_frames):
            self.__explosion_frames.append(pygame.image.load(os.path.join(explosion_folder_path, f"{i}.png")).convert())
        self.__explosion_duration = 0.5

    def create(self):
        new_asteroid = AsteroidData()
        new_asteroid.is_moving = True
        angle = np.random.uniform(2*np.pi)
        
        new_asteroid.x = np.cos(angle)
        new_asteroid.y = np.sin(angle)

        speed = np.random.uniform(self.speed_min, self.speed_max)
        speed_angle = angle + np.deg2rad(np.random.uniform(-self.angle_range_deg/2, self.angle_range_deg/2))
        new_asteroid.vx = -speed*np.cos(speed_angle)
        new_asteroid.vy = -speed*np.sin(speed_angle)

        new_asteroid.rotation_angle = speed_angle

        new_asteroid.scale = np.random.uniform(self.scale_min, self.scale_max)

        new_asteroid.asteroid_idx = np.random.randint(len(self.__asteroids))

        self.__asteroid_datas.append(new_asteroid)

    def destroy(self):
        if len(self.__asteroid_datas) > 0:
            i = random.randrange(0, len(self.__asteroid_datas))
            self.__asteroid_datas[i].is_exploding = True
            self.__asteroid_datas[i].explosion_start = datetime.now()

    def destroy_all(self):
        for i in range(len(self.__asteroid_datas)):
            self.__asteroid_datas[i].is_exploding = True
            self.__asteroid_datas[i].explosion_start = datetime.now()

    def update(self, screen:pygame.Surface, tick:float, inputs:AsteroidInput):
        if inputs.create:
            self.create()
        # if inputs.destroy:
        #     self.destroy()
        # if inputs.super_destroy:
        #     self.destroy_all()

        ws, hs = screen.get_size()
        for i in range(len(self.__asteroid_datas)):
            astr = self.__asteroid_datas[i]
            j = 0
            if astr.x == astr.start_x and astr.y == astr.start_y:
                while abs(astr.x) > 0.5 + astr.scale and abs(astr.y) > 0.5 * hs/ws + astr.scale and astr.x * astr.vx + astr.y * astr.vy > 0 and j < 100:
                    astr.x += astr.vx * 0.01 / np.sqrt(astr.vx*astr.vx + astr.vy*astr.vy)
                    astr.y += astr.vy * 0.01 / np.sqrt(astr.vx*astr.vx + astr.vy*astr.vy)
                    j += 1
                    astr.start_x = astr.x
                    astr.start_y = astr.y

            astr.x += astr.vx * tick
            astr.y += astr.vy * tick

            if (abs(astr.x) > 0.5 or abs(astr.y) > 0.5 * hs/ws) and astr.x * astr.vx + astr.y * astr.vy > 0:
                astr.is_moving = False

            if astr.is_moving:
                if not astr.is_exploding:
                    asteroid = pygame.transform.rotate(self.__asteroids[astr.asteroid_idx], np.rad2deg(astr.rotation_angle))
                    display_fullscreen(asteroid, screen, astr.x, astr.y, astr.scale)
                else:
                    dt = (datetime.now() - astr.explosion_start).total_seconds()
                    frame = np.floor(self.__explosion_frames * dt / self.__explosion_duration)
                    if frame < self.__explosion_frames:
                        display_fullscreen(self.__explosion_frames[frame], screen, astr.x, astr.y, astr.scale)


        new_aster_array = []

        for astr in self.__asteroid_datas:
            if astr.is_moving:
                new_aster_array.append(astr)

        self.__asteroid_datas = new_aster_array
