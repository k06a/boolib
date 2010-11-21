#ifndef NETTEST_H
#define NETTEST_H

#include "./net/ip_headerTest.h"
#include "./net/ipv4_headerTest.h"
#include "./net/ipv6_headerTest.h"

void netTest()
{
    ip_headerTest();
    ipv4_headerTest();
    ipv6_headerTest();
}

#endif // NETTEST_H
