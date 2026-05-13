import pygame
import random
from display_utils import display_fullscreen
import os

class Planets:
    def __init__(self, photos_folder_path):
        
        planets_file = {"mercury": "Mercury.jpg",
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
        
        self.__planets = dict()
        
        for key in planets_file:
            path = os.path.join(photos_folder_path, planets_file[key])
            self.__planets[key] = pygame.image.load(path).convert()

    def display(self, screen:pygame.Surface, planet:str, x:float, y:float, scale:float):
        display_fullscreen(self.__planets[planet], screen, x, y, scale)
