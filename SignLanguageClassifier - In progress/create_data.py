import mediapipe as mp
import cv2, os 
import matplotlib.pyplot as plt
import config

mp_hands = mp.solutions.hands
mp_drawing = mp.solutions.drawing_utils
mp_styles = mp.solutions.drawing_styles

hands = mp_hands.Hands(static_image_mode=True, min_detection_confidence=0.3)

for dir in os.listdir(config.DATA_DIR):
    for img_path in os.listdir(os.path.join(config.DATA_DIR, dir))[:2]:
        img = cv2.imread(os.path.join(config.DATA_DIR, dir, img_path))
        img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

        #Hand Keypoints
        results = hands.process(img_rgb)
        for hand_landmark in results.multi_hand_landmarks:
            mp_drawing.draw_landmarks(img_rgb, hand_landmark, mp_hands.HAND_CONNECTIONS, mp_styles.get_default_hand_landmarks_style(), mp_styles.get_default_hand_connections_style())

        plt.figure()
        plt.imshow(img_rgb)

plt.show()