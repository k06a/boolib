#include "cryptTest.h"
#include "syncTest.h"
#include "utilTest.h"
#include "wrapTest.h"

int main(int argc, char * argv[])
{
    cryptTest();
    syncTest();
    utilTest();
    wrapTest();
}
