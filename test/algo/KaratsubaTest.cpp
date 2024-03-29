#include <iostream>
#include "algo.h"
#include "gtest/gtest.h"

TEST(KaratsubaMultiplication, 64K_Times)
{
    unsigned int c = 0;
    for (unsigned short a = 0; a < 800; a++)
    for (unsigned short b = 0; b < 800; b++)
    {
        unsigned  char * x = (unsigned  char *)&a;
        unsigned  char * y = (unsigned  char *)&b;
        unsigned short * r = (unsigned short *)&c;
    
        boolib::algo::Karatsuba_multiply(x,y,r);
        EXPECT_EQ((unsigned)a*b, c);
    }
}
