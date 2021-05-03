TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

QT += core

# SOURCES C

SOURCES += src/main.c \
           src/console/console_config.c \
           src/farm/animals/food/food.c \
           src/farm/animals/food/food_menu.c \
           src/farm/animals/animals_menu.c \
           src/farm/farm.c \
           src/farm/lands/lands_menu.c \
           src/farm/management/management.c \
           src/farm/lands/lands.c \
           src/farm/management/management_menu.c \
           src/parking/parking.c \
           src/utils/logger.c \
           src/utils/dynamic_array.c \
           src/utils/std_utils.c \
           src/utils/database/sqlite3.c

# SOURCES C++

SOURCES += src/parking/vehicle/Vehicle.cpp \
           src/utils/database/DBManager.cpp \
           src/parking/parking_menu.cpp \
           src/farm/animals/animal/Animal.cpp \
           src/farm/animals/animal/animals_management.cpp \
           src/farm/crops/crops.cpp \

HEADERS += src/console/console_config.h \
    src/farm/animals/animal/Animal.h \
    src/farm/animals/animal/animals_management.h \
    src/farm/animals/food/food.h \
    src/farm/animals/food/food_menu.h \
    src/farm/lands/lands_menu.h \
    src/farm/management/management_menu.h \
    src/parking/parking.h \
    src/parking/parking_menu.h \
    src/farm/*.h \
    include/*.h \
    src/parking/vehicle/Vehicle.h \
    src/farm/animal/Animal.h \
    src/farm/crops/crops.h

INCLUDEPATH += include/

# Database 4 Unix
unix {
    LIBS += -lpthread -ldl -lm
}
