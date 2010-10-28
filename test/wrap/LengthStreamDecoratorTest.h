
#include <string>

namespace LengthStreamDecoratorTestSpace
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
// namespace LengthStreamDecoratorTestSpace

namespace LengthStreamDecoratorTestSpace
{
    class StringStream : public IStringStream
    {
        std::string stream;
    public:

        virtual ~StringStream() {}

        virtual size_t Send(char * buffer, size_t size)
        {
            for (size_t i = 0; i < size; i++)
                stream.append(1, buffer[i]);
            return size;
        }

        virtual size_t Recv(char * buffer, size_t size)
        {
            for (size_t i = 0; i < size; i++)
                buffer[i] = stream[i];
            stream = stream.substr(size, stream.length() - size);
            return size;
        }

        virtual const std::string & getResult()
        {
            return stream;
        }
    };
}
// namespace LengthStreamDecoratorTestSpace

namespace LengthStreamDecoratorTestSpace
{
    #define LSD_IStream                 IStream
    #define LSD_LengthStreamDecorator   LengthStreamDecorator
    #define LSD_Write                   Send
    #define LSD_Read                    Recv
    #include "wrap/LengthStreamDecorator.h"
}
// namespace LengthStreamDecoratorTestSpace

void LengthControlStreamTest()
{
    using LengthStreamDecoratorTestSpace::IStream;
    using LengthStreamDecoratorTestSpace::IString;
    using LengthStreamDecoratorTestSpace::IStringStream;
    using LengthStreamDecoratorTestSpace::StringStream;
    using LengthStreamDecoratorTestSpace::LengthStreamDecorator;
    
    IStringStream * stringStream = new StringStream();
    IStream * iStream = new LengthStreamDecorator(stringStream);

    // Writing data
    const char hello[] = "Hello World";
    const char hello_result[] = "\x0c\0\0\0" "Hello World";
    iStream->Send((char*)hello, sizeof(hello));

    // Checking what was written
    if (0 != strcmp(stringStream->getResult().c_str(), hello_result))
    {
        std::cout << "LengthControlStreamTest() failed" << std::endl;
        return;
    }
    
    // Reading data
    char buffer[32];
    iStream->Recv((char*)buffer, sizeof(buffer));

    // Checking what was read
    if (0 != strcmp(buffer, hello))
        std::cout << "LengthControlStreamTest() failed" << std::endl;
}
