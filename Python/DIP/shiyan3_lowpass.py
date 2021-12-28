import cv2
import numpy as np
import matplotlib.pyplot as plt

img = cv2.imread("D:\code\experiment\images\lena_noise.jpg",0)
dft = cv2.dft(np.float32(img),flags=cv2.DFT_COMPLEX_OUTPUT)
dshift = np.fft.fftshift(dft)
rs,cs = img.shape
cr,cc = int(rs/2),int(cs/2)
mask = np.zeros((rs,cs,2),np.int8)
mask[cr-40:cr+40,cc-40:cc+40] = 1
md = dshift*mask 
imd = np.fft.ifftshift(md)
img_tq = cv2.idft(imd)
img_tq = cv2.magnitude(img_tq[:,:,0], img_tq[:,:,1])
plt.figure(figsize=(15,15))
plt.subplot(121)
plt.imshow(img,cmap='gray')
plt.axis('off')
plt.title('original')
plt.subplot(122)
plt.imshow(img_tq,cmap='gray')
plt.axis('off')
plt.title('result')
plt.show()