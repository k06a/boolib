#-------------------------------------------------
#
# QtCreator project file
#
#-------------------------------------------------

TARGET =  boolib
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

HEADERS += \
    boolib/sync.h \
    boolib/sync/syncout.h \
    boolib/sync/synchronize.h \
    test/syncTest.h \
    test/sync/syncoutTest.h \
    test/sync/synchronizeTest.h

INCLUDEPATH += \
    ./boolib \
    ./test
