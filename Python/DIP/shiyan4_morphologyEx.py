import cv2

img = cv2.imread("D:\code\experiment\images\shapes.tif") 
img = cv2.resize(img, None, fx=0.5, fy=0.5)
#cv2.morphologyEx(src, op, kernel, dst, 
# anchor, iterations, borderType, borderValue)

kernel = cv2.getStructuringElement(cv2.MORPH_RECT,(20,20))
img_erode = cv2.erode(img, kernel, iterations=1)
img_open = cv2.morphologyEx(img, cv2.MORPH_OPEN, kernel,iterations=1)
img_close = cv2.morphologyEx(img,cv2.MORPH_CLOSE, kernel,iterations=1)
img_do = cv2.morphologyEx(cv2.dilate(img_open, kernel, iterations=1), cv2.MORPH_OPEN, kernel,iterations=1)

cv2.imshow("original ",img)
cv2.imshow("open",img_open)
cv2.imshow("close ",img_close)
cv2.imshow("d&o",img_do)
cv2.waitKey(0)
cv2.destroyAllWindows()