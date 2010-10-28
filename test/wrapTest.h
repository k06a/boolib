#ifndef WRAPTEST_H
#define WRAPTEST_H

#include "./wrap/LengthStreamDecoratorTest.h"
#include "./wrap/ReliableStreamDecoratorTest.h"

void wrapTest()
{
    LengthControlStreamTest();
    ReliableControlStreamTest();
}

#endif // WRAPTEST_H
