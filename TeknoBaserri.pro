TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

QT = core
QT += xml

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
           src/farm/lands/Terrain.cpp \
           src/farm/lands/lands_menu.cpp \
           src/farm/lands/WeatherForecast.cpp


HEADERS += src/farm/lands/Terrain.h \
           src/farm/lands/animals/Animal.h \
           src/farm/lands/animals/food/food.h \
           src/farm/lands/animals/food/food_menu.h \
           src/farm/lands/lands_menu.h \
           src/farm/management/management_menu.h \
           src/parking/parking.h \
           src/parking/parking_menu.h \
           src/parking/vehicle/Vehicle.h \
           src/farm/lands/WeatherForecast.h

INCLUDEPATH += include/

# Sqlite3

SOURCES += 3rdparty/sqlite3/src/sqlite3.c
HEADERS += 3rdparty/sqlite3/include/sqlite3.h
INCLUDEPATH += 3rdparty/sqlite3/include/

# libcurl

win32 {

    INCLUDEPATH += C:\dev\libcurl\include
    LIBS += C:\dev\libcurl\bin\libcurl-x64.dll
}

# SOON - Linux support

# Database 4 Unix

unix {

    LIBS += -lpthread -ldl -lm
}
