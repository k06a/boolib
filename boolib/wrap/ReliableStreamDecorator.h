
//
// Usage:
//
//  namespace MySpace
//  {
//      #define RSD_IStream                 IMyStream
//      #define RSD_ReliableStreamDecorator MyReliableStreamDecorator
//      #define RSD_Write                   Send
//      #define RSD_Read                    Recv
//      #include <boolib/wrap/ReliableStreamDecorator.h>
//  }
//  // namespace MySpace
//

#ifndef RSD_IStream
#error You should redefine macro RSD_IStream \
before including "ReliableStreamDecorator.h"
#endif

#ifndef RSD_ReliableStreamDecorator
#error You should redefine macro RSD_ReliableStreamDecorator \
before including "ReliableStreamDecorator.h"
#endif

#ifndef RSD_Write
#error You should redefine macro RSD_Write \
before including "ReliableStreamDecorator.h"
#endif

#ifndef RSD_Read
#error You should redefine macro RSD_Read \
before including "ReliableStreamDecorator.h"
#endif

class RSD_IStream;

class RSD_ReliableStreamDecorator : public RSD_IStream
{
    RSD_IStream * stream;

public:
    RSD_ReliableStreamDecorator(RSD_IStream * stream)
        : stream(stream)
    {
    }

    /// Послать из буфера ровно size байт
    virtual size_t RSD_Write(char * buffer, IN size_t size)
    {
        size_t needToSend = size;
        while (needToSend > 0)
        {
            int sended = stream->Send(buffer, needToSend);
            needToSend -= sended;
            buffer += sended;
        }
        return size - needToSend;
    }

    /// Прочитать в буфер ровно count байт 
    virtual size_t RSD_Read(char * buffer, IN size_t count)
    {
        size_t needToRecv = count;
        while (needToRecv > 0)
        {
            int recieved = stream->Recv(buffer, needToRecv);
            needToRecv -= recieved;
            buffer += recieved;
        }
        return count - needToRecv;
    }
};

#undef RSD_IStream
#undef RSD_ReliableStreamDecorator
#undef RSD_Write
#undef RSD_Read
