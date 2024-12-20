import cv2
import numpy as np

# 读取图像
img1=cv2.imread('diamond.png')
img2=cv2.imread('flower.png')
img2 = cv2.resize(img2, (img1.shape[1], img1.shape[0]))
# 图像加法
result = cv2.add(img1, img2)

# 显示结果
cv2.imshow('Added Image', result)
cv2.waitKey(0)
cv2.destroyAllWindows()
