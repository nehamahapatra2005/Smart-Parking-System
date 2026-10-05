#include "MainWindow.h"
#include "ThemeToggle.h"
#include "../include/ParkingLot.h"
#include "../include/Vehicle.h"
#include "../include/Billing.h"
#include <QComboBox>
#include <QDialog>
#include <QFormLayout>
#include <QFrame>
#include <QGraphicsOpacityEffect>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QPropertyAnimation>
#include <QScrollArea>
#include <QSignalBlocker>
#include <QStackedWidget>
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <memory>

// ============================================================
// Constructor
// ============================================================
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      themeSwitch(nullptr),
      parkingLot(new ParkingLot(5)),
      totalNumberLabel(nullptr),
      availableNumberLabel(nullptr),
      occupiedNumberLabel(nullptr),
      activityText(nullptr) {
    setWindowTitle("Smart Parking System");
    resize(1200, 750);
    setMinimumSize(1000, 650);
    // --------------------------------------------------------
    // Main central widget
    // --------------------------------------------------------
    QWidget* central = new QWidget(this);
    setCentralWidget(central);
    QHBoxLayout* mainLayout = new QHBoxLayout(central);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    // ========================================================
    // LEFT SIDEBAR
    // ========================================================
    QFrame* sidebar = new QFrame();
    sidebar->setFixedWidth(190);
    sidebar->setObjectName("sidebar");
    QVBoxLayout* sidebarLayout = new QVBoxLayout(sidebar);
    sidebarLayout->setContentsMargins(18, 25, 18, 20);
    sidebarLayout->setSpacing(12);
    QLabel* logoTitle = new QLabel("PARKING");
    logoTitle->setObjectName("logoTitle");
    QLabel* logoSubtitle = new QLabel("MANAGEMENT SYSTEM");
    logoSubtitle->setObjectName("logoSubtitle");
    sidebarLayout->addWidget(logoTitle);
    sidebarLayout->addWidget(logoSubtitle);
    sidebarLayout->addSpacing(25);
    QLabel* menuTitle = new QLabel("MAIN MENU");
    menuTitle->setObjectName("sectionTitle");
    sidebarLayout->addWidget(menuTitle);
    QPushButton* dashboardButton = new QPushButton("Dashboard");
    dashboardButton->setObjectName("menuButton");
    dashboardButton->setProperty("active", true);
    QPushButton* slotsButton = new QPushButton("Parking Slots");
    slotsButton->setObjectName("menuButton");
    QPushButton* vehiclesButton = new QPushButton("Vehicles");
    vehiclesButton->setObjectName("menuButton");
    QPushButton* billingButton = new QPushButton("Billing");
    billingButton->setObjectName("menuButton");
    sidebarLayout->addWidget(dashboardButton);
    sidebarLayout->addWidget(slotsButton);
    sidebarLayout->addWidget(vehiclesButton);
    sidebarLayout->addWidget(billingButton);
    sidebarLayout->addSpacing(25);
    QLabel* systemTitle = new QLabel("SYSTEM");
    systemTitle->setObjectName("sectionTitle");
    sidebarLayout->addWidget(systemTitle);
    QPushButton* settingsButton = new QPushButton("Settings");
    settingsButton->setObjectName("menuButton");
    sidebarLayout->addWidget(settingsButton);
    // --------------------------------------------------------
    // Dark mode toggle
    // --------------------------------------------------------
    QHBoxLayout* themeLayout = new QHBoxLayout();
    themeLayout->setContentsMargins(18, 2, 18, 2);
    themeLayout->setSpacing(8);
    QLabel* darkModeLabel = new QLabel("Dark Mode");
    darkModeLabel->setObjectName("darkModeLabel");
    themeSwitch = new ThemeToggle();
    themeSwitch->setFixedSize(48, 24);
    themeSwitch->setChecked(true);
    themeLayout->addWidget(darkModeLabel);
    themeLayout->addStretch();
    themeLayout->addWidget(themeSwitch);
    sidebarLayout->addLayout(themeLayout);
    sidebarLayout->addStretch();
    QHBoxLayout* onlineLayout = new QHBoxLayout();
    QLabel* onlineDot = new QLabel("●");
    onlineDot->setObjectName("onlineDot");
    QLabel* onlineText = new QLabel("System Online");
    onlineText->setObjectName("onlineText");
    onlineLayout->addWidget(onlineDot);
    onlineLayout->addWidget(onlineText);
    onlineLayout->addStretch();
    sidebarLayout->addLayout(onlineLayout);
    mainLayout->addWidget(sidebar);
    // ========================================================
    // MAIN CONTENT
    // ========================================================
    QWidget* content = new QWidget();
    content->setObjectName("content");
    QVBoxLayout* outerContentLayout = new QVBoxLayout(content);
    outerContentLayout->setContentsMargins(0, 0, 0, 0);
    outerContentLayout->setSpacing(0);
    QStackedWidget* pageStack = new QStackedWidget();
    outerContentLayout->addWidget(pageStack);
    mainLayout->addWidget(content);

    // The dashboard is the first page shown when the application starts.
    QWidget* dashboardPage = new QWidget();
    QVBoxLayout* contentLayout = new QVBoxLayout(dashboardPage);
    contentLayout->setContentsMargins(30, 25, 30, 25);
    contentLayout->setSpacing(20);
    // --------------------------------------------------------
    // Header
    // --------------------------------------------------------
    QHBoxLayout* headerLayout = new QHBoxLayout();
    QVBoxLayout* titleLayout = new QVBoxLayout();
    titleLayout->setSpacing(2);
    QLabel* dashboardTitle = new QLabel("Dashboard");
    dashboardTitle->setObjectName("dashboardTitle");
    QLabel* dashboardSubtitle =
        new QLabel("Overview of your parking facility");
    dashboardSubtitle->setObjectName("dashboardSubtitle");
    titleLayout->addWidget(dashboardTitle);
    titleLayout->addWidget(dashboardSubtitle);
    headerLayout->addLayout(titleLayout);
    headerLayout->addStretch();
    QLabel* smartParkingLabel = new QLabel("SMART PARKING");
    smartParkingLabel->setObjectName("smartParkingLabel");
    headerLayout->addWidget(smartParkingLabel);
    contentLayout->addLayout(headerLayout);
    // ========================================================
    // SUMMARY CARDS
    // ========================================================
    QHBoxLayout* summaryLayout = new QHBoxLayout();
    summaryLayout->setSpacing(15);
    // Total
    QFrame* totalCard = new QFrame();
    totalCard->setObjectName("summaryCard");
    QHBoxLayout* totalLayout = new QHBoxLayout(totalCard);
    QLabel* totalIcon = new QLabel("P");
    totalIcon->setObjectName("blueIcon");
    totalNumberLabel = new QLabel("5");
    totalNumberLabel->setObjectName("summaryNumber");
    QLabel* totalText = new QLabel("TOTAL\nSLOTS");
    totalText->setObjectName("summaryText");
    totalLayout->addWidget(totalIcon);
    totalLayout->addWidget(totalNumberLabel);
    QVBoxLayout* totalTextLayout = new QVBoxLayout();
    totalTextLayout->addStretch();
    totalTextLayout->addWidget(totalText);
    totalTextLayout->addStretch();
    totalLayout->addLayout(totalTextLayout);
    totalLayout->addStretch();
    // Available
    QFrame* availableCard = new QFrame();
    availableCard->setObjectName("summaryCard");
    QHBoxLayout* availableLayout =
        new QHBoxLayout(availableCard);
    QLabel* availableIcon = new QLabel("A");
    availableIcon->setObjectName("greenIcon");
    availableNumberLabel = new QLabel("5");
    availableNumberLabel->setObjectName("summaryNumber");
    QLabel* availableText = new QLabel("AVAILABLE");
    availableText->setObjectName("summaryText");
    availableLayout->addWidget(availableIcon);
    availableLayout->addWidget(availableNumberLabel);
    QVBoxLayout* availableTextLayout = new QVBoxLayout();
    availableTextLayout->addStretch();
    availableTextLayout->addWidget(availableText);
    availableTextLayout->addStretch();
    availableLayout->addLayout(availableTextLayout);
    availableLayout->addStretch();
    // Occupied
    QFrame* occupiedCard = new QFrame();
    occupiedCard->setObjectName("summaryCard");
    QHBoxLayout* occupiedLayout =
        new QHBoxLayout(occupiedCard);
    QLabel* occupiedIcon = new QLabel("O");
    occupiedIcon->setObjectName("redIcon");
    occupiedNumberLabel = new QLabel("0");
    occupiedNumberLabel->setObjectName("summaryNumber");
    QLabel* occupiedText = new QLabel("OCCUPIED");
    occupiedText->setObjectName("summaryText");
    occupiedLayout->addWidget(occupiedIcon);
    occupiedLayout->addWidget(occupiedNumberLabel);
    QVBoxLayout* occupiedTextLayout = new QVBoxLayout();
    occupiedTextLayout->addStretch();
    occupiedTextLayout->addWidget(occupiedText);
    occupiedTextLayout->addStretch();
    occupiedLayout->addLayout(occupiedTextLayout);
    occupiedLayout->addStretch();
    summaryLayout->addWidget(totalCard);
    summaryLayout->addWidget(availableCard);
    summaryLayout->addWidget(occupiedCard);
    contentLayout->addLayout(summaryLayout);
    // ========================================================
    // PARKING SLOTS
    // ========================================================
    QHBoxLayout* parkingTitleLayout = new QHBoxLayout();
    QLabel* parkingTitle = new QLabel("Parking Slots");
    parkingTitle->setObjectName("sectionHeading");
    QLabel* liveStatus = new QLabel("● LIVE STATUS");
    liveStatus->setObjectName("liveStatus");
    parkingTitleLayout->addWidget(parkingTitle);
    parkingTitleLayout->addStretch();
    parkingTitleLayout->addWidget(liveStatus);
    contentLayout->addLayout(parkingTitleLayout);
    QGridLayout* slotGrid = new QGridLayout();
    slotGrid->setSpacing(12);
    for (int i = 0; i < 5; ++i) {
        QFrame* slotCard = new QFrame();
        slotCard->setObjectName("slotCard");
        QVBoxLayout* slotLayout =
            new QVBoxLayout(slotCard);
        slotLayout->setContentsMargins(15, 12, 15, 12);
        slotLayout->setSpacing(5);
        QLabel* slotNumberLabel =
            new QLabel(QString("SLOT %1").arg(i + 1));
        slotNumberLabel->setObjectName("slotNumber");
        QLabel* statusLabel =
            new QLabel("● AVAILABLE");
        statusLabel->setObjectName("availableStatus");
        QLabel* vehicleLabel =
            new QLabel("No vehicle parked");
        vehicleLabel->setObjectName("vehicleText");
        slotLayout->addWidget(slotNumberLabel);
        QHBoxLayout* statusLayout = new QHBoxLayout();
        statusLayout->addStretch();
        statusLayout->addWidget(statusLabel);
        slotLayout->addLayout(statusLayout);
        slotLayout->addStretch();
        slotLayout->addWidget(vehicleLabel);
        slotGrid->addWidget(
            slotCard,
            i / 3,
            i % 3
        );
        slotCards.push_back(slotCard);
        slotStatusLabels.push_back(statusLabel);
        slotVehicleLabels.push_back(vehicleLabel);
    }
    contentLayout->addLayout(slotGrid);
    // ========================================================
    // BOTTOM SECTION
    // ========================================================
    QHBoxLayout* bottomLayout = new QHBoxLayout();
    bottomLayout->setSpacing(20);
    // --------------------------------------------------------
    // Quick actions
    // --------------------------------------------------------
    QVBoxLayout* quickLayout = new QVBoxLayout();
    QLabel* quickTitle = new QLabel("Quick Actions");
    quickTitle->setObjectName("sectionHeading");
    quickLayout->addWidget(quickTitle);
    QHBoxLayout* actionButtons = new QHBoxLayout();
    actionButtons->setSpacing(10);
    QPushButton* parkButton =
        new QPushButton("Park Vehicle");
    parkButton->setObjectName("primaryButton");
    QPushButton* searchButton =
        new QPushButton("Search Vehicle");
    searchButton->setObjectName("secondaryButton");
    actionButtons->addWidget(parkButton);
    actionButtons->addWidget(searchButton);
    quickLayout->addLayout(actionButtons);
    quickLayout->addStretch();
    bottomLayout->addLayout(quickLayout, 2);
    // --------------------------------------------------------
    // Recent activity
    // --------------------------------------------------------
    QFrame* activityCard = new QFrame();
    activityCard->setObjectName("activityCard");
    activityCard->setMinimumWidth(220);
    QVBoxLayout* activityLayout =
        new QVBoxLayout(activityCard);
    QLabel* activityTitle =
        new QLabel("Recent Activity");
    activityTitle->setObjectName("activityTitle");
    activityText =
        new QLabel("No recent parking activity.");
    activityText->setObjectName("activityText");
    activityText->setWordWrap(true);
    activityLayout->addWidget(activityTitle);
    activityLayout->addWidget(activityText);
    activityLayout->addStretch();
    bottomLayout->addWidget(activityCard, 1);
    contentLayout->addLayout(bottomLayout);
    // Add the completed dashboard to the page stack.
    pageStack->addWidget(dashboardPage);

    // ========================================================
    // PARKING SLOTS PAGE
    // ========================================================
    QWidget* slotsPage = new QWidget();
    QVBoxLayout* slotsPageLayout = new QVBoxLayout(slotsPage);
    slotsPageLayout->setContentsMargins(30, 25, 30, 25);
    slotsPageLayout->setSpacing(20);

    QHBoxLayout* slotsHeaderLayout = new QHBoxLayout();
    QVBoxLayout* slotsTitleLayout = new QVBoxLayout();
    slotsTitleLayout->setSpacing(2);

    QLabel* slotsPageTitle = new QLabel("Parking Slots");
    slotsPageTitle->setObjectName("dashboardTitle");
    QLabel* slotsPageSubtitle = new QLabel(
        "Live overview of every parking space");
    slotsPageSubtitle->setObjectName("dashboardSubtitle");

    slotsTitleLayout->addWidget(slotsPageTitle);
    slotsTitleLayout->addWidget(slotsPageSubtitle);
    slotsHeaderLayout->addLayout(slotsTitleLayout);
    slotsHeaderLayout->addStretch();

    QPushButton* slotsRefreshButton = new QPushButton("Refresh");
    slotsRefreshButton->setObjectName("secondaryButton");
    slotsHeaderLayout->addWidget(slotsRefreshButton);
    slotsPageLayout->addLayout(slotsHeaderLayout);

    QHBoxLayout* slotsSummaryLayout = new QHBoxLayout();
    slotsSummaryLayout->setSpacing(15);

    QFrame* slotsTotalCard = new QFrame();
    slotsTotalCard->setObjectName("summaryCard");
    QHBoxLayout* slotsTotalLayout = new QHBoxLayout(slotsTotalCard);
    QLabel* slotsTotalIcon = new QLabel("P");
    slotsTotalIcon->setObjectName("blueIcon");
    QLabel* slotsTotalNumber = new QLabel("5");
    slotsTotalNumber->setObjectName("summaryNumber");
    QLabel* slotsTotalText = new QLabel("TOTAL\nSLOTS");
    slotsTotalText->setObjectName("summaryText");
    slotsTotalLayout->addWidget(slotsTotalIcon);
    slotsTotalLayout->addWidget(slotsTotalNumber);
    slotsTotalLayout->addWidget(slotsTotalText);
    slotsTotalLayout->addStretch();

    QFrame* slotsAvailableCard = new QFrame();
    slotsAvailableCard->setObjectName("summaryCard");
    QHBoxLayout* slotsAvailableLayout = new QHBoxLayout(slotsAvailableCard);
    QLabel* slotsAvailableIcon = new QLabel("A");
    slotsAvailableIcon->setObjectName("greenIcon");
    QLabel* slotsAvailableNumber = new QLabel("5");
    slotsAvailableNumber->setObjectName("summaryNumber");
    QLabel* slotsAvailableText = new QLabel("AVAILABLE");
    slotsAvailableText->setObjectName("summaryText");
    slotsAvailableLayout->addWidget(slotsAvailableIcon);
    slotsAvailableLayout->addWidget(slotsAvailableNumber);
    slotsAvailableLayout->addWidget(slotsAvailableText);
    slotsAvailableLayout->addStretch();

    QFrame* slotsOccupiedCard = new QFrame();
    slotsOccupiedCard->setObjectName("summaryCard");
    QHBoxLayout* slotsOccupiedLayout = new QHBoxLayout(slotsOccupiedCard);
    QLabel* slotsOccupiedIcon = new QLabel("O");
    slotsOccupiedIcon->setObjectName("redIcon");
    QLabel* slotsOccupiedNumber = new QLabel("0");
    slotsOccupiedNumber->setObjectName("summaryNumber");
    QLabel* slotsOccupiedText = new QLabel("OCCUPIED");
    slotsOccupiedText->setObjectName("summaryText");
    slotsOccupiedLayout->addWidget(slotsOccupiedIcon);
    slotsOccupiedLayout->addWidget(slotsOccupiedNumber);
    slotsOccupiedLayout->addWidget(slotsOccupiedText);
    slotsOccupiedLayout->addStretch();

    slotsSummaryLayout->addWidget(slotsTotalCard);
    slotsSummaryLayout->addWidget(slotsAvailableCard);
    slotsSummaryLayout->addWidget(slotsOccupiedCard);
    slotsPageLayout->addLayout(slotsSummaryLayout);

    QLabel* allSlotsHeading = new QLabel("All Parking Spaces");
    allSlotsHeading->setObjectName("sectionHeading");
    slotsPageLayout->addWidget(allSlotsHeading);

    QGridLayout* fullSlotsGrid = new QGridLayout();
    fullSlotsGrid->setSpacing(15);

    std::vector<QLabel*> parkingPageStatusLabels;
    std::vector<QLabel*> parkingPageVehicleLabels;

    for (int i = 0; i < parkingLot->getTotalSlots(); ++i) {
        QFrame* slotCard = new QFrame();
        slotCard->setObjectName("slotCard");
        slotCard->setMinimumHeight(125);

        QVBoxLayout* slotLayout = new QVBoxLayout(slotCard);
        slotLayout->setContentsMargins(18, 15, 18, 15);
        slotLayout->setSpacing(6);

        QLabel* slotNumber = new QLabel(
            QString("SLOT %1").arg(i + 1));
        slotNumber->setObjectName("slotNumber");

        QLabel* statusLabel = new QLabel("● AVAILABLE");
        statusLabel->setObjectName("availableStatus");

        QLabel* vehicleLabel = new QLabel("No vehicle parked");
        vehicleLabel->setObjectName("vehicleText");

        slotLayout->addWidget(slotNumber);
        QHBoxLayout* statusLayout = new QHBoxLayout();
        statusLayout->addStretch();
        statusLayout->addWidget(statusLabel);
        slotLayout->addLayout(statusLayout);
        slotLayout->addStretch();
        slotLayout->addWidget(vehicleLabel);

        fullSlotsGrid->addWidget(slotCard, i / 3, i % 3);
        parkingPageStatusLabels.push_back(statusLabel);
        parkingPageVehicleLabels.push_back(vehicleLabel);
    }

    slotsPageLayout->addLayout(fullSlotsGrid);
    slotsPageLayout->addStretch();

    pageStack->addWidget(slotsPage);

    // Refreshes the dedicated Parking Slots page from the real backend data.
    auto refreshSlotsPage = [this,
                             slotsTotalNumber,
                             slotsAvailableNumber,
                             slotsOccupiedNumber,
                             parkingPageStatusLabels,
                             parkingPageVehicleLabels]() {
        const int totalSlots = parkingLot->getTotalSlots();
        int occupiedSlots = 0;

        for (const auto& vehicle : vehicles) {
            if (parkingLot->findVehicleSlot(vehicle.get()) != -1) {
                ++occupiedSlots;
            }
        }

        const int availableSlots = totalSlots - occupiedSlots;

        slotsTotalNumber->setText(QString::number(totalSlots));
        slotsAvailableNumber->setText(QString::number(availableSlots));
        slotsOccupiedNumber->setText(QString::number(occupiedSlots));

        for (int i = 0; i < totalSlots; ++i) {
            Vehicle* parkedVehicle = nullptr;

            for (const auto& vehicle : vehicles) {
                if (parkingLot->findVehicleSlot(vehicle.get()) == i + 1) {
                    parkedVehicle = vehicle.get();
                    break;
                }
            }

            if (parkedVehicle != nullptr) {
                parkingPageStatusLabels[i]->setText("● OCCUPIED");
                parkingPageStatusLabels[i]->setObjectName("occupiedStatus");
                parkingPageVehicleLabels[i]->setText(
                    QString::fromStdString(
                        parkedVehicle->getVehicleNumber()));
            } else {
                parkingPageStatusLabels[i]->setText("● AVAILABLE");
                parkingPageStatusLabels[i]->setObjectName("availableStatus");
                parkingPageVehicleLabels[i]->setText("No vehicle parked");
            }

            parkingPageStatusLabels[i]->style()->unpolish(
                parkingPageStatusLabels[i]);
            parkingPageStatusLabels[i]->style()->polish(
                parkingPageStatusLabels[i]);
            parkingPageStatusLabels[i]->update();
        }
    };

    // ========================================================
    // VEHICLES PAGE
    // ========================================================
    QWidget* vehiclesPage = new QWidget();
    QVBoxLayout* vehiclesPageLayout = new QVBoxLayout(vehiclesPage);
    vehiclesPageLayout->setContentsMargins(30, 25, 30, 25);
    vehiclesPageLayout->setSpacing(20);

    QHBoxLayout* vehiclesHeaderLayout = new QHBoxLayout();
    QVBoxLayout* vehiclesTitleLayout = new QVBoxLayout();
    vehiclesTitleLayout->setSpacing(2);

    QLabel* vehiclesPageTitle = new QLabel("Vehicles");
    vehiclesPageTitle->setObjectName("dashboardTitle");
    QLabel* vehiclesPageSubtitle = new QLabel(
        "View all registered vehicles and their current parking status");
    vehiclesPageSubtitle->setObjectName("dashboardSubtitle");

    vehiclesTitleLayout->addWidget(vehiclesPageTitle);
    vehiclesTitleLayout->addWidget(vehiclesPageSubtitle);
    vehiclesHeaderLayout->addLayout(vehiclesTitleLayout);
    vehiclesHeaderLayout->addStretch();

    QPushButton* vehiclesRefreshButton = new QPushButton("Refresh");
    vehiclesRefreshButton->setObjectName("secondaryButton");
    vehiclesHeaderLayout->addWidget(vehiclesRefreshButton);
    vehiclesPageLayout->addLayout(vehiclesHeaderLayout);

    QHBoxLayout* vehiclesSummaryLayout = new QHBoxLayout();
    vehiclesSummaryLayout->setSpacing(15);

    QFrame* registeredCard = new QFrame();
    registeredCard->setObjectName("summaryCard");
    QHBoxLayout* registeredLayout = new QHBoxLayout(registeredCard);
    QLabel* registeredIcon = new QLabel("V");
    registeredIcon->setObjectName("blueIcon");
    QLabel* registeredNumber = new QLabel("0");
    registeredNumber->setObjectName("summaryNumber");
    QLabel* registeredText = new QLabel("REGISTERED\nVEHICLES");
    registeredText->setObjectName("summaryText");
    registeredLayout->addWidget(registeredIcon);
    registeredLayout->addWidget(registeredNumber);
    registeredLayout->addWidget(registeredText);
    registeredLayout->addStretch();

    QFrame* parkedVehiclesCard = new QFrame();
    parkedVehiclesCard->setObjectName("summaryCard");
    QHBoxLayout* parkedVehiclesLayout = new QHBoxLayout(parkedVehiclesCard);
    QLabel* parkedVehiclesIcon = new QLabel("P");
    parkedVehiclesIcon->setObjectName("greenIcon");
    QLabel* parkedVehiclesNumber = new QLabel("0");
    parkedVehiclesNumber->setObjectName("summaryNumber");
    QLabel* parkedVehiclesText = new QLabel("CURRENTLY\nPARKED");
    parkedVehiclesText->setObjectName("summaryText");
    parkedVehiclesLayout->addWidget(parkedVehiclesIcon);
    parkedVehiclesLayout->addWidget(parkedVehiclesNumber);
    parkedVehiclesLayout->addWidget(parkedVehiclesText);
    parkedVehiclesLayout->addStretch();

    QFrame* notParkedCard = new QFrame();
    notParkedCard->setObjectName("summaryCard");
    QHBoxLayout* notParkedLayout = new QHBoxLayout(notParkedCard);
    QLabel* notParkedIcon = new QLabel("-");
    notParkedIcon->setObjectName("redIcon");
    QLabel* notParkedNumber = new QLabel("0");
    notParkedNumber->setObjectName("summaryNumber");
    QLabel* notParkedText = new QLabel("NOT\nPARKED");
    notParkedText->setObjectName("summaryText");
    notParkedLayout->addWidget(notParkedIcon);
    notParkedLayout->addWidget(notParkedNumber);
    notParkedLayout->addWidget(notParkedText);
    notParkedLayout->addStretch();

    vehiclesSummaryLayout->addWidget(registeredCard);
    vehiclesSummaryLayout->addWidget(parkedVehiclesCard);
    vehiclesSummaryLayout->addWidget(notParkedCard);
    vehiclesPageLayout->addLayout(vehiclesSummaryLayout);

    QLabel* registeredHeading = new QLabel("All Vehicles");
    registeredHeading->setObjectName("sectionHeading");
    vehiclesPageLayout->addWidget(registeredHeading);

    QScrollArea* vehiclesScrollArea = new QScrollArea();
    vehiclesScrollArea->setWidgetResizable(true);
    vehiclesScrollArea->setFrameShape(QFrame::NoFrame);
    vehiclesScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QWidget* vehiclesListWidget = new QWidget();
    QVBoxLayout* vehiclesListLayout = new QVBoxLayout(vehiclesListWidget);
    vehiclesListLayout->setContentsMargins(0, 0, 5, 0);
    vehiclesListLayout->setSpacing(12);
    vehiclesScrollArea->setWidget(vehiclesListWidget);
    vehiclesPageLayout->addWidget(vehiclesScrollArea, 1);

    pageStack->addWidget(vehiclesPage);

    // Rebuilds the vehicle list using the actual backend data.
    auto refreshVehiclesPage = [this,
                                registeredNumber,
                                parkedVehiclesNumber,
                                notParkedNumber,
                                vehiclesListLayout]() {
        const int totalVehicles = static_cast<int>(vehicles.size());
        int parkedCount = 0;

        while (QLayoutItem* item = vehiclesListLayout->takeAt(0)) {
            if (QWidget* widget = item->widget()) {
                widget->deleteLater();
            }
            delete item;
        }

        // Count all currently parked vehicles.
        for (const auto& vehicle : vehicles) {
            if (parkingLot->findVehicleSlot(vehicle.get()) != -1) {
                ++parkedCount;
            }
        }

        // Show every registered vehicle.
        for (const auto& vehicle : vehicles) {
            const int slotNumber =
                parkingLot->findVehicleSlot(vehicle.get());

            QFrame* vehicleCard = new QFrame();
            vehicleCard->setObjectName("slotCard");

            QHBoxLayout* vehicleLayout = new QHBoxLayout(vehicleCard);
            vehicleLayout->setContentsMargins(18, 14, 18, 14);
            vehicleLayout->setSpacing(15);

            QLabel* vehicleIcon = new QLabel("V");
            vehicleIcon->setObjectName(
                slotNumber == -1 ? "redIcon" : "blueIcon");

            QVBoxLayout* detailsLayout = new QVBoxLayout();
            detailsLayout->setSpacing(3);

            QLabel* numberLabel = new QLabel(
                QString::fromStdString(vehicle->getVehicleNumber()));
            numberLabel->setObjectName("slotNumber");

            QLabel* detailsLabel = new QLabel(
                QString("%1  •  Owner: %2")
                    .arg(QString::fromStdString(vehicle->getVehicleType()))
                    .arg(QString::fromStdString(vehicle->getOwnerName())));
            detailsLabel->setObjectName("vehicleText");

            detailsLayout->addWidget(numberLabel);
            detailsLayout->addWidget(detailsLabel);

            vehicleLayout->addWidget(vehicleIcon);
            vehicleLayout->addLayout(detailsLayout, 1);

            QLabel* statusLabel = new QLabel();
            if (slotNumber == -1) {
                statusLabel->setText("● NOT PARKED");
                statusLabel->setObjectName("occupiedStatus");
            } else {
                statusLabel->setText(
                    QString("● PARKED — SLOT %1").arg(slotNumber));
                statusLabel->setObjectName("availableStatus");
            }

            vehicleLayout->addWidget(statusLabel);
            vehiclesListLayout->addWidget(vehicleCard);
        }

        if (totalVehicles == 0) {
            QLabel* emptyLabel = new QLabel(
                "No vehicles have been registered yet.\n"
                "Use the Park Vehicle button from the Dashboard to add one.");
            emptyLabel->setObjectName("activityText");
            emptyLabel->setAlignment(Qt::AlignCenter);
            emptyLabel->setWordWrap(true);
            vehiclesListLayout->addWidget(emptyLabel);
        }

        vehiclesListLayout->addStretch();

        registeredNumber->setText(QString::number(totalVehicles));
        parkedVehiclesNumber->setText(QString::number(parkedCount));
        notParkedNumber->setText(
            QString::number(totalVehicles - parkedCount));
    };

    // ========================================================
    // BILLING PAGE
    // ========================================================
    QWidget* billingPage = new QWidget();
    QVBoxLayout* billingPageLayout = new QVBoxLayout(billingPage);
    billingPageLayout->setContentsMargins(30, 25, 30, 25);
    billingPageLayout->setSpacing(20);

    QVBoxLayout* billingTitleLayout = new QVBoxLayout();
    billingTitleLayout->setSpacing(2);

    QLabel* billingPageTitle = new QLabel("Billing");
    billingPageTitle->setObjectName("dashboardTitle");

    QLabel* billingPageSubtitle = new QLabel(
        "Select a parked vehicle, calculate its fee, and complete checkout");
    billingPageSubtitle->setObjectName("dashboardSubtitle");

    billingTitleLayout->addWidget(billingPageTitle);
    billingTitleLayout->addWidget(billingPageSubtitle);
    billingPageLayout->addLayout(billingTitleLayout);

    QFrame* billingCard = new QFrame();
    billingCard->setObjectName("summaryCard");
    QVBoxLayout* billingLayout = new QVBoxLayout(billingCard);
    billingLayout->setContentsMargins(24, 22, 24, 22);
    billingLayout->setSpacing(14);

    QLabel* parkedVehiclesTitle = new QLabel("Currently Parked Vehicles");
    parkedVehiclesTitle->setObjectName("sectionHeading");
    billingLayout->addWidget(parkedVehiclesTitle);

    QComboBox* parkedVehicleCombo = new QComboBox();
    billingLayout->addWidget(parkedVehicleCombo);

    QLabel* selectedVehicleLabel = new QLabel(
        "Select a vehicle to view its billing details.");
    selectedVehicleLabel->setObjectName("vehicleText");
    selectedVehicleLabel->setWordWrap(true);
    billingLayout->addWidget(selectedVehicleLabel);

    QHBoxLayout* billingInputLayout = new QHBoxLayout();
    billingInputLayout->setSpacing(12);

    QLabel* durationLabel = new QLabel("Parking Duration:");
    durationLabel->setObjectName("vehicleText");

    QSpinBox* billingHoursSpin = new QSpinBox();
    billingHoursSpin->setRange(1, 999);
    billingHoursSpin->setValue(1);
    billingHoursSpin->setSuffix(" hour(s)");

    billingInputLayout->addWidget(durationLabel);
    billingInputLayout->addWidget(billingHoursSpin);
    billingInputLayout->addStretch();
    billingLayout->addLayout(billingInputLayout);

    QLabel* calculatedFeeLabel = new QLabel("Total: Rs. 20.00");
    calculatedFeeLabel->setObjectName("summaryNumber");
    billingLayout->addWidget(calculatedFeeLabel);

    QHBoxLayout* billingActionLayout = new QHBoxLayout();
    billingActionLayout->setSpacing(10);

    QPushButton* calculateBillButton =
        new QPushButton("Calculate Fee");
    calculateBillButton->setObjectName("secondaryButton");

    QPushButton* payBillButton = new QPushButton("PAY BILL");
    payBillButton->setObjectName("primaryButton");

    QPushButton* refreshBillingButton =
        new QPushButton("Refresh");
    refreshBillingButton->setObjectName("secondaryButton");

    billingActionLayout->addWidget(calculateBillButton);
    billingActionLayout->addWidget(payBillButton);
    billingActionLayout->addWidget(refreshBillingButton);
    billingLayout->addLayout(billingActionLayout);

    billingPageLayout->addWidget(billingCard);
    billingPageLayout->addStretch();

    pageStack->addWidget(billingPage);

    // Refreshes the list of vehicles that are currently parked.
    // The previously selected vehicle is preserved when the list is rebuilt.
    auto refreshBillingPage = [
        this,
        parkedVehicleCombo,
        selectedVehicleLabel,
        billingHoursSpin,
        calculatedFeeLabel,
        payBillButton
    ]() {
        // Remember the selected vehicle before clearing the combo box.
        const QVariant previousSelection =
            parkedVehicleCombo->currentData();

        QSignalBlocker comboBlocker(parkedVehicleCombo);
        parkedVehicleCombo->clear();

        int parkedCount = 0;

        for (std::size_t i = 0; i < vehicles.size(); ++i) {
            Vehicle* vehicle = vehicles[i].get();

            const int slotNumber =
                parkingLot->findVehicleSlot(vehicle);

            if (slotNumber != -1) {
                const QString vehicleNumber =
                    QString::fromStdString(
                        vehicle->getVehicleNumber());

                parkedVehicleCombo->addItem(
                    QString("%1 - Slot %2")
                        .arg(vehicleNumber)
                        .arg(slotNumber),
                    QVariant::fromValue(static_cast<int>(i)));

                ++parkedCount;
            }
        }

        if (parkedCount == 0) {
            selectedVehicleLabel->setText(
                "No vehicles are currently parked.");

            calculatedFeeLabel->setText(
                "Total: Rs. 0.00");

            payBillButton->setEnabled(false);
            billingHoursSpin->setEnabled(false);

            return;
        }

        payBillButton->setEnabled(true);
        billingHoursSpin->setEnabled(true);

        // Try to restore the vehicle that was selected before refresh.
        int restoredIndex = -1;

        for (int i = 0;
             i < parkedVehicleCombo->count();
             ++i) {

            if (parkedVehicleCombo->itemData(i)
                    == previousSelection) {

                restoredIndex = i;
                break;
            }
        }

        // If the previously selected vehicle was removed,
        // select the first currently parked vehicle.
        if (restoredIndex == -1) {
            restoredIndex = 0;
        }

        parkedVehicleCombo->setCurrentIndex(restoredIndex);

        const int vehicleIndex =
            parkedVehicleCombo->currentData().toInt();

        if (vehicleIndex >= 0 &&
            vehicleIndex < static_cast<int>(vehicles.size())) {

            Vehicle* vehicle =
                vehicles[vehicleIndex].get();

            const int slotNumber =
                parkingLot->findVehicleSlot(vehicle);

            selectedVehicleLabel->setText(
                QString(
                    "Vehicle: %1\n"
                    "Owner: %2\n"
                    "Type: %3\n"
                    "Slot: %4"
                )
                    .arg(QString::fromStdString(
                        vehicle->getVehicleNumber()))
                    .arg(QString::fromStdString(
                        vehicle->getOwnerName()))
                    .arg(QString::fromStdString(
                        vehicle->getVehicleType()))
                    .arg(slotNumber)
            );

            const double fee =
                Billing::calculateFee(
                    billingHoursSpin->value());

            calculatedFeeLabel->setText(
                QString("Total: Rs. %1")
                    .arg(fee, 0, 'f', 2));
        }
    };
    connect(
        parkedVehicleCombo,
        &QComboBox::currentIndexChanged,
        this,
        [refreshBillingPage]() {
            refreshBillingPage();
        }
    );

    connect(
        billingHoursSpin,
        qOverload<int>(&QSpinBox::valueChanged),
        this,
        [refreshBillingPage](int) {
            refreshBillingPage();
        }
    );

    connect(
        calculateBillButton,
        &QPushButton::clicked,
        this,
        [this,
         parkedVehicleCombo,
         billingHoursSpin,
         calculatedFeeLabel]() {
            if (parkedVehicleCombo->currentIndex() < 0) {
                QMessageBox::information(
                    this,
                    "Billing",
                    "There are no parked vehicles to bill.");
                return;
            }

            const int hours = billingHoursSpin->value();
            const double fee = Billing::calculateFee(hours);

            calculatedFeeLabel->setText(
                QString("Total: Rs. %1")
                    .arg(fee, 0, 'f', 2));
        }
    );

    connect(
        payBillButton,
        &QPushButton::clicked,
        this,
        [this,
         parkedVehicleCombo,
         billingHoursSpin,
         refreshBillingPage,
         refreshSlotsPage,
         refreshVehiclesPage]() {
            if (parkedVehicleCombo->currentIndex() < 0) {
                return;
            }

            const int vehicleIndex =
                parkedVehicleCombo->currentData().toInt();

            if (vehicleIndex < 0 ||
                vehicleIndex >= static_cast<int>(vehicles.size())) {
                return;
            }

            Vehicle* vehicle = vehicles[vehicleIndex].get();
            const int slotNumber =
                parkingLot->findVehicleSlot(vehicle);
            const int hours = billingHoursSpin->value();
            const double fee = Billing::calculateFee(hours);

            if (slotNumber == -1) {
                QMessageBox::warning(
                    this,
                    "Billing Error",
                    "This vehicle is no longer parked.");
                refreshBillingPage();
                return;
            }

            const QString vehicleNumber =
                QString::fromStdString(
                    vehicle->getVehicleNumber());

            const QMessageBox::StandardButton confirmation =
                QMessageBox::question(
                    this,
                    "Confirm Payment",
                    QString("Vehicle: %1\nSlot: %2\nDuration: %3 hour(s)\nTotal: Rs. %4\n\nConfirm payment and checkout?")
                        .arg(vehicleNumber)
                        .arg(slotNumber)
                        .arg(hours)
                        .arg(fee, 0, 'f', 2),
                    QMessageBox::Yes | QMessageBox::No,
                    QMessageBox::Yes);

            if (confirmation != QMessageBox::Yes) {
                return;
            }

            if (parkingLot->removeVehicle(slotNumber)) {
                saveParkingData();
                updateParkingDashboard();
                refreshSlotsPage();
                refreshVehiclesPage();
                refreshBillingPage();

                activityText->setText(
                    QString("Payment completed for %1.\n\nSlot %2 is now available.")
                        .arg(vehicleNumber)
                        .arg(slotNumber));

                QMessageBox::information(
                    this,
                    "Payment Successful",
                    QString("Payment completed successfully.\n\nVehicle: %1\nAmount Paid: Rs. %2")
                        .arg(vehicleNumber)
                        .arg(fee, 0, 'f', 2));
            }
        }
    );

    connect(
        refreshBillingButton,
        &QPushButton::clicked,
        this,
        [refreshBillingPage]() {
            refreshBillingPage();
        }
    );

    // ========================================================
    // SETTINGS PAGE
    // ========================================================
    QWidget* settingsPage = new QWidget();
    QVBoxLayout* settingsPageLayout = new QVBoxLayout(settingsPage);
    settingsPageLayout->setContentsMargins(30, 25, 30, 25);
    settingsPageLayout->setSpacing(20);

    QVBoxLayout* settingsTitleLayout = new QVBoxLayout();
    settingsTitleLayout->setSpacing(2);
    QLabel* settingsPageTitle = new QLabel("Settings");
    settingsPageTitle->setObjectName("dashboardTitle");
    QLabel* settingsPageSubtitle = new QLabel(
        "Manage application preferences and parking data");
    settingsPageSubtitle->setObjectName("dashboardSubtitle");
    settingsTitleLayout->addWidget(settingsPageTitle);
    settingsTitleLayout->addWidget(settingsPageSubtitle);
    settingsPageLayout->addLayout(settingsTitleLayout);

    QFrame* appearanceCard = new QFrame();
    appearanceCard->setObjectName("summaryCard");
    QHBoxLayout* appearanceLayout = new QHBoxLayout(appearanceCard);
    appearanceLayout->setContentsMargins(22, 18, 22, 18);
    QLabel* appearanceIcon = new QLabel("T");
    appearanceIcon->setObjectName("blueIcon");
    QVBoxLayout* appearanceTextLayout = new QVBoxLayout();
    QLabel* appearanceTitle = new QLabel("Appearance");
    appearanceTitle->setObjectName("sectionHeading");
    QLabel* appearanceInfo = new QLabel();
    appearanceInfo->setObjectName("vehicleText");
    appearanceTextLayout->addWidget(appearanceTitle);
    appearanceTextLayout->addWidget(appearanceInfo);
    appearanceLayout->addWidget(appearanceIcon);
    appearanceLayout->addLayout(appearanceTextLayout, 1);
    QPushButton* settingsThemeButton = new QPushButton("Toggle Theme");
    settingsThemeButton->setObjectName("secondaryButton");
    appearanceLayout->addWidget(settingsThemeButton);

    QFrame* dataCard = new QFrame();
    dataCard->setObjectName("summaryCard");
    QVBoxLayout* dataLayout = new QVBoxLayout(dataCard);
    dataLayout->setContentsMargins(22, 20, 22, 20);
    QLabel* dataTitle = new QLabel("Data Storage");
    dataTitle->setObjectName("sectionHeading");
    QLabel* dataInfo = new QLabel(
        "Parking data is automatically saved to the project's data folder "
        "and restored when the application starts again.");
    dataInfo->setObjectName("vehicleText");
    dataInfo->setWordWrap(true);
    QPushButton* saveDataButton = new QPushButton("Save Data Now");
    saveDataButton->setObjectName("secondaryButton");
    dataLayout->addWidget(dataTitle);
    dataLayout->addWidget(dataInfo);
    dataLayout->addSpacing(5);
    dataLayout->addWidget(saveDataButton, 0, Qt::AlignLeft);

    QFrame* systemInfoCard = new QFrame();
    systemInfoCard->setObjectName("summaryCard");
    QVBoxLayout* systemInfoLayout = new QVBoxLayout(systemInfoCard);
    systemInfoLayout->setContentsMargins(22, 20, 22, 20);
    QLabel* systemInfoTitle = new QLabel("System Information");
    systemInfoTitle->setObjectName("sectionHeading");
    QLabel* systemInfoText = new QLabel(
        "Smart Parking System\n"
        "Frontend: Qt Widgets + C++\n"
        "Backend: C++ parking management classes\n"
        "Storage: Local text files");
    systemInfoText->setObjectName("vehicleText");
    systemInfoLayout->addWidget(systemInfoTitle);
    systemInfoLayout->addWidget(systemInfoText);

    settingsPageLayout->addWidget(appearanceCard);
    settingsPageLayout->addWidget(dataCard);
    settingsPageLayout->addWidget(systemInfoCard);
    settingsPageLayout->addStretch();

    pageStack->addWidget(settingsPage);

    // ========================================================
    // THEME
    // ========================================================
    applyTheme(true);
    appearanceInfo->setText("Dark Mode is currently enabled.");

    // ========================================================
    // BUTTON CONNECTIONS
    // ========================================================
    connect(
        parkButton,
        &QPushButton::clicked,
        this,
        &MainWindow::openParkVehicleDialog
    );
    connect(
        searchButton,
        &QPushButton::clicked,
        this,
        &MainWindow::openSearchVehicleDialog
    );
    // --------------------------------------------------------
    // Sidebar navigation
    // --------------------------------------------------------
    // Each sidebar item now switches the main content area to a
    // dedicated page instead of opening a separate popup window.
    auto setActiveMenu = [
        dashboardButton,
        slotsButton,
        vehiclesButton,
        billingButton,
        settingsButton
    ](QPushButton* activeButton) {
        QPushButton* menuButtons[] = {
            dashboardButton,
            slotsButton,
            vehiclesButton,
            billingButton,
            settingsButton
        };

        for (QPushButton* button : menuButtons) {
            button->setProperty("active", button == activeButton);
            button->style()->unpolish(button);
            button->style()->polish(button);
            button->update();
        }
    };

    connect(
        dashboardButton,
        &QPushButton::clicked,
        this,
        [this, dashboardButton, setActiveMenu, pageStack, dashboardPage]() {
            setActiveMenu(dashboardButton);
            updateParkingDashboard();
            pageStack->setCurrentWidget(dashboardPage);
        }
    );

    connect(
        slotsButton,
        &QPushButton::clicked,
        this,
        [this,
         slotsButton,
         setActiveMenu,
         pageStack,
         slotsPage,
         refreshSlotsPage]() {
            setActiveMenu(slotsButton);
            refreshSlotsPage();
            pageStack->setCurrentWidget(slotsPage);
        }
    );

    connect(
        vehiclesButton,
        &QPushButton::clicked,
        this,
        [this,
         vehiclesButton,
         setActiveMenu,
         pageStack,
         vehiclesPage,
         refreshVehiclesPage]() {
            setActiveMenu(vehiclesButton);
            refreshVehiclesPage();
            pageStack->setCurrentWidget(vehiclesPage);
        }
    );

    connect(
        billingButton,
        &QPushButton::clicked,
        this,
        [billingButton, setActiveMenu, pageStack, billingPage, refreshBillingPage]() {
            setActiveMenu(billingButton);
            refreshBillingPage();
            pageStack->setCurrentWidget(billingPage);
        }
    );

    connect(
        settingsButton,
        &QPushButton::clicked,
        this,
        [this,
         settingsButton,
         setActiveMenu,
         pageStack,
         settingsPage,
         appearanceInfo]() {
            setActiveMenu(settingsButton);
            appearanceInfo->setText(
                themeSwitch->isChecked()
                    ? "Dark Mode is currently enabled."
                    : "Light Mode is currently enabled.");
            pageStack->setCurrentWidget(settingsPage);
        }
    );

    connect(
        vehiclesRefreshButton,
        &QPushButton::clicked,
        this,
        refreshVehiclesPage
    );

    connect(
        calculateBillButton,
        &QPushButton::clicked,
        this,
        [billingHoursSpin, calculatedFeeLabel]() {
            const int hours = billingHoursSpin->value();
            const double fee = Billing::calculateFee(hours);
            calculatedFeeLabel->setText(
                QString("Total: Rs. %1").arg(fee, 0, 'f', 2));
        }
    );

    connect(
        saveDataButton,
        &QPushButton::clicked,
        this,
        [this]() {
            saveParkingData();
            QMessageBox::information(
                this,
                "Data Saved",
                "Parking data has been saved successfully.");
        }
    );

    connect(
        settingsThemeButton,
        &QPushButton::clicked,
        this,
        [this]() {
            themeSwitch->setChecked(!themeSwitch->isChecked());
        }
    );

    connect(
        slotsRefreshButton,
        &QPushButton::clicked,
        this,
        refreshSlotsPage
    );


    connect(
        themeSwitch,
        &QAbstractButton::toggled,
        this,
        [this, appearanceInfo](bool checked) {
            QWidget* central = this->centralWidget();
            QGraphicsOpacityEffect* effect =
                new QGraphicsOpacityEffect(central);
            central->setGraphicsEffect(effect);
            QPropertyAnimation* animation =
                new QPropertyAnimation(effect, "opacity");
            animation->setDuration(180);
            animation->setStartValue(0.75);
            animation->setEndValue(1.0);
            connect(
                animation,
                &QPropertyAnimation::finished,
                animation,
                &QObject::deleteLater
            );
            connect(
                animation,
                &QPropertyAnimation::finished,
                central,
                [central]() {
                    central->setGraphicsEffect(nullptr);
                }
            );
            applyTheme(checked);
            appearanceInfo->setText(
                checked
                    ? "Dark Mode is currently enabled."
                    : "Light Mode is currently enabled.");
            animation->start();
        }
    );
    // Load previously saved parking data before refreshing the dashboard.
    loadParkingData();
    updateParkingDashboard();
}

