#ifndef INTX2_H
#define INTX2_H

#include <iostream>
#include "algo.h"
#include "util/LittleBigEndian.h"

#if defined(__LITTLE_ENDIAN__)
static const int CurrentByteOrder = LITTLE_ENDIAN_BYTE_ORDER;
#elif defined(__BIG_ENDIAN__)
static const int CurrentByteOrder = BIG_ENDIAN_BYTE_ORDER;
#else
#pragma message("Neither of __LITTLE_ENDIAN__ or __BIG_ENDIAN__ byte orders are not defined! Default order - __LITTLE_ENDIAN__.")
static const int CurrentByteOrder = LITTLE_ENDIAN_BYTE_ORDER;
#endif

namespace boolib
{
    namespace util
    {

        // Big Integers

        template<typename T, bool S>
        class Intx2;

        //

        typedef unsigned char u8;           // 1 byte
        typedef Intx2<u8,false> u16;        // 2 bytes
        typedef Intx2<u16,false> u32;       // 4 bytes
        typedef Intx2<u32,false> u64;       // 8 bytes
        typedef Intx2<u64,false> u128;      // 16 bytes
        typedef Intx2<u128,false> u256;     // 32 bytes
        typedef Intx2<u256,false> u512;     // 64 bytes
        typedef Intx2<u512,false> u1024;    // 128 bytes
        typedef Intx2<u1024,false> u2048;   // 256 bytes
        typedef Intx2<u2048,false> u4096;   // 512 bytes
        typedef Intx2<u4096,false> u8192;   // 1024 bytes
        typedef Intx2<u8192,false> u16384;  // 2048 bytes
        typedef Intx2<u16384,false> u32768; // 4096 bytes
        typedef Intx2<u32768,false> u65536; // 8192 bytes

        typedef signed char i8;             // 1 byte
        typedef Intx2<u8,true> i16;         // 2 bytes
        typedef Intx2<u16,true> i32;        // 4 bytes
        typedef Intx2<u32,true> i64;        // 8 bytes
        typedef Intx2<u64,true> i128;       // 16 bytes
        typedef Intx2<u128,true> i256;      // 32 bytes
        typedef Intx2<u256,true> i512;      // 64 bytes
        typedef Intx2<u512,true> i1024;     // 128 bytes
        typedef Intx2<u1024,true> i2048;    // 256 bytes
        typedef Intx2<u2048,true> i4096;    // 512 bytes
        typedef Intx2<u4096,true> i8192;    // 1024 bytes
        typedef Intx2<u8192,true> i16384;   // 2048 bytes
        typedef Intx2<u16384,true> i32768;  // 4096 bytes
        typedef Intx2<u32768,true> i65536;  // 8192 bytes

        // Templates for determite bigger type

        template <typename T, typename U, bool flag>
        struct Select;
        template <typename T, typename U>
        struct Select<T, U, true>  { typedef typename T Result; };
        template <typename T, typename U>
        struct Select<T, U, false> { typedef typename U Result; };

        template <typename T, typename U>
        struct IsBigger {
	        enum { value = sizeof(T) > sizeof(U) };
        };
 
        template <typename T, typename U>
        struct BiggerTypeSelector {
	        typedef typename Select<T,U,IsBigger<T, U>::value>::Result Result;
        };

        //
        
        template<typename TCHILD, typename T, bool S, int BYTE_ORDER = CurrentByteOrder>
        class Intx2_base;

        #pragma pack(push,1)
        template<typename T, bool S = true>
        class Intx2 : public Intx2_base<Intx2<T,S>,T,S>
        {
            //T b;
            //T a;

        public: // Constructing + Destructing

            Intx2(T low = 0, T hi = 0)
                : Intx2_base(low,hi)
            {
            }

            /*
            Intx2(const signed __int64 value)
                : b((T)(value))
                , a((T)(value >> (8*sizeof(T))))
            {
            }

            Intx2(const unsigned __int64 value)
                : b((T)(value))
                , a((T)(value >> (8*sizeof(T))))
            {
            }

            Intx2(const signed int value)
                : b((T)(value))
                , a((T)(value >> (8*sizeof(T))))
            {
            }

            Intx2(const unsigned int value)
                : b((T)(value))
                , a((T)(value >> (8*sizeof(T))))
            {
            }

            Intx2(const signed short value)
                : b((T)(value))
                , a((T)(value >> (8*sizeof(T))))
            {
            }

            Intx2(const unsigned short value)
                : b((T)(value))
                , a((T)(value >> (8*sizeof(T))))
            {
            }

            Intx2(const signed char value)
                : b((T)(value))
                , a((T)(value >> (8*sizeof(T))))
            {
            }

            Intx2(const unsigned char value)
                : b((T)(value))
                , a((T)(value >> (8*sizeof(T))))
            {
            }
            */

