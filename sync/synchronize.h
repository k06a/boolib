#ifndef SYNCRONIZE_H
#define SYNCRONIZE_H

#include <windows.h> 

namespace boolib
{
    namespace sync
    {
    
        //
        // ��������:
        //     synchronize(id)
        //
        // ��������:
        //     ������ c ����������� ����� ��������. � ���� �
        //     ����� id ������������ ����� ����� ������ ���� �����.
        //
        // �������������:
        //     synchronize(55)
        //     {
        //        // ���������� ���� ����
        //     }
        //

        template<unsigned T>
        class Synchro
        {
            static HANDLE mutex;
            static bool isLocked;

        public:
            class Local
            {
            public:
                Local()
                {
                    WaitForSingleObject(mutex, INFINITE);
                }
                ~Local()
                {
                    ReleaseMutex(mutex);
                }
                bool logic()
                {
                    isLocked = !isLocked;
                    return isLocked;
                }
            };
        };

        template<unsigned T>
        HANDLE Synchro<T>::mutex = CreateMutex(NULL, FALSE, NULL);

        template<unsigned T>
        bool Synchro<T>::isLocked = false;

        #define synchronize(id) for (boolib::sync::Synchro<id>::Local s; s.logic(); )

    }
    // namespace sync
}
// namespace boolib

#endif // SYNCRONIZE_H