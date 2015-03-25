# Introducing LittleEndian and BigEndian C++ templates: #

1) Get [source code](http://code.google.com/p/boolib/source/browse/boolib/util/LittleBigEndian.h)

2) Look at [tests](http://code.google.com/p/boolib/source/browse/test/util/LitteBigEndianTest.h)

3) Preview:
```
typedef LittleEndian<int> i32le;
typedef BigEndian<int>    i32be;

const char * blob = "\x01\x02\x03\x04";

i32le & littleEndian = (i32le&)(*blob);
// (littleEndian == 0x04030201)

i32be & bigEndian = (i32be&)(*blob);
// (bigEndian == 0x01020304)
```

You don't need to use htonl() or ntohl().

How? Just look at this using:
```
struct tcp_header
{
    BigEndian<unsigned short> src_port;
    BigEndian<unsigned short> dst_port;
    // ...
};

if ((src_port == 80) ||
    (src_port == 8080)) // HTTP
{
    // ...   
}

if (src_port == 443) // HTTPS
{
    // ...
}
```

Comming soon ...