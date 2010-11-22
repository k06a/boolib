#ifndef IPV6_HEADER_H
#define IPV6_HEADER_H

#include "ip_header.h"
#include "util/LittleBigEndian.h"

namespace boolib
{
    namespace net
    {

        //
        // IPv6 Header Format
        //
        // /---------------+---------------+---------------+---------------|
        // |7 6 5 4 3 2 1 0|7 6 5 4 3 2 1 0|7 6 5 4 3 2 1 0|7 6 5 4 3 2 1 0|
        // +-------+-------+-------+-------+---------------+---------------+
        // |  Ver  | Traffic Class |              Flow Label               |
        // +-------+-------+-------+-------+---------------+---------------+
        // |         Payload Length        |  Next Header  |   Hop Limit   |
        // +---------------+---------------+---------------+---------------+
        // |                  Source IP address (16 bytes)                 |
        // +---------------------------------------------------------------+
        // |               Destination IP address (16 bytes)               |
        // \---------------------------------------------------------------/
        //
        
        #pragma pack(push,1)
        struct ipv6_header : public ip_header_abstract<ipv6_header>
        {
            // ---------------- Fisrt DWORD ----------------
            
            unsigned  int version:4;
            unsigned  int trafficClass:8;
            unsigned  int flowLabel:20;

            // ---------------- Second DWORD ----------------
            
            unsigned short payloadLength;
            unsigned  char nextHeader;
            unsigned  char hopLimit;

            // ----------------  3-10 DWORDS ----------------

            mutable ipv6_data src_data;
            
            virtual ip_address src_ip() const
            {
                return ip_address(ip_address::IPv6, &src_data);
            }

            mutable ipv6_data dst_data;
            
            virtual ip_address dst_ip() const
            {
                return ip_address(ip_address::IPv6, &dst_data);
            }

            // ----------------------------------------------

            virtual int size() const
            {
                return 40;
            }
        };
        #pragma pack(pop)

    }
    // namespace net
}
// namespace boolib

#endif // IPV6_HEADER_H
