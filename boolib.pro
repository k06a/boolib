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
    boolib/wrap.h \
    boolib/wrap/ReliableStreamDecorator.h \
    boolib/wrap/LengthStreamDecorator.h

HEADERS += \
    test/syncTest.h \
    test/sync/syncoutTest.h \
    test/sync/synchronizeTest.h \
    test/wrapTest.h \
    test/wrap/ReliableStreamDecoratorTest.h \
    test/wrap/LengthStreamDecoratorTest.h

INCLUDEPATH += \
    ./boolib \
    ./test