            Intx2(const Intx2<T,S> & value)
                : Intx2_base(value.b,value.a)
            {
            }
            
            template<typename T2>//, bool S2> // Intx2<T2,S2>
            Intx2(const T2 & value)
            {
                *this = value;
            }

            template<typename T2>//, bool S2> // Intx2<T2,S2>
            Intx2<T,S> & operator = (const T2  & value)
            {
                int copySize = (sizeof(*this) < sizeof(value))
                                              ? sizeof(*this)
                                              : sizeof(value);

                memset(this, ((value<0)?0xff:0x00), sizeof(*this));

                if (IS_LITTLE_ENDIAN)
                    memcpy(this, &value, copySize);
                if (IS_BIG_ENDIAN)
                    memcpy(this, ((char*)(&value+1)) - copySize, copySize);

                return *this;
            }

        public: // Tools

            inline bool isZero() const
            {
                return (a == 0) && (b == 0);
            }

            inline bool isNegative() const
            {
                //if (!S) return false;

                if (sizeof(a) == 1)
                    return (a>>7) == 1;
                else
                    return (a < 0);
                //return (S == true) && (a < 0);
            }

            inline bool isPositive() const
            {
                //if (!S) retrun true;

                if (sizeof(a) == 1)
                    return (a>>7) == 0;
                else
                    return (a >= 0);
                //return (S == false) || (a > 0);
            }

            template<typename T1>
            inline T1 toInteger(T1 * unused = 0) const
            {
                T1 answer;

                int copySize = (sizeof(*this) < sizeof(T1))
                                              ? sizeof(*this)
                                              : sizeof(T1);

                memset(&answer, (isNegative()?0xff:0x00), sizeof(T1));

                if (IS_LITTLE_ENDIAN)
                    memcpy(&answer, this, copySize);
                if (IS_BIG_ENDIAN)
                    memcpy(&answer + (sizeof(T1)-copySize), this, copySize);

                return answer;

                //return (T1(a << (8*sizeof(T)))) | ((T1)b);
            }

            template<typename T1, bool S1>
            inline operator Intx2<T1,S1> () const
            {
                return *this;
            }
            
            // Signed operators
            /*
            typedef signed __int64 Intx2<T,S>::* signed_int64;
            inline operator signed_int64() const {
                return toInteger<signed __int64>();
            }
            typedef signed int Intx2<T,S>::* signed_int;
            inline operator signed_int() const {
                return toInteger<signed int>();
            }
            typedef signed short Intx2<T,S>::* signed_short;
            inline operator signed_short() const {
                return toInteger<signed short>();
            }
            typedef signed char Intx2<T,S>::* signed_char;
            inline operator signed_char() const {
                return toInteger<signed char>();
            }

            // Unsigned operators
            
            inline operator unsigned __int64() const {
                return toInteger<unsigned __int64>();
            }
            inline operator unsigned int() const {
                return toInteger<unsigned int>();
            }
            inline operator unsigned short() const {
                return toInteger<unsigned short>();
            }
            inline operator unsigned char() const {
                return toInteger<unsigned char>();
            }
            */
        public: // Boolean friend operators

            // 1. The same type with may be different signs
            // 2,3. Different types
            template<typename T1, bool S1, bool S2>
            friend bool operator == (const Intx2<T1,S1> & x, const Intx2<T1, S2> & y);
            template<typename T1, typename T2, bool S1> // const bool T2_SIGN = ((T2(-1))<0)
            friend bool operator == (const Intx2<T1,S1> & x, const T2 & y);
            template<typename T1, typename T2, bool S1> // const bool T2_SIGN = ((T2(-1))<0)
            friend bool operator == (const T2 & x, const Intx2<T1,S1> & y);

            // 1. The same type with may be different signs
            // 2,3. Different types
            template<typename T1, bool S1, bool S2>
            friend bool operator != (const Intx2<T1,S1> & x, const Intx2<T1,S2> & y);
            template<typename T1, typename T2, bool S1> // const bool T2_SIGN = ((T2(-1))<0)
            friend bool operator != (const Intx2<T1,S1> & x, const T2 & y);
            template<typename T1, typename T2, bool S1> // const bool T2_SIGN = ((T2(-1))<0)
            friend bool operator != (const T2 & x, const Intx2<T1,S1> & y);
        
