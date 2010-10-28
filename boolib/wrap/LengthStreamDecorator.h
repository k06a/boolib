
//
// Usage:
//
//  namespace MySpace
//  {
//      #define LSD_IStream                 IMyStream
//      #define LSD_LengthStreamDecorator   MyLengthStreamDecorator
//      #define LSD_Write                   Send
//      #define LSD_Read                    Recv
//      #include <boolib/wrap/LengthStreamDecorator.h>
//  }
//  // namespace MySpace
//

#ifndef LSD_IStream
#error You should redefine macro LSD_IStream \
before including "LengthStreamDecorator.h"
#endif

#ifndef LSD_LengthStreamDecorator
#error You should redefine macro LSD_LengthStreamDecorator \
before including "LengthStreamDecorator.h"
#endif

#ifndef LSD_Write
#error You should redefine macro LSD_Write \
before including "LengthStreamDecorator.h"
#endif

#ifndef LSD_Read
#error You should redefine macro LSD_Read \
before including "LengthStreamDecorator.h"
#endif

class LSD_IStream;

class LSD_LengthStreamDecorator : public LSD_IStream
{
    LSD_IStream * stream;

public:
    LSD_LengthStreamDecorator(LSD_IStream * stream)
        : stream(stream)
    {
    }

    /// Послать из буфера ровно size байт
    virtual size_t LSD_Write(char * buffer, size_t size)
    {
        stream->LSD_Write((char*)&size, sizeof(size));
        stream->LSD_Write(buffer, size);
        return size;
    }

    /// Прочитать в буфер ровно count байт
    virtual size_t LSD_Read(char * buffer, size_t count)
    {
        size_t realCount;
        stream->LSD_Read((char*)&realCount, sizeof(realCount));
        stream->LSD_Read(buffer, realCount);
        return realCount;
    }
};

#undef LSD_IStream
#undef LSD_LengthStreamDecorator
#undef LSD_Write
#undef LSD_Read
    