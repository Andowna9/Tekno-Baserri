TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

QT += core

# SOURCES C

SOURCES += src/console/console_config.c \
           src/farm/lands/animals/food/food.c \
           src/farm/lands/animals/food/food_menu.c \
           src/farm/farm.c \
           src/farm/management/management.c \
           src/farm/management/management_menu.c \
           src/parking/parking.c \
           src/utils/logger.c \
           src/utils/dynamic_array.c \
           src/utils/std_utils.c


# SOURCES C++

SOURCES += src/main.cpp \
           src/parking/vehicle/Vehicle.cpp \
           src/utils/database/DBManager.cpp \
           src/parking/parking_menu.cpp \
           src/farm/lands/animals/Animal.cpp \
           src/farm/lands/animals/animals_menu.cpp \
           src/farm/lands/crops/crops.cpp \
           src/farm/lands/Terrain.cpp \
           src/farm/lands/lands_menu.cpp

HEADERS += src/console/console_config.h \
    src/farm/lands/Terrain.h \
    src/farm/lands/animals/Animal.h \
    src/farm/lands/animals/food/food.h \
    src/farm/lands/animals/food/food_menu.h \
    src/farm/lands/lands_menu.h \
    src/farm/management/management_menu.h \
    src/parking/parking.h \
    src/parking/parking_menu.h \
    src/farm/*.h \
    include/*.h \
    src/parking/vehicle/Vehicle.h \
    src/farm/lands/crops/crops.h

INCLUDEPATH += include/

# Sqlite3

SOURCES += 3rdparty/sqlite3/src/sqlite3.c
HEADERS += 3rdparty/sqlite3/include/sqlite3.h
INCLUDEPATH += 3rdparty/sqlite3/include/

# Database 4 Unix

unix {

    LIBS += -lpthread -ldl -lm
}
