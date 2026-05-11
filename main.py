import pygame
import numpy as np
import random
from planet_images import Planets
from warp import Warp
import os
import platform

SHOULD_FULLSCREEN = True

pygame.init()
if SHOULD_FULLSCREEN:
    screen = pygame.display.set_mode((0, 0), flags = pygame.FULLSCREEN)
else:
    screen = pygame.display.set_mode((1000, 1000))
clock = pygame.time.Clock()
running = True

t = 0.0

if platform.system() == "Linux":
    base_path = "/home/space-station/junior_astronaut_capstone"
if platform.system() == "Windows":
    base_path = "C:\\Users\\fowlerlm\\OneDrive - Rose-Hulman Institute of Technology\\Documents\\_Capstone\\Code\\junior_astronaut_capstone\\"

warp = Warp(os.path.join(base_path, "Photos", "WarpTrails001_frames"), os.path.join(base_path, "SFX", "warp_woosh.wav"), 2, 0.2)
planets = Planets(os.path.join(base_path, "Photos"))

while running:
    # Update current time
    # poll for events
    for event in pygame.event.get():
        # If quit button pressed, quit game
        if event.type == pygame.QUIT:
            running = False
        
        # If escape button pressed, quit game
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                running = False
            if event.key == pygame.K_SPACE:
                # planets.go_to_random()
                warp.start()
                pass
    
    # Fill screen
    screen.fill("black")

    planets.display(screen, 0, 0, 1)
        
    if warp.should_switch_background():
        planets.go_to_random()
        warp.continue_warp()
    
    warp.update(screen, clock.get_time() * 1e-3)

    
    # Hide Mouse
    pygame.mouse.set_visible(False)
    
    # Display onto screen
    pygame.display.flip()
    
    t += clock.tick(60) * 1e-3
    
pygame.quit()
