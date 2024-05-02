from ultralytics import YOLO

# Load a model, the folders path is provided
yaml_path =r'C:\Users\karag\Pictures\Dots.v3-glyphset_v2.yolov8\data.yaml'
model_path =r'C:\Users\karag\Documents\Senior-Design-Project\Models\model.pt'

model=YOLO() #intace of a model
model.to('cuda') #move model onto GPU

if __name__=='__main__': 
    # training model, with 100 raining sessions and an image size of 640, 
    results = model.train(data=yaml_path, epochs = 100, imgsz = 640)

    model.save(model_path)