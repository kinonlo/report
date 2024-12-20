import cv2
import numpy as np

def get_points(event, x, y, flags, param):
    global points
    if event == cv2.EVENT_LBUTTONDOWN and len(points) < 4:
        points.append([x, y])
        cv2.circle(img, (x, y), 5, (0, 255, 0), -1)
        cv2.imshow('image', img)

img = cv2.imread('picture\\flower1.png')
if img is None:
    print("Error: Could not open or find the image.")
    exit()

clone = img.copy()
points = []

cv2.imshow('image', img)
cv2.setMouseCallback('image', get_points)

cv2.waitKey(0)

if len(points) == 4:
    pts1 = np.float32(points)  # 输入图像中的四个点
    pts2 = np.float32([[0, 0], [300, 0], [300, 300], [0, 300]])  # 目标矩形的四个点

    M = cv2.getPerspectiveTransform(pts1, pts2)

    dst = cv2.warpPerspective(clone, M, (300, 300))

    cv2.imshow('Transformed', dst)
    cv2.imwrite('output.jpg', dst)
    cv2.waitKey(0)

cv2.destroyAllWindows()
