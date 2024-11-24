#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->organSelect->addItems({"Heart", "Lungs", "Liver", "Kidney", "Spleen", "Stomach",
    "Large Intestine", "Small Intestine", "Bladder", "Gallbladder", "Pancreas", "Adrenal Glands"});

    // Load profiles from System and populate the profileSelect combobox
    QVector<Profile *> profiles = system.getProfiles();
    for (Profile *profile : profiles) {
        ui->profileSelect->addItem(profile->getName());
    }

    // Set the current index if profiles exist
    if (!profiles.isEmpty()) {
        ui->profileSelect->setCurrentIndex(system.getSelectedProfileSlot());
    }

    // Connect timer and set up battery
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateBattery);
    timer->start(1000);
    connect(ui->chargingBox, &QCheckBox::stateChanged, this, &MainWindow::updateBatteryColor);
    updateBatteryColor();

    // Set up button connections
    connect(ui->genButton, &QPushButton::clicked, this, &MainWindow::generateResults);
    connect(ui->printAllButton, &QPushButton::clicked, this, &MainWindow::printAllResults);
    connect(ui->newProfileButton, &QPushButton::clicked, this, &MainWindow::newProfile);
    connect(ui->deleteProfileButton, &QPushButton::clicked, this, &MainWindow::deleteProfile);
    connect(ui->showProfiles, &QPushButton::clicked, this, &MainWindow::printProfiles);
    connect(ui->printLastButton, &QPushButton::clicked, this, &MainWindow::printLastResults);
    connect(ui->printOrganButton, &QPushButton::clicked, this, &MainWindow::printOrganResults);
    connect(ui->profileSelect, &QComboBox::currentTextChanged, this, &MainWindow::updateCurrentProfile);
    connect(ui->printAveragesButton, &QPushButton::clicked, this, &MainWindow::printAverageResults);

    updateCurrentProfile();

    qDebug() << "Connected";
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::generateResults() {
    if (this->checkDeadBattery()) {return;}
    if (this->checkLowBattery()) {return;}
    if (this->checkValidProfile()) {return;}


    QPushButton *button = qobject_cast<QPushButton*>(sender());
        if (button) {
            QString buttonText = button->text();
            system.generateResults(system.getSelectedProfileSlot());
            qDebug() << "System scan complete for: " << system.getCurrentProfileName() << ",  data has been stored";
        }
}

void MainWindow::newProfile() {
    if (this->checkDeadBattery()) { return; }
    if (this->checkLowBattery()) { return; }

    // Add new profile
    QLineEdit *inputTextBox = ui->newProfileInput;
    QString newUserName = inputTextBox->text();
    if (!system.newProfile(newUserName)) { return; } // Return if profile not added properly

    // Add to combo box
    ui->profileSelect->addItem(newUserName);
    ui->profileSelect->setCurrentIndex(system.getTotalProfiles() - 1);

    // Update current selected profile
    updateCurrentProfile();

    // Clear name box
    ui->newProfileInput->clear();
}

void MainWindow::deleteProfile()
{
    if (this->checkDeadBattery()) { return; }
    if (this->checkValidProfile()) { return; }

    int currentSlot = ui->profileSelect->currentIndex();
    QString profileName = system.getProfiles().at(currentSlot)->getName(); // Get the name before deletion

    if (system.deleteProfile(currentSlot)) {
        qDebug() << "Profile: " << profileName << "deleted.";

        // Update the combobox
        ui->profileSelect->removeItem(currentSlot);

        // Set the combobox to the first item if profiles exist, otherwise clear selection
        if (ui->profileSelect->count() > 0) {
            ui->profileSelect->setCurrentIndex(0);
        } else {
            ui->profileSelect->clear();
        }

        updateCurrentProfile();
    } else {
        qDebug() << "Profile could not be deleted.";
    }
}


