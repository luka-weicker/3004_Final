#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "System.h"
#include <QDebug>
#include <QComboBox>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QProgressBar>
#include <QCheckBox>
#include <QTimer>
#include <QPalette>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

        // Checks   (These will return true if there IS a problem)
        bool checkValidProfile();   // Check if selected profile is valid
        bool checkScanned();        // Check if user has at least one scan
        bool checkLowBattery();     // Check if device is in low battery mode
        bool checkDeadBattery();    // Check if device is dead


    private slots:
        // Functionality
        void generateResults();         // Add a new random set of data for selected profile
        void newProfile();              // Make a new  profile
        void deleteProfile();           // delete profile
        void updateCurrentProfile();    // Select a new currently selected user
        void updateBattery();           // Update value of battery
        void updateBatteryColor();      // Update color of battery

        // Printing                     // (Prints here just call the print in System class)
        void printAllResults();         // Print all data for current  user
        void printLastResults();        // Print most recent data for each organ
        void printHealthResults();
        void printOrganResults();       // Print data for current organ
        void printProfiles();           // Print all profiles


    private:
        Ui::MainWindow *ui;
        System system;
        QTimer *timer;
};
#endif // MAINWINDOW_H
