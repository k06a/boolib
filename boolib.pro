#-------------------------------------------------
#
# QtCreator project file
#
#-------------------------------------------------

TARGET =  boolib
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    main.cpp \
    gtest/src/gtest-all.cc

SOURCES += \
    test/algo/KaratsubaTest.cpp

HEADERS += \
    boolib/algo/Karatsuba.h \
    boolib/crypt.h \
    boolib/crypt/ShakedValue.h \
    boolib/net.h \
    boolib/net/ip_header.h \
    boolib/net/ipv4_header.h \
    boolib/net/ipv6_header.h \
    boolib/sync.h \
    boolib/sync/syncout.h \
    boolib/sync/synchronize.h \
    boolib/util.h \
    boolib/util/LittleBigEndian.h \
    boolib/wrap.h \
    boolib/wrap/ReliableStreamDecorator.h \
    boolib/wrap/LengthStreamDecorator.h

HEADERS += \
    test/cryptTest.h \
    test/crypt/ShakedValueTest.h \
    test/netTest.h \
    test/net/ip_headerTest.h \
    test/net/ipv4_headerTest.h \
    test/net/ipv6_headerTest.h \
    test/syncTest.h \
    test/sync/syncoutTest.h \
    test/sync/synchronizeTest.h \
    test/utilTest.h \
    test/util/LitteBigEndianTest.h \
    test/wrapTest.h \
    test/wrap/ReliableStreamDecoratorTest.h \
    test/wrap/LengthStreamDecoratorTest.h


INCLUDEPATH += \
    ./boolib \
    ./test \
    ./gtest \
    ./gtest/include/
