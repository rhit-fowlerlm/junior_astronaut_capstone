import pygame
from planet_images import Planets
from warp import Warp
from inputs import JoystickInput
import numpy as np
from PlanetOrbits import PlanetsOrbits

class Spacecraft:
    def __init__(self, planet_photos_path:str, warp_animation_folder:str, warp_sfx_file:str, travel_time:float, max_speed:float):
        self.__planets = Planets(planet_photos_path)
        self.__warp = Warp(warp_animation_folder, warp_sfx_file, travel_time, max_speed)
        self.__planet_orbits = PlanetsOrbits()
        self.x = 0
        self.y = 0
        self.z = 1
        self.speed_xy = 1e-1
        self.speed_z = 1e-1
        self.curr_planet_idx = 2
        self.target_planet_idx = 2
        self.planet_names = ["mercury", "venus", "earth", "mars", "jupiter", "saturn", "uranus", "neptune"]

        self.R = 0.1
        self.k = 0.2

    def set_planet(self, target_planet_idx):
        self.target_planet_idx = target_planet_idx

    def update(self, screen:pygame.Surface, joystick:JoystickInput, tick:float):
        if not self.__warp.is_warping():
            dx = -joystick.x - self.k * self.x / self.z
            dy =  joystick.y - self.k * self.y / self.z
            dz =  joystick.z - self.k * (self.z - 1)


            self.x += dx * self.speed_xy * tick / self.z
            self.y += dy * self.speed_xy * tick / self.z
            self.z += dz * self.speed_z * tick

            self.x = np.clip(self.x, -1.5, 1.5)
            self.y = np.clip(self.y, -1.5, 1.5)
            self.z = np.clip(self.z, 0.1, 10)

        d = (self.x*self.x + self.y*self.y)*self.z
        
        if d > self.R:
            self.change_planets_out_of_bounds()

        if self.curr_planet_idx != self.target_planet_idx and not self.__warp.is_warping():
            self.__warp.start()
                

        if self.__warp.should_switch_background():
            self.curr_planet_idx = self.target_planet_idx
            self.x = 0
            self.y = 0
            self.z = 1
            self.__warp.continue_warp()
            

        self.__planets.display(screen, self.planet_names[self.curr_planet_idx], self.x, self.y, self.z)
        self.__warp.update(screen, tick)

    def change_planets_out_of_bounds(self):
        
        if self.curr_planet_idx == 0:
            self.target_planet_idx = self.curr_planet_idx + 1
            return
        if self.curr_planet_idx == len(self.planet_names) - 1:
            self.target_planet_idx = self.target_planet_idx - 1
            return
        
        cos_next = self.get_cos_from_vector_to_planet(self.curr_planet_idx+1)
        cos_prev = self.get_cos_from_vector_to_planet(self.curr_planet_idx-1)
        
        if cos_next > cos_prev:
            self.target_planet_idx = self.curr_planet_idx + 1
        else:
            self.target_planet_idx = self.curr_planet_idx - 1

    def get_cos_from_vector_to_planet(self, planet_idx:int):
        positions = self.__planet_orbits.get_planet_positions()

        curr_planet_pos = positions[self.planet_names[self.curr_planet_idx]]
        other_planet = positions[self.planet_names[planet_idx]]

        dx = other_planet[0] - curr_planet_pos[0]
        dy = other_planet[1] - curr_planet_pos[1]

        cos = self.x*dx + self.y*dy / np.sqrt((self.x*self.x+self.y*self.y)*(dx*dx+dy*dy))

        return cos