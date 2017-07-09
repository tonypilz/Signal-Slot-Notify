TEMPLATE = app
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++98

SOURCES += main.cpp \
    ./testing/TestMain.cpp

HEADERS += \
    ./include/signal_slot.h \
    ./testing/TestMain.h \
    CompilerExplorerRunMethod.h

