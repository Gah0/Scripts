import cv2
import numpy as np

img = cv2.imread("D:\code\experiment\images\douzi_gaitubao_792x682.jpg")

#灰度
img_cvt = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
#高斯
img_cvt_GaussianBlur = cv2.GaussianBlur(img_cvt,(9,9),20)
#二值化
ret,img_cvt_GaussianBlur_binary = cv2.threshold(img_cvt_GaussianBlur, 42, 255, cv2.THRESH_BINARY_INV)

#开运算
kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE,(1,1))
img_mor = cv2.morphologyEx(img_cvt_GaussianBlur_binary, cv2.MORPH_OPEN, kernel, iterations=1)

#find
contours, img_find = cv2.findContours(img_mor,cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
#img_f=img_find.astype("uint8")
#dws
#contours = np.int0(contours)
d_img = img_find.copy()
img_dw=cv2.drawContours(img,contours,-1,(0,0,255),2)

cv2.imshow("img_find",img_dw)

cv2.waitKey(0)
cv2.destroyAllWindows()

