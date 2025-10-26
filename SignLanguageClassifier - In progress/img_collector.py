import os, cv2, config

#Create directory if needed
if not os.path.exists(config.DATA_DIR):
    try:
        os.makedirs(config.DATA_DIR)
        print(f"Directory created.")
    except Exception as e:
        print("Error: ", e)
else:
    print(f"Directory already exists.")

#1 class per sign, number of pictures taken = set_size
classes = 3
set_size = 100
#Web cam stream started
webcam_capture = cv2.VideoCapture(0)

#Creating files for data collection
for i in range(classes):
    if not os.path.exists(os.path.join(config.DATA_DIR, str(i))):
        os.makedirs(os.path.join(config.DATA_DIR, str(i)))

    print(f"Collecting data for Class {i}")

    #Start collection
    while True:
        ret, frame = webcam_capture.read()

        cv2.putText(frame, "Press 'q' to begin.", (50, 50), cv2.FONT_HERSHEY_SIMPLEX, 1.5, (0, 255, 0), 3, cv2.LINE_AA)
        cv2.imshow('Capture', frame)
       
        key = cv2.waitKey(1)

        if key & 0xFF == ord('q'):
            print("Starting data collection. . . .")
            break

    counter = 0
    while counter < set_size:
        ret, frame = webcam_capture.read()
        cv2.imshow("Capture", frame)
        cv2.waitKey(1)
        cv2.imwrite(os.path.join(config.DATA_DIR, str(i), f'{counter}.jpg'), frame)
        counter += 1

webcam_capture.release()
cv2.destroyAllWindows()