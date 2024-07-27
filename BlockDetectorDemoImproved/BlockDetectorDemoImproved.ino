#include <LibPrintf.h>


// Demo for 5 types of sensor Improved code

const int PIN_SENSOR[] = { 4, 5, 3, 16 };
const int PIN_LED[] = { 9, 12, 10, 8 };
const int PIN_IR = 7;
bool IRon = 0;
bool IREnabled = 0;
unsigned long flashTime = 0;
const int FLASH_DLY = 8;



void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(PIN_SENSOR[i], INPUT_PULLUP);
    pinMode(PIN_LED[i], OUTPUT);
    pinMode(PIN_IR, OUTPUT);
  }
  pinMode(PIN_SENSOR[3], INPUT);
  Serial.begin(115200);
}

bool getSensorValue(int i) {
  if (i < 2) return !digitalRead(PIN_SENSOR[i]);
  if (i==2) return flashIR();
  if (i == 3) {
    delay(8);
    int sampleTotal = 0;
    for (int j = 0; j < 50; j++) {
      int analogVal = (analogRead(PIN_SENSOR[3]));
      sampleTotal += (abs(analogVal - 500));
    }

    if (sampleTotal > 2000) {
      return 1;
    } else {
      return 0;
    }
  }
}
bool flashIR() {
  if (millis() - flashTime >= FLASH_DLY) {
    IRon = !IRon;
    digitalWrite(PIN_IR, IRon);
  }
  bool IRSensor = digitalRead(PIN_IR);
  if (!IRon) IREnabled = !IRSensor;
  return (IRon && IRSensor && IREnabled);
}

void loop() {
  
  for (int i = 0; i < 4; i++) {
    bool sensorVal = getSensorValue(i);
    digitalWrite(PIN_LED[i], sensorVal);
    printf("%d ", sensorVal);
  }
  printf("\n");
}
