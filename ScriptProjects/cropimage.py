# coding: utf-8
from PIL import Image
import os.path
import os

# 指明被遍历的文件夹
root = r'./data/RLSP7-64/'
rootdir = root + 'OriRecons/'
savedir = root + 'PixelLine_Subimage/'
if not os.path.isdir(savedir):  ##不用加引号，如果是多级目录，只判断最后一级目录是否存在
    os.makedirs(savedir)
for parent, dirnames, filenames in os.walk(rootdir):  # 遍历每一张图片
    for filename in filenames:
        currentPath = os.path.join(parent, filename)
        img = Image.open(currentPath)
        print(img.format, img.size, img.mode)

        box1 = (160, 232, 246, 233)  # 设置左、上、右、下的像素
        image1 = img.crop(box1)  # 图像裁剪
        image1.save(savedir + '/' + filename)  # 存储裁剪得到的图像

# img = Image.open('vid4/Frame 001.png')
# box1 = (210, 152, 332, 160)  # 设置左、上、右、下的像素
# image1 = img.crop(box1)  # 图像裁剪
# image1.save("001crop.png")  # 存储裁剪得到的图像