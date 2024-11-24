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
#include "defs.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

        // Checks (These will return true if there IS a problem)
        bool checkValidProfile();
        bool checkScanned();
        bool checkLowBattery();
        bool checkDeadBattery();


    private slots:
        // Functionality
        void generateResults();
        void newProfile();
        void deleteProfile();
        void updateCurrentProfile();
        void updateBattery();
        void updateBatteryColor();

        // Printing
        void printAllResults();
        void printLastResults();
        void printHealthResults();
        void printOrganResults();
        void printProfiles();


    private:
        Ui::MainWindow *ui;
        System system;
        QTimer *timer;
};
#endif
