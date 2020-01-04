/* ABSAUGAUTOMATIK
 * A0  ----- CURRENT1
 * A1  ----- CURRENT2
 * A2  ----- CURRENT3
 * 
 * D2  ----- S3 - TEACH3
 * D3  ----- S2 - TEACH2
 * D4  ----- S1 - TEACH1
 * D5  ----- SWITCH1
 * D6  ----- SWITCH2
 * D7  ----- SWITCH3
 * D8  ----- RELAIS1
 * D9  ----- RELAIS2
 * D10 ----- RELAIS3
 * 
 */



#define CURRENT_INPUT01 1
#define TEACH1 3

#define ABSAUGUNG 6


#include "EmonLib.h"                   // Include Emon Library
#include <EEPROM.h>
EnergyMonitor current1;                   // Create an instance

const double offset = 0.1;
const int addr = 0;
double threeshold = 100.0;



void setup()
{  
  Serial.begin(9600);

  pinMode(TEACH1, INPUT_PULLUP);
  pinMode(ABSAUGUNG, OUTPUT);

  current1.current(CURRENT_INPUT01, 61.2);             // Current: input pin, calibration.
  
  threeshold = 100.0;
  delay(6000);
  //EEPROM.get(addr,threeshold);
}

void loop()
{

  int sensorVal = digitalRead(TEACH1);
  double Irms = current1.calcIrms(1480);  // Calculate Irms only

  
  if (sensorVal == LOW) {
    threeshold = Irms + offset;
    //EEPROM.put(addr, threeshold);
  } else {
    
  }


  if(Irms>threeshold){
    digitalWrite(ABSAUGUNG, HIGH);
  } else{
    digitalWrite(ABSAUGUNG, LOW);
  }
  
  
  
  Serial.print(Irms);	       // Apparent power
  Serial.print(" ");  
  Serial.println(threeshold);
  
}