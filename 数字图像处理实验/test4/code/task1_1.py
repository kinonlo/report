import cv2
import numpy as np
from matplotlib import pyplot as plt
img = cv2.imread('picture\\fig3.png',0)
plt.hist(img.ravel(),256,[0,256])
plt.show()