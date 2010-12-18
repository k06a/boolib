#ifndef INTX2_H
#define INTX2_H

#include <iostream>
#include "algo.h"
#include "LittleBigEndian.h"


namespace boolib
{
    namespace util
    {

        // Big Integers

        template<typename T>
        class Intx2;

        //

        //typedef unsigned  char  u8;     // 1 byte
        typedef unsigned short u16;     // 2 bytes
        typedef Intx2<u16> u32;         // 4 bytes
        typedef Intx2<u32> u64;         // 8 bytes
        typedef Intx2<u64> u128;        // 16 bytes
        typedef Intx2<u128> u256;       // 32 bytes
        typedef Intx2<u256> u512;       // 64 bytes
        typedef Intx2<u512> u1024;      // 128 bytes
        typedef Intx2<u1024> u2048;     // 256 bytes
        typedef Intx2<u2048> u4096;     // 512 bytes
        typedef Intx2<u4096> u8192;     // 1024 bytes
        typedef Intx2<u8192> u16384;    // 2048 bytes
        typedef Intx2<u16384> u32768;   // 4096 bytes
        typedef Intx2<u32768> u65536;   // 8192 bytes

        //
        
        #pragma pack(push,1)
        template<typename T>
        class Intx2
        {
            T b;
            T a;

        public: // Constructing + Destructing

            Intx2() : b(0), a(0)
            {
            }

            Intx2(const unsigned __int64 value)
                : b((T)(value %  (1 << (8*sizeof(T)))))
                , a((T)(value >> (8*sizeof(T))))
            {
            }

            Intx2(const Intx2<T> & value)
                : b(value.b), a(value.a)
            {
            }

            template<typename T2>
            Intx2(const Intx2<T2> & value)
                : b(0), a(0)
            {
                *this = value;
            }

            template<typename T2>
            Intx2<T> & operator = (const Intx2<T2> & value)
            {
                int copySize = (sizeof(*this) < sizeof(value))
                                              ? sizeof(*this)
                                              : sizeof(value);

                if (IS_LITTLE_ENDIAN)
                    memcpy(this, &value, copySize);
                if (IS_BIG_ENDIAN)
                    memcpy(this, ((char*)(&value+1)) - copySize, copySize);

                return *this;
            }

            operator unsigned __int64 () const
            {
                return ((a << (8*sizeof(a))) | b);
            }

            operator unsigned int () const
            {
                return ((a << (8*sizeof(a))) | b);
            }

            operator unsigned short () const
            {
                return ((a << (8*sizeof(a))) | b);
            }

        public: // Comparing

            template<typename T1, typename T2>
            friend bool operator == (const Intx2<T1> & x, const Intx2<T2> & y);
            template<typename T1, typename T2>
            friend bool operator == (const Intx2<T1> & x, const T2 & y);
            template<typename T1, typename T2>
            friend bool operator == (const T2 & x, const Intx2<T1> & y);

            template<typename T1, typename T2>
            friend bool operator != (const Intx2<T1> & x, const Intx2<T2> & y);
            template<typename T1, typename T2>
            friend bool operator != (const Intx2<T1> & x, const T2 & y);
            template<typename T1, typename T2>
            friend bool operator != (const T2 & x, const Intx2<T1> & y);
        
            template<typename T1, typename T2>
            friend bool operator < (const Intx2<T1> & x, const Intx2<T2> & y);
            template<typename T1, typename T2>
            friend bool operator < (const Intx2<T1> & x, const T2 & y);
            template<typename T1, typename T2>
            friend bool operator < (const T2 & x, const Intx2<T1> & y);
        
        public:
            Intx2<T> operator - () const
            {
                Intx2<T> res;
                res.b = ~b;
                res.a = -a;
                return res;
            }

            Intx2<T> & operator ++ ()
            {
                b++;
                if (b == 0) a++;
                return *this;
            }

            Intx2<T> & operator -- ()
            {
                if (b == 0) a--;
                b--;
                return *this;
            }

            Intx2<T> operator ++ (int) const
            {
                Intx2<T> res = (*this);
                return ++res;
            }

            Intx2<T> operator -- (int) const
            {
                Intx2<T> res = (*this);
                return --res;
            }

            template<typename T1>
            Intx2<T> & operator += (Intx2<T1> & value)
            {
                *this = *this + value;
                return *this;
            }

            template<typename T1>
            Intx2<T> & operator -= (Intx2<T1> & value)
            {
                *this = *this - value;
                return *this;
            }

            template<typename T1>
            friend Intx2<T1> operator + (const Intx2<T1> & x, const Intx2<T1> & y);
            template<typename T1, typename T2>
            friend Intx2<T1> operator + (const Intx2<T1> & x, const T2 & y);
            template<typename T1, typename T2>
            friend Intx2<T1> operator + (const T2 & x, const Intx2<T1> & y);

            template<typename T1>
            friend Intx2<T1> operator - (const Intx2<T1> & x, const Intx2<T1> & y);
            template<typename T1, typename T2>
            friend Intx2<T1> operator - (const Intx2<T2> & x, const T2 & y);
            template<typename T1, typename T2>
            friend Intx2<T1> operator - (const T2 & x, const Intx2<T1> & y);

            template<typename T1>
            friend Intx2<Intx2<T1> > operator * (const Intx2<T1> & x, const Intx2<T1> & y);
            template<typename T1, typename T2>
            friend Intx2<Intx2<T1> > operator * (const Intx2<T1> & x, const T2 & y);
            template<typename T1,typename T2>
            friend Intx2<Intx2<T1> > operator * (const T2 & x, const Intx2<T1> & y);

