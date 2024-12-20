import cv2
import numpy as np
img1=cv2.imread('diamond.png')
img2=cv2.imread('flower.png')
img2 = cv2.resize(img2, (img1.shape[1], img1.shape[0]))
dst=cv2.addWeighted(img1,0.7,img2,0.3,0)
cv2.imshow('dst',dst)
cv2.waitKey(0)
cv2.destroyAllWindows()