#include "cryptTest.h"
#include "netTest.h"
#include "syncTest.h"
#include "utilTest.h"
#include "wrapTest.h"

int main(int argc, char * argv[])
{
    cryptTest();
    netTest();
    syncTest();
    utilTest();
    wrapTest();
}
