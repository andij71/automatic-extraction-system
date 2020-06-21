// automatic extraction system V1.0
      
#include "automatic.h"           
#include "pins.h"

Automatic c1(aiCURRENT1,iSWITCH1,iTEACH1,oRELAIS1);
Automatic c2(aiCURRENT2,iSWITCH2,iTEACH2,oRELAIS2);
Automatic c3(aiCURRENT3,iSWITCH3,iTEACH3,oRELAIS3);

bool sj1 = HIGH;
bool sj2 = HIGH;
bool sj3 = HIGH;

const unsigned int addr = 0;

void setup()
{ 


  pinMode(iSJ1, INPUT_PULLUP);
  pinMode(iSJ2, INPUT_PULLUP);
  pinMode(iSJ3, INPUT_PULLUP);
  c1.initCalibration(61.2);
  c2.initCalibration(61.2);
  c3.initCalibration(61.2);

  c1.initEEPROM(addr);
  c2.initEEPROM(addr+4);
  c3.initEEPROM(addr+8);

  //c1.initDelay(3.0);
  //c2.initDelay(3.0);
  //c3.initDelay(3.0);
  
  sj1 = digitalRead(iSJ1);
  //sj1=LOW;
  sj2 = digitalRead(iSJ2);
  //sj2=LOW;
  sj3 = digitalRead(iSJ3);
  //sj3=LOW;
  Serial.begin(9600);

  delay(1000);
  if(sj1==LOW) Serial.print("   CHANNEL1   ");
  if(sj2==LOW) Serial.print("   CHANNEL2   ");
  if(sj3==LOW) Serial.println("   CHANNEL3   ");
  
}

void loop()
{
  if(sj1==LOW) c1.run();
  if(sj2==LOW) c2.run();
  if(sj3==LOW) c3.run();

  if(sj1==LOW) c1.print();
  if(sj2==LOW) c2.print();
  if(sj3==LOW) c3.print();
  Serial.println(); 
}