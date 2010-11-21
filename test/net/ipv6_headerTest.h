#ifndef IPV6_HEADERTEST_H
#define IPV6_HEADERTEST_H

#include <iostream>
#include "net.h"

void ipv6_headerTest()
{
    using boolib::net::ip_address;
    using boolib::net::ip_header;
    using boolib::net::ipv6_address;
    using boolib::net::ipv6_header;
    
    bool testFailed = false;

    ip_address * ipa = new ipv6_address();
    if ((ip_address*)ipa != (ipv6_address*)ipa)
        testFailed = true;
    if (ipa->size() != 16)
        testFailed = true;

    ipv6_header * ipv6h = new ipv6_header();
    ip_header * iph = (ip_header*)ipv6h;
    if ((ip_header*)iph != (ipv6_header*)iph)
        testFailed = true;
    if (iph->size() != 40)
        testFailed = true;

    ipv6_address * ipv6a = (ipv6_address*)&iph->src_ip();
    ipv6_address * ipv6b = (ipv6_address*)&iph->dst_ip();
    ipv6a->qwords[0] = 0x0102030405060708LL;
    ipv6a->qwords[1] = 0x090A0B0C0D0E0FFFLL;
    ipv6b->qwords[0] = 0x1112131415161718LL;
    ipv6b->qwords[1] = 0x191A1B1C1D1E1FFFLL;
    
    if ((ipv6h->src.qwords[0] != 0x0102030405060708LL) ||
        (ipv6h->src.qwords[1] != 0x090A0B0C0D0E0FFFLL) ||
        (ipv6h->dst.qwords[0] != 0x1112131415161718LL) ||
        (ipv6h->dst.qwords[1] != 0x191A1B1C1D1E1FFFLL))
    {
        testFailed = true;
    }

    delete ipa;
    delete iph;

    if (testFailed)
        std::cout << "ipv6_headerTest() failed" << std::endl;
}

#endif // IPV6_HEADERTEST_H
