import cv2
import math
import random
import numpy as np
from scipy.signal import wiener
from matplotlib import pyplot as plt

def ft(image):
    img_dft=cv2.dft(np.float32(image),
                    flags=cv2.DFT_COMPLEX_OUTPUT)
    #result_dft = 20*np.log(cv2.magnitude(img_dft[:,:,0],
    #                                img_dft[:,:,1]))
    img_dft_shift = np.fft.fftshift(img_dft)
    #result_shift = 20*np.log(cv2.magnitude(img_dft_shift[:,:,0],
    #                                img_dft_shift[:,:,1]))
    rs,cs=image.shape
    cr,cc=int(rs/2),int(cs/2)
    mask=np.zeros((rs,cs,2),np.int8)
    mask[cr-40:cr+40,cc-40:cc+40] = 1
    md=img_dft_shift*mask
    imd=np.fft.ifftshift(md)
    io=cv2.idft(imd)
    img_lowpass=cv2.magnitude(io[:,:,0], io[:,:,1])
    return img_lowpass

def vinr(image):
#   val
    kernel_size = 15
    angle = 60
    eps = 1e-3
#   bluropreator
    PSF=np.diag(np.ones(kernel_size))
    angle = angle+45
    M=cv2.getRotationMatrix2D(((kernel_size/2,kernel_size/2)), angle, 1)
    PSF = cv2.warpAffine(PSF, M, (kernel_size, kernel_size), flags=cv2.INTER_LINEAR)
    PSF = PSF / PSF.sum()
    [img_h,img_w] = image.shape
    [h,w] = PSF.shape
    PSF0 = PSF
    Result_PSF=np.zeros((img_h,img_w))
    Result_PSF[0:h, 0:w] = PSF0 
#   ft*PSF
    img_fft =np.fft.fft2(image)   
    PSF_fft0 = np.fft.fft2(Result_PSF) + eps 
    blurred = np.fft.ifft2(img_fft * PSF_fft0)  
    img_blurred = np.abs(blurred)
#   BLUR_noisy
    blurred_noisy = blurred + 0.1 * blurred.std() * \
                        np.random.standard_normal(blurred.shape)
#   wienrnr
    K=0.01
    blurred_noisy_fft = np.fft.fft2(blurred_noisy)
    Result_PSF_fft = np.fft.fft2(Result_PSF)
    Result_PSF_fft1 = (np.conj(Result_PSF_fft) / (np.abs(Result_PSF_fft)**2 + K))*blurred_noisy_fft         
    result = np.fft.ifft2(Result_PSF_fft1)
    img_wie = np.abs(result)
    return img_blurred,img_wie


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

def find(image):
    img_cvt = cv2.cvtColor(image,cv2.COLOR_BGR2GRAY)  
    ret, img_bin = cv2.threshold(img_cvt,178,255,cv2.THRESH_BINARY_INV) 
    contours, img_find = cv2.findContours(img_bin,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_NONE)  
    img_dw=cv2.drawContours(image,contours,-1,(0,0,255),3)   
    return img_dw, contours

def total_entropy(img):
    n=[]
    P=[]
    grey_lvl=0
    k=0
    res=0 
    #test = [[5,4,3,2,1]]
    weight = img.shape[0]
    height = img.shape[1]
    total = weight * height

    for i in range(256):
        n.append(0)

    for i in range(weight):
        for j in range(height):
            grey_lvl = img[i][j]
            n[grey_lvl] = float(n[grey_lvl] + 1)
            k = float(k+1)
            
    P=n
    for i in range(len(n)):
        P[i] = (n[i]/k)

    for i in range(len(n)):
        if(P[i]==0):
            res = res
        else:
            res = float(res - P[i]*(math.log(P[i])/math.log(2.0)))

    return res

class Point(object):
    def __init__(self,x,y):
        self.x=x
        self.y=y

def getgraydiff(img,currentPoint,tmpPoint):
    return abs(int(img[currentPoint.x, currentPoint.y]) - int(img[tmpPoint.x, tmpPoint.y]))

# operator
def selectcon(p):
    if p != 0:
        connects = [Point(-1, -1), Point(0, -1), Point(1, -1), Point(1, 0), Point(1, 1), Point(0, 1), Point(-1, 1), Point(-1, 0)]
    else:
        connects = [Point(0, -1), Point(1, 0), Point(0, 1), Point(-1, 0)]
    return connects

def regiong(img,seeds,thresh,p=1):
    height,weight = img.shape
    seedMart = np.zeros(img.shape)
    seedList = []
    for seed in seeds:
        seedList.append(seed)
    
    label = 1
    connects = selectcon(p)
    while(len(seedList)>0):
        currentPoint = seedList.pop(0)

        seedMart[currentPoint.x,currentPoint.y] = label
        for i in range(8):
            tmpX = currentPoint.x + connects[i].x
            tmpY = currentPoint.y+ connects[i].y
            if tmpX<0 or tmpY < 0 or tmpX >=height or tmpY >= weight:
                continue
                
            graydiff=getgraydiff(img, currentPoint, Point(tmpX,tmpY))
            if graydiff < thresh and seedMart[tmpX,tmpY]==0:
                seedMart[tmpX,tmpY] = label
                seedList.append(Point(tmpX,tmpY))
    return seedMart

def calcarea(contours):
    area = 0
    for i in contours:
        area += cv2.contourArea(i)
    return area

def plot():
    plt.figure(figsize=(25,25))
    plt.subplot(241)
    plt.imshow(cv2.imread("D:\code\experiment\images\cao.png"),cmap="gray")
    plt.axis('off')
    plt.title('original')

    plt.subplot(242)
    plt.imshow(img_grey,cmap="gray")
    plt.axis('off')
    plt.title('grey original')

    plt.subplot(243)
    plt.imshow(img_equ,cmap="gray")
    plt.axis('off')
    plt.title('grey with eq2(brighter)')

    plt.subplot(244)
    plt.imshow(img_lowpass,cmap="gray")
    plt.axis('off')
    plt.title('ft result')
    plt.subplot(245)
    plt.imshow(img_psf,cmap="gray")
    plt.axis('off')
    plt.title('ft with psf result')
    plt.subplot(246)
    plt.imshow(img_wienrr,cmap="gray")
    plt.axis('off')
    plt.title('wienrr result')

    plt.subplot(247)
    plt.imshow(img_sap)
    plt.axis('off')
    plt.title('sap result')

    plt.subplot(248)
    plt.imshow(img_mb)
    plt.axis('off')
    plt.title('sap result with medianBlur')

if __name__ == '__main__':
    img_grey = cv2.imread("D:\code\experiment\images\cao.png",cv2.IMREAD_GRAYSCALE)
    img_origin = cv2.imread("D:\code\experiment\images\cao.png")

    img_equ = cv2.equalizeHist(img_grey)
    img_lowpass = ft(img_grey)
    img_psf,img_wienrr = vinr(img_grey)
    img_sap = SaltAndPepper(img_origin,0.15)
    img_mb = cv2.medianBlur(img_sap,15)
    plot()

    img_dw, contours=find(img_origin)
    contours_area=calcarea(contours)

    seeds = [Point(366,321)]
    img_rg = regiong(img_grey, seeds, 5)

    cv2.imshow("img_dw",img_dw)
    cv2.imshow("img_rg",img_rg)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    
    print("entropy=%f"%total_entropy(img_origin))
    print("compression ratio=%f%%"%(total_entropy(img_origin)/8.0*100))
    print("calc Area=%f"%contours_area)
