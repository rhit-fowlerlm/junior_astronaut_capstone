from PIL import Image

save_location = "/home/space-station/Documents/test/Photos/WarpTrails001_frames"

with Image.open("/home/space-station/Documents/test/Photos/WarpTrails001.gif") as im:
    for i in range(im.n_frames):
        im.seek(i)
        im.save("{}/{}.png".format(save_location, i))