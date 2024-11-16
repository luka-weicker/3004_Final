#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set up button connections
    connect(ui->genButton, &QPushButton::clicked, this, &MainWindow::generateResults);
    connect(ui->printAllButton, &QPushButton::clicked, this, &MainWindow::printAllResults);
    connect(ui->newProfileButton, &QPushButton::clicked, this, &MainWindow::newProfile);
    connect(ui->showProfiles, &QPushButton::clicked, this, &MainWindow::printProfiles);
    connect(ui->printLastButton, &QPushButton::clicked, this, &MainWindow::printLastResults);
    connect(ui->printOrganButton, &QPushButton::clicked, this, &MainWindow::printOrganResults);
    connect(ui->updateProfileButton, &QPushButton::clicked, this, &MainWindow::updateCurrentProfile);
    connect(ui->printAveragesButton, &QPushButton::clicked, this, &MainWindow::printAverageResults);

    qDebug() << "Connected";
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::generateResults() {
    if (this->checkValidProfile()) {return;}

    QPushButton *button = qobject_cast<QPushButton*>(sender());
        if (button) {
            QString buttonText = button->text();
            system.generateResults(system.getSelectedProfileSlot());
            qDebug() << "System scan complete,  data has been stored";
        }
}

void MainWindow::newProfile() {
    QLineEdit* inputTextBox = ui->newProfileInput;
    QString newUserName = inputTextBox->text();

    system.newProfile(newUserName);
}

void MainWindow::updateCurrentProfile(){
    QComboBox* profileSelecctBox = ui->profileSelect;
    int newSlot = profileSelecctBox->currentIndex();

    // Check if selected user is out of range
    if (newSlot>=system.getTotalProfiles()){
        qDebug() << "Selected user is not initialized yet, please create a new user for this slot";
        qDebug() << "Current user did not change";
        return;
    }
    if ((newSlot>=0) && (newSlot<MAX_PROFILES)) {
        system.setSelectedProfileSlot(newSlot);
    }
}

void MainWindow::printAllResults() {
    if (this->checkValidProfile()) {return;}

    qDebug().nospace().noquote() << "\n\n\n - - Here are all of "<< system.getCurrentProfileName() <<"'s results - - ";
    QPushButton *button = qobject_cast<QPushButton*>(sender());
        if (button) {
            QString buttonText = button->text();
            qDebug() << buttonText;
            system.printAllResults(system.getSelectedProfileSlot());
        }
}

void MainWindow::printLastResults(){
    if (this->checkValidProfile()) {return;}

    qDebug().nospace().noquote() << "\n\n\n - - Here are "<< system.getCurrentProfileName() <<"'s most recent results - - ";
    system.printLastResults(system.getSelectedProfileSlot());
}

void MainWindow::printAverageResults(){
    if (this->checkValidProfile()) {return;}

    qDebug().nospace().noquote() << "\n\n\n - - Here are "<< system.getCurrentProfileName() <<"'s average lifetime results - - ";
    system.printAverageResults(system.getSelectedProfileSlot());
}



void MainWindow::printProfiles() {
    qDebug() << "\n\n\n - - Here are all of your profiles - - ";
    system.printProfiles();
}

void MainWindow::printOrganResults(){
    if (this->checkValidProfile()) {return;}

    qDebug().nospace().noquote() << "\n\n\n - - Here are all of "<< system.getCurrentProfileName() <<"'s results for the selected organ - - ";
    QComboBox* organSelect = ui->organSelect;
    QString organName = organSelect->currentText();

    system.printOrganResults(system.getSelectedProfileSlot(), organName);
}

// Will return true if position is NOT valid
bool MainWindow::checkValidProfile(){
    if (system.getSelectedProfileSlot()>=system.getTotalProfiles()){
        qDebug() << "Cannot perform action. Current user is not initalized.";
        return true;
    }
    return false;
}

