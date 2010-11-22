#ifndef IPV4_HEADERTEST_H
#define IPV4_HEADERTEST_H

#include <iostream>
#include "net.h"

void ipv4_headerTest()
{
    using boolib::net::ip_address;
    using boolib::net::ip_header;
    using boolib::net::ipv4_header;
    
    bool testFailed = false;

    ip_address * ipa = new ip_address(ip_address::IPv4);
    if (ipa->size() != 4)
        testFailed = true;

    ip_address * ipb = new ip_address(ip_address::IPv6);
    if (ipb->size() != 16)
        testFailed = true;

    ipv4_header * ipv4h = new ipv4_header();
    ip_header * iph = (ip_header*)ipv4h;
    if (ipv4h != iph)
        testFailed = true;
    if (iph->size() != 20)
        testFailed = true;
    
    ip_address ipv4a = iph->src_ip();
    ip_address ipv4b = iph->dst_ip();
    ipv4a->dwords[0] = 0x01020304;
    ipv4b->dwords[0] = 0x11223344;
    if ((ipv4h->src_data.dwords[0] != 0x01020304)
     || (ipv4h->dst_data.dwords[0] != 0x11223344))
    {
        testFailed = true;
    }

    delete ipa;
    delete iph;

    if (testFailed)
        std::cout << "ipv4_headerTest() failed" << std::endl;
}

#endif // IPV4_HEADERTEST_H