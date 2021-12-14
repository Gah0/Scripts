import cv2


if __name__ == '__main__':
    img = cv2.imread("D:\code\experiment\images\hudie.png",cv2.IMREAD_GRAYSCALE)
    equ=cv2.equalizeHist(img)
