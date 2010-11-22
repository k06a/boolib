#ifndef IP_HEADER_H
#define IP_HEADER_H

#include "util/LittleBigEndian.h"

namespace boolib
{
    namespace net
    {

        #pragma pack(push,1)
        struct ip_data
        {
            #pragma warning(push)
            #pragma warning(disable:4200)
            union {
                unsigned  char bytes[];
                unsigned short words[];
                unsigned   int dwords[];
                unsigned long long qwords[];
            };
            #pragma warning(pop)
        };
        #pragma pack(pop)
        
        #pragma pack(push,1)
        struct ip_ad
        {
            enum ip_version {
                IPv4 = 4,
                IPv6 = 6
            };

            ip_version version;
            ip_data * ptr;

            ip_ad(ip_version version, char * existing = NULL)
                :  version(version), ptr((ip_data*)existing)
            {
                if (ptr == NULL)
                    ptr = (ip_data*)(new char [(version == 4) ? 4 : 16]);
            }
        };
        #pragma pack(pop)

        #pragma pack(push,1)
        template<unsigned T>
        struct ip_addr
        {
            #pragma warning(push)
            #pragma warning(disable:4200)
            union {
                unsigned  char bytes[T];
                unsigned short words[T/2];
                unsigned   int dwords[T/4];
                unsigned long long qwords[T/8];
            };
            #pragma warning(pop)
            
            unsigned char * data() const
            {
                return (unsigned char *)this;
            }

            unsigned size() const
            {
                return T;
            }

            template<unsigned T2>
            bool operator == (const ip_addr<T2> & value) const
            {
                return (T == T2) && (memcmp(this, &value, T) == 0);
            }

            template<unsigned T2>
            bool operator != (const ip_addr<T2> & value) const
            {
                return (T != T2) || (memcmp(this, &value, T) != 0);
            }

            template<unsigned T2>
            bool operator < (const ip_addr<T2> & value) const
            {
                return (T == T2) && (memcmp(this, &value, T) < 0);
            }
        };
        #pragma pack(pop)

        typedef ip_addr<4>  ipv4_addr;
        typedef ip_addr<16> ipv6_addr;

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
