from PIL import Image
import os

path = os.path.join("Photos", "Explosion")

img = Image.open(os.path.join(path, "exp2_alpha_1.png"))

k = 15

print(img.size)

for x in range(4):
    for y in range(4):
        i = y
        j = x
        res = img.crop((i*64, j*64, (i+1)*64, (j+1)*64))
        res.save(os.path.join(path, f"{k}.png"))
        k -= 1