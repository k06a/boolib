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
            //virtual ~ip_address() {}

            virtual int size() const = 0;
            virtual char * data() const = 0;
            virtual int version() const = 0;

            bool operator == (const ip_address & address) const
            {
                int sz = this->size();
                int * a = (int*)this->data();
                int * b = (int*)address.data();
                int ret = memcmp(a, b, sz);

                return (sz == address.size()) &&
                       (memcmp(this->data(), address.data(), sz) == 0);
            }

            bool operator != (const ip_address & address) const
            {
                return !(*this == address);
            }

            bool operator < (const ip_address & address) const
            {
                int sz = this->size();
                return (sz <= address.size()) &&
                       (memcmp(this, &address, sz) < 0);
            }
        };
        #pragma pack(pop)
        
        #pragma pack(push,1)
        template<typename T>
        struct ip_address_abstract : public ip_address
        {
            virtual ~ip_address_abstract() {}

            virtual int size() const = 0;

            virtual char * data() const
            {
                // +4 - is HACK to skip Virtual Class Table pointer
                return ((char*)(T*)this) + 4;
            }

            operator T & () const
            {
                return reinterpret_cast<T&>(*this);
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

            virtual int size() const = 0;
            virtual char * data() const = 0;
            virtual ip_address & src_ip() const = 0;
            virtual ip_address & dst_ip() const = 0;

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

            virtual int size() const = 0;

            virtual char * data() const
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
