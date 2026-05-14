import pygame
import os
# from scipy.ndimage import gaussian_filter

class GIF_animation:
    def __init__(self, path, num_frames):
        self.__frames = []
        for i in range(num_frames):
            self.__frames.append(pygame.image.load(os.path.join(path, f"{i}.png")).convert())
        self.__i = 0
    
    def update(self, speed, tick):
        self.__i += speed * len(self.__frames) * tick
        self.__i %= len(self.__frames)
        
    def get_surf(self):
        i = round(self.__i)
        i %= len(self.__frames)
        return self.__frames[i]

def display_fullscreen(surf:pygame.Surface, screen:pygame.Surface, x:float, y:float, scale:float):
        w, h = surf.get_size()
        ws, hs = screen.get_size()
        scale_ratio = hs/h

        scale_ratio = scale_ratio * scale
        
        w_new = round(scale_ratio * w)
        h_new = round(scale_ratio * h)

        dx = ws*x
        dy = ws*y
        
        surf_scaled = pygame.transform.scale(surf, (w_new, h_new))
        
        pos_x = (ws - w_new) / 2
        pos_y = (hs - h_new) / 2

        screen.blit(surf_scaled, (pos_x + dx, pos_y + dy))

# def smooth_screen(screen:pygame.Surface, sig:int):
#         r = pygame.surfarray.pixels_red(screen)
#         gaussian_filter(r, sigma=sig, mode="nearest", output=r)
#         g = pygame.surfarray.pixels_green(screen)
#         gaussian_filter(g, sigma=sig, mode="nearest", output=g)
#         b = pygame.surfarray.pixels_red(screen)
#         gaussian_filter(r, sigma=sig, mode="nearest", output=b)