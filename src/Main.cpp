#include <Arduino.h>
#include <VariablesDeclaration.h>
#include <MyFunctions.h>
#include <ConnectionSetup.h>
#include <RfConnection.h>

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