#include <Arduino.h>

//-------- Inputs --------------
const int ThresholdTrimpot = 34;
const int ServerLight = 2;
const int TouchSensor = T0;
//const int IrSensor = 35;

//-------- OutPuts -------------
const int ShelfLight = 23;
const int InternalLed = 18;
const int ExternalLed = 13;
const int ServerSwitch = 19;
const int SpareSwitch1 = 21;
const int SpareSwitch2 = 22;

void IoInicialization(){
  pinMode(ShelfLight, OUTPUT);
  pinMode(InternalLed, OUTPUT);
  pinMode(ExternalLed, OUTPUT);
  pinMode(ServerSwitch, OUTPUT);
  pinMode(SpareSwitch1, OUTPUT);
  pinMode(SpareSwitch2, OUTPUT);

  pinMode(ServerLight, INPUT_PULLUP);

  digitalWrite(InternalLed, HIGH);
}