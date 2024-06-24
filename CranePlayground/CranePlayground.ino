// demo crane & Playcround Steve Lomax 2024
/*
 * The crane has 3 standard servos. Skew (rotation at the base), Boom (arm) and hook (winch). 
 * 3 potentiometers control each crane function. Pot right to +5V, Pot Centre to GND and wiper to A0, A1, and A2 
 * The servos must connect directly to the power supply. The Arduino Vcc (+5V) cannot deliver enough power
*/
#include <Servo.h>

Servo skewServo;
Servo boomServo;
Servo hookServo;
Servo playServo;  // give the servo a name "playServo"

const int POT_SKEW = A0;  // pin connected to skew potentiometer wiper
const int POT_BOOM = A1;
const int POT_HOOK = A2;

int value;                   // the value sent to the servo
const int PLAY_SPEED = 100;  // this is the speed the playground will operate. Change tis value to suit
const int PLAY_PIN = 5;      // Arduino pin number for the servo
const int PLAY_SWITCH = 6;   //Arduino pin number for the push switch
boolean playOn;              // playground running status


void setup() {
  skewServo.attach(2);  // connect to Skew pin
  boomServo.attach(3);
  hookServo.attach(4);
  pinMode(PLAY_SWITCH, INPUT_PULLUP);  // tell the Arduino a switch is connected to the PLAY_SWITCH pin)
}

void loop() {
  value = analogRead(POT_SKEW);         // read the pot skew value
  value = map(value, 0, 1023, 0, 180);  // re-scale value of pot reading (0-1023) to match the range of the servo (0 - 180)
  skewServo.write(value);               // move (write)  value to servo[i]

  value = analogRead(POT_BOOM);
  value = map(value, 0, 1023, 0, 180);
  boomServo.write(value);

  value = analogRead(POT_HOOK);
  value = map(value, 0, 1023, 0, 180);
  hookServo.write(value);


  delay(15);  //wait for servos to move

  if (digitalRead(PLAY_SWITCH) == 0) {  //if the button is pressed
    if (playOn == 1) {                  // if the playground is running
      playServo.detach();               // disconnect the playground servo
      playOn = 0;                       // set the playground off (false)
    } else {                            // otherwise, if the playground is not running
      playServo.attach(PLAY_PIN);       // attach the playground servo
      delay(100);                       // delay for 100 milliseconds to stableise the servo
      playServo.write(PLAY_SPEED);      //write the playground speed to the servo.
      playOn = 1;                       // mark the playground as running
    }
    while (digitalRead(PLAY_SWITCH) == 0) {};  // wait for the user to let go of the button
    delay(200);
  }
}
