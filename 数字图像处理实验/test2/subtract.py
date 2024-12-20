import cv2
import numpy as np

img1=cv2.imread('diamond.png')
img2=cv2.imread('flower.png')
img2 = cv2.resize(img2, (img1.shape[1], img1.shape[0]))

# 图像减法
result = cv2.subtract(img1, img2)

# 显示结果
cv2.imshow('Subtracted Image', result)
cv2.waitKey(0)
cv2.destroyAllWindows()
