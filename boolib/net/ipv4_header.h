#ifndef IPV4_HEADER_H
#define IPV4_HEADER_H

#include "ip_header.h"
#include "util/LittleBigEndian.h"

namespace boolib
{
    namespace net
    {

        //
        // IPv4 Address Format
        //

        #pragma pack(push,1)
        struct ipv4_address : public ip_address_abstract<ipv4_address>
        {
            union {
                unsigned   int dword;
                unsigned short words[2];
                unsigned  char bytes[4];
            };

            virtual int size()
            {
                return 4;
            }

            virtual int version()
            {
                return 4;
            }
        };
        #pragma pack(pop)

        //
        // IPv4 Header Format
        //
        // /---------------+---------------+---------------+---------------|
        // |7 6 5 4 3 2 1 0|7 6 5 4 3 2 1 0|7 6 5 4 3 2 1 0|7 6 5 4 3 2 1 0|
        // +-------+-------+---------------+-------------------------------+
        // |  Ver  |Hdr len| Type of Serv. |         Total Length          |
        // +-------+-------+---------------+-----+-------------------------+
        // |         Identificator         |flags|    Fragment Offset      |
        // +---------------+---------------+-----+-------------------------+
        // | Time to Live  |    Protocol   |        Header Checksum        |
        // +---------------+---------------+-------------------------------+
        // |                       Source IP Address                       |
        // +---------------------------------------------------------------+
        // |                    Destination IP Address                     |
        // \---------------------------------------------------------------/
        //
        
        #pragma pack(push,1)
        struct ipv4_header : public ip_header_abstract<ipv4_header>
        {
            // ---------------- Fisrt DWORD ----------------
	        
            unsigned char version:4;
	        unsigned char hdr_len:4;

	        struct {
		        unsigned char dscp:6;
		        unsigned char ect:1;
		        unsigned char ce:1;
            } dsfield;

            boolib::util::BigEndian<unsigned short> totalLength;

            // ---------------- Second DWORD ----------------
	        
	        unsigned short identificator;

	        unsigned short flag_rb:1;
		    unsigned short flag_df:1;
		    unsigned short flag_mf:1;
        private:
	        unsigned short frag_offset:13;
        public:
            unsigned short fragmentOffset() {
                return (frag_offset << 3);
            }
            void setFragmentOffset(unsigned short value) {
                frag_offset = (value >> 3);
            }

            // ---------------- Third DWORD ----------------
	        
	        unsigned  char ttl;
	        unsigned  char proto;
	        unsigned short checksum;

            // ---------------- Fourth DWORD ----------------
	        
            ipv4_address src;

            // ---------------- Fifth DWORD ----------------
	        
            ipv4_address dst;
            
            // ----------------------------------------------

            ipv4_header()
                : version(4)
                , hdr_len(5)
            {
            }

            virtual int size()
            {
                return hdr_len*4;
            }

            virtual ip_address & src_ip()
            {
                return reinterpret_cast<ip_address&>(src);
            }

            virtual ip_address & dst_ip()
            {
                return reinterpret_cast<ip_address&>(dst);
            }
        };
        #pragma pack(pop)

    }
    // namespace net
}
// namespace boolib

#endif // IPV4_HEADER_H
