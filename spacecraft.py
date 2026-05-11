import pygame
from planet_images import Planets
from warp import Warp
from inputs import JoystickInput
import numpy as np

class Spacecraft:
    def __init__(self, planet_photos_path:str, warp_animation_folder:str, warp_sfx_file:str, travel_time:float, max_speed:float):
        self.__planets = Planets(planet_photos_path)
        self.__warp = Warp(warp_animation_folder, warp_sfx_file, travel_time, max_speed)
        self.x = 0
        self.y = 0
        self.z = 1
        self.speed_xy = 1e-2
        self.speed_z = 1e-2
        self.planet = "earth"

    def update(self, screen:pygame.Surface, joystick:JoystickInput, tick:float):
        self.x -= joystick.x * self.speed_xy * tick
        self.y += joystick.y * self.speed_xy * tick
        self.z += joystick.z * self.speed_z * tick

        self.x = np.clip(self.x, -1, 1)
        self.y = np.clip(self.y, -1, 1)
        self.z = np.clip(self.z, 0.1, 10)
        

        self.__planets.display(screen, self.planet, self.x, self.y, self.z)
        self.__warp.update(screen, tick)