// ============================================================
// Destructor
// ============================================================
MainWindow::~MainWindow() {
    delete parkingLot;
}

// ============================================================
// Theme
// ============================================================
void MainWindow::applyTheme(bool darkMode) {
    if (darkMode) {
        setStyleSheet(R"(
            QMainWindow {
                background: #0b1220;
            }
            QWidget#content {
                background: #0b1220;
            }
            QFrame#sidebar {
                background: #080f1c;
            }
            QLabel#logoTitle {
                color: white;
                font-size: 20px;
                font-weight: bold;
            }
            QLabel#logoSubtitle {
                color: #64748b;
                font-size: 9px;
            }
            QLabel#sectionTitle {
                color: #64748b;
                font-size: 10px;
                font-weight: bold;
            }
            QLabel#darkModeLabel {
                color: #94a3b8;
                font-size: 11px;
            }
            QPushButton#menuButton {
                background: transparent;
                border: none;
                border-radius: 6px;
                color: #94a3b8;
                text-align: left;
                padding: 10px 12px;
                font-size: 12px;
            }
            QPushButton#menuButton:hover {
                background: #162033;
                color: white;
            }
            QLabel#onlineDot {
                color: #27d17f;
                font-size: 12px;
            }
            QLabel#onlineText {
                color: #27d17f;
                font-size: 11px;
            }
            QLabel#dashboardTitle {
                color: white;
                font-size: 25px;
                font-weight: bold;
            }
            QLabel#dashboardSubtitle {
                color: #64748b;
                font-size: 12px;
            }
            QLabel#smartParkingLabel {
                color: #94a3b8;
                background: #111c2d;
                border: 1px solid #26344a;
                border-radius: 6px;
                padding: 10px 14px;
                font-size: 10px;
                font-weight: bold;
            }
            QFrame#summaryCard {
                background: #111c2d;
                border: 1px solid #24334a;
                border-radius: 10px;
            }
            QLabel#summaryNumber {
                color: white;
                font-size: 24px;
                font-weight: bold;
            }
            QLabel#summaryText {
                color: #64748b;
                font-size: 9px;
                font-weight: bold;
            }
            QLabel#blueIcon,
            QLabel#greenIcon,
            QLabel#redIcon {
                border-radius: 22px;
                min-width: 44px;
                max-width: 44px;
                min-height: 44px;
                max-height: 44px;
                qproperty-alignment: AlignCenter;
                font-size: 17px;
                font-weight: bold;
            }
            QLabel#blueIcon {
                background: #122e56;
                color: #4da3ff;
            }
            QLabel#greenIcon {
                background: #12352d;
                color: #35d28a;
            }
            QLabel#redIcon {
                background: #3b2224;
                color: #ff6b61;
            }
            QLabel#sectionHeading {
                color: white;
                font-size: 17px;
                font-weight: bold;
            }
            QLabel#liveStatus {
                color: #32d583;
                font-size: 10px;
                font-weight: bold;
            }
            QFrame#slotCard {
                background: #111c2d;
                border: 1px solid #26364e;
                border-radius: 9px;
            }
            QLabel#slotNumber {
                color: white;
                font-size: 12px;
                font-weight: bold;
            }
            QLabel#availableStatus {
                color: #35d28a;
                font-size: 9px;
                font-weight: bold;
            }
            QLabel#occupiedStatus {
                color: #ff6b61;
                font-size: 9px;
                font-weight: bold;
            }
            QLabel#vehicleText {
                color: #64748b;
                font-size: 10px;
            }
            QPushButton#primaryButton {
                background: #2f80ed;
                color: white;
                border: none;
                border-radius: 6px;
                padding: 10px 18px;
                font-size: 11px;
                font-weight: bold;
            }
            QPushButton#primaryButton:hover {
                background: #4090f5;
            }
            QPushButton#secondaryButton {
                background: #162235;
                color: #cbd5e1;
                border: 1px solid #2b3b54;
                border-radius: 6px;
                padding: 10px 18px;
                font-size: 11px;
            }
            QPushButton#secondaryButton:hover {
                background: #1d2c43;
            }
            QFrame#activityCard {
                background: #111c2d;
                border: 1px solid #26364e;
                border-radius: 9px;
            }
            QLabel#activityTitle {
                color: white;
                font-size: 11px;
                font-weight: bold;
            }
            QLabel#activityText {
                color: #64748b;
                font-size: 10px;
            }
            QDialog {
                background: #111c2d;
            }
            QDialog QLabel {
                color: #cbd5e1;
            }
            QLineEdit,
            QComboBox,
            QSpinBox {
                background: #0b1422;
                color: white;
                border: 1px solid #334155;
                border-radius: 5px;
                padding: 8px;
            }
            QLineEdit:focus,
            QComboBox:focus,
            QSpinBox:focus {
                border: 1px solid #2f80ed;
            }
            QComboBox QAbstractItemView {
                background: #111c2d;
                color: white;
                selection-background-color: #2f80ed;
            }
        )");
    } else {
        setStyleSheet(R"(
            QMainWindow {
                background: #f4f7fb;
            }
            QWidget#content {
                background: #f4f7fb;
            }
            QFrame#sidebar {
                background: #ffffff;
            }
            QLabel#logoTitle {
                color: #172033;
                font-size: 20px;
                font-weight: bold;
            }
            QLabel#logoSubtitle {
                color: #94a3b8;
                font-size: 9px;
            }
            QLabel#sectionTitle {
                color: #94a3b8;
                font-size: 10px;
                font-weight: bold;
            }
            QLabel#darkModeLabel {
                color: #64748b;
                font-size: 11px;
            }
            QPushButton#menuButton {
                background: transparent;
                border: none;
                border-radius: 6px;
                color: #64748b;
                text-align: left;
                padding: 10px 12px;
                font-size: 12px;
            }
            QPushButton#menuButton:hover {
                background: #edf3fa;
                color: #172033;
            }
            QLabel#onlineDot {
                color: #22b573;
            }
            QLabel#onlineText {
                color: #22b573;
            }
            QLabel#dashboardTitle {
                color: #172033;
                font-size: 25px;
                font-weight: bold;
            }
            QLabel#dashboardSubtitle {
                color: #94a3b8;
                font-size: 12px;
            }
            QLabel#smartParkingLabel {
                color: #64748b;
                background: white;
                border: 1px solid #dbe3ed;
                border-radius: 6px;
                padding: 10px 14px;
                font-size: 10px;
                font-weight: bold;
            }
            QFrame#summaryCard {
                background: white;
                border: 1px solid #e2e8f0;
                border-radius: 10px;
            }
            QLabel#summaryNumber {
                color: #172033;
                font-size: 24px;
                font-weight: bold;
            }
            QLabel#summaryText {
                color: #94a3b8;
                font-size: 9px;
                font-weight: bold;
            }
            QLabel#blueIcon,
            QLabel#greenIcon,
            QLabel#redIcon {
                border-radius: 22px;
                min-width: 44px;
                max-width: 44px;
                min-height: 44px;
                max-height: 44px;
                qproperty-alignment: AlignCenter;
                font-size: 17px;
                font-weight: bold;
            }
            QLabel#blueIcon {
                background: #e4f0ff;
                color: #2f80ed;
            }
            QLabel#greenIcon {
                background: #e2f8ed;
                color: #20a66a;
            }
            QLabel#redIcon {
                background: #ffe9e7;
                color: #e05248;
            }
            QLabel#sectionHeading {
                color: #172033;
                font-size: 17px;
                font-weight: bold;
            }
            QLabel#liveStatus {
                color: #20a66a;
                font-size: 10px;
                font-weight: bold;
            }
            QFrame#slotCard {
                background: white;
                border: 1px solid #e2e8f0;
                border-radius: 9px;
            }
            QLabel#slotNumber {
                color: #172033;
                font-size: 12px;
                font-weight: bold;
            }
            QLabel#availableStatus {
                color: #20a66a;
                font-size: 9px;
                font-weight: bold;
            }
            QLabel#occupiedStatus {
                color: #e05248;
                font-size: 9px;
                font-weight: bold;
            }
            QLabel#vehicleText {
                color: #94a3b8;
                font-size: 10px;
            }
            QPushButton#primaryButton {
                background: #2f80ed;
                color: white;
                border: none;
                border-radius: 6px;
                padding: 10px 18px;
                font-size: 11px;
                font-weight: bold;
            }
            QPushButton#secondaryButton {
                background: white;
                color: #475569;
                border: 1px solid #dbe3ed;
                border-radius: 6px;
                padding: 10px 18px;
                font-size: 11px;
            }
            QFrame#activityCard {
                background: white;
                border: 1px solid #e2e8f0;
                border-radius: 9px;
            }
            QLabel#activityTitle {
                color: #172033;
                font-size: 11px;
                font-weight: bold;
            }
            QLabel#activityText {
                color: #94a3b8;
                font-size: 10px;
            }
            QDialog {
                background: white;
            }
            QDialog QLabel {
                color: #334155;
            }
            QLineEdit,
            QComboBox,
            QSpinBox {
                background: white;
                color: #172033;
                border: 1px solid #cbd5e1;
                border-radius: 5px;
                padding: 8px;
            }
            QComboBox QAbstractItemView {
                background: white;
                color: #172033;
                selection-background-color: #2f80ed;
                selection-color: white;
            }
        )");
    }
    updateParkingDashboard();
}

