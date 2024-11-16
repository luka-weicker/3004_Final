#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "System.h"
#include <QDebug>
#include <QComboBox>
#include <QLineEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private slots:
        // Functionality
        void generateResults();         // Add a new random set of data for selected profile
        void newProfile();              // Make a new  profile
        void updateCurrentProfile();    // Select a new currently selected user

        // Printing                     // (Prints here just call the print in System class)
        void printAllResults();         // Print all data for current  user
        void printLastResults();        // Print most recent data for each organ
        void printAverageResults();
        void printOrganResults();       // Print data for current organ
        void printProfiles();           // Print all profiles


    private:
        Ui::MainWindow *ui;
        System system;
};
#endif // MAINWINDOW_H
