# coding: utf-8
import cv2
import os
import numpy as np

rootdir = r'./Results/REDS4_abla_noTemporal'
final = cv2.imread("./Results/REDS4_abla_noTemporal/REDS4_abla_noTemporal-1.png")

for parent, dirnames, filenames in os.walk(rootdir):  # 遍历每一张图片
    for filename in filenames:
        currentPath = os.path.join(parent, filename)
        img = cv2.imread(currentPath)
        final = np.vstack((final, img))
cv2.imshow('image', final)
cv2.imwrite("./Results/REDS4_abla_noTemporal/REDS4_abla_noTemporal.png", final)
cv2.waitKey(0)





