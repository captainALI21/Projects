import cv2
import pytesseract
import numpy as np

imgPath = "sudoku-puzzle-games.jpg"

img = cv2.imread(imgPath, cv2.IMREAD_GREYSCALE)
thresholded = cv2.threshold(img, 128, 255, cv2.THRESH_BINARY_INV)
blurred_image = cv2.GaussianBlur(thresholded, (5, 5), 0)
