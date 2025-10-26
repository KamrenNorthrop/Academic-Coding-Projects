import cv2, os

#Read video
video_path = os.path.join(r'c:\Users\nkamr\Videos', "proof.mp4")
vid = cv2.VideoCapture(video_path)

#vizualize 
ret = True
while ret:
    ret, frame = vid.read()

    if ret:
        cv2.imshow('frame', frame)
        cv2.waitKey(40)

vid.release()
cv2.destroyAllWindows()