            // 1. The same type with may be different signs
            // 2,3. Different types
            template<typename T1, bool S1, bool S2>
            friend bool operator < (const Intx2<T1,S1> & x, const Intx2<T1,S2> & y);
            template<typename T1, typename T2, bool S1> // const bool T2_SIGN = ((T2(-1))<0)
            friend bool operator < (const Intx2<T1,S1> & x, const T2 & y);
            template<typename T1, typename T2, bool S1> // const bool T2_SIGN = ((T2(-1))<0)
            friend bool operator < (const T2 & x, const Intx2<T1,S1> & y);
        
        public: // Bitwise operators

            Intx2<T,S> operator ~ () const
            {
                Intx2<T,S> res;
                res.b = ~b;
                res.a = ~a;
                return res;
            }
            
            Intx2<T,S> operator << (const int value) const
            {
                Intx2<T,S> res;
                res.b = (b << value);
                res.a = (a << value) | (b >> (8*sizeof(b)-value));
                return res;
            }

            Intx2<T,S> operator >> (const int value) const
            {
                Intx2<T,S> res;
                res.b = (b >> value) | (a << (8*sizeof(a)-value));
                res.a = a >> value;
                return res;
            }

            // 1. The same type with may be different signs
            // 2,3. Different types
            template<typename T1, bool S1, bool S2>
            friend Intx2<T1,S1||S2> operator | (const Intx2<T1,S1> & x, const Intx2<T1,S2> & y);
            template<typename T1, typename T2, bool S1> // const bool T2_SIGN = ((T2(-1))<0)
            friend Intx2<T1,S1||((T2(-1))<0)> operator | (const Intx2<T1,S1> & x, const T2 & y);
            template<typename T1, typename T2, bool S1> // const bool T2_SIGN = ((T2(-1))<0)
            friend Intx2<T1,S1||((T2(-1))<0)> operator | (const T2 & x, const Intx2<T1,S1> & y);

            // 1. The same type with may be different signs
            // 2,3. Different types
            template<typename T1, bool S1, bool S2>
            friend Intx2<T1,S1||S2> operator & (const Intx2<T1,S1> & x, const Intx2<T1,S2> & y);
            template<typename T1, typename T2, bool S1> // const bool T2_SIGN = ((T2(-1))<0)
            friend Intx2<T1,S1||((T2(-1))<0)> operator & (const Intx2<T1,S1> & x, const T2 & y);
            template<typename T1, typename T2, bool S1> // const bool T2_SIGN = ((T2(-1))<0)
            friend Intx2<T1,S1||((T2(-1))<0)> operator & (const T2 & x, const Intx2<T1,S1> & y);

            // 1. The same type with may be different signs
            // 2,3. Different types
            template<typename T1, bool S1, bool S2>
            friend Intx2<T1,S1||S2> operator ^ (const Intx2<T1,S1> & x, const Intx2<T1,S2> & y);
            template<typename T1, typename T2, bool S1> // const bool T2_SIGN = ((T2(-1))<0)
            friend Intx2<T1,S1||((T2(-1))<0)> operator ^ (const Intx2<T1,S1> & x, const T2 & y);
            template<typename T1, typename T2, bool S1> // const bool T2_SIGN = ((T2(-1))<0)
            friend Intx2<T1,S1||((T2(-1))<0)> operator ^ (const T2 & x, const Intx2<T1,S1> & y);

        public: // Self-Bitwise operators

            Intx2<T,S> & operator <<= (const int value)
            {
                a = (a << value) | (b >> (8*sizeof(b)-value));
                b = b << value;
                return *this;
            }

            Intx2<T,S> & operator >>= (const int value)
            {
                b = (b >> value) | (a << (8*sizeof(a)-value));
                a = a >> value;
                return *this;
            }

            template<typename T1, bool S1>
            Intx2<T,S> & operator |= (const Intx2<T1,S1> & value)
            {
                b |= value.b;
                a |= value.a;
                return *this;
            }

            template<typename T2>
            Intx2<T,S> & operator |= (const T2 & value)
            {
                if (IS_LITTLE_ENDIAN)
                {
                    b |= value;
                    a |= value >> (8*sizeof(b));
                }
                else if (IS_BIG_ENDIAN)
                {
                    b |= value >> (8*sizeof(b));
                    a |= value;
                }
                return *this;
            }

