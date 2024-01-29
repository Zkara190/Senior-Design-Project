from ultralytics import YOLO
#from ultralytics.yolo.v8.detect.predict import DetectionPredictor
import cv2

#loading model
model = YOLO('yolov8n.pt')

#perform tracking with the model
results = model.track(source = 0, show=True, tracker = "bytetrack.yaml") #tracking with default tracker
