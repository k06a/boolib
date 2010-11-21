#ifndef IPV4_HEADERTEST_H
#define IPV4_HEADERTEST_H

#include <iostream>
#include "net.h"

void ipv4_headerTest()
{
    using boolib::net::ip_address;
    using boolib::net::ip_header;
    using boolib::net::ipv4_address;
    using boolib::net::ipv4_header;
    
    bool testFailed = false;

    ip_address * ipa = new ipv4_address();
    if ((ip_address*)ipa != (ipv4_address*)ipa)
        testFailed = true;
    if (ipa->size() != 4)
        testFailed = true;

    ipv4_header * ipv4h = new ipv4_header();
    ip_header * iph = (ip_header*)ipv4h;
    if (ipv4h != iph)
        testFailed = true;
    if (iph->size() != 20)
        testFailed = true;
    
    ipv4_address * ipv4a = (ipv4_address*)&iph->src_ip();
    ipv4_address * ipv4b = (ipv4_address*)&iph->dst_ip();
    ipv4a->dword = 0x01020304;
    ipv4b->dword = 0x11223344;
    if ((ipv4h->src.dword != 0x01020304) || (ipv4h->dst.dword != 0x11223344))
        testFailed = true;

    delete ipa;
    delete iph;

    if (testFailed)
        std::cout << "ipv4_headerTest() failed" << std::endl;
}

#endif // IPV4_HEADERTEST_H