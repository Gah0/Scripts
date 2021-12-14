import cv2
import random
import numpy as np
from scipy.signal import wiener
from matplotlib import pyplot as plt

def ft(image):
    img_dft=cv2.dft(np.float32(equ),
                    flags=cv2.DFT_COMPLEX_OUTPUT)
    #result_dft = 20*np.log(cv2.magnitude(img_dft[:,:,0],
    #                                img_dft[:,:,1]))
    img_dft_shift = np.fft.fftshift(img_dft)
    #result_shift = 20*np.log(cv2.magnitude(img_dft_shift[:,:,0],
    #                                img_dft_shift[:,:,1]))
    rs,cs=equ.shape
    cr,cc=int(rs/2),int(cs/2)
    mask=np.zeros((rs,cs,2),np.int8)
    mask[cr-40:cr+40,cc-40:cc+40] =1
    md=img_dft_shift*mask
    imd=np.fft.ifftshift(md)
    io=cv2.idft(imd)
    io=cv2.magnitude(io[:,:,0], io[:,:,1])
    return io

def vinr(image):
    Noise = image.astype('float64')
    Wiener = wiener(Noise, [3, 3])
    Wiener = np.uint8(Wiener / Wiener.max() * 255)
    return Wiener

def SaltAndPepper(src,percetage):  
    SP_NoiseImg=src 
    SP_NoiseNum=int(percetage*src.shape[0]*src.shape[1]) 
    for i in range(SP_NoiseNum): 
        randX=np.random.randint(0,src.shape[0]-1) 
        randY=np.random.randint(0,src.shape[1]-1) 
        if np.random.randint(0,1)==0: 
            SP_NoiseImg[randX,randY]=0 
        else: 
            SP_NoiseImg[randX,randY]=255 
    return SP_NoiseImg

def plot(equ,io,wienrr):
    plt.figure(figsize=(15,15))
    plt.subplot(331)
    plt.imshow(img)
    plt.axis('off')
    plt.title('original')

    plt.subplot(332)
    plt.imshow(equ)
    plt.axis('off')
    plt.title('eq2')

    plt.subplot(333)
    plt.imshow(io)
    plt.axis('off')
    plt.title('ft result')
    
    plt.subplot(334)
    plt.imshow(wienrr)
    plt.axis('off')
    plt.title('wienrr result')

    plt.subplot(335)
    plt.imshow(sap)
    plt.axis('off')
    plt.title('sap result')
    
if __name__ == '__main__':
    img = cv2.imread("D:\code\experiment\images\hudie.png",cv2.IMREAD_GRAYSCALE)
    equ=cv2.equalizeHist(img)
    io=ft(equ)
    wienrr=vinr(io)
    sap=SaltAndPepper(equ,0.15)
    plot(equ,io,wienrr,sap)
