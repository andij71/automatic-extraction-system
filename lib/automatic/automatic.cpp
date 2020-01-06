#include "automatic.h"
#include <EEPROM.h>


Automatic:: Automatic(unsigned int _pinCurrent,unsigned int _pinSwitch,unsigned int _pinTeach, unsigned int _pinRelais):
    pCT(new EnergyMonitor),
    pinCurrent(_pinCurrent),
    pinSwitch(_pinSwitch),
    pinTeach(_pinTeach),
    pinRelais(_pinRelais)
{
    pinMode(pinSwitch, INPUT_PULLUP);
    pinMode(pinTeach, INPUT_PULLUP);
    pinMode(pinRelais, OUTPUT);

    Serial.begin(9600);
}

Automatic::~Automatic()
{
    delete pCT;
}

void Automatic::initCalibration(double _calibration)
{
    pCT->current(pinCurrent,_calibration);
}

void Automatic::initEEPROM(unsigned int _addr)
{
    this->addrEEPROM = _addr;
    EEPROM.get(_addr,threeshold);
}

void Automatic::initDelay(double _delay)
{
    this->delay = _delay;
}

void Automatic::initOffset(double _offset)
{
    this->offset = _offset;
}

void Automatic::teach()
{
    this->threeshold = irms + offset;
    EEPROM.put(addrEEPROM, threeshold);
}

void Automatic::run()
{
    bool teachActiv = digitalRead(pinTeach);
    bool switchActiv = digitalRead(pinSwitch);
    

    if(teachActiv == false){
        teach();
        return;
    }


    if(switchActiv == true){
        relaisState = true;
        return;
    }
    else{
        irms = getCT();
        if(irms>threeshold)
        {
            relaisState = true;
        }
        else
        {
            relaisState = false;
        }
    }

    TOF1.parameters(relaisState,delay,"Seconds");
    digitalWrite(pinRelais,TOF1.Q());


}

void Automatic::print()
{
    Serial.print(this->irms);
    Serial.print(" (");
    Serial.print(this->threeshold);
    Serial.print(") ");
}



double Automatic::getCT()
{
    return pCT->calcIrms(samples);
}



