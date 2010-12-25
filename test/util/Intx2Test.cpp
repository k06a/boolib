#ifndef INTX2TEST_H
#define INTX2TEST_H

#include <iostream>
#include "gtest/gtest.h"
#include "util.h"

//#define FULL_RANGE

#ifdef FULL_RANGE
#define RANGE_FROM -32768
#define RANGE_TO    32767
#else
#define RANGE_FROM -500
#define RANGE_TO    500
#endif

TEST(Intx2_i32, Add_1M_Times)
{
    using boolib::util::i16;
    using boolib::util::i32;
    
    for (short a = RANGE_FROM; a < RANGE_TO; a++)
    for (short b = RANGE_FROM; b < RANGE_TO; b++)
    {
        short sum_ab = a+b;
        
        i16 x = a;        
        i16 y = b;
        i16 sum_xy = x+y;

        EXPECT_EQ(sum_ab, sum_xy);
    }
}

TEST(Intx2_i32, Sub_1M_Times)
{
    using boolib::util::i16;
    using boolib::util::i32;
    
    for (short a = RANGE_FROM; a < RANGE_TO; a++)
    for (short b = RANGE_FROM; b < RANGE_TO; b++)
    {
        short sub_ab = a-b;
        
        i16 x = a;        
        i16 y = b;
        i16 sub_xy = x-y;

        EXPECT_EQ(sub_ab, sub_xy);
    }
}

TEST(Intx2_i32, Mul_1M_Times)
{
    using boolib::util::i16;
    using boolib::util::i32;
    
    for (short a = RANGE_FROM; a < RANGE_TO; a++)
    for (short b = RANGE_FROM; b < RANGE_TO; b++)
    {
        int mul_ab = a*b;
        
        i16 x = a;        
        i16 y = b;
        i32 mul_xy = x*y;

		EXPECT_EQ(mul_ab, mul_xy);
    }
}
/*
TEST(Intx2_i32, Div_1M_Times)
{
    using boolib::util::i16;
    using boolib::util::i32;
    
    for (short a = RANGE_FROM; a < RANGE_TO; a++)
    for (short b = RANGE_FROM; b < RANGE_TO; b++)
    {
		if (b == 0) continue;

        int div_ab = a/b;
        
        i16 x = a;        
        i16 y = b;
        i32 div_xy = x/y;

        if (div_xy != div_ab)
        {
            x = x;
        }

		EXPECT_EQ(div_ab, div_xy);
    }
}

TEST(Intx2_i32, Bitwise_Operators)
{
    using boolib::util::i16;
    using boolib::util::i32;
    
    i16 a = 5;
    a = a << 3;    EXPECT_EQ(a, 40);
    a = a >> 2;    EXPECT_EQ(a, 10);
    a <<= 3;       EXPECT_EQ(a, 80);
    a >>= 4;       EXPECT_EQ(a, 5);
}
*/
#endif // INTX2TEST_H
