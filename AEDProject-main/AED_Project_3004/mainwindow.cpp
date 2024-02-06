#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), aed(new AED()), fAider(new FirstAider())
{
    ui->setupUi(this);
    ui->Picture->setStyleSheet("background-color: red;");
    ui->label_8->setStyleSheet("background-color: #a2f5bf; border: 2px solid #70db70; border-radius: 15px;");
    ui->powerButton->setStyleSheet("background-color: #ffcc00; border: 2px solid #e5e5e5; border-radius: 5px; padding: 5px;");
    ui->label->setStyleSheet("background-color: yellow");

    batteryLevelImages.append(":/Images/Images/battery_100.png");
    batteryLevelImages.append(":/Images/battery_80.png");
    batteryLevelImages.append(":/Images/battery_50.png");
    batteryLevelImages.append(":/Images/battery_30.png");
    batteryLevelImages.append(":/Images/battery_5.png");
    batteryLevelImages.append(":/Images/battery_0.png");

    QPixmap img1(":/Images/Images/1.png");
    ui->label_2->setPixmap(img1.scaled(ui->label_2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QPixmap img2(":/Images/Images/2.png");
    ui->label_3->setPixmap(img2.scaled(ui->label_3->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QPixmap img3(":/Images/Images/3.png");
    ui->label_4->setPixmap(img3.scaled(ui->label_4->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QPixmap img4(":/Images/Images/4.png");
    ui->label_5->setPixmap(img4.scaled(ui->label_5->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QPixmap img5(":/Images/Images/5.png");
    ui->label_6->setPixmap(img5.scaled(ui->label_6->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QPixmap img6(":/Images/Images/6.png");
    ui->label_7->setPixmap(img6.scaled(ui->label_7->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QPixmap img7(":/Images/Images/7.png");
    ui->label_9->setPixmap(img7.scaled(ui->label_9->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QPixmap img8(":/Images/Images/8.png");
    ui->label_19->setPixmap(img8.scaled(ui->label_19->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));



    batteryTimer = new QTimer(this);
    batteryTimer->setInterval(5000);
    connect(batteryTimer, SIGNAL(timeout()), this, SLOT(decreaseBattery()));
    batteryTimer->start();


}

MainWindow::~MainWindow()
{
    delete ui;
    delete aed;
    delete fAider;
}

void MainWindow::displayConsoleLogs(QString message) { ui->ConsoleLogs->append(message); }

void MainWindow::on_ConsButton_clicked()
{
    displayConsoleLogs(fAider->checkConscious());
}

void MainWindow::on_EmergencyButton_clicked()
{
    displayConsoleLogs(fAider->Emergency());
}

void MainWindow::on_AirButton_clicked()
{
    displayConsoleLogs(fAider->Airway());
}

void MainWindow::on_BreathButton_clicked()
{
    displayConsoleLogs(fAider->CheckBreath());
}

void MainWindow::on_ShockButton_clicked()
{
    if(aed->getShockable() == false){
        return ;
    }


    if (fAider->StandClear() == true)
    {
        displayConsoleLogs(aed->ShockProceed(true));
        ui->ShockButton->setStyleSheet("");
        aed->setShockable(false);
        ui->cprLabel->setStyleSheet("background-color:rgb(51, 209, 122)");

    }
    else
    {
        displayConsoleLogs(aed->ShockProceed(false));
        return;
    }

    QString url = "null";
    if(aed->getRhythm() == 0){
        url = ":/Images/Images/vf.png";
    }else if(aed->getRhythm() == 1){
        url = ":/Images/Images/vt.png";
    }else if(aed->getRhythm() == 2){
        url = ":/Images/Images/flat.png";
    }else if(aed->getRhythm() == 3){
        url = ":/Images/Images/norm.png";
    }

    QPixmap img(url);
    ui->Picture->setPixmap(img.scaled(ui->Picture->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void MainWindow::on_RBreathButton_clicked()
{
    if(aed->getRhythm() == 2){
        return;
    }


    //So We press the button, and we first check if the rhythm was shockable
    //CPR will send a message asking the user do 2 breaths and 30 compressions
    //Delay for a few seconds
    //The compressions is too fast/too slow//just right, keep doing it or change
    //delay by a few seconds
    //We use the getCompression-> and then check if the compression is good or bad
    //delay once more
    //Checks the compression, if its just right, patient is conscious, if not, unconsicous, and it asks you to restart the cpr
    //
    displayConsoleLogs(aed->CompressionCorrection(fAider->ChestCompression()));
    displayConsoleLogs(fAider->RescueBreath());
    if (fAider->getConscious() == true)
    {
        ui->ConsCheck->setCheckState(Qt::Checked);
        ui->BreathCheck->setCheckState(Qt::Checked);
        ui->HeartRhythm->setCurrentIndex(3);
        aed->setRhythm(3);
        ui->cprLabel->setStyleSheet("");
        if (aed->getPower() == true && aed->getPadPlaced() == true){
            QString url = ":/Images/Images/norm.png";
            QPixmap img(url);
            ui->Picture->setPixmap(img.scaled(ui->Picture->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
        displayConsoleLogs("Please remove pads");
        if (aed->getPadPlaced() == true){
            aed->setPadPlaced(false);
        }

    }
    else if(fAider->getConscious() == false)
    {
        ui->ConsCheck->setCheckState(Qt::Unchecked);
        ui->BreathCheck->setCheckState(Qt::Unchecked);
    }    
}

void MainWindow::on_ConsCheck_clicked(bool checked)
{
    fAider->setConscious(checked);
}

void MainWindow::on_BreathCheck_clicked(bool checked)
{
    fAider->setBreath(checked);
}

void MainWindow::on_HeartRhythm_activated(int index)
{
    aed->setRhythm(index);
    if(index == 2){
        ui->ConsCheck->setCheckState(Qt::Unchecked);
        ui->BreathCheck->setCheckState(Qt::Unchecked);    }
}

void MainWindow::on_PadBox_activated(int index)
{
    fAider->setPadPlacement(index);
}

void MainWindow::on_ContactCheck_clicked(bool checked)
{
    fAider->setStandClear(checked);
}

void MainWindow::on_CompressionCheck_activated(int index)
{
    fAider->setCompression(index);
    int compression;
    compression = fAider->ChestCompression();
    displayConsoleLogs(aed->CompressionCorrection(compression));

}


void MainWindow::on_powerButton_clicked()
{


    displayConsoleLogs(aed->powerOn());


    if(aed->getPower() == true){
        ui->powerButton->setStyleSheet("background-color:green");
        batteryLevel = aed->getBatteryLevel();
        displayBattery(batteryLevel);

        if(aed->getPadPlaced() == false){


            if(aed->getPower() == true){
                displayConsoleLogs("\nAudio: Check Consciousness");
                displayConsoleLogs(aed->checkConsciousness());
                ui->consciousLabel->setStyleSheet("background-color:rgb(51, 209, 122)");
                delay(5);
                ui->consciousLabel->setStyleSheet("");
            }

            if(aed->getPower() == true){
                displayConsoleLogs("\nAudio: Call for help");
                displayConsoleLogs(aed->CallEmergency());
                ui->emergencyLabel->setStyleSheet("background-color:rgb(51, 209, 122)");
                delay(5);
                ui->emergencyLabel->setStyleSheet("");
            }

            if(aed->getPower() == true){
                displayConsoleLogs("\nAudio: Open Airway");
                displayConsoleLogs(aed->OpenAirway());
                ui->airwayLabel->setStyleSheet("background-color:rgb(51, 209, 122)");
                delay(5);
                ui->airwayLabel->setStyleSheet("");
            }

            if(aed->getPower() == true){
                displayConsoleLogs("\nAudio: Check Breathing");
                displayConsoleLogs(aed->checkBreathing());
                ui->breathLabel->setStyleSheet("background-color:rgb(51, 209, 122)");
                delay(5);
                ui->breathLabel->setStyleSheet("");
            }

            if(aed->getPower() == true){
                displayConsoleLogs("\nAudio: Place Pad on Patient's chest");
                displayConsoleLogs("Place Electropad on Patient's chest");
                ui->padLabel->setStyleSheet("background-color:rgb(51, 209, 122)");
            }
        }
        else{
            on_Place_Pad_clicked();
        }
    }

    else{
        ui->powerButton->setStyleSheet("");
        ui->batteryLevel->setText("");
        QPixmap noBatteryImg("");
        ui->batteryIcon->setPixmap(noBatteryImg);
        ui->Picture->setPixmap(noBatteryImg);
        ui->powerButton->setStyleSheet("background-color: #ffcc00; border: 2px solid #e5e5e5; border-radius: 5px; padding: 5px;");
        ui->consciousLabel->setStyleSheet("");
        ui->emergencyLabel->setStyleSheet("");
        ui->airwayLabel->setStyleSheet("");
        ui->breathLabel->setStyleSheet("");
        ui->padLabel->setStyleSheet("");
        ui->heartAnalysisLabel->setStyleSheet("");
        ui->ShockButton->setStyleSheet("");

    }
}


void MainWindow::decreaseBattery(){
    if(aed->getPower()==true){
        batteryLevel = aed->getBatteryLevel();
        displayBattery(batteryLevel);
        aed->depleteBattery();
    }
}

void MainWindow::displayBattery(int batteryLevel){
    ui->batteryLevel->setText(QString::fromStdString(std::to_string(batteryLevel) + " %"));
    if(100 >= batteryLevel && batteryLevel >= 90){
        QPixmap battery100img(":/Images/Images/battery_100.png");
        ui->batteryIcon->setPixmap(battery100img.scaled(ui->batteryIcon->size(),Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    else if(99>= batteryLevel && batteryLevel >= 65){
        QPixmap battery80img(":/Images/Images/battery_80.png");
        ui->batteryIcon->setPixmap(battery80img.scaled(ui->batteryIcon->size(),Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    else if(65>= batteryLevel && batteryLevel >= 30){
        QPixmap battery50img(":/Images/Images/battery_50.png");
        ui->batteryIcon->setPixmap(battery50img.scaled(ui->batteryIcon->size(),Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    else if(30>=batteryLevel && batteryLevel >= 5){
        QPixmap battery30img(":/Images/Images/battery_30.png");
        ui->batteryIcon->setPixmap(battery30img.scaled(ui->batteryIcon->size(),Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    else if(5>= batteryLevel && batteryLevel >= 1){
        QPixmap battery5img(":/Images/Images/battery_5.png");
        ui->batteryIcon->setPixmap(battery5img.scaled(ui->batteryIcon->size(),Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    if(batteryLevel == 30){
        displayConsoleLogs("Warning: AED Battery Level Dropped Below 30%!");
    }
    if(batteryLevel == 5){
        displayConsoleLogs("Warning: AED Battery Level Dropped Below 5%!");
    }

    if(batteryLevel == 0 && aed->getPower() == true){
        displayConsoleLogs("Warning: AED Battery Level 0%. Turning off...");
        ui->powerButton->setStyleSheet("");
        ui->batteryLevel->setText("");
        QPixmap noBatteryImg("");
        ui->batteryIcon->setPixmap(noBatteryImg);
        ui->Picture->setPixmap(noBatteryImg);
        ui->powerButton->setStyleSheet("background-color: #ffcc00; border: 2px solid #e5e5e5; border-radius: 5px; padding: 5px;");
    }

    if(batteryLevel == 0 && aed->getPower() == false){
        ui->powerButton->setStyleSheet("");
        ui->batteryLevel->setText("");
        QPixmap noBatteryImg("");
        ui->batteryIcon->setPixmap(noBatteryImg);
        ui->Picture->setPixmap(noBatteryImg);
        ui->powerButton->setStyleSheet("background-color: #ffcc00; border: 2px solid #e5e5e5; border-radius: 5px; padding: 5px;");
    }

}


void MainWindow::on_changeBattery_clicked()
{
    aed->changeBattery();
    clearConsoleLogs();
    on_powerButton_clicked();

}

void MainWindow::delay(int t){
    QTime dieTime = QTime::currentTime().addSecs(t);
        while (QTime::currentTime() < dieTime){
            QCoreApplication::processEvents(QEventLoop::AllEvents,100);
        }
}

void MainWindow::on_Remove_Pad_clicked()
{
    displayConsoleLogs("Pads removed");
    aed->setPadPlaced(false);

}


void MainWindow::on_Place_Pad_clicked()
{

    displayConsoleLogs("Pad Placed");
    aed->setPadPlaced(true);

   if(aed->getPower()== false){
       return;
   }


   if(fAider->PadPlacement() == 0){
       displayConsoleLogs(aed->DetectRhythm(aed->getRhythm()));
       ui->padLabel->setStyleSheet("");
       ui->heartAnalysisLabel->setStyleSheet("background-color:rgb(51, 209, 122)");
       delay(5);

   }else{
       if(aed->getPower() == 1){
           displayConsoleLogs("\nWarning: Cannot analyze as Pads are misplaced!");
           displayConsoleLogs("Warning: To continue set Pad Placement to Just Right!");
       }else{
           displayConsoleLogs(aed->DetectRhythm(aed->getRhythm()));
       }
   }
   ui->heartAnalysisLabel->setStyleSheet("");
   QString url = "null";
   if(aed->getPower() == 1 && fAider->PadPlacement() == 0){
       if(aed->getRhythm() == 0){
           ui->ShockButton->setStyleSheet("background-color:rgb(51, 209, 122)");
           aed->setShockable(true);
           url = ":/Images/Images/vf.png";
       }else if(aed->getRhythm() == 1){
           ui->ShockButton->setStyleSheet("background-color:rgb(51, 209, 122)");
           aed->setShockable(true);
           url = ":/Images/Images/vt.png";
       }else if(aed->getRhythm() == 2){
           url = ":/Images/Images/flat.png";
       }else if(aed->getRhythm() == 3){
           url = ":/Images/Images/norm.png";
       }
       QPixmap img(url);
       ui->Picture->setPixmap(img.scaled(ui->Picture->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
   }
}

