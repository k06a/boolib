#ifndef SYNCOUT_CPP
#define SYNCOUT_CPP

#include "sync.h"
#include <iostream>
#include <sstream>
#include <windows.h>

DWORD WINAPI syncoutFunc(LPVOID p)
{
    std::stringstream & mystream = *(std::stringstream*&)p;

    for (int i = 0; i < 100; i++)
    {
        syncout_t(mystream)
            << "a" << "b" << "c" << "d" << "e"
            << 'A' << 'B' << 'C' << 'D' << 'E'
            <<  1  <<  2  <<  3  <<  4  <<  5  << ' ';
    }
    return 0;
}

void syncoutTest()
{
    std::stringstream stream;

    HANDLE th[2];
    th[0] = CreateThread(NULL, 0, syncoutFunc, (LPVOID)&stream, 0, NULL);
    th[1] = CreateThread(NULL, 0, syncoutFunc, (LPVOID)&stream, 0, NULL);
    WaitForMultipleObjects(2, th, TRUE, INFINITE);

    std::string text = stream.str();
    const char * data = text.c_str();
    for (int i = 0; i < 100; i++)
    {
        const char *d = data + 16*i;
        if (memcmp(data + 16*i, "abcdeABCDE12345 ", 16) != 0)
        {
            std::cout << "syncoutTest() failed" << std::endl;
            break;
        }
        d = 0;
    }
}

#endif // SYNCOUT_CPP