        public: // Math operators

            Intx2<T,S> operator - () const
            {
                Intx2<T,S> res;
                res.b = ~b;
                res.a = ~a;
                return ++res;
            }

            Intx2<T,S> & operator ++ ()
            {
                b++;
                if (b == 0) a++;
                return *this;
            }

            Intx2<T,S> & operator -- ()
            {
                if (b == 0) a--;
                b--;
                return *this;
            }

            Intx2<T,S> operator ++ (int)
            {
                return ++(*this);
            }

            Intx2<T,S> operator -- (int)
            {
                return --(*this);
            }
            
            template<typename T1>
            Intx2<T,S> & operator += (const T1 & value)
            {
                *this = *this + value;
                return *this;
            }

            /*
            template<typename T1>
            Intx2<T,S> & operator -= (const T1 & value)
            {
                *this = *this - value;
                return *this;
            }

            template<typename T1>
            Intx2<T,S> & operator *= (const T1 & value)
            {
                *this = *this * value;
                return *this;
            }
            */
        public: // Math friend operators

            // 1. The same type with may be different signs
            // 2,3. Different types
            template<typename T1, bool S1, bool S2>
            friend Intx2<T1,S1||S2> operator + (const Intx2<T1,S1> & x, const Intx2<T1,S2> & y);
            template<typename T1, typename T2, bool S1, bool S2>
            friend Intx2<typename BiggerTypeSelector<T1,T2>::Result,S1||S2> operator + (const Intx2<T1,S1> & x, const Intx2<T2,S2> & y);
            template<typename T1, typename T2, bool S1> // const bool T2_SIGN = ((T2(-1))<0)
            friend Intx2<T1,S1||((T2(-1))<0)> operator + (const Intx2<T1,S1> & x, const T2 & y);
            template<typename T1, typename T2, bool S1> // const bool T2_SIGN = ((T2(-1))<0)
            friend Intx2<T1,S1||((T2(-1))<0)> operator + (const T2 & x, const Intx2<T1,S1> & y);

            // 1. The same type with may be different signs
            // 2,3. Different types
            template<typename T1, bool S1, bool S2>
            friend Intx2<T1,S1||S2> operator - (const Intx2<T1,S1> & x, const Intx2<T1,S2> & y);
            template<typename T1, typename T2, bool S1, bool S2> // const bool T2_SIGN = ((T2(-1))<0)
            friend Intx2<typename BiggerTypeSelector<T1,T2>::Result,S1||S2> operator - (const Intx2<T1,S1> & x, const Intx2<T2,S2> & y);
            template<typename T1, typename T2, bool S1> // const bool T2_SIGN = ((T2(-1))<0)
            friend Intx2<T1,S1||((T2(-1))<0)> operator - (const Intx2<T1,S1> & x, const T2 & y);
            template<typename T1, typename T2, bool S1> // const bool T2_SIGN = ((T2(-1))<0)
            friend Intx2<T1,S1||((T2(-1))<0)> operator - (const T2 & x, const Intx2<T1,S1> & y);

            // 1. The same type with may be different signs
            // 2,3. Different types
            template<typename T1, bool S1, bool S2>
            friend Intx2<Intx2<T1,false>,S1||S2> operator * (const Intx2<T1,S1> & x, const Intx2<T1,S2> & y);
            template<typename T1, typename T2, bool S1, bool S2> // const bool T2_SIGN = ((T2(-1))<0)
            friend Intx2<Intx2<typename BiggerTypeSelector<T1,T2>::Result,false>,S1||S2> operator * (const Intx2<T1,S1> & x, const Intx2<T2,S2> & y);
            template<typename T1, typename T2, bool S1> // const bool T2_SIGN = ((T2(-1))<0)
            friend Intx2<Intx2<T1,false>,S1||((T2(-1))<0)> operator * (const Intx2<T1,S1> & x, const T2 & y);
            template<typename T1,typename T2, bool S1> // const bool T2_SIGN = ((T2(-1))<0)
            friend Intx2<Intx2<T1,false>,S1||((T2(-1))<0)> operator * (const T2 & x, const Intx2<T1,S1> & y);

