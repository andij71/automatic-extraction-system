#include "EmonLib.h"


class Automatic{

public:
    void init();
    void teach();

    Automatic(int p,double calibration):
        pCT(new EnergyMonitor)
    {
        pCT->current(p, calibration);
    }

    ~Automatic()
    {
        delete pCT;
    }

    double getCT()
    {
        return pCT->calcIrms(samples);
    }


    void setOffset(float os){
        this->offset = os;
    }

private:
    EnergyMonitor *pCT;
    double threeshold = 100.0;
    double offset = 0.1;
    int samples = 300;



};