from fastapi import FastAPI, HTTPException, Request
from pydantic import BaseModel
import serial

app = FastAPI()


class AngleData(BaseModel):
    car_angle: float    #, "target": []}

stored_angle: float = 21.0  #
#arduino = serial.Serial('COMX', 9600) #replacing COMX with the chosen port; 9600 is baud rate

@app.post("/angles/")
async def store_angle(angle_data: AngleData):
    global stored_angle
    stored_angle = angle_data.car_angle
    return {"message": "Angle stored"}

@app.get("/angles/")
async def get_angle():
    if stored_angle is None:
        raise HTTPException(status_code=404, detail = "Angle data not found")
    return{"car_angles": stored_angle}      #, "target_angles": stored_angles["target"]
'''
@app.exception_handler(HTTPException)
async def http_exception_handler(request: Request, exc: HTTPException):
    return JSONResponse(
        status_code=exc.status_code,
        content={"message": exc.detail}
    )
'''
if __name__ == "__main__":
    import uvicorn
    uvicorn.run(app, host="0.0.0.0", port=8000)