import cv2
import math
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
    img = cv2.imread("D:\code\experiment\images\cao.png",cv2.IMREAD_GRAYSCALE)
    img2 = cv2.imread("D:\code\experiment\images\cao.png")
    equ=cv2.equalizeHist(img)
    io=ft(equ)
    wienrr=vinr(io)
    sap=SaltAndPepper(equ,0.15)
    plot(equ,io,wienrr,sap)
    img_dw, contours=find(img2)
    contours_area=calcarea(contours)
    seeds = [Point(366,321)]
    img_rg = regiong(img, seeds, 5)
    
    print("entropy=%f"%total_entropy(img))
    print("compression ratio=%f%%"%(total_entropy(img)/8.0*100))
    print("calc Area=%f"%contours_area)
    
    cv2.imshow("img_dw",img_dw)
    cv2.imshow("img_rg",img_rg)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
