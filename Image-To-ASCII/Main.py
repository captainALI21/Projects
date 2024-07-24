from PIL import Image

img = (Image.open("Test-Img.png")).convert('L')
pixels = list(img.getdata())
width, height = img.size

asciiChar = [' ', '.', ':', '-', '=', '+', '*', '#', '%', '@', '&', '8', 'B', 'W', 'M', '█']

for i in range(height):
    for j in range(width):
        pixel_value = pixels[(i * width) + j]
        index = int((pixel_value / 255) * 15)
        print(asciiChar[index], end="")
    print()