// ============================================================
// Park Vehicle
// ============================================================
void MainWindow::openParkVehicleDialog() {
    int occupiedSlots = 0;
    for (const auto& vehicle : vehicles) {
        if (parkingLot->findVehicleSlot(vehicle.get()) != -1) {
            occupiedSlots++;
        }
    }
    if (occupiedSlots >= parkingLot->getTotalSlots()) {
        QMessageBox::warning(
            this,
            "Parking Full",
            "There are no available parking slots."
        );
        return;
    }
    QDialog dialog(this);
    dialog.setWindowTitle("Park Vehicle");
    dialog.setFixedWidth(420);
    QVBoxLayout* mainLayout =
        new QVBoxLayout(&dialog);
    mainLayout->setContentsMargins(25, 25, 25, 25);
    mainLayout->setSpacing(15);
    QLabel* title =
        new QLabel("Park a Vehicle");
    title->setStyleSheet(
        "font-size: 20px; font-weight: bold;"
    );
    QLabel* subtitle =
        new QLabel("Enter the vehicle details below.");
    subtitle->setStyleSheet(
        "color: #64748b; font-size: 11px;"
    );
    mainLayout->addWidget(title);
    mainLayout->addWidget(subtitle);
    QFormLayout* formLayout =
        new QFormLayout();
    formLayout->setSpacing(12);
    QLineEdit* vehicleNumberEdit =
        new QLineEdit();
    vehicleNumberEdit->setPlaceholderText(
        "e.g. OD02AB1234"
    );
    QComboBox* typeCombo =
        new QComboBox();
    typeCombo->addItem("Car");
    typeCombo->addItem("Bike");
    typeCombo->addItem("EV");
    QLineEdit* ownerNameEdit =
        new QLineEdit();
    ownerNameEdit->setPlaceholderText(
        "Enter owner's name"
    );
    formLayout->addRow(
        "Vehicle Number:",
        vehicleNumberEdit
    );
    formLayout->addRow(
        "Vehicle Type:",
        typeCombo
    );
    formLayout->addRow(
        "Owner Name:",
        ownerNameEdit
    );
    mainLayout->addLayout(formLayout);
    QHBoxLayout* buttonLayout =
        new QHBoxLayout();
    buttonLayout->addStretch();
    QPushButton* cancelButton =
        new QPushButton("Cancel");
    QPushButton* parkButton =
        new QPushButton("Park Vehicle");
    cancelButton->setObjectName("secondaryButton");
    parkButton->setObjectName("primaryButton");
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(parkButton);
    mainLayout->addLayout(buttonLayout);
    connect(
        cancelButton,
        &QPushButton::clicked,
        &dialog,
        &QDialog::reject
    );
    connect(
        parkButton,
        &QPushButton::clicked,
        &dialog,
        [&]() {
            QString vehicleNumber =
                vehicleNumberEdit->text().trimmed();
            QString vehicleType =
                typeCombo->currentText();
            QString ownerName =
                ownerNameEdit->text().trimmed();
            if (vehicleNumber.isEmpty()) {
                QMessageBox::warning(
                    &dialog,
                    "Missing Information",
                    "Please enter the vehicle number."
                );
                return;
            }
            if (ownerName.isEmpty()) {
                QMessageBox::warning(
                    &dialog,
                    "Missing Information",
                    "Please enter the owner's name."
                );
                return;
            }
            auto newVehicle =
                std::make_unique<Vehicle>(
                    vehicleNumber.toStdString(),
                    vehicleType.toStdString(),
                    ownerName.toStdString()
                );
            Vehicle* vehiclePointer =
                newVehicle.get();
            if (!parkingLot->parkVehicle(
                    vehiclePointer)) {
                QMessageBox::warning(
                    &dialog,
                    "Parking Error",
                    "Unable to park the vehicle."
                );
                return;
            }
            vehicles.push_back(
                std::move(newVehicle)
            );
        // Save the updated parking data to disk.
        saveParkingData();
            updateParkingDashboard();
            int assignedSlot =
                parkingLot->findVehicleSlot(
                    vehiclePointer
                );
            activityText->setText(
                QString(
                    "Vehicle %1 parked in Slot %2."
                )
                .arg(
                    QString::fromStdString(
                        vehiclePointer->
                        getVehicleNumber()
                    )
                )
                .arg(assignedSlot)
            );
            QMessageBox::information(
                &dialog,
                "Vehicle Parked",
                QString(
                    "Vehicle parked successfully!\n\n"
                    "Vehicle Number: %1\n"
                    "Vehicle Type: %2\n"
                    "Slot Number: %3"
                )
                .arg(vehicleNumber)
                .arg(vehicleType)
                .arg(assignedSlot)
            );
            dialog.accept();
        }
    );
    dialog.exec();
}

