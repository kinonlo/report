import cv2
import numpy as np
img = cv2.imread('picture\\flower2.png', 0)
if img is None:
    print("Error: Could not open or find the image.")
    exit()

rows, cols = img.shape
M = cv2.getRotationMatrix2D((cols / 2, rows / 2), 45, 0.6)
dst = cv2.warpAffine(img, M, (cols, rows))

cv2.imwrite('before.png', dst)
cv2.imshow('after', dst)
cv2.waitKey(0)
cv2.destroyAllWindows()
