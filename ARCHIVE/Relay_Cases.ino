#include "Arduino_LED_Matrix.h"
#include <stdint.h>
#define r1 2
#define r2 3
#define r3 4
#define r4 5
#define r5 6
#define r6 7
int Volt;

ArduinoLEDMatrix matrix;
int test;
const uint32_t frames[][4] = {
  {
    0xe0000000,
    0x0,
    0x0,
    66
  },
  {
    0x400e0000,
    0x0,
    0x0,
    66
  },
  {
    0x400e0,
    0x0,
    0x0,
    66
  },
  {
    0x40,
    0xe000000,
    0x0,
    66
  },
  {
    0x3000000,
    0x400e000,
    0x0,
    66
  },
  {
    0x3003000,
    0x400e,
    0x0,
    66
  },
  {
    0x3003,
    0x4,
    0xe00000,
    66
  },
  {
    0x3,
    0x300000,
    0x400e00,
    66
  },
  {
    0x0,
    0x300300,
    0x400e00,
    66
  },
  {
    0x1c000000,
    0x300,
    0x30400e00,
    66
  },
  {
    0x401c000,
    0x0,
    0x30430e00,
    66
  },
  {
    0x401c,
    0x0,
    0x430e30,
    66
  },
  {
    0x4,
    0x1c00000,
    0x430e30,
    66
  },
  {
    0x0,
    0x401c00,
    0x430e30,
    66
  },
  {
    0x800000,
    0x401,
    0xc0430e30,
    66
  },
  {
    0x800800,
    0x0,
    0x405f0e30,
    66
  },
  {
    0x800800,
    0x80000000,
    0x470ff0,
    66
  },
  {
    0x800800,
    0x80080000,
    0x470ff0,
    66
  },
  {
    0x800,
    0x80080080,
    0x470ff0,
    66
  },
  {
    0x38000000,
    0x80080080,
    0x8470ff0,
    66
  },
  {
    0x10038000,
    0x80080,
    0x8478ff0,
    66
  },
  {
    0x10038,
    0x80,
    0x8478ff8,
    66
  },
  {
    0x700010,
    0x3800080,
    0x8478ff8,
    66
  },
  {
    0x400700,
    0x1003880,
    0x8478ff8,
    66
  },
  {
    0x400,
    0x70001083,
    0x88478ff8,
    66
  },
  {
    0xf000000,
    0x40070081,
    0x87f8ff8,
    66
  },
  {
    0xf000,
    0x400f1,
    0x87f8ff8,
    66
  },
  {
    0x8000000f,
    0xc1,
    0xf7f8ff8,
    66
  },
  {
    0xc0080000,
    0xf00081,
    0xc7ffff8,
    66
  },
  {
    0x400c0080,
    0xf81,
    0x87fcfff,
    66
  },
  {
    0x3400c0,
    0x8000081,
    0xf87fcfff,
    66
  },
  {
    0x20200340,
    0xc008081,
    0xf87fcfff,
    66
  },
  {
    0x38220200,
    0x3400c089,
    0xf87fcfff,
    66
  },
  {
    0x38220,
    0x2003408d,
    0xf8ffcfff,
    66
  },
  {
    0x86100038,
    0x220240bd,
    0xf8ffcfff,
    66
  },
  {
    0xec186100,
    0x38260ad,
    0xfbffcfff,
    66
  },
  {
    0x3ec186,
    0x100078af,
    0xfaffffff,
    66
  },
  {
    0x114003ec,
    0x186178af,
    0xfaffffff,
    66
  },
  {
    0x3b411400,
    0x3ec1febf,
    0xfaffffff,
    66
  },
  {
    0x143b411,
    0x4ec3febf,
    0xfbffffff,
    66
  },
  {
    0xc040143b,
    0x4fd7febf,
    0xfbffffff,
    66
  },
  {
    0xc60c0439,
    0x4ff7ffff,
    0xfbffffff,
    66
  },
  {
    0x33c60f9,
    0x4ff7ffff,
    0xffffffff,
    66
  },
  {
    0x3cbc33ff,
    0x4ff7ffff,
    0xffffffff,
    66
  },
  {
    0x8ffbff,
    0x7ff7ffff,
    0xffffffff,
    66
  },
  {
    0xf0cffbff,
    0xfff7ffff,
    0xffffffff,
    66
  },
  {
    0xfe1fffff,
    0xffffffff,
    0xffffffff,
    66
  },
  {
    0xffffffff,
    0xffffffff,
    0xffffffff,
    66
  },
  {
    0x7fffffff,
    0xffffffff,
    0xfffff7ff,
    66
  },
  {
    0x3fe7ffff,
    0xffffffff,
    0xff7ff3fe,
    66
  },
  {
    0x1fc3fe7f,
    0xfffffff7,
    0xff3fe1fc,
    66
  },
  {
    0xf81fc3f,
    0xe7ff7ff3,
    0xfe1fc0f8,
    66
  },
  {
    0x500f81f,
    0xc3fe3fe1,
    0xfc0f8070,
    66
  },
  {
    0x500f,
    0x81fc1fc0,
    0xf8070020,
    66
  },
  {
    0x5,
    0xf80f80,
    0x70020000,
    66
  },
  {
    0x5,
    0xa80880,
    0x50020000,
    600
  },
  {
    0xd812,
    0x41040880,
    0x50020000,
    200
  },
  {
    0x5,
    0xa80880,
    0x50020000,
    0xFFFFFFFF
  }
};


