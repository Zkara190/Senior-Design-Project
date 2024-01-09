from ultralytics import YOLO

# Load a model
model = YOLO('yolov8n.pt') # Loading a pretrained model

model.to('cuda') # move model onto GPU

if __name__ == '__main__': #added to enable multiprocessing

    # training model
    results = model.train(data='VisDrone.yaml', epochs = 16, imgsz = 640)
