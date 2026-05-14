import pygame
import os
from spacecraft import Spacecraft
from inputs import Inputs
from asteroid import Asteroid
from soundboard import Soundboard

pygame.mixer.pre_init(buffer=8192)
pygame.init()

screen = pygame.display.set_mode((0, 0), flags = pygame.FULLSCREEN)
clock = pygame.time.Clock()
running = True

t = 0.0

base_path = "/home/space-station/junior_astronaut_capstone/RaspberryPi"

spacecraft = Spacecraft(os.path.join(base_path, "Photos", "Planets"), os.path.join(base_path, "Photos", "WarpTrails001_frames"), os.path.join(base_path, "Sounds", "SFX", "warp_woosh.wav"), 2, 0.2)
asteroid = Asteroid(os.path.join(base_path, "Photos", "Asteroids"), os.path.join(base_path, "Photos", "Explosion"))
inputs = Inputs()
soundboard = Soundboard(os.path.join(base_path, "Sounds"))

while running:
    # Update current time
    # poll for events
    tick = clock.get_time() * 1e-3

    # Process inputs
    inputs.update()

    for event in pygame.event.get():
        # If quit button pressed, quit game
        if event.type == pygame.QUIT:
            running = False
        # If escape button pressed, quit game
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                running = False

    if inputs.planet_encoder.update_flag:
        spacecraft.set_planet(inputs.planet_encoder.planet)
        inputs.planet_encoder.update_flag = False
    
    # Blank screen
    screen.fill("black")

    # Draw new frame
    spacecraft.update(screen, inputs.joystick, tick)
    asteroid.update(screen, tick, inputs.asteroid)
    soundboard.update(inputs.audio, inputs.joystick)

    # Hide Mouse
    pygame.mouse.set_visible(False)
    
    # Display onto screen
    pygame.display.flip()
    
    t += clock.tick(120) * 1e-3
    
pygame.quit()
inputs.close()