import cv2
import numpy as np
from matplotlib import pyplot as plt

img = cv2.imread('picture\\child.jpg', 0)

rows, cols = img.shape

f = np.fft.fft2(img)
fshift = np.fft.fftshift(f)

fshift_high = fshift.copy()
fshift_high[rows//2-30:rows//2+30, cols//2-30:cols//2+30] = 0  
img_back_high = np.abs(np.fft.ifft2(np.fft.ifftshift(fshift_high)))

fshift_low = fshift.copy()
mask = np.zeros((rows, cols), np.uint8)
mask[rows//2-30:rows//2+30, cols//2-30:cols//2+30] = 1  
fshift_low = fshift_low * mask
img_back_low = np.abs(np.fft.ifft2(np.fft.ifftshift(fshift_low)))

fshift_band = fshift.copy()
mask_band = np.zeros((rows, cols), np.uint8)
mask_band[rows//2-60:rows//2+60, cols//2-60:cols//2+60] = 1 
mask_band[rows//2-30:rows//2+30, cols//2-30:cols//2+30] = 0  
fshift_band = fshift_band * mask_band
img_back_band = np.abs(np.fft.ifft2(np.fft.ifftshift(fshift_band)))

plt.subplot(141), plt.imshow(img, cmap='gray'), plt.title('Original Image')
plt.subplot(142), plt.imshow(img_back_high, cmap='gray'), plt.title('High Pass Filtered')
plt.subplot(143), plt.imshow(img_back_low, cmap='gray'), plt.title('Low Pass Filtered')
plt.subplot(144), plt.imshow(img_back_band, cmap='gray'), plt.title('Band Pass Filtered')
plt.show()
