
#include <iostream>

using namespace std;

namespace boolib
{
    namespace crypt
    {

        template<class T>
        class ShakedValue
        {
            T ** items;
            int itemCount;

        public:

            // Конструкторы и деструкторы

            ShakedValue(const T & value = T(), int count = 2, int scrambler = 0)
            {
                init(value, count, scrambler);
            }

            ShakedValue(const ShakedValue<T> & value)
            {
                init(value.currentValue(), value.itemCount);
            }

            ~ShakedValue()
            {
                deinit();
            }

            // Операторы

            ShakedValue<T> & operator = (const T newValue)
            {
                randomItem() += newValue - currentValue();
                return *this;
            }

            operator const T () const
            {
                return currentValue();
            }

            ShakedValue<T> operator +  (T value) { randomItem() += value; return *this; }
            ShakedValue<T> operator -  (T value) { randomItem() -= value; return *this; }
            ShakedValue<T> operator += (T value) { randomItem() += value; return *this; }
            ShakedValue<T> operator -= (T value) { randomItem() -= value; return *this; }
            
            ShakedValue<T> operator *  (T value) { return operator = (currentValue() * value); }
            ShakedValue<T> operator /  (T value) { return operator = (currentValue() / value); }
            ShakedValue<T> operator *= (T value) { return operator = (currentValue() * value); }
            ShakedValue<T> operator /= (T value) { return operator = (currentValue() / value); }

            const ShakedValue<T> & operator ++ (int a) { randomItem()++; return *this; }
            const ShakedValue<T> & operator -- (int a) { randomItem()--; return *this; }
            ShakedValue<T> & operator ++ () { randomItem()++; return *this; }
            ShakedValue<T> & operator -- () { randomItem()--; return *this; }

            // Методы

        private:
            void init(T value = T(), int count = 2, int scrambler = 0)
            {
                this->itemCount = count;
                items = new T * [count];
                char * buf = 0;

                for (int i = 0; i < count; i++)
                {
                    if (scrambler)
                    {
                        delete [] buf;
                        buf = new char [rand() % scrambler];
                    }

                    items[i] = new T;
                }

                operator = (value);
            }

            void deinit()
            {
                for (int i = 0; i < itemCount; i++)
                    delete items[i];
                delete [] items;
                items = NULL;
                itemCount = 0;
            }

            const T currentValue() const
            {
                T summa = T();
                
                for (int i = 0; i < itemCount; i++)
                    summa += *items[i];

                return summa;
            }

            T & randomItem() const
            {
                return *items[rand() % itemCount];
            }
        };

    }
    // namespace crypt
}
// namespace boolib