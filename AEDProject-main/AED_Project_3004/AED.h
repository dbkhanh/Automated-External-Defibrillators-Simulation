#ifndef AED_H
#define AED_H

#include "FirstAider.h"
#include <QString>

class AED {

public:

    AED();
    AED(bool power); //Constructor so we can choose whether the AED is immediately on or not
    ~AED();

    QString powerOn();
    bool selfTest(bool);
    void ProceedOperation(bool);
    QString PadCorrection(int);
    QString DetectRhythm(int); //This will call analyzeRhytm from Electrodepads.h. Keep it void
    QString ShockProceed(bool);
    QString CompressionCorrection(int);
    void setRhythm(int);
    QString CallEmergency();
    QString OpenAirway();
    QString checkBreathing();
    int getRhythm();
    bool getPower();
    int getBatteryLevel();
    void depleteBattery();
    void changeBattery();
    QString checkConsciousness();
    void setShockable(bool);
    bool getShockable();
    void setPadPlaced(bool);
    bool getPadPlaced();
    void setPower(bool);



private:

    bool power; //We need a constructor where we can set power and a default constructor so its always off
    bool test; //This is always false initially until powerOn is pressed
    int rhythm;
    int batteryLevel= 100;
    bool shockable = false;
    bool padPlaced = false;

};

#endif
