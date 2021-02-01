#include <Arduino.h>

void ShelfLightState(){
  static boolean state = false;
  state = !state;
  digitalWrite(ShelfLight, state);
  
}

int TresholdValue(){
  int Threshold = analogRead(ThresholdTrimpot);
  Threshold = map(Threshold, 0, 4095, 0, 100);
  return Threshold;
}

void TouchRead(){
  static int touchReadSum = 0, touchReadsCount = 0;

  if(touchReadsCount <= 10){
    touchReadsCount ++;
    touchReadSum += touchRead(TouchSensor);
    delay(10);
  }else{
    if(touchReadSum / 5 < TresholdValue()){
      ShelfLightState();
      delay(500);
    }
    touchReadsCount = 0;
    touchReadSum = 0;
  }
}