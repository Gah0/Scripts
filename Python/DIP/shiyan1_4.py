import cv2
from matplotlib import pyplot as plt
import numpy as np

def binary(img):
    binnn=img
    ret,im_binary = cv2.threshold(img,80,255,cv2.THRESH_BINARY_INV)
    return binnn,im_binary

def rev(img):
    reeee=img
    r_img = 255-img
    return reeee,r_img

def log(img):
    poll=img
    img_pollent = 20*np.log(1.0+img)
    img_pollent = np.uint8(img_pollent+0.5)
    return poll,img_pollent
    
def add(src1,src2):
    img = cv2.add(src1, src2)
    return img

def subtract(src1,src2):
    img = cv2.subtract(src1, src2)
    return img

def grad_domain(img):
    src =img
    sobelx = cv2.Sobel(src, cv2.CV_64F, 1, 0)
    sobely = cv2.Sobel(src, cv2.CV_64F, 0, 1)
    sobelx = cv2.convertScaleAbs(sobelx)
    sobely = cv2.convertScaleAbs(sobely)
    sobelxy = cv2.addWeighted(sobelx, 0.5, sobely, 0.5, 0)
    return src, sobelxy, src+sobelxy

def la_domain(img):
    kernel = np.array([[-1,-1,-1],
                      [-1,8,-1],
                      [-1,-1,-1]])
    kernel2_1 = np.array([[-1,-1,-1],
                         [-1,9,-1],
                         [-1,-1,-1]])
    dst = cv2.filter2D(img, -1, kernel)
    dst_1 = cv2.filter2D(img, -1, kernel2_1)

    return src,dst,dst_1,src+dst

def plot(bin1,img_pollent,img_rev,poll,binn,reee):
    plt.subplot(231)
    plt.imshow(binn,cmap="gray")
    plt.axis('off')
    plt.title('grey')

    plt.subplot(232)
    plt.imshow(bin1,cmap="gray")
    plt.axis('off')
    plt.title('grey with binary(inv)')

    plt.subplot(233)
    plt.imshow(poll,cmap="gray")
    plt.axis('off')
    plt.title('unpollent')
    plt.show()

    plt.subplot(234)
    plt.imshow(img_pollent,cmap="gray")
    plt.axis('off')
    plt.title('pollent')
    plt.show()

    plt.subplot(235)
    plt.imshow(reee,cmap="gray")
    plt.axis('off')
    plt.title('unreverse')
    plt.show()

    plt.subplot(236)
    plt.imshow(img_rev,cmap="gray")
    plt.axis('off')
    plt.title('reverse')
    plt.show()

if __name__ == '__main__':
    img_1 = cv2.imread('D:\code\experiment\images\cameraman.tif',cv2.IMREAD_GRAYSCALE)
    img_2 = cv2.imread('D:\code\experiment\images\pollens.tif',cv2.IMREAD_GRAYSCALE)
    img3 = cv2.imread('D:\code\experiment\images\/breast.tif',cv2.IMREAD_GRAYSCALE) 
    img_4 = cv2.imread('D:\code\experiment\images\/broken_text.tif',cv2.IMREAD_GRAYSCALE) 
    img_5 = cv2.imread('D:\code\experiment\images\circuit.tif')
    img_lena = cv2.imread('D:\code\experiment\images\lena_color_256.tif')
    img_lena_g = cv2.imread('D:\code\experiment\images\lena_gray_256.tif')
    img_lena_salt = cv2.imread('D:\code\experiment\images\lena_color_512_saltpepper.jpg')
    img_lena_512 = cv2.imread('D:\code\experiment\images\lena_color_512.tif')
    omg_pepper = cv2.imread('D:\code\experiment\images\peppers_color.tif')
#   灰度运算    
    binn,bin1 = binary(img_1)
    poll,img_pollent = log(img_2)
    reee,img_rev = rev(img3)

    plot(bin1,img_pollent,img_rev,poll,binn,reee)
#   融合
    img_add = add(img_lena,img_lena_g)
    img_sub = subtract(img_lena_salt,img_lena_512)
    img_mix = cv2.addWeighted(img_lena_512, 0.4, omg_pepper, 0.7, 0)
#   空域处理
    src,sobelxy,srcsobelxy = grad_domain(img_5)
    la_src,la_dst,la_dst_1,la_srcdst = la_domain(img_5)


    cv2.imshow("add",img_add)
    cv2.imshow("sub",img_sub)
    cv2.imshow("mix",img_mix)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

    cv2.imshow("original", src)
    cv2.imshow("xy", sobelxy)
    cv2.imshow("original+xy", srcsobelxy)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

    cv2.imshow("la_src", la_src)
    cv2.imshow("la_dst", la_dst)
    cv2.imshow("la_dst_1", la_dst_1)
    cv2.imshow("la_srcdst", la_srcdst)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

