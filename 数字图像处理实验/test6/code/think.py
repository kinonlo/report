import cv2
import numpy as np

# 打开摄像头
cap = cv2.VideoCapture(0)

while True:
    # 获取每一帧
    ret, frame = cap.read()
    
    if not ret:
        print("无法读取摄像头帧")
        break
    
    # 转换到HSV颜色空间
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    
    # 设定蓝色的阈值
    lower_blue = np.array([110, 50, 50])
    upper_blue = np.array([130, 255, 255])
    
    # 根据阈值构建掩模
    mask = cv2.inRange(hsv, lower_blue, upper_blue)
    
    # 通过形态学操作去除噪声
    mask = cv2.erode(mask, None, iterations=2)
    mask = cv2.dilate(mask, None, iterations=2)
    
    # 通过轮廓检测找到蓝色物体
    contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    
    # 初始化最大轮廓
    largest_contour = None
    max_area = 0
    
    for contour in contours:
        area = cv2.contourArea(contour)
        # 找到面积最大的轮廓
        if area > max_area:
            max_area = area
            largest_contour = contour
    
    # 如果找到最大的轮廓，则绘制矩形框
    if largest_contour is not None:
        x, y, w, h = cv2.boundingRect(largest_contour)
        cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)
        cv2.putText(frame, 'Tracking', (x, y - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 255, 0), 2)
    
    # 显示图像
    cv2.imshow('frame', frame)
    cv2.imshow('mask', mask)
    
    # 按 'ESC' 键退出
    k = cv2.waitKey(5) & 0xFF
    if k == 27:
        break

# 释放摄像头资源并关闭所有窗口
cap.release()
cv2.destroyAllWindows()
