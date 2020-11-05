void setup(void) { 
  Serial.begin(115200);

  WifiSetup();
  OtaSetup();
  IoInicialization();
}

void loop(void) {
  WebControler();
  delay(1);
  TouchRead();
  delay(1);
}
