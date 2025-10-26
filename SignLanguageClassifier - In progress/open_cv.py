import cv2, os

#Read image
image_path = os.path.join(r'c:\Users\nkamr\OneDrive\Pictures', 'gengartrainers.jpg')
image = cv2.imread(image_path)

#resize
img_resized = cv2.resize(image, (548, 365))

#crop
img_cropped = image[120:640, 90:840]

#Write image
#cv2.imwrite(os.path.join(r'c:\Users\nkamr\OneDrive\Pictures', 'gengar_out.jpg'), image)

#visualize image
cv2.imshow('Image 1', image)
cv2.imshow('image 2', img_resized)
cv2.imshow('Cropped', img_cropped)
print(image.shape)
cv2.waitKey(0)