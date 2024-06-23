#include <LibPrintf.h>


// Demo for 4 types of sensor
const int PM_PIN = 4;//PM:  pocket money 7 kit
const int DD_PIN = 5;//DD: diode drop circuit
const int PS_PIN = 3;//PS: point sensor-> infra red refluctive
const int CT_PIN = A2;//CT: current transformer. NB! short across the capacitor adjacent to the connection pins
const int RS_PIN = 6;// Magnetic reed switch 

const int PM_LED_PIN = 9; // these are the chosen Arduino pins each LED is connected to
const int DD_LED_PIN = 12;
const int PS_LED_PIN = 10;
const int CT_LED_PIN = 8;
const int RS_LED_PIN = 11;

bool PM = 0; //initialise the status variable for each sensor to 0 (off) 
bool DD = 0;
bool PS = 0;
bool CT = 0;
bool RS = 0;
int CTA = 0;
int oldOut = 0;// just for making the debugging display more readable
int sampleCount = 0; // 
int sampleTotal = 0;
int oldSampleTotal = 0;
const int PIN_IR = 7;



void setup() {
  pinMode(PM_PIN, INPUT_PULLUP);
  pinMode(DD_PIN, INPUT_PULLUP);
  pinMode(PS_PIN, INPUT_PULLUP);
  pinMode(PS_PIN, INPUT_PULLUP);
  pinMode(RS_PIN, INPUT_PULLUP);

  pinMode(PM_LED_PIN, OUTPUT);
  pinMode(DD_LED_PIN, OUTPUT);
  pinMode(PS_LED_PIN, OUTPUT);
  pinMode(CT_LED_PIN, OUTPUT);
  pinMode(RS_LED_PIN, OUTPUT);
  pinMode(PIN_IR, OUTPUT);
  digitalWrite(PIN_IR, 1);// turn on IR TX LED

  Serial.begin(115200);
}
void scanSensors() {
  PM = !digitalRead(PM_PIN);
  DD = !digitalRead(DD_PIN);
  PS = !digitalRead(PS_PIN);
  CTA = analogRead(CT_PIN);
  RS = !digitalRead(RS_PIN);
  
}
void outputStatus() {
  
  digitalWrite(PM_LED_PIN, PM);
  digitalWrite(DD_LED_PIN, DD);
  digitalWrite(PS_LED_PIN, PS);
  digitalWrite(CT_LED_PIN, CT);
  digitalWrite(RS_LED_PIN, RS);
}



bool calculateAnalog() {
  sampleCount++;
  if (sampleCount < 50) 
  {
    sampleTotal += (abs(CTA - 500));
  } 
  else 
  {
    sampleCount=0;
    oldSampleTotal=sampleTotal;
    CT=0;
    if (sampleTotal > 2000) {
      CT = 1;
    }
    sampleTotal =0;
  }
  return CT
}

void printOut() {
  int out = (RS <<4)+(PM << 3) + (DD << 2) + (PS << 1) + CT;

  if (out != oldOut) {

    printf("PMK7= %d,   Diode Drop= %d,    Point Sensor= %d,    Current Transformer= %d,  reed switch= %d,   Analog= %d    av tot = %d\n", PM, DD, PS, CT, RS, CTA, oldSampleTotal);
    oldOut = out;
  }
}

void loop() {
  scanSensors();
  CT = calculateAnalog();
  outputStatus();
  printOut();
}
