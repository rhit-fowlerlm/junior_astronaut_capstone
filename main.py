import pygame
import os
import platform

# from display_utils import smooth_screen

from spacecraft import Spacecraft
from inputs import Inputs
from asteroid import Asteroid
from soundboard import Soundboard


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

spacecraft = Spacecraft(os.path.join(base_path, "Photos", "Planets"), os.path.join(base_path, "Photos", "WarpTrails001_frames"), os.path.join(base_path, "Sounds", "SFX", "warp_woosh.wav"), 2, 0.2)
asteroid = Asteroid(os.path.join(base_path, "Photos", "Asteroids"), ["Asteroid1.png"])
inputs = Inputs()
soundboard = Soundboard(os.path.join(base_path, "Sounds"))

p = "earth"

font = pygame.font.SysFont("Arial" , 18 , bold = True)

def fps_counter():
    fps = str(int(clock.get_fps()))
    fps_t = font.render(fps , 1, pygame.Color("RED"))
    screen.blit(fps_t,(100,100))

while running:
    # Update current time
    # poll for events
    tick = clock.get_time() * 1e-3

    inputs.update()

    for event in pygame.event.get():
        # If quit button pressed, quit game
        if event.type == pygame.QUIT:
            running = False
        
        # If escape button pressed, quit game
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                running = False
            if event.key == pygame.K_SPACE:
                # warp.start()
                asteroid.start()
                # soundboard.random_historical()
                soundboard.stir()
                pass
            if event.key == pygame.K_UP:
                inputs.joystick.y = 1
            if event.key == pygame.K_DOWN:
                inputs.joystick.y = -1
            if event.key == pygame.K_RIGHT:
                inputs.joystick.x = 1
            if event.key == pygame.K_LEFT:
                inputs.joystick.x = -1
            if event.key == pygame.K_PAGEUP:
                inputs.joystick.z = 1
            if event.key == pygame.K_PAGEDOWN:
                inputs.joystick.z = -1


    if inputs.planet_encoder.update_flag:
        spacecraft.set_planet(inputs.planet_encoder.planet)
        inputs.planet_encoder.update_flag = False
    
    # Fill screen
    screen.fill("black")

    spacecraft.update(screen, inputs.joystick, tick)

    asteroid.update(screen, tick)

    soundboard.update(inputs.audio, inputs.joystick)

    fps_counter()

    #smooth_screen(screen, 1)

    
    # Hide Mouse
    pygame.mouse.set_visible(False)
    
    # Display onto screen
    pygame.display.flip()
    
    t += clock.tick(120) * 1e-3
    
pygame.quit()