// ============================================================
// Checkout Vehicle
// ============================================================
void MainWindow::openCheckoutDialog() {
    // If there are no vehicles, there is nothing to checkout.
    if (vehicles.empty()) {
        QMessageBox::information(
            this,
            "No Vehicles",
            "There are currently no vehicles parked."
        );
        return;
    }
    QDialog dialog(this);
    dialog.setWindowTitle("Vehicle Checkout");
    dialog.setFixedWidth(420);
    QVBoxLayout* mainLayout =
        new QVBoxLayout(&dialog);
    mainLayout->setContentsMargins(25, 25, 25, 25);
    mainLayout->setSpacing(15);
    // --------------------------------------------------------
    // Title
    // --------------------------------------------------------
    QLabel* title =
        new QLabel("Vehicle Checkout");
    title->setStyleSheet(
        "font-size: 20px; font-weight: bold;"
    );
    QLabel* subtitle =
        new QLabel(
            "Enter the slot number and parking duration."
        );
    subtitle->setStyleSheet(
        "color: #64748b; font-size: 11px;"
    );
    mainLayout->addWidget(title);
    mainLayout->addWidget(subtitle);
    // --------------------------------------------------------
    // Input fields
    // --------------------------------------------------------
    QFormLayout* formLayout =
        new QFormLayout();
    formLayout->setSpacing(12);
    // Slot number
    QSpinBox* slotSpinBox =
        new QSpinBox();
    slotSpinBox->setRange(
        1,
        parkingLot->getTotalSlots()
    );
    slotSpinBox->setValue(1);
    // Parking duration
    QSpinBox* hoursSpinBox =
        new QSpinBox();
    hoursSpinBox->setRange(1, 24);
    hoursSpinBox->setValue(1);
    hoursSpinBox->setSuffix(" hour(s)");
    formLayout->addRow(
        "Slot Number:",
        slotSpinBox
    );
    formLayout->addRow(
        "Duration:",
        hoursSpinBox
    );
    mainLayout->addLayout(formLayout);
    // --------------------------------------------------------
    // Buttons
    // --------------------------------------------------------
    QHBoxLayout* buttonLayout =
        new QHBoxLayout();
    buttonLayout->addStretch();
    QPushButton* cancelButton =
        new QPushButton("Cancel");
    QPushButton* checkoutButton =
        new QPushButton("Checkout");
    cancelButton->setObjectName("secondaryButton");
    checkoutButton->setObjectName("primaryButton");
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(checkoutButton);
    mainLayout->addLayout(buttonLayout);
    connect(
        cancelButton,
        &QPushButton::clicked,
        &dialog,
        &QDialog::reject
    );
    // --------------------------------------------------------
    // Checkout action
    // --------------------------------------------------------
    connect(
        checkoutButton,
        &QPushButton::clicked,
        &dialog,
        [&]() {
            int slotNumber =
                slotSpinBox->value();
            int hours =
                hoursSpinBox->value();
            // Find the vehicle currently parked
            // in this slot.
            Vehicle* parkedVehicle = nullptr;
            for (const auto& vehicle : vehicles) {
                if (parkingLot->findVehicleSlot(
                        vehicle.get()) == slotNumber) {
                    parkedVehicle = vehicle.get();
                    break;
                }
            }
            // No vehicle in selected slot
            if (parkedVehicle == nullptr) {
                QMessageBox::warning(
                    &dialog,
                    "Empty Slot",
                    QString(
                        "There is no vehicle parked "
                        "in Slot %1."
                    ).arg(slotNumber)
                );
                return;
            }
            // ------------------------------------------------
            // Calculate parking fee
            // ------------------------------------------------
            double fee =
                Billing::calculateFee(hours);
            // Save vehicle information before removing it.
            QString vehicleNumber =
                QString::fromStdString(
                    parkedVehicle->getVehicleNumber()
                );
            QString vehicleType =
                QString::fromStdString(
                    parkedVehicle->getVehicleType()
                );
            QString ownerName =
                QString::fromStdString(
                    parkedVehicle->getOwnerName()
                );
            // ------------------------------------------------
            // Remove vehicle from parking lot
            // ------------------------------------------------
            bool removed =
                parkingLot->removeVehicle(slotNumber);
            if (!removed) {
                QMessageBox::warning(
                    &dialog,
                    "Checkout Error",
                    "Unable to remove the vehicle."
                );
                return;
            }
            // ------------------------------------------------
            // Update dashboard
            // ------------------------------------------------
            // Save the updated parking data after checkout.
            saveParkingData();
            updateParkingDashboard();
            activityText->setText(
                QString(
                    "Vehicle %1 checked out from Slot %2."
                )
                .arg(vehicleNumber)
                .arg(slotNumber)
            );
            // ------------------------------------------------
            // Show final bill
            // ------------------------------------------------
            QMessageBox::information(
                &dialog,
                "Checkout Complete",
                QString(
                    "========== PARKING BILL ==========\n\n"
                    "Vehicle Number : %1\n"
                    "Vehicle Type   : %2\n"
                    "Owner Name     : %3\n"
                    "Slot Number    : %4\n"
                    "Duration       : %5 hour(s)\n"
                    "Hourly Rate    : Rs. 20.00\n"
                    "Total Fee      : Rs. %6\n\n"
                    "Thank you for parking!"
                )
                .arg(vehicleNumber)
                .arg(vehicleType)
                .arg(ownerName)
                .arg(slotNumber)
                .arg(hours)
                .arg(fee, 0, 'f', 2)
            );
            dialog.accept();
        }
    );
    dialog.exec();
}

