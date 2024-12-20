import cv2
import numpy as np
from matplotlib import pyplot as plt
img = cv2.imread('picture\\lenawithnoise.bmp')
blur = cv2.GaussianBlur(img,(5,5),0)
plt.subplot(221),plt.imshow(img),plt.title('Original')
plt.xticks([]), plt.yticks([])
plt.subplot(222),plt.imshow(blur),plt.title('Blurred')
plt.xticks([]), plt.yticks([])
plt.show()