#ifndef IP_HEADER_H
#define IP_HEADER_H

#include <string.h>
#include "util/LittleBigEndian.h"

namespace boolib
{
    namespace net
    {

        struct ip_data;

        //
        // IP Address Type
        //

        #pragma pack(push,1)
        struct ip_address
        {
            enum ip_version
            {
                IPv4 = 4,
                IPv6 = 16
            };

            ip_data * ptr;
            bool wasAllocated;
            ip_version version;
            
            ip_address(ip_version version, void * existing = NULL)
                : ptr((ip_data*)existing)
                , wasAllocated(existing == NULL)
                , version(version) 
            {
                if (ptr == NULL)
                    ptr = (ip_data*)(new char [version]);
            }

            ~ip_address()
            {
                if (wasAllocated)
                    delete [] (char*)ptr;
            }

            ip_address(const ip_address & addr)
            {
                wasAllocated = false;
                version = addr.version;
                ptr = addr.ptr;
            }

            ip_data * operator -> () const
            {
                return ptr;
            }

            operator ip_data& () const
            {
                return *ptr;
            }

            bool operator == (const ip_address & addr) const
            {
                return (version == addr.version) &&
                       (memcmp(ptr, addr.ptr, version) == 0);
            }

            bool operator != (const ip_address & addr) const
            {
                return (version != addr.version) ||
                       (memcmp(ptr, addr.ptr, version) != 0);
            }

            bool operator < (const ip_address & addr) const
            {
                return (version < addr.version) ||
                       (memcmp(ptr, addr.ptr, addr.version) < 0);
            }

            const char * data() const
            {
                return (char*)ptr;
            }

            const int size() const
            {
                return version;
            }
        };
        #pragma pack(pop)

        //
        // IP Address Data Interface
        //

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

        //
        // IP Address Data Template
        //

        #pragma pack(push,1)
        template <ip_address::ip_version T>
        struct ip_data_t
        {
            #pragma warning(push)
            #pragma warning(disable:4200)
            union {
                unsigned  char bytes[T];
                unsigned short words[T/2];
                unsigned   int dwords[T/4];
            };
            #pragma warning(pop)

            unsigned long long * qwords()
            {
                return (unsigned long long *)this;
            }

            operator ip_data & ()
            {
                return reinterpret_cast<ip_data&>(*this);
            }

            template<ip_address::ip_version T2>
            bool operator == (const ip_data_t<T2> & addr) const
            {
                return (T == T2) && (memcmp(this, &addr, T) == 0);
            }

            template<ip_address::ip_version T2>
            bool operator != (const ip_data_t<T2> & addr) const
            {
                return (T != T2) || (memcmp(this, &addr, T) != 0);
            }

            template<ip_address::ip_version T2>
            bool operator < (const ip_data_t<T2> & addr) const
            {
                return (T < T2) || (memcmp(this, &addr, T2) < 0);
            }
        };
        #pragma pack(pop)

        typedef ip_data_t<ip_address::IPv4> ipv4_data;
        typedef ip_data_t<ip_address::IPv6> ipv6_data;
        
        //
        // IP Header Interface
        //
        
        #pragma pack(push,1)
        struct ip_header
        {
            virtual ~ip_header() {}

            virtual int size() const = 0;
            virtual char * data() const = 0;
            virtual ip_address src_ip() const = 0;
            virtual ip_address dst_ip() const = 0;

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
