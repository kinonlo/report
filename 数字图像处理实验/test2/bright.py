import cv2
import numpy as np

# 读取图像
img = cv2.imread('woman.png', 0)

# 增加亮度
img1 = cv2.add(img, 80)

# 减少亮度
img2 = cv2.subtract(img, 80)

# 显示结果
cv2.imshow('Increased Brightness', img1)
cv2.imshow('Decreased Brightness', img2)
cv2.waitKey(0)
cv2.destroyAllWindows()
