#ifndef FIRSTAIDER_H
#define FIRSTAIDER_H

#include <QString>

class FirstAider {

public:

    FirstAider();
    ~FirstAider();
    QString checkConscious();//Consicous getter
    
    void setConscious(bool); //Conscious setter
    QString CheckBreath(); //Breath getter
    void setBreath(bool); //Breath setter
    int PadPlacement(); // Padplacement getter
    void setPadPlacement(int); //Padplacement setter
    bool StandClear(); //Clear getter
    void setStandClear(bool); //Clear setter
    int ChestCompression(); //Compression getter
    void setCompression(int); //Compression setter
    QString RescueBreath();
    bool getConscious();
    QString Emergency();
    QString Airway();

private:

    bool conscious;
    bool breathing;
    int compression;
    int pad;
    bool clear;

};

#endif