// ============================================================
// ============================================================
// Search Vehicle
// ============================================================
void MainWindow::openSearchVehicleDialog() {
    QDialog dialog(this);
    dialog.setWindowTitle("Search Vehicle");
    dialog.setFixedWidth(420);
    QVBoxLayout* mainLayout = new QVBoxLayout(&dialog);
    mainLayout->setContentsMargins(25, 25, 25, 25);
    mainLayout->setSpacing(15);
    QLabel* title = new QLabel("Search Vehicle");
    title->setStyleSheet("font-size: 20px; font-weight: bold;");
    QLabel* subtitle = new QLabel(
        "Enter a vehicle number to view its details."
    );
    subtitle->setStyleSheet("color: #64748b; font-size: 11px;");
    mainLayout->addWidget(title);
    mainLayout->addWidget(subtitle);
    QLineEdit* vehicleNumberEdit = new QLineEdit();
    vehicleNumberEdit->setPlaceholderText("e.g. OD02AB1234");
    mainLayout->addWidget(vehicleNumberEdit);
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    QPushButton* cancelButton = new QPushButton("Cancel");
    QPushButton* searchButton = new QPushButton("Search");
    cancelButton->setObjectName("secondaryButton");
    searchButton->setObjectName("primaryButton");
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(searchButton);
    mainLayout->addLayout(buttonLayout);
    connect(
        cancelButton,
        &QPushButton::clicked,
        &dialog,
        &QDialog::reject
    );
    connect(
        searchButton,
        &QPushButton::clicked,
        &dialog,
        [&]() {
            QString searchNumber = vehicleNumberEdit->text().trimmed();
            if (searchNumber.isEmpty()) {
                QMessageBox::warning(
                    &dialog,
                    "Missing Information",
                    "Please enter the vehicle number."
                );
                return;
            }
            Vehicle* foundVehicle = nullptr;
            for (const auto& vehicle : vehicles) {
                QString storedNumber = QString::fromStdString(
                    vehicle->getVehicleNumber()
                );
                if (storedNumber.compare(
                        searchNumber,
                        Qt::CaseInsensitive
                    ) == 0) {
                    foundVehicle = vehicle.get();
                    break;
                }
            }
            if (foundVehicle == nullptr) {
                QMessageBox::information(
                    &dialog,
                    "Vehicle Not Found",
                    QString(
                        "No vehicle record was found for %1."
                    ).arg(searchNumber)
                );
                return;
            }
            int currentSlot =
                parkingLot->findVehicleSlot(foundVehicle);
            QString status;
            if (currentSlot != -1) {
                status = QString(
                    "Currently Parked\n"
                    "Current Slot: %1"
                ).arg(currentSlot);
            } else {
                status = "Currently Not Parked";
            }
            QMessageBox::information(
                &dialog,
                "Vehicle Details",
                QString(
                    "========== VEHICLE DETAILS ==========\n\n"
                    "Vehicle Number : %1\n"
                    "Vehicle Type   : %2\n"
                    "Owner Name     : %3\n\n"
                    "%4"
                )
                .arg(QString::fromStdString(
                    foundVehicle->getVehicleNumber()
                ))
                .arg(QString::fromStdString(
                    foundVehicle->getVehicleType()
                ))
                .arg(QString::fromStdString(
                    foundVehicle->getOwnerName()
                ))
                .arg(status)
            );
        }
    );
    dialog.exec();
}
// Update Dashboard
// ============================================================
void MainWindow::updateParkingDashboard() {
    int totalSlots =
        parkingLot->getTotalSlots();
    int occupiedSlots = 0;
    for (const auto& vehicle : vehicles) {
        if (parkingLot->findVehicleSlot(
                vehicle.get()) != -1) {
            occupiedSlots++;
        }
    }
    int availableSlots =
        totalSlots - occupiedSlots;
    totalNumberLabel->setText(
        QString::number(totalSlots)
    );
    availableNumberLabel->setText(
        QString::number(availableSlots)
    );
    occupiedNumberLabel->setText(
        QString::number(occupiedSlots)
    );
    for (int i = 0; i < totalSlots; ++i) {
        updateSlotCard(i + 1);
    }
}

