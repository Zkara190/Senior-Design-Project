from collections import defaultdict
from ultralytics import YOLO
import cv2
import numpy as np
import requests
import threading

# Uses threading to allow posting process to be ran similaniously along with the tracking.
def send_payload_async(payload):
    threading.Thread(target=send_payload, args=(payload,)).start()

# Function for posting  JSON file to a url
def send_payload(payload):           
    try:
        response = requests.post(url, json=payload)
        response.raise_for_status()
        print("Angle sent correctly")
    except Exception as e:
        print("failed to send: ", e)


url = "http://10.0.140.183:8000/glyph/" # site to post angles to API address
# Address is going to change depending on host.

# Loading model
model = YOLO(r'C:\Users\karag\Documents\SeniorDesignProject\Ultralytics\runs\detect\train9\weights\best.pt')
model.to('cuda')  # Move model onto GPU
vid = cv2.VideoCapture(0) # selects camera from camera index, tells what cameras are conected

# dictionary containing object coordinate data
glyphdict = {
    "theta": {"coords": [0.0,0.0]},
    "sigma": {"coords": [0.0,0.0]},
    "delta": {"coords": [0.0,0.0]},
    "pi": {"coords": [0.0,0.0]},
}

# Perform tracking with the model
while vid.isOpened():
    success, frame = vid.read()
    if success:
        height, _ = frame.shape[:2] # sets bottom left corner of screen as [0,0] for easy math!
        results = model.track(frame, show=True, persist=True, verbose=False)  # Tracking with default tracker

        for result in results:
            boxes = result.boxes  # Boxes object for bbox outputs

            for box in boxes:
                # Get the center of the box tensor
                x_center = (box.xyxy[0][0] + box.xyxy[0][2]) / 2
                y_center = height - ((box.xyxy[0][1] + box.xyxy[0][3]) / 2)

                # Convert tensor to numerical values
                x_center_value = x_center.item()
                y_center_value = y_center.item()

                cls = box.cls     # Class index
                cls_int = int(cls)  # transforms class index to integer
                label = model.names.get(cls_int)    # .names is a integer indexed dictionary of classes
                conf = box.conf.item()     # Confidence score
            
                # desicion based on label, update spesific position variable
                if label:
                    glyphdict[label]["coords"] = [round(x_center_value, 2), round(y_center_value,2)] # updates respective dictionary entry with rounded coord values.
                    print(glyphdict)
                else: 
                    print("Error in assigning coordinates")

            # Check if sigma, theta, and pi are detected, send data to API
            if all(label in glyphdict for label in ["sigma", "theta", "pi"]):
                # Send payload asynchronously
                send_payload_async(glyphdict)
    # Allows to hold 'q' to quit the video feed
    if cv2.waitKey(1) & 0xFF == ord("q"): 
        break
    else:
        pass
# uninitialize windows and camera
vid.release()
cv2.destroyAllWindows()