import pygame

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