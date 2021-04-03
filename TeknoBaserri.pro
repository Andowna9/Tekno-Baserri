TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += src/main.c \
           src/console/console_config.c \
           src/farm/animal_food.c \
           src/farm/animals.c \
           src/farm/crops.c \
           src/farm/farm.c \
           src/farm/management/management.c \
           src/farm/lands.c \
           src/parking/parking.c \
           src/parking/parking_menu.c \
           src/utils/stdin_fix.c

HEADERS += src/console/console_config.h \
    src/parking/parking.h \
    src/parking/parking_menu.h \
    src/farm/*.h \
    include/*.h

INCLUDEPATH += include/