            // 1. The same type with may be different signs
            template<typename T1, bool S1, bool S2>
            friend Intx2<Intx2<T1,false>,S1||S2> operator / (const Intx2<Intx2<T1,false>,S1> & x, const Intx2<T1,S2> & y);
            template<typename T1, bool S1, bool S2>
            friend Intx2<T1,S1||S2> operator / (const Intx2<T1,S1> & x, const Intx2<T1,S2> & y);
            template<typename T1, typename T2, bool S1> // const bool T2_SIGN = ((T2(-1))<0)
            friend Intx2<T1,S1||((T2(-1))<0)> operator / (const Intx2<T1,S1> & x, const T2 & y);
            template<typename T1, typename T2, bool S1> // const bool T2_SIGN = ((T2(-1))<0)
            friend Intx2<T1,S1||((T2(-1))<0)> operator / (const T2 & x, const Intx2<T1,S1> & y);

        public: // Stream operators

            /*
            template<typename T1, bool S1>
            friend std::ostream &
            operator << (std::ostream & os, const Intx2<T1,S1> & value);
            */
        };
        #pragma pack(pop)

        // ----------------------------------------------------------------

        template<typename TCHILD, typename T>
        class Intx2_base<TCHILD,T,true,LITTLE_ENDIAN_BYTE_ORDER>
        {
            #define CHILD ((TCHILD*)this)

        protected:
            T b;
            T a;

        public: // Signed type tools
            
            Intx2_base(const T & b = 0, const T & a = 0)
                : b(b), a(a)
            {
            }

            #undef CHILD
        };

        template<typename TCHILD, typename T>
        class Intx2_base<TCHILD,T,true,BIG_ENDIAN_BYTE_ORDER>
        {
            #define CHILD ((TCHILD*)this)
            
        protected:
            T a;
            T b;

        public: // Signed type tools
            
            Intx2_base(const T & b = 0, const T & a = 0)
                : a(a), b(b)
            {
            }

            #undef CHILD
        };

        // ----------------------------------------------------------------

        template<typename TCHILD, typename T>
        class Intx2_base<TCHILD,T,false,LITTLE_ENDIAN_BYTE_ORDER>
        {
            #define CHILD ((TCHILD*)this)
            
        protected:
            T b;
            T a;

        public: // Unsigned type tools
            
            Intx2_base(const T & b = 0, const T & a = 0)
                : b(b), a(a)
            {
            }

            #undef CHILD
        };

        template<typename TCHILD, typename T>
        class Intx2_base<TCHILD,T,false,BIG_ENDIAN_BYTE_ORDER>
        {
            #define CHILD ((TCHILD*)this)
            
        protected:
            T a;
            T b;

        public: // Unsigned type tools
            
            Intx2_base(const T & b = 0, const T & a = 0)
                : a(a), b(b)
            {
            }

            #undef CHILD
        };

        // ================================================================
        // Operator == ( a , b )
        // ================================================================
        
        template<typename T1, bool S1, bool S2>
        inline bool operator == (const Intx2<T1,S1> & x, const Intx2<T1, S2> & y)
        {
            bool neg_x = (x < 0);
            bool neg_y = (y < 0);

            if (neg_x ^ neg_y)
                return false;

            return (x.a == y.a) && (x.b == y.b);
        }

        template<typename T1, typename T2, bool S1> // const bool T2_SIGN = ((T2(-1))<0)
        inline bool operator == (const Intx2<T1,S1> & x, const T2 & y)
        {
            const bool T2_SIGN = (T2(-1)<0);

            if (sizeof(x) <= sizeof(y))
                return (x.toInteger<T2>() == y);
            else
                return (x == Intx2<T1,S1||T2_SIGN>(y));
        }

        template<typename T1, typename T2, bool S1> // const bool T2_SIGN = ((T2(-1))<0)
        inline bool operator == (const T2 & x, const Intx2<T1,S1> & y)
        {
            const bool T2_SIGN = (T2(-1)<0);

            if (sizeof(x) >= sizeof(y))
                return (x == y.toInteger<T2>());
            else
                return (Intx2<T1,S1||T2_SIGN>(x) == y);
        }

        // ----------------------------------------------------------------
        // Operator != ( a , b )
        // ================================================================
        

        template<typename T1, bool S1, bool S2>
        inline bool operator != (const Intx2<T1,S1> & x, const Intx2<T1,S2> & y)
        {
            return !(x == y);
        }

        template<typename T1, typename T2, bool S1> // const bool T2_SIGN = ((T2(-1))<0)
        inline bool operator != (const Intx2<T1,S1> & x, const T2 & y)
        {
            return !(x == y);
        }

