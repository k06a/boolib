#ifndef SYNCHRONIZE_CPP
#define SYNCHRONIZE_CPP

#include "sync.h"
#include <iostream>
#include <windows.h>

DWORD WINAPI synchronizeFunc(LPVOID p)
{
    int &value = *(int*&)p;

    for (int i = 0; i < 100000; i++)
    {
        synchronize(153)
        {
            int z = value;
            z = z + 1;
            value = z;
        }
    }

    return 0;
}

void synchronizeTest()
{
    int value = 0;

    HANDLE th[2];
    th[0] = CreateThread(NULL, 0, synchronizeFunc, (LPVOID)&value, 0, NULL);
    th[1] = CreateThread(NULL, 0, synchronizeFunc, (LPVOID)&value, 0, NULL);
    WaitForMultipleObjects(2, th, TRUE, INFINITE);

    if (value != 200000)
        std::cout << "synchronizeTest() failed" << std::endl;
}

#endif // SYNCHRONIZE_CPP
