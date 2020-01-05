#include "EmonLib.h"

class Automatic{

public:
    Automatic(unsigned int _pinCurrent,unsigned int _pinSwitch,unsigned int _pinTeach, unsigned int _pinRelais);
    ~Automatic();

    void initCalibration(double _calibration);
    void initEEPROM(unsigned int _addr);
    void initDelay(unsigned int _delay);
    void initOffset(double _offset);
    
    void teach();
    void run();
    void print();
    double getCT();

private:

    EnergyMonitor *pCT;

    unsigned int pinCurrent;
    unsigned int pinSwitch = 0;
    unsigned int pinTeach = 0;
    unsigned int pinRelais = 0;
    unsigned int addrEEPROM = 0;
    unsigned int delay = 0;
    
    double threeshold = 100.0;
    double offset = 0.1;
    double irms;
    int samples = 300;




};