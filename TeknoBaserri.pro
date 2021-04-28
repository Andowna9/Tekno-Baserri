TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

# SOURCES C

SOURCES += src/main.c \
           src/console/console_config.c \
           src/farm/animal_food/food.c \
           src/farm/animal_food/food_menu.c \
           src/farm/animals.c \
           src/farm/crops.c \
           src/farm/farm.c \
           src/farm/lands/lands_menu.c \
           src/farm/management/management.c \
           src/farm/lands/lands.c \
           src/farm/management/management_menu.c \
           src/parking/parking.c \
           src/parking/parking_menu.c \
           src/utils/logger.c \
           src/utils/dynamic_array.c \
           src/utils/std_utils.c \
           src/utils/database/sqlite3.c

# SOURCES C++

SOURCES += src/parking/vehicle/Vehicle.cpp \
           src/utils/database/DBManager.cpp

HEADERS += src/console/console_config.h \
    src/farm/animal_food/food.h \
    src/farm/animal_food/food_menu.h \
    src/farm/lands/lands_menu.h \
    src/farm/management/management_menu.h \
    src/parking/parking.h \
    src/parking/parking_menu.h \
    src/farm/*.h \
    include/*.h \
    src/parking/vehicle/Vehicle.h

INCLUDEPATH += include/
