#ifndef IP_HEADERTEST_H
#define IP_HEADERTEST_H

#include <iostream>
#include "net.h"

void ip_headerTest()
{
    using boolib::net::ip_address;
    using boolib::net::ipv4_address;
    using boolib::net::ipv6_address;
    using boolib::net::ip_header;

    bool testFailed = false;

    if (53974 != ip_header::countSum((char*)"abcd1234", 8))
        testFailed = true;

    ipv4_address ipv4_1;
    ipv4_address ipv4_2;
    ipv4_address ipv4_3;
    ipv6_address ipv6_1;
    ipv6_address ipv6_2;
    ipv6_address ipv6_3;
    
    ipv4_1.dword = 0x7f000001;
    ipv4_2.dword = 0x7f000001;
    ipv4_3.dword = 0x7f000002;
    
    ipv6_1.qwords[0] = 0x7f0000017f000001LL;
    ipv6_1.qwords[1] = 0x7f0000017f000001LL;
    ipv6_2.qwords[0] = 0x7f0000017f000001LL;
    ipv6_2.qwords[1] = 0x7f0000017f000001LL;
    ipv6_3.qwords[0] = 0x7f0000027f000002LL;
    ipv6_3.qwords[1] = 0x7f0000027f000002LL;
    
    if ((ipv4_1 != ipv4_2) || (ipv4_2 == ipv4_3))
        testFailed = true;

    if ((ipv6_1 != ipv6_2) || (ipv6_2 == ipv6_3))
        testFailed = true;

    if ((ipv4_1 == ipv6_1) || (ipv4_2 == ipv6_2) || (ipv4_3 == ipv6_3))
        testFailed = true;

    if (testFailed)
        std::cout << "ip_headerTest() failed" << std::endl;
}

#endif // IP_HEADERTEST_H
