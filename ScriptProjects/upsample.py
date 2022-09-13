# -*-coding:utf-8-*-
import math

import cv2
import matplotlib.image as mpimg  # mpimg 用于读取图片
import matplotlib.pyplot as plt  # plt 用于显示图片
import numpy as np
from PIL import Image


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

    for c in range(target_image.shape[2]):
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
                target_image[tar_x, tar_y][c] = image[src_x, src_y][c]

    return target_image

def nearest2(img, scale):
    width, height, _ = img.shape
    n_width = width*scale
    n_height = height*scale
    n_img = np.zeros((n_width, n_height, 3))
    for k in range(3):
        for i in range(n_width):
            for j in range(n_height):
                #print(i, j, k)
                n_img[i, j, k] = img[math.floor((i-1)/scale), math.floor((j-1)/scale), k]  #映射
    # return Image.fromarray(np.uint8(n_img))
    return np.uint8(n_img)

def double_linear(img, scale):
    width, height, _ = img.shape
    n_width = int(width*scale)
    n_height = int(height*scale)
    n_img = np.zeros((n_width, n_height, 3))
    for k in range(3):
        for i in range(n_width):
            for j in range(n_height):
                src_x = i/scale
                src_y = j/scale
                src_x_0 = int(np.floor(src_x))
                src_y_0 = int(np.floor(src_y))
                src_x_1 = min(src_x_0 + 1, width - 1)
                src_y_1 = min(src_y_0 + 1, height - 1)
                #print(src_x, src_y, src_x_0, src_y_0, src_x_1, src_y_1)
                value0 = (src_x_1 - src_x)*img[src_x_0, src_y_0, k] + (src_x - src_x_0)*img[src_x_1,src_y_0,k]
                value1 = (src_x_1 - src_x)*img[src_x_0, src_y_1, k] + (src_x - src_x_0)*img[src_x_1,src_y_1,k]
                n_img[i, j, k] = int((src_y_1-src_y) * value0 + (src_y-src_y_0)*value1)
    # return Image.fromarray(np.uint8(n_img))
    return np.uint8(n_img)


if __name__ == '__main__':
    image = Image.open('./ScriptProjects/exm/013crop.png')  # RGB通道读取
    image = np.array(image)
    # mpimg = mpimg.imread('./ScriptProjects/exm/013crop.png')  # RGB通道读取
    # cvimg = cv2.imread('./ScriptProjects/exm/013crop.png') # BGR通道读取
    
    # 此时 lena 就已经是一个 np.array 了，可以对它进行任意处理
    # print(type(cvimg))
    # print(type(mpimg))
    
    # print(cvimg.shape)
    # print(mpimg.shape) 
    print(image.shape) 
    
    # target_mp = nearest(mpimg, [512,1024])
    # target_cv = nearest2(cvimg, 4)
    target = nearest2(image, 4)
    print(target.shape, type(target))
    # target_cv = double_linear(cvimg, 4)
    # target_cv = nearest(cvimg, [512,1024])

    from PIL import Image
    # Image.fromarray(np.uint8(target_mp*255)).convert('RGB').save('face_x8.png',"png")


    plt.imshow(image)  # 显示图片
    plt.show()
    # cv2.imshow('mpimg', image)  # 显示图片
    # cv2.waitKey(0)
    
    plt.imshow(target)
    plt.axis('off')  # 不显示坐标轴
    plt.show()
    # cv2.imshow('target_cv', target_cv)
    # cv2.waitKey(0)
    