void setup() {
  Volt = 0;
  test = 0;
  Serial.begin(115200);
  // you can also load frames at runtime, without stopping the refresh
 matrix.loadSequence(frames);
 matrix.begin();
  // turn on autoscroll to avoid calling next() to show the next frame; the parameter is in milliseconds
  // matrix.autoscroll(300);
matrix.play(true);
pinMode(r1, OUTPUT);
pinMode(r2, OUTPUT);
pinMode(r3, OUTPUT);


  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

Serial.println("enter Voltage");

while (Serial.available() == 0) {

}
Volt = Serial.parseInt();
//test volt level and triggering
//r# = relay #
/*
switch (Volt) {
  case 12:
   //12v config
    digitalWrite(r3, LOW);
    delay(10);
    digitalWrite(r2, LOW);
    delay(10);
    digitalWrite(r1, HIGH);
    delay(2000);
    //return to 0v config
    digitalWrite(r3, LOW);
    delay(10);
    digitalWrite(r2, LOW);
    delay(10);
    digitalWrite(r1, LOW);
    delay(10);
    delay(1000);
    break;

  case 9:
    //9v config
    digitalWrite(r3, HIGH);
    delay(10);
    digitalWrite(r2, LOW);
    delay(10);
    digitalWrite(r1, HIGH);
    delay(2000);
    //return to 0v config
    digitalWrite(r3, LOW);
    delay(10);
    digitalWrite(r2, LOW);
    delay(10);
    digitalWrite(r1, LOW);
    delay(10);
    delay(1000);
    break;

  case 6:
    //6v config
    digitalWrite(r3, HIGH);
    delay(10);
    digitalWrite(r2, HIGH);
    delay(10);
    digitalWrite(r1, LOW);
    delay(2000);
    //return to 0v config
    digitalWrite(r3, LOW);
    delay(10);
    digitalWrite(r2, LOW);
    delay(10);
    digitalWrite(r1, LOW);
    delay(10);
    break;
  case 0:
    digitalWrite(r3, LOW);
    delay(10);
    digitalWrite(r2, LOW);
    delay(10);
    digitalWrite(r1, LOW);
    delay(10);
    break;

  default:
    digitalWrite(r3, LOW);
    delay(10);
    digitalWrite(r2, LOW);
    delay(10);
    digitalWrite(r1, LOW);
    delay(10);
}*/

//relay configs for inputs
//we can vary time by changing the final delay n each case

switch (Volt) {
//12 and 12
  case 1:
      //set + or -
      digitalWrite(r5, LOW);
      digitalWrite(r6, LOW);
      //set 12v on left motor
      digitalWrite(r3, LOW);
      delay(10);
      digitalWrite(r1, HIGH);
      delay (10);
      //set 12V on right motor
      digitalWrite(r4, LOW);
      delay(10);
      digitalWrite(r2, HIGH);
      delay (10);
      delay(2000);
    break;
//12 and 9
    case 2:
      //set + or -
      digitalWrite(r5, LOW);
      digitalWrite(r6, LOW);
      //set 12v on left motor
      digitalWrite(r3, LOW);
      delay(10);
      digitalWrite(r1, HIGH);
      delay (10);
      //set 9V on right motor
      digitalWrite(r4, HIGH);
      delay(10);
      digitalWrite(r2, LOW);
      delay (10);
      delay(2000);
    break;
//12 and 6
    case 3:
      //set + or -
      digitalWrite(r5, LOW);
      digitalWrite(r6, LOW);
      //set 12v on left motor
      digitalWrite(r3, LOW);
      delay(10);
      digitalWrite(r1, HIGH);
      delay (10);
      //set 6V on right motor
      digitalWrite(r4, HIGH);
      delay(10);
      digitalWrite(r2, HIGH);
      delay (10);
      delay(2000);
    break;
//12 and 0
    case 4:
      //set + or -
      digitalWrite(r5, LOW);
      digitalWrite(r6, LOW);
      //set 12v on left motor
      digitalWrite(r3, LOW);
      delay(10);
      digitalWrite(r1, HIGH);
      delay (10);
      //set 0V on right motor
      digitalWrite(r4, LOW);
      delay(10);
      digitalWrite(r2, LOW);
      delay (10);
      delay(2000);
    break;
//0 and 12
    case 5:
      //set + or -
      digitalWrite(r5, LOW);
      digitalWrite(r6, LOW);
      //set 0v on left motor
      digitalWrite(r3, LOW);
      delay(10);
      digitalWrite(r1, LOW);
      delay (10);
      //set 12V on right motor
      digitalWrite(r4, LOW);
      delay(10);
      digitalWrite(r2, HIGH);
      delay (10);
      delay(2000);
    break;
//6 and 12
    case 6:
      //set + or -
      digitalWrite(r5, LOW);
      digitalWrite(r6, LOW);
      //set 6v on left motor
      digitalWrite(r3, HIGH);
      delay(10);
      digitalWrite(r1, HIGH);
      delay (10);
      //set 12V on right motor
      digitalWrite(r4, LOW);
      delay(10);
      digitalWrite(r2, HIGH);
      delay (10);
      delay(2000);
    break;
//9 and 12
    case 7:
      //set + or -
      digitalWrite(r5, LOW);
      digitalWrite(r6, LOW);
      //set 9v on left motor
      digitalWrite(r3, HIGH);
      delay(10);
      digitalWrite(r1, LOW);
      delay (10);
      //set 12V on right motor
      digitalWrite(r4, LOW);
      delay(10);
      digitalWrite(r2, HIGH);
      delay (10);
      delay(2000);
    break;
//9 and 6
    case 8:
      //set + or -
      digitalWrite(r5, LOW);
      digitalWrite(r6, LOW);
      //set 9v on left motor
      digitalWrite(r3, HIGH);
      delay(10);
      digitalWrite(r1, LOW);
      delay (10);
      //set 6V on right motor
      digitalWrite(r4, HIGH);
      delay(10);
      digitalWrite(r2, HIGH);
      delay (10);
      delay(2000);
    break;
//6 and 9
    case 9:
      //set + or -
      digitalWrite(r5, LOW);
      digitalWrite(r6, LOW);
      //set 6v on left motor
      digitalWrite(r3, HIGH);
      delay(10);
      digitalWrite(r1, HIGH);
      delay (10);
      //set 9V on right motor
      digitalWrite(r4, HIGH);
      delay(10);
      digitalWrite(r2, LOW);
      delay (10);
      delay(2000);
    break;
//9 and 9
    case 10:
      //set + or -
      digitalWrite(r5, LOW);
      digitalWrite(r6, LOW);
      //set 9v on left motor
      digitalWrite(r3, HIGH);
      delay(10);
      digitalWrite(r1, LOW);
      delay (10);
      //set 9V on right motor
      digitalWrite(r4, HIGH);
      delay(10);
      digitalWrite(r2, LOW);
      delay (10);
      delay(2000);
    break;
//6 and 6
    case 11:
      //set + or -
      digitalWrite(r5, LOW);
      digitalWrite(r6, LOW);
      //set 6v on left motor
      digitalWrite(r3, HIGH);
      delay(10);
      digitalWrite(r1, HIGH);
      delay (10);
      //set 6V on right motor
      digitalWrite(r4, HIGH);
      delay(10);
      digitalWrite(r2, HIGH);
      delay (10);
      delay(2000);
    break;
//0 and 0
    case 12:
      //set + or -
      digitalWrite(r5, LOW);
      digitalWrite(r6, LOW);
      //set 0v on left motor
      digitalWrite(r3, LOW);
      delay(10);
      digitalWrite(r1, LOW);
      delay (10);
      //set 0V on right motor
      digitalWrite(r4, LOW);
      delay(10);
      digitalWrite(r2, LOW);
      delay (10);
      delay(2000);
    break;
//-12 and 12
    case 13:
      //set + or -
      digitalWrite(r5, HIGH);
      digitalWrite(r6, LOW);
      //set -12v on left motor
      digitalWrite(r3, LOW);
      delay(10);
      digitalWrite(r1, HIGH);
      delay (10);
      //set 12V on right motor
      digitalWrite(r4, LOW);
      delay(10);
      digitalWrite(r2, HIGH);
      delay (10);
      delay(2000);
    break;
//12 and -12
    case 14:
      //set + or -
      digitalWrite(r5, LOW);
      digitalWrite(r6, HIGH);
      //set 12v on left motor
      digitalWrite(r3, LOW);
      delay(10);
      digitalWrite(r1, HIGH);
      delay (10);
      //set -12V on right motor
      digitalWrite(r4, LOW);
      delay(10);
      digitalWrite(r2, HIGH);
      delay (10);
      delay(2000);
    break;
//-9 and 9
    case 15:
      //set + or -
      digitalWrite(r5, HIGH);
      digitalWrite(r6, LOW);
      //set -9v on left motor
      digitalWrite(r3, HIGH);
      delay(10);
      digitalWrite(r1, LOW);
      delay (10);
      //set 9V on right motor
      digitalWrite(r4, HIGH);
      delay(10);
      digitalWrite(r2, LOW);
      delay (10);
      delay(2000);
    break;
//-9 and -6
    case 16:
      //set + or -
      digitalWrite(r5, HIGH);
      digitalWrite(r6, HIGH);
      //set -9v on left motor
      digitalWrite(r3, HIGH);
      delay(10);
      digitalWrite(r1, LOW);
      delay (10);
      //set -6V on right motor
      digitalWrite(r4, HIGH);
      delay(10);
      digitalWrite(r2, HIGH);
      delay (10);
      delay(2000);
    break;
//-6 and -9
    case 17:
      //set + or -
      digitalWrite(r5, HIGH);
      digitalWrite(r6, HIGH);
      //set -6v on left motor
      digitalWrite(r3, HIGH);
      delay(10);
      digitalWrite(r1, HIGH);
      delay (10);
      //set -9V on right motor
      digitalWrite(r4, HIGH);
      delay(10);
      digitalWrite(r2, LOW);
      delay (10);
      delay(2000);
    break;
//-6 and -6
    case 18:
      //set + or -
      digitalWrite(r5, HIGH);
      digitalWrite(r6, HIGH);
      //set -6v on left motor
      digitalWrite(r3, HIGH);
      delay(10);
      digitalWrite(r1, HIGH);
      delay (10);
      //set -6V on right motor
      digitalWrite(r4, HIGH);
      delay(10);
      digitalWrite(r2, HIGH);
      delay (10);
      delay(2000);
    break;
//-9 and -9
    case 19:
      //set + or -
      digitalWrite(r5, HIGH);
      digitalWrite(r6, HIGH);
      //set 12v on left motor
      digitalWrite(r3, HIGH);
      delay(10);
      digitalWrite(r1, LOW);
      delay (10);
      //set 9V on right motor
      digitalWrite(r4, HIGH);
      delay(10);
      digitalWrite(r2, LOW);
      delay (10);
      delay(2000);
    break;
//-12 and -12    
    case 20:
      //set + or -
      digitalWrite(r5, HIGH);
      digitalWrite(r6, HIGH);
      //set 12v on left motor
      digitalWrite(r3, LOW);
      delay(10);
      digitalWrite(r1, HIGH);
      delay (10);
      //set 9V on right motor
      digitalWrite(r4, LOW);
      delay(10);
      digitalWrite(r2, HIGH);
      delay (10);
      delay(2000);
    break;
  
  default:
    digitalWrite(r3, LOW);
    delay(10);
    digitalWrite(r2, LOW);
    delay(10);
    digitalWrite(r1, LOW);
    delay(10);
}
Volt = 0;
}