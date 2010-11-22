#ifndef IPV6_HEADERTEST_H
#define IPV6_HEADERTEST_H

#include <iostream>
#include "net.h"

void ipv6_headerTest()
{
    using boolib::net::ip_address;
    using boolib::net::ip_header;
    using boolib::net::ipv6_header;
    
    bool testFailed = false;

    ip_address * ipa = new ip_address(ip_address::IPv6);
    if (ipa->size() != 16)
        testFailed = true;

    ipv6_header * ipv6h = new ipv6_header();
    ip_header * iph = (ip_header*)ipv6h;
    if ((ip_header*)iph != (ipv6_header*)iph)
        testFailed = true;
    if (iph->size() != 40)
        testFailed = true;

    ip_address ipv6a = iph->src_ip();
    ip_address ipv6b = iph->dst_ip();
    ipv6a->qwords[0] = 0x0102030405060708LL;
    ipv6a->qwords[1] = 0x090A0B0C0D0E0FFFLL;
    ipv6b->qwords[0] = 0x1112131415161718LL;
    ipv6b->qwords[1] = 0x191A1B1C1D1E1FFFLL;
    
    if ((ipv6h->src_data.qwords()[0] != 0x0102030405060708LL) ||
        (ipv6h->src_data.qwords()[1] != 0x090A0B0C0D0E0FFFLL) ||
        (ipv6h->dst_data.qwords()[0] != 0x1112131415161718LL) ||
        (ipv6h->dst_data.qwords()[1] != 0x191A1B1C1D1E1FFFLL))
    {
        testFailed = true;
    }

    delete ipa;
    delete iph;

    if (testFailed)
        std::cout << "ipv6_headerTest() failed" << std::endl;
}

#endif // IPV6_HEADERTEST_H