            template<typename T2>
            friend std::ostream &
            operator << (std::ostream & os, const Intx2<T2> & value);
        };
        #pragma pack(pop)

        // ================================================================

        template<typename T1, typename T2>
        inline bool operator == (const Intx2<T1> & x, const Intx2<T2> & y)
        {
            if (sizeof(x) < sizeof(y))
                return (Intx2<T2>(x) == y);
            if (sizeof(x) > sizeof(y))
                return (x == Intx2<T1>(y));
            
            return (x.a == y.a) && (x.b == y.b);
        }

        template<typename T1, typename T2>
        inline bool operator == (const Intx2<T1> & x, const T2 & y)
        {
            if (sizeof(x) <= sizeof(y))
                return (T2(x) == y);
            else
                return (x == Intx2<T1>(y));
        }

        template<typename T1, typename T2>
        inline bool operator == (const T2 & x, const Intx2<T1> & y)
        {
            if (sizeof(x) >= sizeof(y))
                return (x == T2(y));
            else
                return (Intx2<T1>(x) == y);
        }

        // ----------------------------------------------------------------

        template<typename T1, typename T2>
        inline bool operator != (const Intx2<T1> & x, const Intx2<T2> & y)
        {
            return !(x == y);
        }

        template<typename T1, typename T2>
        inline bool operator != (const Intx2<T1> & x, const T2 & y)
        {
            return !(x == y);
        }

        template<typename T1, typename T2>
        inline bool operator != (const T2 & x, const Intx2<T1> & y)
        {
            return !(x == y);
        }

        // ----------------------------------------------------------------

        template<typename T1, typename T2>
        inline bool operator < (const Intx2<T1> & x, const Intx2<T2> & y)
        {
            if (sizeof(x) <= sizeof(y))
                return (Intx2<T2>(x) < y);
            if (sizeof(x) > sizeof(y))
                return (x < Intx2<T1>(y));

            return (x.a < y.a) || ((x.a == y.a) && (x.b < y.b));
        }

        template<typename T1, typename T2>
        inline bool operator < (const Intx2<T1> & x, const T2 & y)
        {
            if (sizeof(x) <= sizeof(y))
                return (T2(x) < y);
            else
                return (x < Intx2<T1>(y));
        }

        template<typename T1, typename T2>
        inline bool operator < (const T2 & x, const Intx2<T1> & y)
        {
            if (sizeof(x) >= sizeof(y))
                return (x < T2(y));
            else
                return (Intx2<T1>(x) < y);
        }

        // ================================================================

        template<typename T1>
        Intx2<T1> operator + (const Intx2<T1> & x, const Intx2<T1> & y)
        {
            Intx2<T1> res;
            res.b = x.b + y.b;
            res.a = x.a + y.a;
            if (res.b < x.b)
                res.a++;
            return res;
        }
        
        template<typename T1, typename T2>
        Intx2<T1> operator + (const Intx2<T1> & x, const T2 & y)
        {
            if (sizeof(x) >= sizeof(y))
                return x + Intx2<T1>(y);
            else
                return T2(x) + y;
        }

        template<typename T1, typename T2>
        Intx2<T1> operator + (const T2 & x, const Intx2<T1> & y)
        {
            if (sizeof(x) >= sizeof(y))
                return x + T2(y);
            else
                return Intx2<T1>(x) + y;
        }

        // ----------------------------------------------------------------

        template<typename T1>
        Intx2<T1> operator - (const Intx2<T1> & x, const Intx2<T1> & y)
        {
            Intx2<T1> res;
            res.b = x.b - y.b;
            res.a = x.a - y.a;
            if (res.b < x.b)
                res.a++;
            return res;
        }

        template<typename T1, typename T2>
        Intx2<T1> operator - (const Intx2<T1> & x, const T2 & y)
        {
            if (sizeof(x) >= sizeof(y))
                return x - Intx2<T1>(y);
            else
                return T2(x) - y;
        }

        template<typename T1, typename T2>
        Intx2<T1> operator - (const T2 & x, const Intx2<T1> & y)
        {
            if (sizeof(x) >= sizeof(y))
                return x - T2(y);
            else
                return Intx2<T1>(x) - y;
        }

        // ----------------------------------------------------------------

        template<typename T1>
        Intx2<Intx2<T1> > operator * (const Intx2<T1> & x, const Intx2<T1> & y)
        {
            Intx2<Intx2<T1> > res;
            Karatsuba_multiply((T1*)&x,(T1*)&y,(Intx2<T1>*)res);
            return res;
        }

        template<typename T1, typename T2>
        Intx2<Intx2<T1> > operator * (const Intx2<T1> & x, const T2 & y)
        {
            if (sizeof(x) >= sizeof(y))
                return x * Intx2<T1>(y);
            else
                return T2(x) * y;
        }

        template<typename T1, typename T2>
        Intx2<Intx2<T1> > operator * (const T2 & x, const Intx2<T1> & y)
        {
            if (sizeof(x) >= sizeof(y))
                return x * T2(y);
            else
                return Intx2<T1>(x) * y;
        }

        // ================================================================

        template<typename T>
        std::ostream &
        operator << (std::ostream & os, const Intx2<T> & value)
        {
            return os << std::hex << value.a << value.b << std::dec;
        }

    }
    // namespace util
}
// namespace boolib

#endif // INTX2_H
