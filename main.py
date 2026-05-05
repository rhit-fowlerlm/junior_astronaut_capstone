import pygame
import numpy as np
import random

SHOULD_FULLSCREEN = True

pygame.init()
if SHOULD_FULLSCREEN:
    screen = pygame.display.set_mode((0, 0), flags = pygame.FULLSCREEN)
else:
    screen = pygame.display.set_mode((1000, 1000))
clock = pygame.time.Clock()
running = True

t = 0.0

base_path = "/home/space-station/junior_astronaut_capstone"

class Planets:
    def __init__(self):
        
        self.planets = {"mercury": "/Photos/Mercury.jpg",
                        "venus": "/Photos/Venus.jpg",
                        "earth": "/Photos/Earth.jpg",
                        "mars": "/Photos/Mars.jpg",
                        "jupiter": "/Photos/Jupiter.jpg",
                        "saturn": "/Photos/Saturn.jpg",
                        "uranus": "/Photos/Uranus.jpg",
                        "neptune": "/Photos/Neptune.jpg",
                        
                        "pluto": "/Photos/Pluto.jpg",
                        "ceres": "/Photos/Ceres.jpg",
                        
                        "titan": "/Photos/Titan.jpg",
                        "enceladus": "/Photos/Enceladus.jpg",
                        
                        "io": "/Photos/Io.jpg",
                        "ganymede": "/Photos/Ganymede.jpg",
                        "callisto": "/Photos/Callisto.jpg",
                        "europa": "/Photos/Europa.jpg",
                        
                        "moon": "/Photos/Moon.jpg",}
        
        self.planet = ""
        self.surf = None
        self.go_to("earth")
        
    def go_to(self, planet):
        if planet != self.planet:
            self.planet = planet
            # print("Loaded", base_path + self.planets[self.planet])
            self.surf = pygame.image.load(base_path + self.planets[self.planet]).convert()
            # print(self.sur  f.get_size())
        
    def go_to_random(self):
        self.go_to(random.choice(list(self.planets)))
    
    

class GIF_animation:
    def __init__(self, path, num_frames):
        self.frames = []
        for i in range(num_frames):
            self.frames.append(pygame.image.load("{}/{}.png".format(path, i)).convert())
        self.i = 0
    def update(self, speed, tick):
        self.i += speed * len(self.frames) * tick
        self.i %= len(self.frames)
        
    def get_surf(self):
        i = round(self.i)
        i %= len(self.frames)
        return self.frames[i]

class Warp:
    def __init__(self, travel_time, max_speed):
        self.warp = GIF_animation(base_path + "/Photos/WarpTrails001_frames", 179)
        self.warp_sound = pygame.mixer.Sound(base_path + "/SFX/warp_woosh.wav")
        self.warping = 0
        self.t = 0
        self.travel_time = travel_time
        self.max_speed = max_speed
        self.surf = None
        self.update(0)
        
    def start(self):
        if self.warping == 0:
            self.warp_sound.play()
            self.t = 0
            self.warping = 1
        
    def is_warping(self):
        return self.warping > 0
            
    def should_switch_background(self):
        return self.warping == 2
    
    def continue_warp(self):
        if self.warping == 2:
            self.warping = 3
        
    def update(self, tick):
        scale = max(np.sin(np.pi * self.t/self.travel_time), 0)
        if self.t > self.travel_time:
            scale = 0
        self.warp.update(self.max_speed * scale + 0.1, tick)
        if self.warping == 0:
            self.surf = pygame.Surface((1,1))
            self.surf.set_alpha(0)
        else:
            if self.warping != 2:
                self.t += tick
            self.surf = self.warp.get_surf()
            self.surf.set_alpha(min(max(round(255 * scale), 0), 255))
            if self.warping == 1:
                if self.t > self.travel_time/2:
                    self.t = self.travel_time/2
                    self.warping = 2
            if self.warping == 3:
                if self.t > self.travel_time:
                    self.warping = 4
            if self.warping == 4:
                if self.t > self.warp_sound.get_length():
                    self.warping = 0
            

def display_fullscreen(surf):
    w, h = surf.get_size()
    ws, hs = screen.get_size()
    scale_ratio = hs/h
    
    w_new = round(scale_ratio * w)
    h_new = round(scale_ratio * h)
    
    surf_scaled = pygame.transform.scale(surf, (w_new, h_new))
    
    pos_x = (ws - w_new) / 2
    pos_y = (hs - h_new) / 2
    
    return surf_scaled, (pos_x, pos_y)

warp = Warp(2, 0.2)
planets = Planets()

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
    
    # Fill screen
    screen.fill("black")
    
    scaled_image, pos = display_fullscreen(planets.surf)
    screen.blit(scaled_image, pos)
        
    if warp.should_switch_background():
        planets.go_to_random()
        warp.continue_warp()
    
    warp.update(clock.get_time() * 1e-3)
    
    scaled_image, pos = display_fullscreen(warp.surf)
    screen.blit(scaled_image, pos)

    
    # Hide Mouse
    pygame.mouse.set_visible(False)
    
    # Display onto screen
    pygame.display.flip()
    
    t += clock.tick(60) * 1e-3
    
pygame.quit()
