#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->organSelect->addItems({"Heart", "Lungs", "Liver", "Kidney", "Spleen", "Stomach",
    "Large Intestine", "Small Intestine", "Bladder", "Gallbladder", "Pancreas", "Adrenal Glands"});

    // QGraphics View setup
    auto *scene = new QGraphicsScene(this);
    ui->resultsGraphicsView->setScene(scene);

    auto *recs_scene = new QGraphicsScene(this);
    ui->recommendationsGraphicsView->setScene(recs_scene);
    int yOffset = 0;
    const int lineSpacing = 20;
    QGraphicsTextItem *recs_title = recs_scene->addText("Once a specialist is available, recommendations will be posted here.");
    recs_title->setDefaultTextColor(Qt::black);
    recs_title->setTextWidth(ui->recommendationsGraphicsView->width());
    recs_title->setPos(0, yOffset);



    // Loading profiles from JSON file
    QVector<Profile *> profiles = system.getProfiles();
    for (Profile *profile : profiles) {
        ui->profileSelect->addItem(profile->getName());
    }

    if (!profiles.isEmpty()) {
        ui->profileSelect->setCurrentIndex(system.getSelectedProfileSlot());
    }

    // Timer and battery setup
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
    connect(ui->printHealthResultsButton, &QPushButton::clicked, this, &MainWindow::printHealthResults);

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
            qDebug() << "System scan complete for: " << system.getCurrentProfileName() << ", data has been stored";
        }
}

void MainWindow::newProfile() {
    if (this->checkDeadBattery()) { return; }
    if (this->checkLowBattery()) { return; }

    // Adding new profile from text field on Qt window
    QLineEdit *inputTextBox = ui->newProfileInput;
    QString newUserName = inputTextBox->text();
    if (!system.newProfile(newUserName)) { return; }

    // Adding to combo box
    ui->profileSelect->addItem(newUserName);
    ui->profileSelect->setCurrentIndex(system.getTotalProfiles() - 1);


    updateCurrentProfile();
    ui->newProfileInput->clear();
}

void MainWindow::deleteProfile()
{
    if (this->checkDeadBattery()) { return; }
    if (this->checkValidProfile()) { return; }

    // Getting profile slot
    int currentSlot = ui->profileSelect->currentIndex();
    QString profileName = system.getProfiles().at(currentSlot)->getName();

    if (system.deleteProfile(currentSlot)) {
        qDebug() << "Profile: " << profileName << "deleted.";

        // Update the combobox
        ui->profileSelect->removeItem(currentSlot);
        if (ui->profileSelect->count() > 0) {
            ui->profileSelect->setCurrentIndex(0);
        } else {
            ui->profileSelect->clear();
        }

        updateCurrentProfile();
    } else {
        qDebug() << "Profile could not be deleted.";
    }

    QGraphicsScene *scene = ui->resultsGraphicsView->scene();
    scene->clear();
}


void MainWindow::updateCurrentProfile()
{
    QComboBox *profileSelectBox = ui->profileSelect;
    int newSlot = profileSelectBox->currentIndex();

    if (newSlot < 0 || profileSelectBox->count() == 0) {
        system.setSelectedProfileSlot(-1); // Invalid choice
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

void MainWindow::printHealthResults()
{
    if (this->checkDeadBattery()) { return; }
    if (this->checkValidProfile()) { return; }
    if (this->checkScanned()) { return; }

    int selectedProfileSlot = system.getSelectedProfileSlot();

    // Analyze health results before putting onto screen (filling profile values)
    system.analyzeHealthResults(selectedProfileSlot);
    QGraphicsScene *scene = ui->resultsGraphicsView->scene();

    if (!scene) {
        qDebug() << "Graphics scene is not initialized.";
        return;
    }

    scene->clear();

    // Obtaining values from helper functions
    QVector<QPair<QString, int>> healthResults = {
        {"Energy", system.getProfileEnergy(selectedProfileSlot)},
        {"Immune System", system.getProfileIS(selectedProfileSlot)},
        {"Metabolism", system.getProfileMetabolism(selectedProfileSlot)},
        {"Psycho-Emotional", system.getProfilePsycho(selectedProfileSlot)},
        {"Musculoskeletal", system.getProfileMusc(selectedProfileSlot)}
    };

    int yOffset = 0;
    const int lineSpacing = 20;

    for (const auto &result : healthResults) {
        QString label = result.first;
        int value = result.second;

        // Determining which colour to use
        QColor color;
        if (value < BELOW_HEALTHY) {
            color = Qt::blue;
        } else if (value > ABOVE_HEALTHY) {
            color = Qt::red;
        } else {
            color = Qt::green;
        }

        QString text = QString("%1: %2%").arg(label).arg(value);
        QGraphicsTextItem *textItem = scene->addText(text);
        textItem->setDefaultTextColor(color);
        textItem->setPos(0, yOffset);

        yOffset += lineSpacing;
    }

    // Legend
    yOffset += lineSpacing;
    QGraphicsTextItem *legendTitle = scene->addText("Legend:");
    legendTitle->setDefaultTextColor(Qt::black);
    legendTitle->setPos(0, yOffset);

    yOffset += lineSpacing;

    QGraphicsTextItem *blueLegend = scene->addText("Blue: Below Normal");
    blueLegend->setDefaultTextColor(Qt::blue);
    blueLegend->setPos(0, yOffset);

    yOffset += lineSpacing;

    QGraphicsTextItem *greenLegend = scene->addText("Green: Normal");
    greenLegend->setDefaultTextColor(Qt::green);
    greenLegend->setPos(0, yOffset);

    yOffset += lineSpacing;

    QGraphicsTextItem *redLegend = scene->addText("Red: Above Normal");
    redLegend->setDefaultTextColor(Qt::red);
    redLegend->setPos(0, yOffset);
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
bool MainWindow::checkValidProfile()
{
    int selectedSlot = system.getSelectedProfileSlot();

    if (selectedSlot < 0 || selectedSlot >= system.getTotalProfiles()) {
        qDebug() << "No profile is currently selected. Please select a profile to proceed.";
        return true; // Indicates an issue (no profile selected)
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


