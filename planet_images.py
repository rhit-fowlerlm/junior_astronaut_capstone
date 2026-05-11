import pygame
import random
from display_utils import display_fullscreen
import os

class Planets:
    def __init__(self, photos_folder_path):
        
        self.planets = {"mercury": "Mercury.jpg",
                        "venus": "Venus.jpg",
                        "earth": "Earth.jpg",
                        "mars": "Mars.jpg",
                        "jupiter": "Jupiter.jpg",
                        "saturn": "Saturn.jpg",
                        "uranus": "Uranus.jpg",
                        "neptune": "Neptune.jpg",
                        
                        "pluto": "Pluto.jpg",
                        "ceres": "Ceres.jpg",
                        
                        "titan": "Titan.jpg",
                        "enceladus": "Enceladus.jpg",
                        
                        "io": "Io.jpg",
                        "ganymede": "Ganymede.jpg",
                        "callisto": "Callisto.jpg",
                        "europa": "Europa.jpg",
                        
                        "moon": "Moon.jpg",}
        
        for key in self.planets:
            self.planets[key] = os.path.join(photos_folder_path, self.planets[key])
        
        self.planet:str = ""
        self.surf:pygame.Surface = None
        self.go_to("earth")
        
    def go_to(self, planet:str):
        if planet != self.planet:
            self.planet = planet
            # print("Loaded", base_path + self.planets[self.planet])
            self.surf = pygame.image.load(self.planets[self.planet]).convert()
            # print(self.sur  f.get_size())
        
    def go_to_random(self):
        self.go_to(random.choice(list(self.planets)))

    def display(self, screen:pygame.Surface, x:float, y:float, scale:float):
        display_fullscreen(self.surf, screen, x, y, scale)
