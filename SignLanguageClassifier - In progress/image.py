import os
import cv2

#Read image
img = cv2.imread(os.path.join(r'C:\Users\nkamr\OneDrive\Pictures', 'DogBangs.png'))

img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)


cv2.imshow("Dog bangs", img)
cv2.imshow("Dog Bangs RGB", img_rgb)
cv2.waitKey(0)