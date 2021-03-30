TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += src/main.c \
           src/console/console_config.c \
           src/parking/parking.c \
           src/parking/parking_menu.c \
           src/utils/stdin_fix.c

HEADERS += src/console/console_config.h \
    src/parking/parking.h \
    src/parking/parking_menu.h \
    include/*.h

INCLUDEPATH += include/
