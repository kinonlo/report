import cv2
import numpy as np

# 读取图像
img = cv2.imread('picture\\j.png', 0)

kernel = np.ones((5, 5), np.uint8)
    
dilation = cv2.dilate(img,kernel,iterations = 1)

cv2.imshow('Original Image', img)
cv2.imshow('Erosion', dilation)
cv2.waitKey(0)
cv2.destroyAllWindows()