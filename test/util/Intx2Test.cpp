#ifndef INTX2TEST_H
#define INTX2TEST_H

#include <iostream>
#include "gtest/gtest.h"
#include "util.h"

TEST(Intx2_i32, Add_1M_Times)
{
    using boolib::util::i16;
    using boolib::util::i32;
    
    for (short a = -500; a < 500; a++)
    for (short b = -500; b < 500; b++)
    {
        int sum_ab = a+b;
        
        i16 x = a;        
        i16 y = b;
        i32 sum_xy = x+y;

        EXPECT_EQ(sum_ab, sum_xy);
    }
}

TEST(Intx2_i32, Sub_1M_Times)
{
    using boolib::util::i16;
    using boolib::util::i32;
    
    for (short a = -500; a < 500; a++)
    for (short b = -500; b < 500; b++)
    {
        int sub_ab = a+b;
        
        i16 x = a;        
        i16 y = b;
        i32 sub_xy = x+y;

        EXPECT_EQ(sub_ab, sub_xy);
    }
}

TEST(Intx2_i32, Mul_1M_Times)
{
    using boolib::util::i16;
    using boolib::util::i32;
    
    for (short a = -500; a < 500; a++)
    for (short b = -500; b < 500; b++)
    {
        int mul_ab = a*b;
        
        i16 x = a;        
        i16 y = b;
        i32 mul_xy = x*y;

		EXPECT_EQ(mul_ab, mul_xy);
    }
}

#endif // INTX2TEST_H
