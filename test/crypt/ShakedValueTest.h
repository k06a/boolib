#ifndef SHAKEDVALUETEST_H
#define SHAKEDVALUETEST_H

#include <iostream>
#include "crypt.h"

void ShakedValueTest()
{
    bool testFailed = false;

    #define AssertCompare(a,b) if (a != b) testFailed = true;

    #define PARAM_TYPE char
    #define MIN_VALUE -128
    #define MAX_VALUE  127

    for (PARAM_TYPE i = MIN_VALUE; i < MAX_VALUE; i++)
    {
        PARAM_TYPE a = i;

        boolib::crypt::ShakedValue<char> value = a;
        AssertCompare(value, a);

        value = a;
        AssertCompare(value, a);

        a++;    value++;    AssertCompare(value, a);
        a--;    value--;    AssertCompare(value, a);
        ++a;    ++value;    AssertCompare(value, a);
        --a;    --value;    AssertCompare(value, a);
        ++++a;  ++++value;  AssertCompare(value, a);
        ----a;  ----value;  AssertCompare(value, a);

        for (PARAM_TYPE j = MIN_VALUE; j < MAX_VALUE; j++) {
            a+=j;   value+=j;   AssertCompare(value, a);
        }

        for (PARAM_TYPE j = MIN_VALUE; j < MAX_VALUE; j++) {
            a-=j;   value-=j;   AssertCompare(value, a);
        }

        for (PARAM_TYPE j = MIN_VALUE; j < MAX_VALUE; j++) {
            a*=j;   value*=j;   AssertCompare(value, a);
        }

        for (PARAM_TYPE j = MIN_VALUE; j < MAX_VALUE; j++) {
            if (j == 0) continue;
            a/=j;   value/=j;   AssertCompare(value, a);
        }
    }

    #undef PARAM_TYPE
    #undef MIN_VALUE
    #undef MAX_VALUE

    if (testFailed)
        std::cout << "ShakedValueTest() failed" << std::endl;
}

#endif // SHAKEDVALUETEST_H