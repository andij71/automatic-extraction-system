// ABSAUGAUTOMATIK V1.0

// analog inputs
#define aiCURRENT1   0
#define aiCURRENT2   1
#define aiCURRENT3   2


// digital inputs
#define iTEACH1      4   // active low
#define iTEACH2      3   // active low
#define iTEACH3      2   // active low
#define iSWITCH1     5   // active low
#define iSWITCH2     6   // active low
#define iSWITCH3     7   // active low
#define iSJ1         11  // active low  
#define iSJ2         12  // active low
#define iSJ3         13  // active low

// digital outputs
#define oRELAIS1     8
#define oRELAIS2     9
#define oRELAIS3     10



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

  bool teach1 = digitalRead(TEACH1);
  double Irms = current1.calcIrms(1480);  // Calculate Irms only

  
  if (teach1 == LOW) {
    threeshold = Irms + offset;
    EEPROM.put(addr, threeshold);
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