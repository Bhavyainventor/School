# pip install opencv-python mediapipe pyautogui

import cv2
import mediapipe as mp
import pyautogui
import math
import tkinter as tk
from threading import Thread, Event

# Event to signal the threads to stop
stop_event = Event()

# Default sensitivity
sensitivity = 2  # Default value

def on_start():
    global sensitivity  # Access the global sensitivity variable
    
    def calculate_distance(point1, point2):
        return math.sqrt((point1.x - point2.x) ** 2 + (point1.y - point2.y) ** 2)
    
    cap = cv2.VideoCapture(1)

    
    
        
    # Initialize the MediaPipe Hands solution
    mp_hands = mp.solutions.hands
    hands = mp_hands.Hands()
    mp_drawing = mp.solutions.drawing_utils

    # Variables to store the previous index finger tip position for navigation
    prev_index_tip = None

    # Loop to continuously read frames from the webcam
    while not stop_event.is_set():
        # Read a frame from the webcam
        ret, frame = cap.read()

        # Check if the frame was read correctly
        if not ret:
            break
        
        # Check camera selection
        camera_choice = camera_var.get()
        if camera_choice == "Front":
          frame = cv2.rotate(frame, cv2.ROTATE_180)
          # Convert the frame to RGB format
          frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

        # Process the frame to detect hand landmarks
        result = hands.process(frame)

        # Convert the frame back to BGR format for display
        frame = cv2.cvtColor(frame, cv2.COLOR_RGB2BGR)

        # Initialize variables to store left hand and right hand index and thumb landmarks
        left_index_tip = None
        left_thumb_tip = None
        right_index_tip = None
        right_thumb_tip = None

        # If hand landmarks are detected, draw them on the frame
        if result.multi_hand_landmarks:
            for hand_landmarks in result.multi_hand_landmarks:
                mp_drawing.draw_landmarks(frame, hand_landmarks, mp_hands.HAND_CONNECTIONS)

                # Determine which hand is being processed based on the first landmark's position
                if hand_landmarks.landmark[0].x < 0.5:
                    # Left hand (hand with index finger on the left side of the screen)
                    left_index_tip = hand_landmarks.landmark[mp_hands.HandLandmark.INDEX_FINGER_TIP]
                    left_thumb_tip = hand_landmarks.landmark[mp_hands.HandLandmark.THUMB_TIP]
                else:
                    # Right hand (hand with index finger on the right side of the screen)
                    right_index_tip = hand_landmarks.landmark[mp_hands.HandLandmark.INDEX_FINGER_TIP]
                    right_thumb_tip = hand_landmarks.landmark[mp_hands.HandLandmark.THUMB_TIP]

                    # Store the current index finger tip position for navigation
                    if prev_index_tip:
                        # Calculate the movement delta
                        delta_x = (right_index_tip.x - prev_index_tip.x) * sensitivity
                        delta_y = (right_index_tip.y - prev_index_tip.y) * sensitivity

                        # Move the mouse cursor by the delta values
                        pyautogui.moveRel(delta_x * pyautogui.size()[0], delta_y * pyautogui.size()[1])

                    prev_index_tip = right_index_tip

        # Check for scroll up action
        if left_index_tip and right_thumb_tip:
            # Calculate the distance between the left index tip and right thumb tip
            distance = calculate_distance(left_index_tip, right_thumb_tip)

            # If the distance is below a certain threshold, perform a scroll up
            if distance < 0.05:  # Adjust the threshold value as needed
                pyautogui.scroll(20)

        # Check for scroll down action
        if left_thumb_tip and right_thumb_tip:
            # Calculate the distance between the left thumb tip and right thumb tip
            distance = calculate_distance(left_thumb_tip, right_thumb_tip)

            # If the distance is below a certain threshold, perform a scroll down
            if distance < 0.05:  # Adjust the threshold value as needed
                pyautogui.scroll(-20)

        # Check for click action
        if left_index_tip and left_thumb_tip:
            # Calculate the distance between the left index tip and left thumb tip
            distance = calculate_distance(left_index_tip, left_thumb_tip)

            # If the distance is below a certain threshold, perform a click
            if distance < 0.05:  # Adjust the threshold value as needed
                pyautogui.click()

        # Display the frame with hand landmarks
        cv2.imshow("Invisible Mouse", frame)

        # Wait for 1 millisecond for a key event
        key = cv2.waitKey(1)

        # Check if the 'ESC' key was pressed (ASCII value 27)
        if key == 27:
            break

    # Release resources and close windows
    cap.release()
    cv2.destroyAllWindows()

def on_exit():
    stop_event.set()
    root.destroy()

def on_stop():
    stop_event.set()

def start_thread():
    global sensitivity
    sensitivity = float(sensitivity_var.get())
    stop_event.clear()
    t = Thread(target=on_start)
    t.start()

