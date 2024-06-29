#include <Servo.h>

// Define servo objects
Servo servo1;
Servo servo2;

// Define button pins
const int buttonPin1 = 8;
const int buttonPin2 = 9;

// Define LED pins
const int greenLedPin1 = 10;
const int redLedPin1 = 11;
const int greenLedPin2 = 12;
const int redLedPin2 = 13;

// Define servo positions
const int servoMinAngle = 0;   // Minimum angle
const int servoMaxAngle = 90;   // Maximum angle

// Variables to store servo positions
int servoPos1 = servoMinAngle;
int servoPos2 = servoMinAngle;

// Variables to store previous button states
int prevButtonState1 = HIGH;
int prevButtonState2 = HIGH;

// Debounce variables
unsigned long lastDebounceTime1 = 0;
unsigned long lastDebounceTime2 = 0;
unsigned long debounceDelay = 50; // milliseconds

void setup() {
  // Attach servos to pins
  servo1.attach(4);
  servo2.attach(5);

  // Set servos to initial position
  servo1.write(servoPos1);
  servo2.write(servoPos2);

  // Enable internal pull-up resistors for button pins
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);

  // Set LED pins as outputs
  pinMode(greenLedPin1, OUTPUT);
  pinMode(redLedPin1, OUTPUT);
  pinMode(greenLedPin2, OUTPUT);
  pinMode(redLedPin2, OUTPUT);

  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Read button states
  int buttonState1 = digitalRead(buttonPin1);
  int buttonState2 = digitalRead(buttonPin2);

  // Debug print button states
  Serial.print("Button 1 state: ");
  Serial.println(buttonState1);
  Serial.print("Button 2 state: ");
  Serial.println(buttonState2);

  // Check for button 1 toggle
  if (buttonState1 != prevButtonState1 && buttonState1 == LOW) {
    servoPos1 = (servoPos1 == servoMinAngle) ? servoMaxAngle : servoMinAngle;
    servo1.write(servoPos1);
    Serial.print("Servo 1 position: ");
    Serial.println(servoPos1);
    delay(100); // Delay for servo movement
  }

  // Check for button 2 toggle
  if (buttonState2 != prevButtonState2 && buttonState2 == LOW) {
    servoPos2 = (servoPos2 == servoMinAngle) ? servoMaxAngle : servoMinAngle;
    servo2.write(servoPos2);
    Serial.print("Servo 2 position: ");
    Serial.println(servoPos2);
    delay(100); // Delay for servo movement
  }

  // Update previous button states
  prevButtonState1 = buttonState1;
  prevButtonState2 = buttonState2;

  // Update LED states based on servo positions
  digitalWrite(greenLedPin1, (servoPos1 == servoMinAngle) ? HIGH : LOW);
  digitalWrite(redLedPin1, (servoPos1 == servoMinAngle) ? LOW : HIGH);
  digitalWrite(greenLedPin2, (servoPos2 == servoMinAngle) ? HIGH : LOW);
  digitalWrite(redLedPin2, (servoPos2 == servoMinAngle) ? LOW : HIGH);

  // Add a small delay to prevent overwhelming the serial port
  delay(10);
}
