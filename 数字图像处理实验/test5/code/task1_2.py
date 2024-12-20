import cv2
import numpy as np
from matplotlib import pyplot as plt
img = cv2.imread('picture\\lenawithnoise.bmp')
median3 = cv2.medianBlur(img, 3)
median5 = cv2.medianBlur(img, 5)
median7 = cv2.medianBlur(img, 7)
plt.subplot(221),plt.imshow(img),plt.title('Original')
plt.xticks([]), plt.yticks([])
plt.subplot(222),plt.imshow(median3),plt.title('Blurred3*3')
plt.xticks([]), plt.yticks([])
plt.subplot(223),plt.imshow(median5),plt.title('Blurred 5*5')
plt.xticks([]), plt.yticks([])
plt.subplot(224),plt.imshow(median7),plt.title('Blurred 7*7')
plt.xticks([]), plt.yticks([])
plt.show()