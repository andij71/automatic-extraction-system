#include "EmonLib.h"
#include "toff.h"
#include "ton.h"

class Automatic{

public:
    Automatic(unsigned int _pinCurrent,unsigned int _pinSwitch,unsigned int _pinTeach, unsigned int _pinRelais);
    ~Automatic();

    void initCalibration(double _calibration);
    void initEEPROM(unsigned int _addr);
    void initDelay(double _delay);
    void initOffset(double _offset);
    
    void teach();
    void run();
    void print();
    

private:

    const double delay_on = 1.0;
    const int samples = 1500;
    double delay_off = 5.0;
    double offset = 0.5;

    double getCT();

    EnergyMonitor *pCT;
    TOF TOF1;
    TON TON1;
    
    unsigned int pinCurrent = 0;
    unsigned int pinSwitch = 0;
    unsigned int pinTeach = 0;
    unsigned int pinRelais = 0;
    unsigned int addrEEPROM = 0;


    
    bool relaisState = false;
    bool teachActiv = true;
    bool onTrigger = false;
    double threeshold = 100.0;
    double irms = 0.0;




};