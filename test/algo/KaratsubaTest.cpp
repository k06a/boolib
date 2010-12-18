#include <iostream>
#include "algo.h"
#include "gtest/gtest.h"

TEST(KaratsubaMultiplication, ShortIntTime)
{
    unsigned int c = 0;
    for (unsigned short a = 0; a < 1000; a++)
    for (unsigned short b = 0; b < 1000; b++)
    {
        unsigned  char * x = (unsigned  char *)&a;
        unsigned  char * y = (unsigned  char *)&b;
        unsigned short * r = (unsigned short *)&c;
    
        c = a*b;
        EXPECT_EQ(a*b, c);
    }
}

TEST(KaratsubaMultiplication, KaratsubaTime)
{
    unsigned int c = 0;
    for (unsigned short a = 0; a < 1000; a++)
    for (unsigned short b = 0; b < 1000; b++)
    {
        unsigned  char * x = (unsigned  char *)&a;
        unsigned  char * y = (unsigned  char *)&b;
        unsigned short * r = (unsigned short *)&c;
    
        boolib::algo::Karatsuba_multiply(x,y,r);
        EXPECT_EQ(a*b, c);
    }
}