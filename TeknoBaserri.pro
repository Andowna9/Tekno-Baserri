TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += src/main.c \
           src/console/console_config.c \
           src/granja/animal_food.c \
           src/granja/animals.c \
           src/granja/crops.c \
           src/granja/farm.c \
           src/granja/management/management.c \
           src/granja/lands.c \
           src/parking/parking.c \
           src/parking/parking_menu.c \
           src/utils/stdin_fix.c

HEADERS += src/console/console_config.h \
    src/parking/parking.h \
    src/parking/parking_menu.h \
    src/granja/*.h \
    include/*.h

INCLUDEPATH += include/
