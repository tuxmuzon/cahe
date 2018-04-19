#-------------------------------------------------
#
# Project created by QtCreator 2016-02-04T10:33:57
#
#-------------------------------------------------

QT       += core gui sql
#if defined(Q_OS_WIN32)
#QT       += axcontainer
#endif
QT       += network
#QT       += activeqt
#QT       += core gui widgets axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RR_Cash
TEMPLATE = app


SOURCES += main.cpp\
        rr_cash.cpp \
    fiscal.cpp \
    egais.cpp \
    servicedialog.cpp \
    additionaly.cpp \
    priceinput.cpp


HEADERS  += rr_cash.h \
    fiscal.h \
    egais.h \
    servicedialog.h \
    additionaly.h \
    priceinput.h


FORMS    += \
    rr_cash.ui \
    servicedialog.ui \
    additionaly.ui \
    priceinput.ui

#INCLUDEPATH += D://Qt//

#LIBS += -L"C:\Qt" -ldrvFR #" "c:\Program Files\SHTRIH-M\DrvFR 4.12\Bin\"
#LIBS += -lqaxserver
#LIBS += -lqaxcontainer -loleaut32 -lole32 -lgdi32 -luuid


#write QT += axcontainer

