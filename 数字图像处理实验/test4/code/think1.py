import cv2
import numpy as np
from matplotlib import pyplot as plt

img = cv2.imread('picture\\fig6.png')
hsv_img = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
h, s, v = cv2.split(hsv_img)
v_equalized = cv2.equalizeHist(v)
hsv_img_equalized = cv2.merge([h, s, v_equalized])
rgb_img_equalized = cv2.cvtColor(hsv_img_equalized, cv2.COLOR_HSV2BGR)

cv2.imshow('Original Image', img)
cv2.imshow('Equalized Image (HSI - Intensity)', rgb_img_equalized)
cv2.waitKey(0)
cv2.destroyAllWindows()
