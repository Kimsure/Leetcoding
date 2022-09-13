# -*-coding:utf-8-*-
import math
from PIL import Image
import numpy as np
import matplotlib.pyplot as plt  # plt 用于显示图片
import matplotlib.image as mpimg  # mpimg 用于读取图片
import numpy as np
import cv2

def nearest(image, target_size):
    """
    Nearest Neighbour interpolate for RGB  image

    :param image: rgb image
    :param target_size: tuple = (height, width)
    :return: None
    """
    if target_size[0] < image.shape[0] or target_size[1] < image.shape[1]:
        raise ValueError("target image must bigger than input image")
    # 1：按照尺寸创建目标图像
    # target_image = np.zeros(shape=(*target_size, 3)) '*'给tuple(target_size)解包
    target_image = np.zeros(shape=(target_size[0], target_size[1], 3))
    # print(image.shape, target_image.shape)
    # 2:计算height和width的缩放因子
    alpha_h = target_size[0] / image.shape[0]
    alpha_w = target_size[1] / image.shape[1]

    for tar_x in range(target_image.shape[0]):
        for tar_y in range(target_image.shape[1]):
            # 3:计算目标图像人任一像素点
            # target_image[tar_x,tar_y]需要从原始图像
            # 的哪个确定的像素点image[src_x, xrc_y]取值
            # 也就是计算坐标的映射关系
            # src_x = round(tar_x / alpha_h) # 四舍五入，可能出现越界
            # src_y = round(tar_y / alpha_w)
            src_x = int(math.floor(tar_x / alpha_h)) # 向下取整
            src_y = int(math.floor(tar_y / alpha_w))

            # 4：对目标图像的任一像素点赋值
            target_image[tar_x, tar_y] = image[src_x, src_y]

    return target_image

def bi_linear(src, target_size):
    pic = cv2.imread(src)       # 读取输入图像
    th, tw = target_size[0], target_size[1]
    emptyImage = np.zeros(target_size, np.uint8)
    for k in range(3):
        for i in range(th):
            for j in range(tw):
                # 首先找到在原图中对应的点的(X, Y)坐标
                corr_x = (i+0.5)/th*pic.shape[0]-0.5
                corr_y = (j+0.5)/tw*pic.shape[1]-0.5
                # if i*pic.shape[0]%th==0 and j*pic.shape[1]%tw==0:     # 对应的点正好是一个像素点，直接拷贝
                #   emptyImage[i, j, k] = pic[int(corr_x), int(corr_y), k]
                point1 = (math.floor(corr_x), math.floor(corr_y))   # 左上角的点
                point2 = (point1[0], point1[1]+1)
                point3 = (point1[0]+1, point1[1])
                point4 = (point1[0]+1, point1[1]+1)

                fr1 = (point2[1]-corr_y)*pic[point1[0], point1[1], k] + (corr_y-point1[1])*pic[point2[0], point2[1], k]
                fr2 = (point2[1]-corr_y)*pic[point3[0], point3[1], k] + (corr_y-point1[1])*pic[point4[0], point4[1], k]
                emptyImage[i, j, k] = (point3[0]-corr_x)*fr1 + (corr_x-point1[0])*fr2
    return emptyImage

if __name__ == '__main__':
    image = mpimg.imread('./exm/013crop.png')  # RGB通道读取
    cvimg = cv2.imread('./exm/013crop.png') # BGR通道读取
    # 此时 lena 就已经是一个 np.array 了，可以对它进行任意处理
    # print(type(cvimg))
    # print(type(image))
    print(cvimg.shape)
    print(image.shape) 
    target_mp = nearest(image, [512,1024])
    target_cv = nearest(cvimg, [512,1024])
    print(target_cv.shape)
    from PIL import Image
    Image.fromarray(np.uint8(target_mp*255)).convert('RGB').save('face_x8.png',"png")


    plt.imshow(image)  # 显示图片
    plt.show()
    cv2.imshow('image', cvimg)  # 显示图片
    cv2.waitKey(0)
    plt.imshow(target_mp)
    plt.axis('off')  # 不显示坐标轴
    plt.show()
    cv2.imshow('target_cv', target_cv)
    cv2.waitKey(0)
    

