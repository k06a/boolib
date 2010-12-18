#include "cryptTest.h"
#include "netTest.h"
#include "syncTest.h"
#include "utilTest.h"
#include "wrapTest.h"
#include "gtest/gtest.h"

int main(int argc, char * argv[])
{
    cryptTest();
    netTest();
    syncTest();
    utilTest();
    wrapTest();

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
