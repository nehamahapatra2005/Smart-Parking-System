#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <memory>
#include <vector>

class ThemeToggle;
class QLabel;
class QFrame;

class Vehicle;
class ParkingLot;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    // Changes between dark and light mode
    void applyTheme(bool darkMode);

    // Opens the vehicle parking form
    void openParkVehicleDialog();

    // Opens the checkout form
    void openCheckoutDialog();

    // Opens the vehicle search form
    void openSearchVehicleDialog();

    // Updates the parking dashboard
    void updateParkingDashboard();

    // Updates one individual parking slot card
    void updateSlotCard(int slotNumber);

    // Saves current vehicle and parking information
    void saveParkingData();

    // Loads previously saved vehicle and parking information
    void loadParkingData();

    ThemeToggle* themeSwitch;

    // Parking system backend
    ParkingLot* parkingLot;

    // Keeps all Vehicle objects alive
    std::vector<std::unique_ptr<Vehicle>> vehicles;

    // Dashboard labels
    QLabel* totalNumberLabel;
    QLabel* availableNumberLabel;
    QLabel* occupiedNumberLabel;
    QLabel* activityText;

    // Parking slot GUI cards
    std::vector<QFrame*> slotCards;
    std::vector<QLabel*> slotStatusLabels;
    std::vector<QLabel*> slotVehicleLabels;
};

#endif