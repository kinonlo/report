import numpy as np
import cv2

# 创建一个黑色背景的空白图像
img = np.zeros((512, 512, 3), np.uint8)

# 使用参数方程绘制爱心形状
for y in range(512):
    for x in range(512):
        # 爱心的数学方程 (适当缩放到画布)
        xp = (x - 256) / 100.0
        yp = -(y - 256) / 100.0  # 对 y 进行翻转
        if (xp**2 + (yp - (xp**2)**(1/3))**2) <= 1:
            img[y, x] = (0, 0, 255)  # 红色爱心

# 显示图像
cv2.imshow('Heart', img)

# 等待用户按键，关闭窗口
cv2.waitKey(0)
cv2.destroyAllWindows()
