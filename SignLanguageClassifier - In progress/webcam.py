import cv2

#Read webcam
webcam = cv2.VideoCapture(0)

#vizualize
while True:
    ret, frame = webcam.read()

    cv2.imshow('frame', frame)
    key = cv2.waitKey(40)
    
    if key & 0xFF == ord('q'):
        break

webcam.release()
cv2.destroyAllWindows()