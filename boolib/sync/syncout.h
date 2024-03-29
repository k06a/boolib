#ifndef SYNC_COUT_H
#define SYNC_COUT_H

#include <iostream>
#include <sstream>

namespace boolib
{
    namespace sync
    {

        //
        // Name:
        //     syncout, syncout_t(stream)
        //
        // Description:
        //     Unbreakable writing to the output straem.
        //
        // �������������:
        //     syncout << "Hello" << ' ' << "World";
        //     syncout_t(mystream) << "Hello" << ' ' << "World";
        //

        template<typename T>
        class syncout_class : public std::stringstream
        {
            T & value;
        public:
            syncout_class(T & V) : std::stringstream(), value(V) {}
            ~syncout_class()
            {
               value.write(str().c_str(), str().length());
            }
            syncout_class & func()
            {
                return *this;
            }
        };

        #define syncout \
            (*static_cast<std::stringstream*> \
            (&(boolib::sync::syncout_class<std::ostream>(std::cout).func())))

        #define syncout_t(mystream) \
            (*static_cast<std::stringstream*> \
            (&(boolib::sync::syncout_class<std::ostream>(mystream).func())))
        
    }
    // namespace sync
}
// namespace std

#endif // SYNC_COUT_H
