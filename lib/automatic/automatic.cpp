#include "automatic.h"
#include <EEPROM.h>

Automatic::Automatic(unsigned int _pinCurrent, unsigned int _pinSwitch, unsigned int _pinTeach, unsigned int _pinRelais) : pCT(new EnergyMonitor),
                                                                                                                           pinCurrent(_pinCurrent),
                                                                                                                           pinSwitch(_pinSwitch),
                                                                                                                           pinTeach(_pinTeach),
                                                                                                                           pinRelais(_pinRelais)
{
    pinMode(pinSwitch, INPUT_PULLUP);
    pinMode(pinTeach, INPUT_PULLUP);
    pinMode(pinRelais, OUTPUT);
    onTrigger = false;
    //TON1.parameters(onTrigger,10,"Seconds");
    //Serial.begin(9600);
}

Automatic::~Automatic()
{
    delete pCT;
}

void Automatic::initCalibration(double _calibration)
{
    pCT->current(pinCurrent, _calibration);
}

void Automatic::initEEPROM(unsigned int _addr)
{
    this->addrEEPROM = _addr;
    EEPROM.get(_addr, threeshold);
}

void Automatic::initDelay(double _delay)
{
    this->delay_off = _delay;
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
    teachActiv = digitalRead(pinTeach);
    TON1.parameters(onTrigger, delay_on, "Seconds");

    if (!teachActiv)
    {
        teach();
        return;
    }

    bool switchActiv = digitalRead(pinSwitch);
    if (!switchActiv)
        relaisState = true;
    else
    {
        this->irms = getCT();
        if (irms > threeshold && TON1.Q())
            relaisState = true;
        else
            relaisState = false;
    }

    TOF1.parameters(relaisState, delay_off, "Seconds");
    digitalWrite(pinRelais, TOF1.Q());

    onTrigger = true;
}

void Automatic::print()
{

    if (!this->teachActiv)
    {
        Serial.print("     TEACH     ");
        return;
    }

    Serial.print(this->irms);
    Serial.print(" (");
    Serial.print(this->threeshold);
    Serial.print(") ");

    if (TOF1.Q())
        Serial.print("•  ");
    else
        Serial.print("o  ");
}

double Automatic::getCT()
{
    return pCT->calcIrms(samples);
}
