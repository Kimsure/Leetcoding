# coding: utf-8
import cv2
import os
import numpy as np

rootdir = r'./data/RLSP7-64/PixelLine_Subimage'
# final = cv2.imread("./gopro1/ours_new/000.png")
for parent, dirnames, filenames in os.walk(rootdir):  # 遍历每一张图片
    i = 0
    for filename in filenames:
        currentPath = os.path.join(parent, filename)
        img = cv2.imread(currentPath)
        if i==0:
            final=img
        else:
            final = np.vstack((final, img))
        i+=1
# cv2.imshow('image', final)
cv2.imwrite(rootdir + '/' + 'stack.png', final)
cv2.waitKey(0)





