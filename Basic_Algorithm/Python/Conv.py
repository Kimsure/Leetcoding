# 1
import numpy as np
# img # in: c_in*h*w out:c_out*h*w

def conv_onemap(image,k):#单张图的卷积
    h,w = image.shape()
    k_h, k_w = k.shape()

    ans = []
    for i in range(h-k_h):
        line = []
        for j in range(w-k_w):
            line.append(np.sum(image[i:i+k_h][j:j+k_w]*k))
        ans.append(line)
    return np.array(ans)


def convolution(c_out, image, kernel_size):#更正规的应该写成类，这里只是简单的表示一下
    c_in, h, w = image.shape()
    kernels = np.zeros((c_out,c_in,kernel_size[0], kernel_size[1]))

    ans = []
    for i in range(c_out):
        maps = []
        for j in range(c_in):
            k = kernels[i,j]
            new_map = conv_onemap(image[j], k)
            maps.append(new_map.tolist())
        maps = np.array(maps)
        maps = np.sum(maps, dim=0).tolist()
        ans.append(maps)
    return ans #c_out,h,w

# 2
from PIL import Image
import matplotlib.pyplot as plt
import numpy as np

img = Image.open('金鱼姬.jpg')
plt.axis("off")
plt.imshow(img)
gray = img.convert('L')
plt.figure()
plt.imshow(gray, cmap='gray')
plt.axis('off')

r, g, b = img.split()
plt.imshow(r, cmap='gray')
plt.axis('off')

np.array(img)
np.array(r)
np.array(g)
np.array(b)

#定义卷积核（3*3）
k = np.array([
    [1,2,1],
    [2,4,2],
    [1,2,1]
])

data = np.array(r)
n,m = data.shape
def convolution(k, data):
    n,m = data.shape
    img_new = []
    for i in range(n-3):
        line = []
        for j in range(m-3):
            a = data[i:i+3,j:j+3]
            line.append(np.sum(np.multiply(k, a)))
        img_new.append(line)
    return np.array(img_new)
img_new = convolution(k, data)#卷积过程
#卷积结果可视化
plt.imshow(img_new, cmap='gray')
plt.axis('off')