// ============================================================
// Update Individual Slot Card
// ============================================================
void MainWindow::updateSlotCard(int slotNumber) {
    int index = slotNumber - 1;
    if (index < 0 ||
        index >= static_cast<int>(
            slotCards.size())) {
        return;
    }
    Vehicle* parkedVehicle = nullptr;
    for (const auto& vehicle : vehicles) {
        if (parkingLot->findVehicleSlot(
                vehicle.get()) == slotNumber) {
            parkedVehicle = vehicle.get();
            break;
        }
    }
    if (parkedVehicle != nullptr) {
        slotStatusLabels[index]->setText(
            "● OCCUPIED"
        );
        slotStatusLabels[index]->setObjectName(
            "occupiedStatus"
        );
        slotVehicleLabels[index]->setText(
            QString::fromStdString(
                parkedVehicle->getVehicleNumber()
            )
        );
    } else {
        slotStatusLabels[index]->setText(
            "● AVAILABLE"
        );
        slotStatusLabels[index]->setObjectName(
            "availableStatus"
        );
        slotVehicleLabels[index]->setText(
            "No vehicle parked"
        );
    }
    // Reapply stylesheet after changing object name.
    slotStatusLabels[index]->style()->unpolish(
        slotStatusLabels[index]
    );
    slotStatusLabels[index]->style()->polish(
        slotStatusLabels[index]
    );
    slotStatusLabels[index]->update();
}