def show_gestures_window():
    # Hide the main window
    root.withdraw()

    # Create gestures window
    gestures_window = tk.Toplevel(root)
    gestures_window.title("Gestures Window")
    gestures_window.config(bg='#518a9c')

    # Back button to return to main window
    back_button = tk.Button(gestures_window, text="Back to Main", command=lambda: close_gestures_window(gestures_window), bg="dark orange", fg="white", font=("Helvetica", 20, "bold"))
    back_button.pack(pady=20, padx=20, anchor='w')

    # Labels for gestures
    gestures_label = tk.Label(gestures_window, text="Gestures", font=("Time New Roman", 40, "bold"), bg='#518a9c', fg='#f23a3a')
    gestures_label.pack(pady=100, padx=20, anchor='w')

    # Gesture details
    gesture_details = [
        "Right hand's >> Index Finger Tip = Cursor",
        "",
        "Left hand's >> Index Finger Tip + Left hand's >> Thumb Tip = Left Click",
        '',
        "Left hand's >> Index Finger Tip + Right hand's >> Thumb Tip = Scroll Up",
        '',
        "Left hand's >> Thumb Tip + Right hand's >> Thumb Tip = Scroll Down",
        ''
    ]

    for detail in gesture_details:
        detail_label = tk.Label(gestures_window, text=detail, font=("Time New Roman", 25), bg='#518a9c', fg='gold', anchor='w')
        detail_label.pack(pady=5, padx=20)

def close_gestures_window(window):
    window.destroy()
    root.deiconify()

# Disable PyAutoGUI failsafe
pyautogui.FAILSAFE = False

root = tk.Tk()
root.title("Invisible Mouse")
root.config(bg='#518a9c')

# Create a main frame to hold all widgets
main_frame = tk.Frame(root, bg='#518a9c')
main_frame.grid(row=0, column=0, sticky='nsew')

# Add title and subtitle
title_label = tk.Label(main_frame, text="The Ultimate App for Invisible Mouse", font=("Time New Roman", 50, "bold"), bg='#518a9c', fg='#f23a3a')
title_label.grid(row=0, column=0, padx=30, pady=20, )

subtitle_label = tk.Label(main_frame, text="Created by Team PHOENIX", font=("Ink Free", 40, "bold"), bg='#518a9c', fg='#e6c925')
subtitle_label.grid(row=1, column=0, padx=20, pady=10)

# Frame for camera selection
camera_frame = tk.Frame(main_frame, bg='#518a9c')
camera_frame.grid(row=2, column=0, padx=20, pady=20, sticky='w')

# Camera dropdown
camera_label = tk.Label(camera_frame, text="Select Camera Viewing Angle:", font=("Helvetica", 22), bg='#518a9c')
camera_label.grid(row=0, column=0, padx=5, pady=5)

camera_var = tk.StringVar(value="Front")
camera_options = ["Front", "Back"]
camera_menu = tk.OptionMenu(camera_frame, camera_var, *camera_options)
camera_menu.grid(row=0, column=1, padx=5, pady=5)

# Frame for sensitivity controls
sensitivity_frame = tk.Frame(main_frame, bg='#518a9c')
sensitivity_frame.grid(row=3, column=0, padx=20, pady=20, sticky='w')

# Sensitivity dropdown
sensitivity_label = tk.Label(sensitivity_frame, text="Select Mouse Sensitivity:", font=("Helvetica", 22), bg='#518a9c')
sensitivity_label.grid(row=0, column=0, padx=5, pady=5)

sensitivity_var = tk.StringVar(value="2")
sensitivity_options = ["1", "1.5", "2", "2.5", "3", "4", "5", "6"]
sensitivity_menu = tk.OptionMenu(sensitivity_frame, sensitivity_var, *sensitivity_options)
sensitivity_menu.grid(row=0, column=1, padx=5, pady=5)

# Start button on a new line
start_button_frame = tk.Frame(main_frame, bg='#518a9c')
start_button_frame.grid(row=4, column=0, padx=20, pady=20, sticky='n')

start_button = tk.Button(start_button_frame, text="Start", command=start_thread, bg="green", fg="white", font=("Helvetica", 25, "bold"))
start_button.pack(padx=20, pady=10)

# Stop button
stop_button = tk.Button(main_frame, text="Stop", command=on_stop, bg="dark orange", fg="white", font=("Helvetica", 25, "bold"))
stop_button.grid(row=5, column=0, pady=20)

# Exit button
exit_button = tk.Button(main_frame, text="Exit The App", command=on_exit, bg="#e31717", fg="white", font=("Helvetica", 25, "bold"))
exit_button.grid(row=6, column=0, pady=80)

# Gestures button
gestures_button = tk.Button(main_frame, text="Gestures", command=show_gestures_window, bg="#9f17e3", fg="white", font=("Helvetica", 25, "bold"))
gestures_button.grid(row=4, column=0, padx=20, pady=10, sticky='w')

# Configure grid weights to ensure proper resizing behavior
root.grid_rowconfigure(0, weight=1)
root.grid_columnconfigure(0, weight=1)
main_frame.grid_rowconfigure(2, weight=1)
main_frame.grid_columnconfigure(0, weight=1)

root.mainloop()
