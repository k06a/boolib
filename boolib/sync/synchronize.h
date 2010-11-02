#ifndef SYNCHRONIZE_H
#define SYNCHRONIZE_H

#include <windows.h> 

namespace boolib
{
    namespace sync
    {
    
        //
        // Name:
        //     synchronize(int)
        //
        // Description:
        //     Only one thread can get inside
        //     this block at the same time.
        //
        // Usage:
        //     synchronize(55)
        //     {
        //        // protected block
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

        #define synchronize(myint) \
            for (boolib::sync::Synchro<myint>::Local s; s.logic(); )

    }
    // namespace sync
}
// namespace boolib

#endif // SYNCHRONIZE_H
