#-------------------------------------------------
#
# Project created by QtCreator 2014-09-21T16:09:27
#
#-------------------------------------------------

QT       += core gui

TARGET = QHRIR_AI_demo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    smarthrir.cpp \
    propertymanager.cpp \
    propertymanagerfactory.cpp \
    propertytreeview.cpp \
    stringconverter.cpp

HEADERS  += mainwindow.h \
    datamap.hpp \
    mutationsettings.h \
    smarthrir.h \
    propertymanager.h \
    propertymanagerfactory.h \
    propertytreeview.h \
    stringconverter.h \
    globalpropertieswrapper.h \
    runpropertieswrapper.h

FORMS    += mainwindow.ui

debug {
LIBS += -L"../lib/libs"\
        -lsmart_hrir_d -lhrir_d -lai_evol_d\
        -ldebug_util_d\
}
release {
LIBS += -L"../lib/libs"\
        -lsmart_hrir -lhrir -lai_evol\
        -ldebug_util\
}
INCLUDEPATH += ../libs/include

OTHER_FILES += \
    QHRIR_AI_demo.supp
