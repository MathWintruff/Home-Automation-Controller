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

void TouchRead(){
  int touchReadSum = 0, touchReadResult = 0;
  for(int i = 0; i < 100; i++){
    touchReadSum += touchRead(T0);
  }
  touchReadResult = (touchReadSum / 100);
  
  if(touchReadResult < TresholdValue()){
    ShelfLightState();
    delay(1000);
  }
}

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
