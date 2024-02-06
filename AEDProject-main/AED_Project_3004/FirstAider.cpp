#include "FirstAider.h"

FirstAider::FirstAider(): conscious(false), breathing(false), compression(0), pad(0), clear(false) {}
FirstAider::~FirstAider(){}

QString FirstAider::checkConscious(){
    if (this->conscious == true){
        return "FirstAider: Patient is conscious";
    }else{
        return "FirstAider: Patient is unconscious";
    }
}

bool FirstAider::getConscious(){
    return conscious;
}
void FirstAider::setConscious(bool conscious){
    this->conscious = conscious;
}

QString FirstAider::CheckBreath() {
    if (breathing == false){
        return "Firstaider: Patient is abnormally breathing";
    }
    return "Firstaider: Patient is breathing normally";

}

int FirstAider::PadPlacement(){
    return pad;
}

void FirstAider::setPadPlacement(int pad){
    this->pad = pad;
}

bool FirstAider::StandClear(){
    return clear;
}

void FirstAider::setStandClear(bool clear){
    this->clear = clear;
}

int FirstAider::ChestCompression(){
    return compression;
}

void FirstAider::setCompression(int compression){
    this->compression = compression;

}

QString FirstAider::RescueBreath(){
    QString result = "";
    if (compression == 0){
        setConscious(true);
        result += "\nFirstAider: The patient is conscious!";
        return result;
    }
    setConscious(false);
    result += "\nFirstAider: Patient is unconscious!";
    return result;
}

void FirstAider::setBreath(bool breath){
    this->breathing = breath;
}

QString FirstAider::Emergency(){

    return "FirstAider: Somebody help!";
}

QString FirstAider::Airway(){

    return "FirstAider: Let me open the airway as instructed!";
}