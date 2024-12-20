import cv2
import numpy as np

def calculate_cdf(histogram):
    # 计算累积分布函数（CDF）
    cdf = histogram.cumsum()
    cdf_normalized = cdf / cdf.max()  # 归一化到[0,1]
    return cdf_normalized

def match_histograms(source, template):
    # 计算源图像和模板图像的直方图
    source_hist, bins = np.histogram(source.flatten(), 256, [0, 256])
    template_hist, bins = np.histogram(template.flatten(), 256, [0, 256])
    
    # 计算源图像和模板图像的CDF
    source_cdf = calculate_cdf(source_hist)
    template_cdf = calculate_cdf(template_hist)
    
    # 创建映射表，根据模板的CDF找到最接近的源像素值
    lookup_table = np.zeros(256)
    for i in range(256):
        closest_value = np.argmin(np.abs(source_cdf[i] - template_cdf))
        lookup_table[i] = closest_value
    
    # 应用映射表，生成匹配的图像
    matched_image = cv2.LUT(source, lookup_table.astype('uint8'))
    
    return matched_image

# 加载源图像Fig7A和目标图像Fig7B
source_image = cv2.imread('picture\\fig7A.png', cv2.IMREAD_GRAYSCALE)
template_image = cv2.imread('picture\\fig7B.png', cv2.IMREAD_GRAYSCALE)

# 进行直方图规定化
matched_image = match_histograms(source_image, template_image)

# 显示结果
cv2.imshow('Source Image', source_image)
cv2.imshow('Template Image', template_image)
cv2.imshow('Matched Image', matched_image)

cv2.waitKey(0)
cv2.destroyAllWindows()

# 保存结果图像
cv2.imwrite('Matched_Fig7A.jpg', matched_image)
