TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += src/main.c \
           src/console/console_config.c \
           src/parking/parking.c \
           src/parking/parking_menu.c \
           src/granja/granja.c src/granja/alimentos.c src/granja/cultivos.c src/granja/terrenos.c src/granja/animales.c src/granja/gestion/gestion.c\
           src/utils/stdin_fix.c

HEADERS += src/console/console_config.h \
    src/parking/parking.h \
    src/parking/parking_menu.h \
    src/granja/*.h \
    include/*.h

INCLUDEPATH += include/
