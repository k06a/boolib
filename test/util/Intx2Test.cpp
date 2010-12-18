#ifndef INTX2TEST_H
#define INTX2TEST_H

#include "gtest/gtest.h"
#include "util.h"

using namespace boolib::util;

TEST(Intx2Test, SumTest)
{
    //using boolib::util::u32;
    //using boolib::util::u64;

    for (unsigned short a = 0; a < 1000; a++)
    for (unsigned short b = 0; b < 1000; b++)
    {
        //unsigned int r1 = a+b;
        u32 r1 = a+b;
        
        u32 x = a;
        u32 y = b;
        u32 r2 = x+y;

        EXPECT_EQ(r1, r2);
    }
/*
    for (unsigned int a = 0; a < 1000; a++)
    for (unsigned int b = 0; b < 1000; b++)
    {
        //unsigned __int64 r1 = ((unsigned __int64)a) + ((unsigned __int64)b);
        u64 r1 = ((unsigned __int64)a) + ((unsigned __int64)b);
        
        u64 x = a;
        u64 y = b;
        u64 r2 = x+y;

        EXPECT_EQ(r1, r2);
    }
*/
}

#endif // INTX2TEST_H
