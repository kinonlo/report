import cv2

# 列出所有以 'COLOR_' 开头的标志
flags = [i for i in dir(cv2) if i.startswith('COLOR_')]
print(flags)
