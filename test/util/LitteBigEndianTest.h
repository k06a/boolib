#ifndef LITTLEBIGENDIANTEST_H
#define LITTLEBIGENDIANTEST_H

#include <iostream>
#include "util.h"

void LittleBigEndianTest()
{
    using boolib::util::LittleEndian;
    using boolib::util::BigEndian;

    bool testFailed = false;

    const int a = 0x90;
    const int b = 0x80;
    const int c = 0x70;
    const int d = 0x60;
    const int e = 0x15;
    const int f = 0x25;
    const int g = 0x35;
    const int h = 0x45;
    char mem[] =
    {
        (char)a,(char)b,(char)c,(char)d,
        (char)e,(char)f,(char)g,(char)h
    };

    // Little-Endian test

    LittleEndian<short> *le_int16 = (LittleEndian<short> *)mem;
    if (*le_int16 != (short)(a+(b<<8)))
        testFailed = true;

    LittleEndian<unsigned short> *le_uint16 = (LittleEndian<unsigned short> *)mem;
    if (*le_uint16 != (unsigned short)(a+(b<<8)))
        testFailed = true;

    LittleEndian<int> *le_int32 = (LittleEndian<int> *)mem;
    if (*le_int32 != (int)(a+(b<<8)+(c<<16)+(d<<24)))
        testFailed = true;

    LittleEndian<unsigned int> *le_uint32 = (LittleEndian<unsigned int> *)mem;
    if (*le_uint32 != (unsigned int)(a+(b<<8)+(c<<16)+(d<<24)))
        testFailed = true;

    // Big-Endian test

    BigEndian<short> *be_int16 = (BigEndian<short> *)mem;
    if (*be_int16 != (short)(b+(a<<8)))
        testFailed = true;

    BigEndian<unsigned short> *be_uint16 = (BigEndian<unsigned short> *)mem;
    if (*be_uint16 != (unsigned short)(b+(a<<8)))
        testFailed = true;

    BigEndian<int> *be_int32 = (BigEndian<int> *)mem;
    if (*be_int32 != (int)(d+(c<<8)+(b<<16)+(a<<24)))
        testFailed = true;

    BigEndian<unsigned int> *be_uint32 = (BigEndian<unsigned int> *)mem;
    if (*be_uint32 != (unsigned int)(d+(c<<8)+(b<<16)+(a<<24)))
        testFailed = true;

    if (testFailed)
        std::cout << "LittleBigEndianTest() failed" << std::endl;
}

#endif // LITTLEBIGENDIANTEST_H