        template<typename T1, typename T2, bool S1> // const bool T2_SIGN = ((T2(-1))<0)
        inline bool operator != (const T2 & x, const Intx2<T1,S1> & y)
        {
            return !(x == y);
        }

        // ----------------------------------------------------------------
        // Operator < ( a , b )
        // ================================================================
        
        template<typename T1, bool S1, bool S2>
        inline bool operator < (const Intx2<T1,S1> & x, const Intx2<T1,S2> & y)
        {
            bool neg_x = (x < 0);
            bool neg_y = (y < 0);

            if (neg_x && !neg_y) return true;
            if (!neg_x && neg_y) return false;
            
            bool result = (x.a < y.a) || ((x.a == y.a) && (x.b < y.b));

            if (neg_x && neg_y)
                return !result;

            return result;
        }

        template<typename T1, typename T2, bool S1> // const bool T2_SIGN = ((T2(-1))<0)
        inline bool operator < (const Intx2<T1,S1> & x, const T2 & y)
        {
            if (y == 0)
                return x.isNegative();

            const bool T2_SIGN = (T2(-1)<0);

            if (sizeof(x) <= sizeof(y))
                return (x.toInteger<T2>() < y);
            else
                return (x < Intx2<T1,S1||T2_SIGN>(y));
        }

        template<typename T1, typename T2, bool S1> // const bool T2_SIGN = ((T2(-1))<0)
        inline bool operator < (const T2 & x, const Intx2<T1,S1> & y)
        {
            if (x == 0)
                return x.isPositive();

            const bool T2_SIGN = (T2(-1)<0);

            if (sizeof(x) >= sizeof(y))
                return (x < T2(y));
            else
                return (Intx2<T1,S1||T2_SIGN>(x) < y);
        }

        // ================================================================
        // Operator | ( a , b )
        // ================================================================

        // 1. The same type with may be different signs
        // 2,3. Different types
        template<typename T1, bool S1, bool S2>
        inline Intx2<T1,S1||S2> operator | (const Intx2<T1,S1> & x, const Intx2<T1,S2> & y)
        {
            return Intx2<T1,S1||S2>(x.b | y.b, x.a | y.a);
        }

        template<typename T1, typename T2, bool S1> // const bool T2_SIGN = ((T2(-1))<0)
        inline Intx2<T1,S1||((T2(-1))<0)> operator | (const Intx2<T1,S1> & x, const T2 & y)
        {
        }

        template<typename T1, typename T2, bool S1> // const bool T2_SIGN = ((T2(-1))<0)
        inline Intx2<T1,S1||((T2(-1))<0)> operator | (const T2 & x, const Intx2<T1,S1> & y)
        {
        }

        // ================================================================
        // Operator & ( a , b )
        // ================================================================

        // 1. The same type with may be different signs
        // 2,3. Different types
        template<typename T1, bool S1, bool S2>
        inline Intx2<T1,S1||S2> operator & (const Intx2<T1,S1> & x, const Intx2<T1,S2> & y)
        {
            return Intx2<T1,S1||S2>(x.b & y.b, x.a & y.a);
        }

        template<typename T1, typename T2, bool S1> // const bool T2_SIGN = ((T2(-1))<0)
        inline Intx2<T1,S1||((T2(-1))<0)> operator & (const Intx2<T1,S1> & x, const T2 & y)
        {
        }

        template<typename T1, typename T2, bool S1> // const bool T2_SIGN = ((T2(-1))<0)
        inline Intx2<T1,S1||((T2(-1))<0)> operator & (const T2 & x, const Intx2<T1,S1> & y)
        {
        }

        // ================================================================
        // Operator ^ ( a , b )
        // ================================================================

        // 1. The same type with may be different signs
        // 2,3. Different types
        template<typename T1, bool S1, bool S2>
        inline Intx2<T1,S1||S2> operator ^ (const Intx2<T1,S1> & x, const Intx2<T1,S2> & y)
        {
            return Intx2<T1,S1||S2>(x.b ^ y.b, x.a ^ y.a);
        }

        template<typename T1, typename T2, bool S1> // const bool T2_SIGN = ((T2(-1))<0)
        inline Intx2<T1,S1||((T2(-1))<0)> operator ^ (const Intx2<T1,S1> & x, const T2 & y)
        {
        }

        template<typename T1, typename T2, bool S1> // const bool T2_SIGN = ((T2(-1))<0)
        inline Intx2<T1,S1||((T2(-1))<0)> operator ^ (const T2 & x, const Intx2<T1,S1> & y)
        {
        }


