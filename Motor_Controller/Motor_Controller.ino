#include "ArduinoHttpClient.h"
#include "WiFiS3.h"
#include <stdint.h>
#define r1 2//relays assigned to SIO pin of arduino
#define r2 3
#define r3 4
#define r4 5
#define r5 6
#define r6 7
#define r7 8
#define r8 9
#define r9 10
#define r10 11
int turn_or_straight;
int turn_speed;
int distance_speed;
const char ssid[] = "WINDI";  // change your network SSID
const char pass[] = "HELPME123";   // change your network password


char server[] = "10.0.140.183";// hotspot host ip
int port = 8000;  // Port where your FastAPI server is running

WiFiClient wifi;
HttpClient client = HttpClient(wifi, server, port);

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // Connect to Wi-Fi network
  Serial.print("Attempting to connect to ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    Serial.print(".");
    delay(5000);  // Wait 5 seconds before retrying
  }
  Serial.println("WiFi connected");
  pinMode(r1, OUTPUT);//set the relay pins to outputs
  pinMode(r2, OUTPUT);
  pinMode(r3, OUTPUT);
  pinMode(r4, OUTPUT);
  pinMode(r5, OUTPUT);
  pinMode(r6, OUTPUT);
  pinMode(r7, OUTPUT);
  pinMode(r8, OUTPUT);
  pinMode(r9, OUTPUT);
  pinMode(r10, OUTPUT);

 
  
}

void loop() {

  getStoredAngleData();//grab data from fast API
  switch (turn_or_straight){//check what command needs to run based on first integer
    case 1:
      turn_speed_right_cases ();//Turn right command
      break;
    case 2:
      turn_speed_left_cases ();//turn left command
      break;
    case 3:
      distance_speed_cases ();//Go straight command
      break;
    default:
      rst();//make sure all pins are set to low
  }
}
    
void getStoredAngleData() {
  // Make a GET request to the /glyph/ endpoint
  String url = "/glyph/";
  client.get(url);
  char tmp;
  //Read HTTP response
  String response = client.responseBody();


  tmp = response[1];//set first integer to the command variable
  turn_or_straight = tmp -'0';

  tmp = response[3];//set second integer to the turn speed
  turn_speed = tmp -'0';

  tmp = response[5];// set third integer to the distance/speed of going straight
  distance_speed = tmp -'0';
}

void distance_speed_cases(){//different tasks for moving straight
  switch (distance_speed) {
    case 4://reverse at -12v config
      r_neg_twelve();//set right motor to -12v
      l_neg_twelve();//set left motor to -12v
      delay(1000);
      rst();//make sure all pins are set to low
      break;

    case 3:
    //12v config

      r_twelve();//set right motor to 12v
      l_twelve();//set left motor to 12v
      delay(1000);
      rst();//make sure all pins are set to low
      
      break;

    case 2:
    //9v left config

      r_nine();//set right motor to 9v
      l_nine();//set left motor to 9v
      delay(1000);
      rst();//make sure all pins are set to low
      
      break;

    case 1:
    //6V config
      r_six();//set right motor to 6v
      l_six();//set left motor to 6v
      delay(1000);
      rst();//make sure all pins are set to low
      break;

    default:
      rst();//make sure all pins are set to low
  }


}

void turn_speed_right_cases(){


  switch (turn_speed) {//different tasks for turning right
    case 1:
      //turn right 15 degrees
      l_six();//set left motor to 6v
      delay(150);
      rst();//make sure all pins are set to low
      
      break;

    case 2:
      //turn right 35 degrees
      l_nine();//set left motor to 9v
      delay(1050);
      rst();//make sure all pins are set to low
      
      break;

    case 3:
      //turn right 90 degrees
      l_twelve();//set left motor to 12v
      delay(2250);
      rst();//make sure all pins are set to low

      break;
    
    case 4:
      //turn in place
      l_twelve();//set left motor to 12v
      r_neg_twelve();//set right motor to -12v
      delay(2250);
      rst();//make sure all pins are set to low

      break;

    default:
      rst();//make sure all pins are set to low
  }

}

void turn_speed_left_cases(){


  switch (turn_speed) {
    case 1:
      //turn left 15 degrees
      r_six();//set right motor to 6v
      delay(150);
      rst();//make sure all pins are set to low
      
      break;

    case 2:
      //turn left 45 degrees
      r_nine();//set right motor to 9v
      delay(1050);
      //Serial.println("turn left 45 degrees");
      rst();//make sure all pins are set to low
      
      break;

    case 3:
      //turn left 90 degrees
      r_twelve();//set right motor to 12v
      delay(2250);
      rst();//make sure all pins are set to low

      break;
    
    case 4:
      //turn left in place
      r_twelve();//set left motor to -12v
      l_neg_twelve();//set right motor to 12v
      delay(2250);
      //Serial.println("turn right 90 degrees");
      rst();//make sure all pins are set to low

      break;

    default:
      rst();//make sure all pins are set to low
  }
}

void rst(){//make sure all pins are set to low
    digitalWrite(r4, LOW);
    digitalWrite(r9, LOW);
    digitalWrite(r3, LOW);
    digitalWrite(r7, LOW);
    digitalWrite(r2, LOW);
    digitalWrite(r1, LOW);
    digitalWrite(r5, LOW);
    digitalWrite(r8, LOW);
    digitalWrite(r6, LOW);
    digitalWrite(r10, LOW);
}

void r_neg_twelve(){
  //set relays to get the right motor to have -12v

    digitalWrite(r5, HIGH);
    digitalWrite(r4, HIGH);
    digitalWrite(r1, LOW);
    digitalWrite(r2, HIGH);
    digitalWrite(r3, HIGH);
 

}
void l_neg_twelve(){
  //set relays to get the left motor to have -12 v
    digitalWrite(r10, HIGH);
    digitalWrite(r9, HIGH);
    digitalWrite(r6, LOW);
    digitalWrite(r7, HIGH);
    digitalWrite(r8, HIGH);


}
void r_twelve(){

  //set relays to get the right motor to have 12V
  digitalWrite(r5, LOW);
  digitalWrite(r1, LOW);
  digitalWrite(r2, HIGH);
  digitalWrite(r3, HIGH);
 

}
void l_twelve(){
  //set relays to get the left motor to have 12V
  digitalWrite(r10, LOW);
  digitalWrite(r6, LOW);
  digitalWrite(r7, HIGH);
  digitalWrite(r8, HIGH);


}
void r_nine(){

  //set relays to get the right motor to have 9V
  digitalWrite(r5, LOW);
  //delay(200);
  digitalWrite(r1, LOW);
  //delay(200);
  digitalWrite(r2, LOW);
  //delay(200);
  digitalWrite(r3, HIGH);


}
void l_nine(){
  //set relays to get the left motor to have 9V
  digitalWrite(r10, LOW);
  //delay(200);
  digitalWrite(r6, LOW);
  //delay(200);
  digitalWrite(r7, LOW);
  //delay(200);
  digitalWrite(r8, HIGH);

}
void r_six(){
  //set relays to get the right motor to have 6V
  digitalWrite(r5, LOW);
  //delay(200);
  digitalWrite(r1, HIGH);
  //delay(200);
  digitalWrite(r2, LOW);
  //delay(200);
  digitalWrite(r3, LOW);
    
}
void l_six(){

  //set relays to get the left motor to have 6V
  digitalWrite(r10, LOW);
  //delay(200);
  digitalWrite(r6, HIGH);
  //delay(200);
  digitalWrite(r7, LOW);
  //delay(200);
  digitalWrite(r8, LOW);


}
