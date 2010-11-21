#ifndef IP_HEADER_H
#define IP_HEADER_H

#include "util/LittleBigEndian.h"

namespace boolib
{
    namespace net
    {

        //
        // IP Address Interface
        //

        struct ipv4_address;
        struct ipv6_address;

        #pragma pack(push,1)
        struct ip_address
        {
            virtual ~ip_address() {}

            virtual int size() = 0;
            virtual char * data() = 0;
            virtual int version() = 0;
        };
        #pragma pack(pop)
        
        #pragma pack(push,1)
        template<typename T>
        struct ip_address_abstract : public ip_address
        {
            virtual ~ip_address_abstract() {}

            virtual int size() = 0;

            virtual char * data()
            {
                return (char*)(T*)this;
            }
        };
        #pragma pack(pop)
        
        //
        // IP Header Interface
        //
        
        #pragma pack(push,1)
        struct ip_header
        {
            virtual ~ip_header() {}

            virtual int size() = 0;
            virtual char * data() = 0;
            virtual ip_address & src_ip() = 0;
            virtual ip_address & dst_ip() = 0;

            static unsigned short countSum(char * buffer, unsigned short length)
            {
                unsigned int sum = 0;

                for (char * end = buffer + length; buffer < end; buffer+=2)
                    sum += (*buffer<<8) | *(buffer+1);
                
                while (sum >> 16)
                    sum = (sum & 0xffff) + (sum >> 16);

                return ~((sum >> 8) | (sum << 8));
            }
        };
        #pragma pack(pop)

        #pragma pack(push,1)
        template<typename T>
        struct ip_header_abstract : ip_header
        {
            virtual ~ip_header_abstract() {}

            virtual int size() = 0;

            virtual char * data()
            {
                return (char*)(T*)this;
            }
        };
        #pragma pack(pop)

    }
    // namespace net
}
// namespace boolib

#endif // IP_HEADER_H