        // ================================================================
        // Operator + ( a , b )
        // ================================================================
        
        template<typename T1, bool S1, bool S2>
        inline Intx2<T1,S1||S2> operator + (const Intx2<T1,S1> & x, const Intx2<T1,S2> & y)
        {
            Intx2<T1,S1||S2> res;
            res.b = x.b + y.b;
            res.a = x.a + y.a;
            if (res.b < x.b)
                res.a++;
            return res;
        }

        template<typename T1, typename T2, bool S1, bool S2> // const bool T2_SIGN = ((T2(-1))<0)
        inline Intx2<typename BiggerTypeSelector<T1,T2>::Result,S1||S2> operator + (const Intx2<T1,S1> & x, const Intx2<T2,S2> & y)
        {
            if (sizeof(x) >= sizeof(y))
                return x + Intx2<T1,S1||S2>(y);
            else
                return Intx2<T2,S1||S2>(x) + y;
        }
        
        template<typename T1, typename T2, bool S1> // const bool T2_SIGN = ((T2(-1))<0)
        inline Intx2<T1,S1||((T2(-1))<0)> operator + (const Intx2<T1,S1> & x, const T2 & y)
        {
            const bool T2_SIGN = (T2(-1)<0);

            if (sizeof(x) >= sizeof(y))
                return x + Intx2<T1,S1||T2_SIGN>(y);
            else
                return x.toInteger<T2>() + y;
        }

        template<typename T1, typename T2, bool S1> // const bool T2_SIGN = ((T2(-1))<0)
        inline Intx2<T1,S1||((T2(-1))<0)> operator + (const T2 & x, const Intx2<T1,S1> & y)
        {
            const bool T2_SIGN = (T2(-1)<0);

            if (sizeof(x) >= sizeof(y))
                return x + T2(y);
            else
                return Intx2<T1,S1||T2_SIGN>(x) + y;
        }

        // ----------------------------------------------------------------
        // Operator - ( a , b )
        // ================================================================
        
        template<typename T1, bool S1, bool S2>
        inline Intx2<T1,S1||S2> operator - (const Intx2<T1,S1> & x, const Intx2<T1,S2> & y)
        {
            Intx2<T1,S1||S2> res;
            res.b = x.b - y.b;
            res.a = x.a - y.a;
            if (x.b < res.b)
                res.a--;
            return res;
        }

        template<typename T1, typename T2, bool S1, bool S2> // const bool T2_SIGN = ((T2(-1))<0)
        inline Intx2<typename BiggerTypeSelector<T1,T2>::Result,S1||S2> operator - (const Intx2<T1,S1> & x, const Intx2<T2,S2> & y)
        {
            if (sizeof(x) >= sizeof(y))
                return x - Intx2<T1,S1||S2>(y);
            else
                return Intx2<T2,S1||S2>(x) - y;
        }

        template<typename T1, typename T2, bool S1> // const bool T2_SIGN = ((T2(-1))<0)
        inline Intx2<T1,S1||((T2(-1))<0)> operator - (const Intx2<T1,S1> & x, const T2 & y)
        {
            const bool T2_SIGN = (T2(-1)<0);

            if (sizeof(x) >= sizeof(y))
                return x - Intx2<T1,S1||T2_SIGN>(y);
            else
                return T2(x) - y;
        }

        template<typename T1, typename T2, bool S1> // const bool T2_SIGN = ((T2(-1))<0)
        inline Intx2<T1,S1||((T2(-1))<0)> operator - (const T2 & x, const Intx2<T1,S1> & y)
        {
            const bool T2_SIGN = (T2(-1)<0);

            if (sizeof(x) >= sizeof(y))
                return x - T2(y);
            else
                return Intx2<T1,S1||T2_SIGN>(x) - y;
        }

        // ----------------------------------------------------------------
        // Operator * ( a , b )
        // ================================================================
        
        template<typename T1, bool S1, bool S2>
        inline Intx2<Intx2<T1,false>,S1||S2> operator * (const Intx2<T1,S1> & x_, const Intx2<T1,S2> & y_)
        {
            Intx2<T1,S1> & x = const_cast<Intx2<T1,S1> &>(x_); 
            Intx2<T1,S2> & y = const_cast<Intx2<T1,S2> &>(y_); 

            bool neg_x = (x < 0);
            bool neg_y = (y < 0);

            // Change
            if (neg_x) x = -x;
            if (neg_y) y = -y;

            Intx2<Intx2<T1,false>,S1||S2> res;
            boolib::algo::Karatsuba_multiply((T1*)&x,(T1*)&y,(Intx2<T1,false>*)&res);

            // Recover
            if (neg_x) x = -x;
            if (neg_y) y = -y;

            if ((neg_x ^ neg_y) && (!res.isZero()))
                return -res;

            return res;
        }

