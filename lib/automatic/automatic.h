#include "EmonLib.h"
#include "toff.h"

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

    // Testkommentar
    double getCT();

    EnergyMonitor *pCT;
    TOF TOF1;
    
    unsigned int pinCurrent = 0;
    unsigned int pinSwitch = 0;
    unsigned int pinTeach = 0;
    unsigned int pinRelais = 0;
    unsigned int addrEEPROM = 0;
    double delay = 3.0;
    
    bool relaisState = true;
    double threeshold = 100.0;
    double offset = 0.1;
    double irms;
    int samples = 300;




};