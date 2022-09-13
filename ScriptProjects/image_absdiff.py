import cv2
import numpy as np

img1 = cv2.imread('./ScriptProjects/exm/00000013.png')
img2 = cv2.imread('./ScriptProjects/exm/00000014.png')

imgsub = cv2.absdiff(img1,img2)     #差值的绝对值
gray= cv2.cvtColor(imgsub,cv2.COLOR_BGR2GRAY)

cv2.imshow('img1',img1)
cv2.imshow('img2',img2)
cv2.imshow('img_sub',gray)
# cv2.imshow('err',err)
cv2.imwrite('img_sub.png',gray)
cv2.waitKey()
cv2.destroyAllWindows()