        template<typename T1, typename T2, bool S1, bool S2> // const bool T2_SIGN = ((T2(-1))<0)
        inline Intx2<Intx2<typename BiggerTypeSelector<T1,T2>::Result,false>,S1||S2> operator * (const Intx2<T1,S1> & x, const Intx2<T2,S2> & y)
        {
            if (sizeof(x) >= sizeof(y))
                return x + Intx2<Intx2<T1,false>,S1||S2>(y);
            else
                return Intx2<Intx2<T2,false>,S1||S2>(x) + y;
        }

        template<typename T1, typename T2, bool S1> // const bool T2_SIGN = ((T2(-1))<0)
        inline Intx2<Intx2<T1,false>,S1||((T2(-1))<0)> operator * (const Intx2<T1,S1> & x, const T2 & y)
        {
            const bool T2_SIGN = (T2(-1)<0);

            if (sizeof(x) >= sizeof(y))
                return x * Intx2<T1,S1||T2_SIGN>(y);
            else
                return T2(x) * y;
        }

        template<typename T1,typename T2, bool S1> // const bool T2_SIGN = ((T2(-1))<0)
        inline Intx2<Intx2<T1,false>,S1||((T2(-1))<0)> operator * (const T2 & x, const Intx2<T1,S1> & y)
        {
            const bool T2_SIGN = (T2(-1)<0);

            if (sizeof(x) >= sizeof(y))
                return x * T2(y);
            else
                return Intx2<T1,S1||T2_SIGN>(x) * y;
        }

        // ================================================================
        // Operator / ( a , b )
        // ================================================================
        
        template<typename T1, bool S1, bool S2>
        inline Intx2<Intx2<T1,false>,S1||S2> operator / (const Intx2<Intx2<T1,false>,S1> & x_, const Intx2<T1,S2> & y_)
        {
            Intx2<Intx2<T1,false>,S1> & x = const_cast<Intx2<Intx2<T1,false>,S1> &>(x_); 
            Intx2<T1,S2> & y = const_cast<Intx2<T1,S2> &>(y_); 

            bool neg_x = (x < 0);
            bool neg_y = (y < 0);

            // Change
            if (neg_x) x = -x;
            if (neg_y) y = -y;

            Intx2<Intx2<T1,false>,S1||S2> res;
            if (x.a != 0)
            {
                res += x.a / y;
                res <<= 8*sizeof(res.a);
            }
            res += x.b / y;
            
            // Recover
            if (neg_x) x = -x;
            if (neg_y) y = -y;

            if (neg_x ^ neg_y) res = -res;

            return res;
        }

        template<typename T1, bool S1, bool S2>
        inline Intx2<T1,S1||S2> operator / (const Intx2<T1,S1> & x, const Intx2<T1,S2> & y)
        {
            return Intx2<Intx2<T1,false>,S1>(x) / y;
        }
            

        template<typename T1, typename T2, bool S1> // const bool T2_SIGN = ((T2(-1))<0)
        inline Intx2<T1,S1||((T2(-1))<0)> operator / (const Intx2<T1,S1> & x, const T2 & y)
        {
            const bool T2_SIGN = (T2(-1)<0);

            if (sizeof(x) >= sizeof(y))
                return x / Intx2<T1,S1||T2_SIGN>(y);
            else
                return T2(x) / y;
        }

        template<typename T1, typename T2, bool S1> // const bool T2_SIGN = ((T2(-1))<0)
        inline Intx2<T1,S1||((T2(-1))<0)> operator / (const T2 & x, const Intx2<T1,S1> & y)
        {
            const bool T2_SIGN = (T2(-1)<0);

            if (sizeof(x) >= sizeof(y))
                return x / T2(y);
            else
                return Intx2<T1,S1||T2_SIGN>(x) / y;
        }

        // ================================================================
        /*
        template<typename T1, bool S1>
        std::ostream &
        operator << (std::ostream & os, const Intx2<T1,S1> & value)
        {
            if (value < 0)
                os << '-';
            return os << std::hex << value.a << value.b << std::dec;
        }
        */
    }
    // namespace util
}
// namespace boolib

#endif // INTX2_H
