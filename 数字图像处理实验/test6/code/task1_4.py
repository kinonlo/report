import cv2
import numpy as np

img = cv2.imread('picture\\j_pengzhang.png', 0)

kernel = np.ones((5, 5), np.uint8)

closing = cv2.morphologyEx(img, cv2.MORPH_CLOSE, kernel)

cv2.imshow('Original Image', img)
cv2.imshow('Erosion', closing)
cv2.waitKey(0)
cv2.destroyAllWindows()