void MainWindow::updateCurrentProfile()
{
    QComboBox *profileSelectBox = ui->profileSelect;
    int newSlot = profileSelectBox->currentIndex();

    // Check if the combobox is empty
    if (newSlot < 0 || profileSelectBox->count() == 0) {
        system.setSelectedProfileSlot(-1); // No valid selection
        qDebug() << "No profile selected.";
        return;
    }

    system.setSelectedProfileSlot(newSlot);
}



void MainWindow::updateBattery(){
    int currentBattery = ui->batteryBar->value();
    if (ui->chargingBox->isChecked()) {
        // Charging
        if (currentBattery < 100) {
            ui->batteryBar->setValue(currentBattery + 1);
        }
    } else {
        // Draining
        if (currentBattery > 0) {
            ui->batteryBar->setValue(currentBattery - 1);
        }
    }
    updateBatteryColor();
}

void MainWindow::updateBatteryColor(){
    QPalette palette = ui->chargingBox->palette();
    if (ui->chargingBox->isChecked()) {
        // Charging - Green
        palette.setColor(QPalette::Highlight, Qt::green);
    }
    else if(ui->batteryBar->value()<=LOW_BATTERY){
        // Low battery - Yellow
        palette.setColor(QPalette::Highlight, Qt::yellow);
    }
    else if(ui->batteryBar->value()<=5){
        // Dead battery - Red
        palette.setColor(QPalette::Highlight, Qt::red);
    }
    else {
        // Draining - Gray
        palette.setColor(QPalette::Highlight, Qt::gray);
    }
    ui->batteryBar->setPalette(palette);

}

void MainWindow::printAllResults() {
    if (this->checkDeadBattery()) {return;}
    if (this->checkValidProfile()) {return;}
    if (this->checkScanned()) {return;}

    qDebug().nospace().noquote() << "\n\n\n - - Here are all of "<< system.getCurrentProfileName() <<"'s results - - ";
    QPushButton *button = qobject_cast<QPushButton*>(sender());
        if (button) {
            QString buttonText = button->text();
            qDebug() << buttonText;
            system.printAllResults(system.getSelectedProfileSlot());
        }
}

void MainWindow::printLastResults(){
    if (this->checkDeadBattery()) {return;}
    if (this->checkValidProfile()) {return;}
    if (this->checkScanned()) {return;}

    qDebug().nospace().noquote() << "\n\n\n - - Here are "<< system.getCurrentProfileName() <<"'s most recent results - - ";
    system.printLastResults(system.getSelectedProfileSlot());
}

void MainWindow::printAverageResults(){
    if (this->checkDeadBattery()) {return;}
    if (this->checkValidProfile()) {return;}
    if (this->checkScanned()) {return;}

    qDebug().nospace().noquote() << "\n\n\n - - Here are "<< system.getCurrentProfileName() <<"'s average lifetime results - - ";
    system.printAverageResults(system.getSelectedProfileSlot());
}


void MainWindow::printProfiles() {
    qDebug() << "\n\n\n - - Here are all of your profiles - - ";
    system.printProfiles();
}

void MainWindow::printOrganResults(){
    if (this->checkDeadBattery()) {return;}
    if (this->checkValidProfile()) {return;}
    if (this->checkScanned()) {return;}

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

// Will return true if there are NO scans
bool MainWindow::checkScanned(){
    if(system.getSelectedProfileTotalScans()<=0){
        qDebug() << "The  current user does not currently have any scans.";
        return true;
    }
    return false;
}

// Will return true if device IS in low battery
bool MainWindow::checkLowBattery(){
    if(ui->batteryBar->value() <= LOW_BATTERY){
        qDebug() << "The device battery is too low to perform this action, please charge.";
        return true;
    }
    return false;
}

// Will return true if device IS dead
bool MainWindow::checkDeadBattery(){
    if(ui->batteryBar->value() <= DEAD_BATTERY){
        qDebug() << "The device is dead, please charge.";
        return true;
    }
    return false;
}


