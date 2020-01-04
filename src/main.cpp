// ABSAUGAUTOMATIK V1.0

#include "EmonLib.h"                  
#include <EEPROM.h>
#include "pins.h"

EnergyMonitor ct1;            
EnergyMonitor ct2;
EnergyMonitor ct3;



const double offset = 0.2;
const int addr = 0;

double threeshold1 = 100.0;
double threeshold2 = 100.0;
double threeshold3 = 100.0;

void setup()
{  
  Serial.begin(9600);

  pinMode(iTEACH1, INPUT_PULLUP);
  pinMode(iTEACH2, INPUT_PULLUP);
  pinMode(iTEACH3, INPUT_PULLUP);
  pinMode(oRELAIS1, OUTPUT);
  pinMode(oRELAIS2, OUTPUT);
  pinMode(oRELAIS3, OUTPUT);

  ct1.current(aiCURRENT1, 61.2);            
  ct2.current(aiCURRENT2, 61.2); 
  ct3.current(aiCURRENT3, 61.2); 
  
  EEPROM.get(addr,threeshold1);
  EEPROM.get(addr+4,threeshold2);
  EEPROM.get(addr+8,threeshold3);
}

void loop()
{
  bool teach1 = digitalRead(iTEACH1);
  bool teach2 = digitalRead(iTEACH2);
  bool teach3 = digitalRead(iTEACH3);

  double Irms1 = ct1.calcIrms(1480);
  double Irms2 = ct2.calcIrms(1480);
  double Irms3 = ct3.calcIrms(1480);

  
  if (teach1 == LOW) {
    threeshold1 = Irms1 + offset;
    EEPROM.put(addr, threeshold1);
  }

  if (teach2 == LOW) {
    threeshold2 = Irms2 + offset;
    EEPROM.put(addr+4, threeshold2);
  }

  if (teach3 == LOW) {
    threeshold3 = Irms2 + offset;
    EEPROM.put(addr+8, threeshold3);
  }


  if(Irms1>threeshold1)
  {
    digitalWrite(oRELAIS1, HIGH);
  } 
  else
  {
    digitalWrite(oRELAIS1, LOW);
  }

  if(Irms2>threeshold2)
  {
    digitalWrite(oRELAIS2, HIGH);
  } 
  else
  {
    digitalWrite(oRELAIS2, LOW);
  }

  if(Irms3>threeshold3)
  {
    digitalWrite(oRELAIS3, HIGH);
  } 
  else
  {
    digitalWrite(oRELAIS3, LOW);
  }
    
  Serial.print(Irms1);	       
  Serial.print(" (");
  Serial.print(threeshold1);
  Serial.print(") ");
  Serial.print(Irms2);	       
  Serial.print(" (");
  Serial.print(threeshold2);
  Serial.print(") ");
  Serial.print(Irms3);
  Serial.print(" (");
  Serial.print(threeshold3);
  Serial.println(") ");	       

}