// ============================================================
// Save Parking Data
// ============================================================
//
// Saves all known vehicles and their current parking status.
// A slot number of -1 means the vehicle is currently not parked.
// ============================================================
void MainWindow::saveParkingData() {
    QString dataDir =
        QCoreApplication::applicationDirPath() + "/../data";
    // Make sure the data folder exists.
    QDir().mkpath(dataDir);
    // --------------------------------------------------------
    // Save vehicle records
    // --------------------------------------------------------
    QFile vehiclesFile(dataDir + "/vehicles.txt");
    if (vehiclesFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&vehiclesFile);
        for (const auto& vehicle : vehicles) {
            int slotNumber =
                parkingLot->findVehicleSlot(vehicle.get());
            QString vehicleNumber =
                QString::fromStdString(
                    vehicle->getVehicleNumber()
                );
            QString vehicleType =
                QString::fromStdString(
                    vehicle->getVehicleType()
                );
            QString ownerName =
                QString::fromStdString(
                    vehicle->getOwnerName()
                );
            // Avoid breaking the file format if a user enters '|'.
            vehicleNumber.replace("|", "/");
            vehicleType.replace("|", "/");
            ownerName.replace("|", "/");
            out << vehicleNumber << "|"
                << vehicleType << "|"
                << ownerName << "|"
                << slotNumber << "\n";
        }
        vehiclesFile.close();
    }
    // --------------------------------------------------------
    // Save currently occupied parking slots
    // --------------------------------------------------------
    QFile slotsFile(dataDir + "/parking_slots.txt");
    if (slotsFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&slotsFile);
        for (const auto& vehicle : vehicles) {
            int slotNumber =
                parkingLot->findVehicleSlot(vehicle.get());
            if (slotNumber != -1) {
                QString vehicleNumber =
                    QString::fromStdString(
                        vehicle->getVehicleNumber()
                    );
                vehicleNumber.replace("|", "/");
                out << slotNumber << "|"
                    << vehicleNumber << "\n";
            }
        }
        slotsFile.close();
    }
}

