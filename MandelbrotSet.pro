TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += include/

QMAKE_CXXFLAGS_RELEASE += -Ofast

SOURCES += \
    src/main.cc \
    src/Mandelbrot/ComplexNumber.cc \
    src/Mandelbrot/Mandelbrot.cc

unix:!macx: LIBS += -lsfml-system -lsfml-window -lsfml-graphics

HEADERS += \
    include/Mandelbrot/ComplexNumber.hpp \
    include/Mandelbrot/Mandelbrot.hpp
