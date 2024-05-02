from fastapi import FastAPI, HTTPException
from pydantic import BaseModel
import math
import sqlite3
from datetime import datetime


angle_diff = 0
mag = 0
mag_end = 0
app = FastAPI()#set the application running to the API

conn = sqlite3.connect('glyphs.db')#set directory to the database file
cursor = conn.cursor()
cursor.execute('''CREATE TABLE IF NOT EXISTS glyphs
                (id INTEGER PRIMARY KEY, Time REAL, theta_x REAL, theta_y REAL, sigma_x REAL, sigma_y REAL, pi_x REAL, pi_y REAL, delta_x REAL, delta_y REAL, car_angle REAL, Target_angle REAL, Command REAL, Angle_diff REAL, Magnitude REAL, Turn_Speed REAL)''')
conn.commit()#if the database doesnt exist create one with the list of column titles

class GlyphDict(BaseModel):#class of the coordinates
    theta: list[float] = []
    sigma: list[float] = []
    pi: list[float] = []
    delta: list[float] = []

glyph_data = GlyphDict()  # Initializing glyph_data
glyph_data.theta = [0.0,0.0]
glyph_data.sigma = [0.0,0.0]
glyph_data.pi = [0.0,0.0]
glyph_data.delta= [0.0,0.0]

@app.post("/glyph/")
#update coordinate data by recieving
async def store_glyph(json_data: dict):
    global glyph_data
    glyph_data = GlyphDict(
        theta=json_data.get('theta', {}).get('coords', []),
        sigma=json_data.get('sigma', {}).get('coords', []),
        pi=json_data.get('pi', {}).get('coords', []),
        delta=json_data.get('delta', {}).get('coords', [])
    )

    return glyph_data

def calc_angle(p1, p2):
    #Function to calculate angle between two glyphs
    delta_x = p1[0] - p2[0]
    delta_y = p1[1] - p2[1]
    angle_deg = math.degrees(math.atan2(delta_y, delta_x))
    print(angle_deg)
    return angle_deg

def generate_command(A1, A2):
    #decide the task that is required first to reach the target
    global angle_diff, mag, mag_end
    angle_diff = A1 - A2
    print(angle_diff)
    #limit the angle to 180 or -180
    if (angle_diff <= (-181.0)):
        angle_diff = 180 + ((angle_diff) + 180)
        
    elif (angle_diff >= 181.0):
        angle_diff = (-180) + (angle_diff - 180)
    #check special case if outside of stop range
    if mag > 110:
        #check if turning is needed
        if angle_diff < -15:
            command = 1 # turn right
        elif angle_diff > 15:
            command = 2 # turn left
        elif (-15<=angle_diff<=15):
            command = 3 # go straight
        else:
            command = 0
    #check special case if inside of stop range
    elif mag <= 110:
        #check if relignment command is needed
        if (-15<=angle_diff<=15):
            command = 0 # go straight

        elif -15 > angle_diff:
            command = 3
            mag_end = 4
    
        elif 15 < angle_diff:
            command = 3
            mag_end = 4
      
    return command

def calc_turnspeed(angle):
    #check how extreme the angle the robot needs to turn
    speed = 0    
    if(-90<=angle<=90):
        if(-60<=angle<=60):
            if(-20<=angle<=20):
                speed = 1   #15 degree speed
            else:
                speed = 2 # 30 degree speed
        else:
            speed = 3 #90 degree speed
    else:
        speed = 4 #120 degree speed
    return speed

def calc_magnitude(P1, P2):
    #calculate distance that robot has to travel
    global mag
    mag = math.sqrt((P2[0]-P1[0])**2 + (P2[1]-P1[1])**2)
    #check for what distance option will get to traget most efficiently
    if mag <= 110:
        return 0# stopped
    elif 110 < mag <= 200:
        return 1 #move 3 inches
    elif 200 < mag <= 275:
        return 2 #move 5 inches
    elif 275 < mag:
        return 3 #move 7 inches

@app.get("/glyph/")
async def get_angle():
    global conn, cursor, mag_end
    

    if glyph_data == None: #if no data error no data
        raise HTTPException(status_code=404, detail="Glyph data not found")

    mag_end = calc_magnitude(glyph_data.sigma, glyph_data.pi) # calculate distance
    car_direct = calc_angle(glyph_data.sigma, glyph_data.theta)  # calculate car angle
    target_direct = calc_angle(glyph_data.pi, glyph_data.theta)  # calculate target angle
    direction = generate_command(calc_angle(glyph_data.pi, glyph_data.theta), calc_angle(glyph_data.sigma, glyph_data.theta))# decide the command for movement
    turn_speed = calc_turnspeed(angle_diff)#calculate the desired turn speed


    now = datetime.now() #retrieve timestamp for database
    #insert all data into sql databse file
    cursor.execute('INSERT INTO glyphs (Time, theta_x, theta_y, sigma_x, sigma_y, pi_x, pi_y, delta_x, delta_y, car_angle, Target_angle, Command, Angle_diff, Magnitude, Turn_Speed) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)', (
        now, glyph_data.theta[0], glyph_data.theta[1],
        glyph_data.sigma[0], glyph_data.sigma[1],
        glyph_data.pi[0], glyph_data.pi[1],
        glyph_data.delta[0], glyph_data.delta[1],
        car_direct, target_direct,
        direction, angle_diff,
        mag_end, turn_speed
    ))
    conn.commit()
    return direction, turn_speed, mag_end 

if __name__ == "__main__":# set the ip to local host
    import uvicorn
    uvicorn.run(app, host="0.0.0.0", port=8000)