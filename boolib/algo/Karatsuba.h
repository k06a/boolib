#ifndef KARATSUBA_H
#define KARATSUBA_H

#include <stdlib.h>
#include <util/LittleBigEndian.h>

namespace boolib
{
    namespace algo
    {

        //
        // Karatsuba multiplication algorhytm
        //
        //      high                    low     high      low     high      low
        //     +------+------+------+------+   +------+------+   +------+------+
        //     |  r3  |  r2  |  r1  |  r0  | = |  x1  |  x0  | * |  y1  |  y0  |
        //     +------+------+------+------+   +------+------+   +------+------+
        //     |             |             |
        //     +-------------+-------------+
        // add |    x1*y1    |    x0*y0    |
        //     +----+-+------+------+------+
        //          | |             |
        //          +-+------+------+
        //      add | x0*y1 + x1*y0 |
        //          +-+------+------+
        //

        //
        // Params:
        //     T  - is type of x0, x1, y0 and y1 halves
        //     T2 - is type of x, y and half of res
        //

        template<typename T, typename T2>
        inline void Karatsuba_multiply(const T * x, const T * y, T2 * res)
        {
            const unsigned short endian = 0x0001;
        
            if (IS_LITTLE_ENDIAN)
                return Karatsuba_multiply_little_endian(x,y,res);
            if (IS_BIG_ENDIAN)
                return Karatsuba_multiply_big_endian(x,y,res);
        }

        template<typename T, typename T2>
        inline void Karatsuba_multiply_little_endian(const T * x, const T * y, T2 * res)
        {
            // Define vars (differs from byte order)

            #define ptrRes ((T*)res)
            T2 &  lowWord = (T2&)(ptrRes[0]);
            T2 &  midWord = (T2&)(ptrRes[1]);
            T2 & highWord = (T2&)(ptrRes[2]);
            T  & highByte = (T &)(ptrRes[3]);

            const T & x0 = x[0];
            const T & x1 = x[1];
            const T & y0 = y[0];
            const T & y1 = y[1];

            // Multiply action

            lowWord  = x0 * y0;
            highWord = x1 * y1;

            T2 m1 = x0 * y1;
            T2 m2 = x1 * y0;

            midWord += m1;
            if (midWord < m1) highByte++;
            midWord += m2;
            if (midWord < m2) highByte++;
        }

        template<typename T, typename T2>
        inline void Karatsuba_multiply_big_endian(const T * x, const T * y, T2 * res)
        {
            // Define vars (differs from byte order)

            #define ptrRes ((T*)res)
            T2 & highWord = *(T2*)(ptrRes+3);
            T2 &  lowWord = *(T2*)(ptrRes+2);
            T2 &  midWord = *(T2*)(ptrRes+1);
            T  & highByte = *(T *)(ptrRes+0);

            const T & x0 = x[1];
            const T & x1 = x[0];
            const T & y0 = y[1];
            const T & y1 = y[0];

            // Multiply action

            lowWord  = x0 * y0;
            highWord = x1 * y1;

            T m1 = x0 * y1;
            T m2 = x1 * y0;

            midWord += m1;
            if (midWord < m1) highByte++;
            midWord += m2;
            if (midWord < m2) highByte++;
        }

    }
    // namespace algo
}
// namespace boolib

#endif // KARATSUBA_H
