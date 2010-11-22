#ifndef IP_HEADERTEST_H
#define IP_HEADERTEST_H

#include <iostream>
#include "net.h"

void ip_headerTest()
{
    using boolib::net::ip_ad;
    using boolib::net::ip_data;

    bool testFailed = false;

    char a[] = "abcdef";
    ip_data * b = (ip_data *)(a+1);
    b->bytes[0] = '0';
    b->bytes[1] = '1';
    b->bytes[2] = '2';
    b->bytes[3] = '3';
    if (memcmp(a, "a0123f", 6) != 0)
        testFailed = true;

    if (testFailed)
        std::cout << "ip_headerTest() failed" << std::endl;
}

#endif // IP_HEADERTEST_H
