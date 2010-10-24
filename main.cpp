#include <iostream>
#include <Windows.h>
#include "sync.h"

using namespace std;

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
        cout << "synchronizeTest() failed" << endl;
}

int main(int argc, char * argv[])
{
    synchronizeTest();
}
