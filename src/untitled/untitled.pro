QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
VERSION = 2.0.0.1
QMAKE_TARGET_COMPANY = JesusAha
QMAKE_TARGET_PRODUCT = SmartCalc_21
QMAKE_TARGET_COPYRIGHT = JesusAha_school_21

CONFIG += c++17
CONFIG += warn_off

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../model/s21_calc.cc \
   ../model/s21_sort.cc \
   ../model/s21_credits.cc \
   ../model/s21_deposid.cc \
    ../model/s21_val.cc \
    ../view/credit.cc \
    ../view/depos.cc \
    main.cpp \
    ../view/mainwindow.cc \
    qcustomplot.cpp \


HEADERS += \
    ../controller/s21_controller_calc.h\
    ../controller/s21_controller_credit.h\
    ../controller/s21_controller_dep.h\
    ../model/s21_credits.h \
    ../model/s21_sort.h \
    ../model/s21_calc.h \
    ../model/s21_deposid.h \
    ../model/s21_val.h \
    ../view/graf.h \
    ../view/credit.h \
    ../view/depos.h \
    ../view/mainwindow.h \
    qcustomplot.h

FORMS += \
    ../view/credit.ui \
    ../view/depos.ui \
    ../view/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
