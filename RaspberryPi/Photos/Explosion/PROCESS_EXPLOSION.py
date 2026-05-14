from PIL import Image
import os
import numpy as np

path = os.path.join("Photos", "Explosion")

img = Image.open(os.path.join(path, "exp2_alpha_1.png"))

img = img.convert("RGBA")
datas = img.getdata()

newData = []
for item in datas:
    d_white = int(np.sqrt((255 - item[0])**2 + (255 - item[1])**2 + (255 - item[2])**2))
    if  d_white < 100:
        newData.append((item[0], item[1], item[2], d_white))
    else:
        newData.append(item)

img.putdata(newData)

k = 15

print(img.size)

for x in range(4):
    for y in range(4):
        i = y
        j = x
        res = img.crop((i*64, j*64, (i+1)*64, (j+1)*64))
        res.save(os.path.join(path, f"{k}.png"))
        k -= 1