// ============================================================
// Load Parking Data
// ============================================================
//
// Loads vehicle records saved by saveParkingData().
// Vehicles with a valid slot number are restored to that slot.
// ============================================================
void MainWindow::loadParkingData() {
    QString dataDir =
        QCoreApplication::applicationDirPath() + "/../data";
    QFile vehiclesFile(dataDir + "/vehicles.txt");
    if (!vehiclesFile.exists()) {
        return;
    }
    if (!vehiclesFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    // Start with a clean in-memory state.
    vehicles.clear();
    QTextStream in(&vehiclesFile);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) {
            continue;
        }
        QStringList fields = line.split("|");
        // Expected format:
        // vehicleNumber|vehicleType|ownerName|slotNumber
        if (fields.size() != 4) {
            continue;
        }
        QString vehicleNumber = fields.at(0).trimmed();
        QString vehicleType = fields.at(1).trimmed();
        QString ownerName = fields.at(2).trimmed();
        bool slotOk = false;
        int slotNumber = fields.at(3).trimmed().toInt(&slotOk);
        if (vehicleNumber.isEmpty() ||
            vehicleType.isEmpty() ||
            ownerName.isEmpty() ||
            !slotOk) {
            continue;
        }
        auto vehicle =
            std::make_unique<Vehicle>(
                vehicleNumber.toStdString(),
                vehicleType.toStdString(),
                ownerName.toStdString()
            );
        Vehicle* vehiclePointer = vehicle.get();
        vehicles.push_back(std::move(vehicle));
        // Restore the parking position only if the vehicle
        // was parked when the application was closed.
        if (slotNumber != -1) {
            parkingLot->parkVehicleInSlot(
                vehiclePointer,
                slotNumber
            );
        }
    }
    vehiclesFile.close();
}
