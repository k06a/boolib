#ifndef IPV6_HEADER_H
#define IPV6_HEADER_H

#include "ip_header.h"
#include "util/LittleBigEndian.h"

namespace boolib
{
    namespace net
    {

        //
        // IPv4 Address Format
        //

        struct ip_address;
        struct ip_address_abstarct;
        struct ip_header;
        struct ip_header_abstarct;


        #pragma pack(push,1)
        struct ipv6_address : public ip_address_abstract<ipv6_address>
        {
            union {
                unsigned __int64 qwords[2];
                unsigned     int dwords[4];
                unsigned   short  words[8];
                unsigned    char bytes[16];
            };

            virtual int size() const
            {
                return 16;
            }

            virtual int version() const
            {
                return 6;
            }
        };
        #pragma pack(pop)

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

	        mutable ipv6_address src;
            mutable ipv6_address dst;
            
            // ----------------------------------------------

            virtual int size() const
            {
                return 40;
            }

            virtual ip_address & src_ip() const
            {
                return reinterpret_cast<ip_address&>(src);
            }

            virtual ip_address & dst_ip() const
            {
                return reinterpret_cast<ip_address&>(dst);
            }
        };
        #pragma pack(pop)

    }
    // namespace net
}
// namespace boolib

#endif // IPV6_HEADER_H
