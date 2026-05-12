import pygame
import os

class SFXSoundboard:
    def __init__(self, sfx_folder):

        sfx_files = dict()

        self.__sfx = dict()

        for key in sfx_files:
            path = os.path.join(sfx_folder, sfx_files[key])
            self.__sfx[key] = pygame.mixer.Sound(path)

        