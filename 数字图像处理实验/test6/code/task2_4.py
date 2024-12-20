import cv2
import numpy as np

# 读取图像
img = cv2.imread('picture/noisy.tif', 0)

# 检查图像是否成功读取
if img is None:
    print("Error: Could not read the image.")
else:
    # 应用高斯模糊
    blur = cv2.GaussianBlur(img, (5, 5), 0)
    
    # 计算归一化直方图
    hist = cv2.calcHist([blur], [0], None, [256], [0, 256])
    hist_norm = hist.ravel() / hist.max()
    Q = hist_norm.cumsum()
    bins = np.arange(256)
    
    fn_min = np.inf
    thresh = -1

    for i in range(1, 256):
        p1, p2 = np.hsplit(hist_norm, [i])  # 概率
        q1, q2 = Q[i], Q[255] - Q[i]  # 类的累计和
        b1, b2 = np.hsplit(bins, [i])  # 权重
        
        # 确保 q1 和 q2 不为零
        if q1 == 0 or q2 == 0:
            continue
        
        # 计算均值和方差
        m1, m2 = np.sum(p1 * b1) / q1, np.sum(p2 * b2) / q2
        v1, v2 = np.sum(((b1 - m1) ** 2) * p1) / q1, np.sum(((b2 - m2) ** 2) * p2) / q2
        
        # 计算最小化函数
        fn = v1 * q1 + v2 * q2
        if fn < fn_min:
            fn_min = fn
            thresh = i

    # 使用 OpenCV 的 Otsu 函数找到阈值
    ret, otsu = cv2.threshold(blur, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)
    
    # 输出结果
    print(thresh, ret)
