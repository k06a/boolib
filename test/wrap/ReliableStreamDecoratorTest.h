
#include <string>

namespace ReliableStreamDecoratorTestSpace
{
    class IStream
    {
    public:
        virtual ~IStream() {}

        virtual size_t Send(char * buffer, size_t size) = 0;
        virtual size_t Recv(char * buffer, size_t size) = 0;
    };

    class IString
    {
    public:
        virtual ~IString() {}

        virtual const std::string & getResult() = 0;
    };

    class IStringStream : public IStream, public IString
    {
    public:
        virtual ~IStringStream() {}
    };
}
// namespace ReliableStreamDecoratorTestSpace

namespace ReliableStreamDecoratorTestSpace
{
    class StringStream : public IStringStream
    {
        std::string stream;
    public:

        virtual ~StringStream() {}

        // It writes only a half of (size) per call
        virtual size_t Send(char * buffer, size_t size)
        {
            size_t i;
            for (i = 0; (i == 0) || (i < size/2); i++)
                stream.append(1, buffer[i]);
            return i;
        }

        // It reads only a half of (size) per call
        virtual size_t Recv(char * buffer, size_t size)
        {
            size_t i;
            for (i = 0; (i == 0) || (i < size/2); i++)
                buffer[i] = stream[i];
            stream = stream.substr(i, stream.length() - i);
            return i;
        }

        virtual const std::string & getResult()
        {
            return stream;
        }
    };
}
// namespace ReliableStreamDecoratorTestSpace

namespace ReliableStreamDecoratorTestSpace
{
    #define RSD_IStream                 IStream
    #define RSD_ReliableStreamDecorator ReliableStreamDecorator
    #define RSD_Write                   Send
    #define RSD_Read                    Recv
    #include "wrap/ReliableStreamDecorator.h"
}
// namespace ReliableStreamDecoratorTestSpace

void ReliableControlStreamTest()
{
    using ReliableStreamDecoratorTestSpace::IStream;
    using ReliableStreamDecoratorTestSpace::IString;
    using ReliableStreamDecoratorTestSpace::IStringStream;
    using ReliableStreamDecoratorTestSpace::StringStream;
    using ReliableStreamDecoratorTestSpace::ReliableStreamDecorator;
    
    IStringStream * stringStream = new StringStream();
    IStream * iStream = new ReliableStreamDecorator(stringStream);

    // Writing data
    const char hello[] = "Hello World";
    iStream->Send((char*)hello, sizeof(hello));

    // Checking what was written
    if (0 != strcmp(stringStream->getResult().c_str(), hello))
    {
        std::cout << "ReliableControlStreamTest() failed" << std::endl;
        return;
    }

    // Reading data
    char buffer[32];
    iStream->Recv((char*)buffer, sizeof(hello));

    // Checking what was read
    if (0 != strcmp(buffer, hello))
    {
        std::cout << "ReliableControlStreamTest() failed" << std::endl;
        return;
    }
}