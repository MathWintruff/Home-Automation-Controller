//------- RF 24L01 ----------------
#include  <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
RF24 RfTransceiver(12, 14, 26, 25, 27);
byte writePipeAdress[17] = "FanControlerPipe";
byte readPipeAdress[14] = "FanDevicePipe";

void RfSetup(){
  RfTransceiver.begin();
  RfTransceiver.setChannel(2);
  RfTransceiver.setPayloadSize(7);
  RfTransceiver.setDataRate(RF24_250KBPS);
  RfTransceiver.openWritingPipe(writePipeAdress);
  
}

void RfSender(String SMsg){
  int SMsgLength = SMsg.length();
  char CMsg[SMsgLength + 1];
  SMsg.toCharArray(CMsg, SMsgLength);

  RfTransceiver.write(CMsg, SMsgLength + 1);
  delay(50);
}
