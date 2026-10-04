QT += widgets

CONFIG += c++17

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    ThemeToggle.cpp \
    ../src/Vehicle.cpp \
    ../src/ParkingSlot.cpp \
    ../src/ParkingLot.cpp \
    ../src/Ticket.cpp \
    ../src/Billing.cpp

HEADERS += \
    MainWindow.h \
    ThemeToggle.h \
    ../include/Vehicle.h \
    ../include/ParkingSlot.h \
    ../include/ParkingLot.h \
    ../include/Ticket.h \
    ../include/Billing.h