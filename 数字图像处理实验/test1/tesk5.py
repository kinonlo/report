import numpy as np
import cv2

# 定义字幕显示状态，初始状态为不显示
show_text = False

# 定义鼠标回调函数，点击切换字幕显示状态
def mouse_callback(event, x, y, flags, param):
    global show_text
    if event == cv2.EVENT_LBUTTONDOWN:  # 检测左键点击
        show_text = not show_text  # 切换字幕显示状态

# 打开摄像头
cap = cv2.VideoCapture(0)

# 创建窗口并设置鼠标回调函数
cv2.namedWindow('Video')
cv2.setMouseCallback('Video', mouse_callback)

while True:
    ret, frame = cap.read()  # 读取每帧视频
    if not ret:
        break

    # 如果字幕开关打开，叠加字幕
    if show_text:
        cv2.putText(frame, 'This is a subtitle', (50, 50), 
                    cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 255, 255), 2, cv2.LINE_AA)

    # 显示视频帧
    cv2.imshow('Video', frame)

    # 退出条件：按下 'ESC' 键
    if cv2.waitKey(1) & 0xFF == 27:
        break

# 释放资源并关闭窗口
cap.release()
cv2.destroyAllWindows()
