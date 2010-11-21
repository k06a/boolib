#ifndef IP_HEADERTEST_H
#define IP_HEADERTEST_H

#include <iostream>
#include "net.h"

void ip_headerTest()
{
    using boolib::net::ip_address;
    using boolib::net::ip_header;

    bool testFailed = false;

    if (53974 != ip_header::countSum((char*)"abcd1234", 8))
        testFailed = true;

    if (testFailed)
        std::cout << "ip_headerTest() failed" << std::endl;
}

#endif // IP_HEADERTEST_H
