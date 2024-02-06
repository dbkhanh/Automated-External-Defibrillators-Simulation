#include "AED.h"
#include "iostream"

AED::AED(): power(false), test(false), rhythm(0) {batteryLevel = 100;}

AED::AED(bool power): power(power), test(false), rhythm(2) {}

AED::~AED(){}

QString AED::powerOn(){
    if (power == true){
        power = false;
        return "AED turning off";
    }
    else{ //power == false --> turning on
        if(batteryLevel != 0){
            power = true;
            QString str = "";
            str += "\nAED powered on. Doing self-test...";
            str += "\nAudio: AED powered on. Doing self-test...";
            if (selfTest(true) == true){
                str += "\nSelf test passed. Ready for operation";
                str += "\nAudio: Self test passed. Ready for operation";
            }
            return str;
        }
        else{
            QString str = "";
            str += "\nPlease change the battery.";
            return str;
        }
    }
}

bool AED::selfTest(bool test){
    this->test = true;

    return test;
}


QString AED::checkConsciousness(){
    return "Check consciousness of patient.";
}



QString AED::DetectRhythm(int heart){

    if (power == false){
        return "\nFirstAider: The AED is off. Let me turn it on";
    }
    QString str = "";
    str += "Analyzing rhythm with pads..Don't touch patient.";
    str += "Audio: Analyzing rhythm with pads..Don't touch patient.";
    rhythm = heart;
    if (heart == 0){
        str += "\nShock advised: Ventricular fibrillation";
        str += "\nAudio: Shock advised: Ventricular fibrillation";
    }
    else if (heart == 1){
        str += "\nShock advised: Ventricular tachycardia";
        str += "\nAudio: Shock advised: Ventricular tachycardia";
    }
    else if (heart == 2){
        str += "\nFlatline...";
        str += "\nAudio: Flatline...";
    }
    else if (heart == 3){
        str += "\nNormal heart rate";
        str += "\nAudio: Normal heart rate";
    }
    return str;
}

void AED::setShockable(bool shock){
    shockable = shock;
}

bool AED::getShockable(){
    return shockable;
}

void AED::setPadPlaced(bool pad){
    padPlaced = pad;
}

bool AED::getPadPlaced(){
    return padPlaced;
}


QString AED::ShockProceed(bool proceed){

    if (power == false){
        return "\nFirstAider: The AED is off. Let me turn it on";
    }

    QString str = "";
    if(proceed == false){
        str += "\nFirstAider: Cannot proceed since not clear of patient";
        return str;
    }else{
        if (rhythm == 3){
            str += "\nNormal heart rate. No shock needed.";
            str += "\nAudio: Normal heart rate. No shock needed.";
        }
        else if (rhythm == 2){
            str += "\nFlatline. No shock needed";
            str += "\nAudio: Flatline. No shock needed";
        }

        if (rhythm == 0){
            str += "\nApplying Shock on ventricular fibrillation";
            str += "\nAudio: Applying Shock on ventricular fibrillation";
        }
        else if (rhythm == 1){
            str += "\nApplying Shock on ventricular tachycardia";
            str += "\nAudio: Applying Shock on ventricular tachycardia";
        }
    }
    str += "\n";
    str += "\nProceed to CPR";
    str += "\nAudio: Proceed to CPR";
    str += "\nContinously give sets of 30 chest compressions and 2 breaths";
    str += "\nAudio: Continously give sets of 30 chest compressions and 2 breaths";
    return str;
}

void AED::setRhythm(int rhythm){
    this->rhythm = rhythm;
}

QString AED::CallEmergency(){

    return "Call for help!";
}

QString AED::OpenAirway(){
    return "Open Airway";
}

QString AED::checkBreathing(){
    return "Check breathing";
}

QString AED::PadCorrection(int padPlacement){

    if(padPlacement == 0){
        return "\nPad Placed Just Right";
    }else if(padPlacement == 1){
        return "\nPad Placed Too Low";
    }else if(padPlacement == 2){
        return "\nPad Placed Too High";
    }
    return "\nError";
}

QString AED::CompressionCorrection(int chestCompression){

    if(chestCompression == 0){
        return "\nKeep pushing the chest of the patient at this rate!";
    }else if(chestCompression == 1){
        return "\nYou're doing it too slow. Try faster";
    }else if(chestCompression == 2){
        return "\nYou're doing it too fast. Try slower";
    }
    return "\nError";
}

int AED::getRhythm(){
    return rhythm;
}

bool AED::getPower(){
    return power;
}

void AED::depleteBattery(){
    if(batteryLevel > 0){
        batteryLevel -= 1;
    }
    else{
        batteryLevel = 0;
        power = false;
    }
}

int AED::getBatteryLevel(){
    return batteryLevel;
}


void AED::changeBattery(){
    batteryLevel = 100;
}

void AED::setPower(bool reset){
    power = reset;
}