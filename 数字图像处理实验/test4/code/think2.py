import cv2
import numpy as np
from matplotlib import pyplot as plt

img = cv2.imread('picture\\fig6.png')
b, g, r = cv2.split(img)

b_equalized = cv2.equalizeHist(b)
g_equalized = cv2.equalizeHist(g)
r_equalized = cv2.equalizeHist(r)

img_equalized_bgr = cv2.merge([b_equalized, g_equalized, r_equalized])

cv2.imshow('Original Image', img)
cv2.imshow('Equalized Image (BGR)', img_equalized_bgr)
cv2.waitKey(0)
cv2.destroyAllWindows()
