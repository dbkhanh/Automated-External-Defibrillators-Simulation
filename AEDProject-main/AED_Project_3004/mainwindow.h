#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QString>
#include <QTimer>
#include <QTime>

#include "AED.h"
#include "FirstAider.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    
    AED* aed;
    FirstAider* fAider;
    int batteryLevel;

    QVector<QString> batteryLevelImages;
    QTimer *batteryTimer;

    void displayConsoleLogs(QString);
    void clearConsoleLogs();
    void delay(int t);



private slots:

    void on_EmergencyButton_clicked();

    void on_ShockButton_clicked();

    void on_RBreathButton_clicked();

    void on_ConsCheck_clicked(bool);

    void on_BreathCheck_clicked(bool);

    void on_HeartRhythm_activated(int);

    void on_PadBox_activated(int);

    void on_ContactCheck_clicked(bool);

    void on_CompressionCheck_activated(int index);

    void on_powerButton_clicked();

    void decreaseBattery();

    void displayBattery(int);

    void on_changeBattery_clicked();

    void on_Remove_Pad_clicked();

    void on_Place_Pad_clicked();
};
#endif // MAINWINDOW_H