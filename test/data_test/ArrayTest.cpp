#include "ArrayTest.hpp"
#include "Array.hpp"
#include "../TestStruct.hpp"
#include "../Serializer.hpp"

#include <iostream> //For std::cout and std::fixed
#include <string>
#include <sstream>  //For std::stringstream

static std::stringstream s_FileBuffer;

bool ArrayTest::RunAllTest() noexcept
{
    std::stringstream test_results_buffer;
    bool test_result = true;
    size_t passed = 6;
    s_FileBuffer << "Array Bug Tests:" << std::endl;
    s_FileBuffer << "Total test executed: " << passed << std::endl;

    if (!Iterators()) { test_results_buffer << std::endl << "Iterator Test Failed" << std::endl; test_result = false; --passed; }
    if (!Copy()) { test_results_buffer << std::endl << "Copy Test Failed" << std::endl; test_result = false; --passed; }
    if (!Move()) { test_results_buffer << std::endl << "Move Test Failed" << std::endl; test_result = false; --passed; }
    if (!Fill()) { test_results_buffer << std::endl << "Fill Test Failed" << std::endl; test_result = false; --passed; }
    if (!Swap()) { test_results_buffer << std::endl << "Swap Test Failed" << std::endl; test_result = false; --passed; }
    if (!Operators()) { test_results_buffer << std::endl << "Operator Test Failed" << std::endl; test_result = false; --passed; }

    s_FileBuffer << "Total test passed: " << passed << std::endl << std::endl;
    if (test_result) { s_FileBuffer << "No errors found" << std::endl; }
    else { s_FileBuffer << test_results_buffer.str(); }
    s_FileBuffer << std::endl << std::endl;
    Serializer::SerializeResults("Array_Results.txt", s_FileBuffer);

    return test_result;
}

bool ArrayTest::Iterators() noexcept
{
    //operator++() noexcept
    //operator++(int) noexcept
    //operator+=(size_t) noexcept
    //operator+=(int) noexcept
    //Advance(size_t)
    //operator--() noexcept
    //operator--(int) noexcept
    //operator-=(size_t) noexcept
    //operator-=(int) noexcept
    //Retreat(size_t)
    //operator+(size_t) noexcept
    //operator+(int) noexcept
    //Next(size_t) const
    //operator-(size_t) noexcept
    //operator-(int) noexcept
    //Prev(size_t) const
    //operator[](size_t) const noexcept
    //operator[](int) const noexcept
    //At(size_t) const
    //At(int) const
    //operator*() const noexcept
    //Data() const noexcept
    //operator->() const noexcept
    //Get() const noexcept
    //Distance(const Iterator&) const noexcept
    //operator==(const Iterator&) const noexcept
    //operator==(const T*) const noexcept
    //operator!=(const Iterator&) const noexcept
    //operator!=(const T*) const noexcept
    //operator<(const Iterator&) const noexcept
    //operator<=(const Iterator&) const noexcept
    //operator>(const Iterator&) const noexcept
    //operator>=(const Iterator&) const noexcept
    //operator bool() const noexcept
    //IsValid() const noexcept
    //Iterator(T*) noexcept
    //Iterator(const Iterator&) noexcept
    //Iterator(Iterator&&) noexcept
    //operator=(const Iterator&) noexcept
    //operator=(Iterator&&) noexcept
    //operator=(const T*) noexcept

    {
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::iterator it(array.begin());

            for (size_t i = 0; i < array.Size(); ++i)
            {
                if (*it != TestStruct((float)i)) { return false; }
                ++it;
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::iterator it(array.begin());

            for (size_t i = 0; i < array.Size(); ++i)
            {
                if (*it++ != TestStruct((float)i)) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 0; i < array.Size(); ++i)
            {
                Array<TestStruct, 5>::iterator it(array.begin());
                it += i;
                if (*it != TestStruct((float)i)) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 1; i <= (int)array.Size(); ++i)
            {
                Array<TestStruct, 5>::iterator it(array.end());
                it += -i;
                if (*it != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::iterator it;

            for (size_t i = 0; i < array.Size(); ++i)
            {
                it = array.begin();
                it.Advance(i);
                if (*it != TestStruct((float)i)) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::iterator it(array.end());

            for (size_t i = 0; i < array.Size(); ++i)
            {
                if (*--it != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::iterator it(array.end());

            --it;
            for (size_t i = 0; i < array.Size(); ++i)
            {
                if (*it-- != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 1; i <= array.Size(); ++i)
            {
                Array<TestStruct, 5>::iterator it(array.end());
                it -= i;
                if (*it != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 0; i < (int)array.Size(); ++i)
            {
                Array<TestStruct, 5>::iterator it(array.begin());
                it -= -i;
                if (*it != TestStruct((float)i)) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::iterator it;

            for (size_t i = 1; i <= array.Size(); ++i)
            {
                it = array.end();
                it.Retreat(i);
                if (*it != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 0; i < array.Size(); ++i)
            {
                Array<TestStruct, 5>::iterator it(array.begin());
                if (*(it + i) != TestStruct((float)i)) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 1; i <= (int)array.Size(); ++i)
            {
                Array<TestStruct, 5>::iterator it(array.end());
                if (*(it + -i) != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::iterator it;

            for (size_t i = 0; i < array.Size(); ++i)
            {
                it = array.begin();
                if (*it.Next(i) != TestStruct((float)i)) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 1; i <= array.Size(); ++i)
            {
                Array<TestStruct, 5>::iterator it(array.end());
                if (*(it - i) != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 0; i < (int)array.Size(); ++i)
            {
                Array<TestStruct, 5>::iterator it(array.begin());
                if (*(it - -i) != TestStruct((float)i)) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::iterator it;

            for (size_t i = 1; i <= array.Size(); ++i)
            {
                it = array.end();
                if (*it.Prev(i) != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::iterator it(array.begin());

            for (size_t i = 0; i < array.Size(); ++i)
            {
                if (it[i] != TestStruct((float)i)) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::iterator it(array.end());

            for (int i = 1; i <= (int)array.Size(); ++i)
            {
                if (it[-i] != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::iterator it(array.begin());

            for (size_t i = 0; i < array.Size(); ++i)
            {
                if (it.At(i) != TestStruct((float)i)) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::iterator it(array.end());

            for (int i = 1; i <= (int)array.Size(); ++i)
            {
                if (it.At(-i) != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::iterator it(array.begin());

            for (size_t i = 0; i < array.Size(); ++i, ++it)
            {
                auto& aux = *it;
                if (aux != TestStruct((float)i)) { return false; }
                aux.x += 5.0f;
            }
            it = array.begin();
            for (size_t i = 0; i < array.Size(); ++i, ++it)
            {
                if ((*it).x != (float)(5 + i)) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::iterator it(array.begin());

            for (size_t i = 0; i < array.Size(); ++i, ++it)
            {
                auto& aux = it.Data();
                if (aux != TestStruct((float)i)) { return false; }
                aux.x += 5.0f;
            }
            it = array.begin();
            for (size_t i = 0; i < array.Size(); ++i, ++it)
            {
                if ((*it).x != (float)(5 + i)) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::iterator it(array.begin());

            for (size_t i = 0; i < array.Size(); ++i, ++it)
            {
                float& aux = it->x;
                if (aux != (float)i) { return false; }
                aux += 5.0f;
            }
            it = array.begin();
            for (size_t i = 0; i < array.Size(); ++i, ++it)
            {
                if ((*it).x != (float)(5 + i)) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::iterator it(array.begin());

            for (size_t i = 0; i < array.Size(); ++i, ++it)
            {
                auto& aux = it.Get()->x;
                if (aux != (float)i) { return false; }
                aux += 5.0f;
            }
            it = array.begin();
            for (size_t i = 0; i < array.Size(); ++i, ++it)
            {
                if ((*it).x != (float)(5 + i)) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::iterator it(array.begin());

            for (size_t i = 0; i < array.Size(); ++i, ++it)
            {
                auto& aux = *it;
                if (aux != TestStruct((float)i)) { return false; }
                aux.x += 5.0f;
            }
            it = array.begin();
            for (size_t i = 0; i < array.Size(); ++i, ++it)
            {
                if ((*it).x != (float)(5 + i)) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::iterator it(array.begin());

            for (size_t i = 0; i < array.Size(); ++i, ++it)
            {
                auto& aux = it.Data();
                if (aux != TestStruct((float)i)) { return false; }
                aux.x += 5.0f;
            }
            it = array.begin();
            for (size_t i = 0; i < array.Size(); ++i, ++it)
            {
                if ((*it).x != (float)(5 + i)) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::iterator it(array.begin());

            for (size_t i = 0; i < array.Size(); ++i, ++it)
            {
                auto aux = &it;
                if (**aux != TestStruct((float)i)) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::iterator it(array.begin());

            for (size_t i = 0; i < array.Size(); ++i, ++it)
            {
                Array<TestStruct, 5>::iterator aux(array.begin());
                if (it.Distance(aux) != i) { return false; }
                if (aux.Distance(it) != i) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::iterator it;
            if (it) { return false; }
            if (it.IsValid()) { return false; }
            it = array.end();
            if (it == array.begin()) { return false; }
            if (it == &array[0]) { return false; }
            it = array.begin();
            if (it != array.begin()) { return false; }
            if (it != &array[0]) { return false; }
            if (array.end() < array.begin()) { return false; }
            if (array.begin() > array.end()) { return false; }
            if (!(it <= array.begin())) { return false; }
            if (!(it >= array.begin())) { return false; }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::iterator it0(&array[3]);
            if (*it0 != TestStruct(3.0f)) { return false; }
            Array<TestStruct, 5>::iterator it1(array.begin());
            if (*it1 != TestStruct(0.0f)) { return false; }
            Array<TestStruct, 5>::iterator aux(&array[2]);
            Array<TestStruct, 5>::iterator it2(std::move(aux));
            if (aux) { return false; }
            if (*it2 != TestStruct(2.0f)) { return false; }
            it0 = &array[4];
            if (*it0 != TestStruct(4.0f)) { return false; }
            it1 = it0;
            if (*it1 != TestStruct(4.0f)) { return false; }
            it0 = std::move(it2);
            if (*it0 != TestStruct(2.0f)) { return false; }
            if (it2) { return false; }
        }
    }
    {
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::const_iterator it(array.cbegin());

            for (size_t i = 0; i < array.Size(); ++i)
            {
                if (*it != TestStruct((float)i)) { return false; }
                ++it;
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::const_iterator it(array.cbegin());

            for (size_t i = 0; i < array.Size(); ++i)
            {
                if (*it++ != TestStruct((float)i)) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 0; i < array.Size(); ++i)
            {
                Array<TestStruct, 5>::const_iterator it(array.cbegin());
                it += i;
                if (*it != TestStruct((float)i)) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 1; i <= (int)array.Size(); ++i)
            {
                Array<TestStruct, 5>::const_iterator it(array.cend());
                it += -i;
                if (*it != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::const_iterator it;

            for (size_t i = 0; i < array.Size(); ++i)
            {
                it = array.cbegin();
                it.Advance(i);
                if (*it != TestStruct((float)i)) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::const_iterator it(array.cend());
            --it;

            for (size_t i = 0; i < array.Size(); ++i)
            {
                if (*it-- != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::const_iterator it(array.cend());

            for (size_t i = 0; i < array.Size(); ++i)
            {
                if (*--it != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 1; i <= array.Size(); ++i)
            {
                Array<TestStruct, 5>::const_iterator it(array.cend());
                it -= i;
                if (*it != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 0; i < (int)array.Size(); ++i)
            {
                Array<TestStruct, 5>::const_iterator it(array.cbegin());
                it -= -i;
                if (*it != TestStruct((float)i)) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::const_iterator it;

            for (size_t i = 1; i <= array.Size(); ++i)
            {
                it = array.cend();
                it.Retreat(i);
                if (*it != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 0; i < array.Size(); ++i)
            {
                Array<TestStruct, 5>::const_iterator it(array.cbegin());
                if (*(it + i) != TestStruct((float)i)) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 1; i <= (int)array.Size(); ++i)
            {
                Array<TestStruct, 5>::const_iterator it(array.cend());
                if (*(it + -i) != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::const_iterator it;

            for (size_t i = 0; i < array.Size(); ++i)
            {
                it = array.cbegin();
                if (*it.Next(i) != TestStruct((float)i)) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 1; i <= array.Size(); ++i)
            {
                Array<TestStruct, 5>::const_iterator it(array.cend());
                if (*(it - i) != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 0; i < (int)array.Size(); ++i)
            {
                Array<TestStruct, 5>::const_iterator it(array.cbegin());
                if (*(it - -i) != TestStruct((float)i)) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::const_iterator it;

            for (size_t i = 1; i <= array.Size(); ++i)
            {
                it = array.cend();
                if (*it.Prev(i) != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::const_iterator it(array.cbegin());

            for (size_t i = 0; i < array.Size(); ++i)
            {
                if (it[i] != TestStruct((float)i)) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::const_iterator it(array.cend());

            for (int i = 1; i <= (int)array.Size(); ++i)
            {
                if (it[-i] != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::const_iterator it(array.cbegin());

            for (size_t i = 0; i < array.Size(); ++i)
            {
                if (it.At(i) != TestStruct((float)i)) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::const_iterator it(array.cend());

            for (int i = 1; i <= (int)array.Size(); ++i)
            {
                if (it.At(-i) != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::const_iterator it(array.cbegin());

            for (size_t i = 0; i < array.Size(); ++i, ++it)
            {
                const auto& aux = *it;
                if (aux != TestStruct((float)i)) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::const_iterator it(array.cbegin());

            for (size_t i = 0; i < array.Size(); ++i, ++it)
            {
                const auto& aux = it.Data();
                if (aux != TestStruct((float)i)) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::const_iterator it(array.cbegin());

            for (size_t i = 0; i < array.Size(); ++i, ++it)
            {
                const float& aux = it->x;
                if (aux != (float)i) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::const_iterator it(array.cbegin());

            for (size_t i = 0; i < array.Size(); ++i, ++it)
            {
                const auto& aux = it.Get()->x;
                if (aux != (float)i) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::const_iterator it(array.cbegin());

            for (size_t i = 0; i < array.Size(); ++i, ++it)
            {
                const auto& aux = *it;
                if (aux != TestStruct((float)i)) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::const_iterator it(array.cbegin());

            for (size_t i = 0; i < array.Size(); ++i, ++it)
            {
                auto& aux = it.Data();
                if (aux != TestStruct((float)i)) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::const_iterator it(array.cbegin());

            for (size_t i = 0; i < array.Size(); ++i, ++it)
            {
                const auto aux = &it;
                if (**aux != TestStruct((float)i)) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::const_iterator it(array.cbegin());

            for (size_t i = 0; i < array.Size(); ++i, ++it)
            {
                Array<TestStruct, 5>::const_iterator aux(array.cbegin());
                if (it.Distance(aux) != i) { return false; }
                if (aux.Distance(it) != i) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::const_iterator it;
            if (it) { return false; }
            if (it.IsValid()) { return false; }
            it = array.cend();
            if (it == array.cbegin()) { return false; }
            if (it == &array[0]) { return false; }
            it = array.cbegin();
            if (it != array.cbegin()) { return false; }
            if (it != &array[0]) { return false; }
            if (array.cend() < array.cbegin()) { return false; }
            if (array.cbegin() > array.cend()) { return false; }
            if (!(it <= array.cbegin())) { return false; }
            if (!(it >= array.cbegin())) { return false; }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::const_iterator it0(&array[3]);
            if (*it0 != TestStruct(3.0f)) { return false; }
            Array<TestStruct, 5>::const_iterator it1(array.cbegin());
            if (*it1 != TestStruct(0.0f)) { return false; }
            Array<TestStruct, 5>::const_iterator aux(&array[2]);
            Array<TestStruct, 5>::const_iterator it2(std::move(aux));
            if (aux) { return false; }
            if (*it2 != TestStruct(2.0f)) { return false; }
            it0 = &array[4];
            if (*it0 != TestStruct(4.0f)) { return false; }
            it1 = it0;
            if (*it1 != TestStruct(4.0f)) { return false; }
            it0 = std::move(it2);
            if (*it0 != TestStruct(2.0f)) { return false; }
            if (it2) { return false; }
        }
    }
    {
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::reverse_iterator it(array.rbegin());

            for (size_t i = 0; i < array.Size(); ++i)
            {
                if (*it != TestStruct((float)(4 - i))) { return false; }
                ++it;
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::reverse_iterator it(array.rbegin());

            for (size_t i = 0; i < array.Size(); ++i)
            {
                if (*it++ != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 0; i < array.Size(); ++i)
            {
                Array<TestStruct, 5>::reverse_iterator it(array.rbegin());
                it += i;
                if (*it != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 1; i <= (int)array.Size(); ++i)
            {
                Array<TestStruct, 5>::reverse_iterator it(array.rend());
                it += -i;
                if (*it != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::reverse_iterator it;

            for (size_t i = 0; i < array.Size(); ++i)
            {
                it = array.rbegin();
                it.Advance(i);
                if (*it != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::reverse_iterator it(array.rend());

            for (size_t i = 0; i < array.Size(); ++i)
            {
                if (*--it != TestStruct((float)i)) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::reverse_iterator it(array.rend());
            --it;

            for (size_t i = 0; i < array.Size(); ++i)
            {
                if (*it-- != TestStruct((float)i)) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 1; i <= array.Size(); ++i)
            {
                Array<TestStruct, 5>::reverse_iterator it(array.rend());
                it -= i;
                if (*it != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 0; i < (int)array.Size(); ++i)
            {
                Array<TestStruct, 5>::reverse_iterator it(array.rbegin());
                it -= -i;
                if (*it != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::reverse_iterator it;

            for (size_t i = 1; i <= array.Size(); ++i)
            {
                it = array.rend();
                it.Retreat(i);
                if (*it != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 0; i < array.Size(); ++i)
            {
                Array<TestStruct, 5>::reverse_iterator it(array.rbegin());
                auto a = *(it + i);
                if (a != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 1; i <= (int)array.Size(); ++i)
            {
                Array<TestStruct, 5>::reverse_iterator it(array.rend());
                if (*(it + -i) != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::reverse_iterator it;

            for (size_t i = 0; i < array.Size(); ++i)
            {
                it = array.rbegin();
                if (*it.Next(i) != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 1; i <= array.Size(); ++i)
            {
                Array<TestStruct, 5>::reverse_iterator it(array.rend());
                if (*(it - i) != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 0; i < (int)array.Size(); ++i)
            {
                Array<TestStruct, 5>::reverse_iterator it(array.rbegin());
                if (*(it - -i) != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::reverse_iterator it;

            for (size_t i = 1; i <= array.Size(); ++i)
            {
                it = array.rend();
                if (*it.Prev(i) != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::reverse_iterator it(array.rbegin());

            for (size_t i = 0; i < array.Size(); ++i)
            {
                if (it[i] != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::reverse_iterator it(array.rend());

            for (int i = 1; i <= (int)array.Size(); ++i)
            {
                if (it[-i] != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::reverse_iterator it(array.rbegin());

            for (size_t i = 0; i < array.Size(); ++i)
            {
                if (it.At(i) != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::reverse_iterator it(array.rend());

            for (int i = 1; i <= (int)array.Size(); ++i)
            {
                if (it.At(-i) != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::reverse_iterator it(array.rbegin());

            for (size_t i = 0; i < array.Size(); ++i, ++it)
            {
                auto& aux = *it;
                if (aux != TestStruct((float)(4 - i))) { return false; }
                aux.x += 5.0f;
            }
            it = array.rbegin();
            for (size_t i = 0; i < array.Size(); ++i, ++it)
            {
                if ((*it).x != (float)(9 - i)) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::reverse_iterator it(array.rbegin());

            for (size_t i = 0; i < array.Size(); ++i, ++it)
            {
                auto& aux = it.Data();
                if (aux != TestStruct((float)(4 - i))) { return false; }
                aux.x += 5.0f;
            }
            it = array.rbegin();
            for (size_t i = 0; i < array.Size(); ++i, ++it)
            {
                if ((*it).x != (float)(9 - i)) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::reverse_iterator it(array.rbegin());

            for (size_t i = 0; i < array.Size(); ++i, ++it)
            {
                float& aux = it->x;
                if (aux != (float)(4 - i)) { return false; }
                aux += 5.0f;
            }
            it = array.rbegin();
            for (size_t i = 0; i < array.Size(); ++i, ++it)
            {
                if ((*it).x != (float)(9 - i)) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::reverse_iterator it(array.rbegin());

            for (size_t i = 0; i < array.Size(); ++i, ++it)
            {
                auto& aux = it.Get()->x;
                if (aux != (float)(4 - i)) { return false; }
                aux += 5.0f;
            }
            it = array.rbegin();
            for (size_t i = 0; i < array.Size(); ++i, ++it)
            {
                if ((*it).x != (float)(9 - i)) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::reverse_iterator it(array.rbegin());

            for (size_t i = 0; i < array.Size(); ++i, ++it)
            {
                auto& aux = *it;
                if (aux != TestStruct((float)(4 - i))) { return false; }
                aux.x += 5.0f;
            }
            it = array.rbegin();
            for (size_t i = 0; i < array.Size(); ++i, ++it)
            {
                if ((*it).x != (float)(9 - i)) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::reverse_iterator it(array.rbegin());

            for (size_t i = 0; i < array.Size(); ++i, ++it)
            {
                auto& aux = it.Data();
                if (aux != TestStruct((float)(4 - i))) { return false; }
                aux.x += 5.0f;
            }
            it = array.rbegin();
            for (size_t i = 0; i < array.Size(); ++i, ++it)
            {
                if ((*it).x != (float)(9 - i)) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::reverse_iterator it(array.rbegin());

            for (size_t i = 0; i < array.Size(); ++i, ++it)
            {
                auto aux = &it;
                if (**aux != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::reverse_iterator it(array.rbegin());

            for (size_t i = 0; i < array.Size(); ++i, ++it)
            {
                Array<TestStruct, 5>::reverse_iterator aux(array.rbegin());
                if (it.Distance(aux) != i) { return false; }
                if (aux.Distance(it) != i) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::reverse_iterator it;
            if (it) { return false; }
            if (it.IsValid()) { return false; }
            it = array.rend();
            if (it == array.rbegin()) { return false; }
            if (it == &array[0]) { return false; }
            it = array.rbegin();
            if (it != array.rbegin()) { return false; }
            if (it != &array[4]) { return false; }
            if (array.rend() < array.rbegin()) { return false; }
            if (array.rbegin() > array.rend()) { return false; }
            if (!(it <= array.rbegin())) { return false; }
            if (!(it >= array.rbegin())) { return false; }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::reverse_iterator it0(&array[3]);
            if (*it0 != TestStruct(3.0f)) { return false; }
            Array<TestStruct, 5>::reverse_iterator it1(array.rbegin());
            if (*it1 != TestStruct(4.0f)) { return false; }
            Array<TestStruct, 5>::reverse_iterator aux(&array[2]);
            Array<TestStruct, 5>::reverse_iterator it2(std::move(aux));
            if (aux) { return false; }
            if (*it2 != TestStruct(2.0f)) { return false; }
            it0 = &array[4];
            if (*it0 != TestStruct(4.0f)) { return false; }
            it1 = it0;
            if (*it1 != TestStruct(4.0f)) { return false; }
            it0 = std::move(it2);
            if (*it0 != TestStruct(2.0f)) { return false; }
            if (it2) { return false; }
        }
    }
    {
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::const_reverse_iterator it(array.crbegin());

            for (size_t i = 0; i < array.Size(); ++i)
            {
                if (*it != TestStruct((float)(4 - i))) { return false; }
                ++it;
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::const_reverse_iterator it(array.crbegin());

            for (size_t i = 0; i < array.Size(); ++i)
            {
                if (*it++ != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 0; i < array.Size(); ++i)
            {
                Array<TestStruct, 5>::const_reverse_iterator it(array.crbegin());
                it += i;
                if (*it != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 1; i <= (int)array.Size(); ++i)
            {
                Array<TestStruct, 5>::const_reverse_iterator it(array.crend());
                it += -i;
                if (*it != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::const_reverse_iterator it;

            for (size_t i = 0; i < array.Size(); ++i)
            {
                it = array.crbegin();
                it.Advance(i);
                if (*it != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::const_reverse_iterator it(array.crend());

            for (size_t i = 0; i < array.Size(); ++i)
            {
                if (*--it != TestStruct((float)i)) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::const_reverse_iterator it(array.crend());
            --it;

            for (size_t i = 0; i < array.Size(); ++i)
            {
                if (*it-- != TestStruct((float)i)) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 1; i <= array.Size(); ++i)
            {
                Array<TestStruct, 5>::const_reverse_iterator it(array.crend());
                it -= i;
                if (*it != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 0; i < (int)array.Size(); ++i)
            {
                Array<TestStruct, 5>::const_reverse_iterator it(array.crbegin());
                it -= -i;
                if (*it != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::const_reverse_iterator it;

            for (size_t i = 1; i <= array.Size(); ++i)
            {
                it = array.crend();
                it.Retreat(i);
                if (*it != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 0; i < array.Size(); ++i)
            {
                Array<TestStruct, 5>::const_reverse_iterator it(array.crbegin());
                const auto a = *(it + i);
                if (a != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 1; i <= (int)array.Size(); ++i)
            {
                Array<TestStruct, 5>::const_reverse_iterator it(array.crend());
                if (*(it + -i) != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::const_reverse_iterator it;

            for (size_t i = 0; i < array.Size(); ++i)
            {
                it = array.crbegin();
                if (*it.Next(i) != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 1; i <= array.Size(); ++i)
            {
                Array<TestStruct, 5>::const_reverse_iterator it(array.crend());
                if (*(it - i) != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 0; i < (int)array.Size(); ++i)
            {
                Array<TestStruct, 5>::const_reverse_iterator it(array.crbegin());
                if (*(it - -i) != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::const_reverse_iterator it;

            for (size_t i = 1; i <= array.Size(); ++i)
            {
                it = array.crend();
                if (*it.Prev(i) != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::const_reverse_iterator it(array.crbegin());

            for (size_t i = 0; i < array.Size(); ++i)
            {
                if (it[i] != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::const_reverse_iterator it(array.crend());

            for (int i = 1; i <= (int)array.Size(); ++i)
            {
                if (it[-i] != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::const_reverse_iterator it(array.crbegin());

            for (size_t i = 0; i < array.Size(); ++i)
            {
                if (it.At(i) != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::const_reverse_iterator it(array.crend());

            for (int i = 1; i <= (int)array.Size(); ++i)
            {
                if (it.At(-i) != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::const_reverse_iterator it(array.crbegin());

            for (size_t i = 0; i < array.Size(); ++i, ++it)
            {
                const auto& aux = *it;
                if (aux != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::const_reverse_iterator it(array.crbegin());

            for (size_t i = 0; i < array.Size(); ++i, ++it)
            {
                const auto& aux = it.Data();
                if (aux != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::const_reverse_iterator it(array.crbegin());

            for (size_t i = 0; i < array.Size(); ++i, ++it)
            {
                const float& aux = it->x;
                if (aux != (float)(4 - i)) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::const_reverse_iterator it(array.crbegin());

            for (size_t i = 0; i < array.Size(); ++i, ++it)
            {
                const auto& aux = it.Get()->x;
                if (aux != (float)(4 - i)) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::const_reverse_iterator it(array.crbegin());

            for (size_t i = 0; i < array.Size(); ++i, ++it)
            {
                const auto& aux = *it;
                if (aux != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::const_reverse_iterator it(array.crbegin());

            for (size_t i = 0; i < array.Size(); ++i, ++it)
            {
                const auto& aux = it.Data();
                if (aux != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::const_reverse_iterator it(array.crbegin());

            for (size_t i = 0; i < array.Size(); ++i, ++it)
            {
                auto aux = &it;
                if (**aux != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::const_reverse_iterator it(array.crbegin());

            for (size_t i = 0; i < array.Size(); ++i, ++it)
            {
                Array<TestStruct, 5>::const_reverse_iterator aux(array.crbegin());
                if (it.Distance(aux) != i) { return false; }
                if (aux.Distance(it) != i) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::const_reverse_iterator it;
            if (it) { return false; }
            if (it.IsValid()) { return false; }
            it = array.crend();
            if (it == array.crbegin()) { return false; }
            if (it == &array[0]) { return false; }
            it = array.crbegin();
            if (it != array.crbegin()) { return false; }
            if (it != &array[4]) { return false; }
            if (array.crend() < array.crbegin()) { return false; }
            if (array.crbegin() > array.crend()) { return false; }
            if (!(it <= array.crbegin())) { return false; }
            if (!(it >= array.crbegin())) { return false; }
        }
        {
            Array<TestStruct, 5> array{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5>::const_reverse_iterator it0(&array[3]);
            if (*it0 != TestStruct(3.0f)) { return false; }
            Array<TestStruct, 5>::const_reverse_iterator it1(array.crbegin());
            if (*it1 != TestStruct(4.0f)) { return false; }
            Array<TestStruct, 5>::const_reverse_iterator aux(&array[2]);
            Array<TestStruct, 5>::const_reverse_iterator it2(std::move(aux));
            if (aux) { return false; }
            if (*it2 != TestStruct(2.0f)) { return false; }
            it0 = &array[4];
            if (*it0 != TestStruct(4.0f)) { return false; }
            it1 = it0;
            if (*it1 != TestStruct(4.0f)) { return false; }
            it0 = std::move(it2);
            if (*it0 != TestStruct(2.0f)) { return false; }
            if (it2) { return false; }
        }
    }

    return true;
}

bool ArrayTest::Copy() noexcept
{
    //Array(const Array& other) noexcept
    //operator=(const Array& other) noexcept

    {
        {
            Array<size_t, 5> array0{ 0, 1, 2, 3, 4 };
            Array<size_t, 5> array1(array0);

            for (size_t i = 0; i < array1.Size(); ++i)
            {
                if (array1[i] != i) { return false; }
            }
        }
        {
            Array<size_t, 5> array0{ 0, 1, 2, 3, 4 };
            Array<size_t, 5> array1{ 5, 6, 7, 8, 9 };
            array0 = array1;

            for (size_t i = 0; i < array0.Size(); ++i)
            {
                if (array0[i] != 5 + i) { return false; }
            }
        }
    }
    {
        {
            Array<std::string, 5> array0{ "0", "1", "2", "3", "4" };
            Array<std::string, 5> array1(array0);

            for (size_t i = 0; i < array1.Size(); ++i)
            {
                if (array1[i] != std::to_string(i)) { return false; }
            }
        }
        {
            Array<std::string, 5> array0{ "0", "1", "2", "3", "4" };
            Array<std::string, 5> array1{ "5", "6", "7", "8", "9" };
            array0 = array1;

            for (size_t i = 0; i < array0.Size(); ++i)
            {
                if (array0[i] != std::to_string(5 + i)) { return false; }
            }
        }
    }
    {
        {
            Array<TestStruct, 5> array0{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5> array1(array0);

            for (size_t i = 0; i < array1.Size(); ++i)
            {
                if (array1[i] != TestStruct((float)i)) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array0{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5> array1{ TestStruct(5.0f), TestStruct(6.0f), TestStruct(7.0f), TestStruct(8.0f), TestStruct(9.0f) };
            array0 = array1;

            for (size_t i = 0; i < array0.Size(); ++i)
            {
                if (array0[i] != TestStruct((float)(5 + i))) { return false; }
            }
        }
    }
    {
        {
            Array<std::shared_ptr<TestStruct>, 5> array0;
            for (size_t i = 0; i < array0.Size(); ++i)
            {
                array0[i] = std::make_shared<TestStruct>((float)i);
            }
            Array<std::shared_ptr<TestStruct>, 5> array1(array0);

            for (size_t i = 0; i < array1.Size(); ++i)
            {
                if (*array1[i] != TestStruct((float)i)) { return false; }
            }
        }
        {
            Array<std::shared_ptr<TestStruct>, 5> array0;
            Array<std::shared_ptr<TestStruct>, 5> array1;
            for (size_t i = 0; i < array0.Size(); ++i)
            {
                array0[i] = std::make_shared<TestStruct>((float)i);
                array1[i] = std::make_shared<TestStruct>((float)(5 + i));
            }
            array0 = array1;

            for (size_t i = 0; i < array0.Size(); ++i)
            {
                if (*array0[i] != TestStruct((float)(5 + i))) { return false; }
            }
        }
    }

    return true;
}

bool ArrayTest::Move() noexcept
{
    //Array(Array&& other) noexcept
    //operator=(Array&& other) noexcept

    {
        {
            Array<size_t, 5> array0{ 0, 1, 2, 3, 4 };
            Array<size_t, 5> array1(std::move(array0));

            for (size_t i = 0; i < array1.Size(); ++i)
            {
                if (array1[i] != i) { return false; }
            }
        }
        {
            Array<size_t, 5> array0{ 0, 1, 2, 3, 4 };
            Array<size_t, 5> array1{ 5, 6, 7, 8, 9 };
            array0 = std::move(array1);

            for (size_t i = 0; i < array0.Size(); ++i)
            {
                if (array0[i] != 5 + i) { return false; }
            }
        }
    }
    {
        {
            Array<std::string, 5> array0{ "0", "1", "2", "3", "4" };
            Array<std::string, 5> array1(std::move(array0));

            for (size_t i = 0; i < array1.Size(); ++i)
            {
                if (!array0[i].empty()) { return false; }
                if (array1[i] != std::to_string(i)) { return false; }
            }
        }
        {
            Array<std::string, 5> array0{ "0", "1", "2", "3", "4" };
            Array<std::string, 5> array1{ "5", "6", "7", "8", "9" };
            array0 = std::move(array1);

            for (size_t i = 0; i < array0.Size(); ++i)
            {
                if (array0[i] != std::to_string(5 + i)) { return false; }
                if (!array1[i].empty()) { return false; }
            }
        }
    }
    {
        {
            Array<TestStruct, 5> array0{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5> array1(std::move(array0));

            for (size_t i = 0; i < array1.Size(); ++i)
            {
                if (array0[i].p) { return false; }
                if (array1[i] != TestStruct((float)i)) { return false; }
            }
        }
        {
            Array<TestStruct, 5> array0{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Array<TestStruct, 5> array1{ TestStruct(5.0f), TestStruct(6.0f), TestStruct(7.0f), TestStruct(8.0f), TestStruct(9.0f) };
            array0 = std::move(array1);

            for (size_t i = 0; i < array0.Size(); ++i)
            {
                if (array0[i] != TestStruct((float)(5 + i))) { return false; }
                if (array1[i].p) { return false; }
            }
        }
    }
    {
        {
            Array<std::shared_ptr<TestStruct>, 5> array0;
            for (size_t i = 0; i < array0.Size(); ++i)
            {
                array0[i] = std::make_shared<TestStruct>((float)i);
            }
            Array<std::shared_ptr<TestStruct>, 5> array1(std::move(array0));

            for (size_t i = 0; i < array1.Size(); ++i)
            {
                if (array0[i]) { return false; }
                if (*array1[i] != TestStruct((float)i)) { return false; }
            }
        }
        {
            Array<std::shared_ptr<TestStruct>, 5> array0;
            Array<std::shared_ptr<TestStruct>, 5> array1;
            for (size_t i = 0; i < array0.Size(); ++i)
            {
                array0[i] = std::make_shared<TestStruct>((float)i);
                array1[i] = std::make_shared<TestStruct>((float)(5 + i));
            }
            array0 = std::move(array1);

            for (size_t i = 0; i < array0.Size(); ++i)
            {
                if (*array0[i] != TestStruct((float)(5 + i))) { return false; }
                if (array1[i]) { return false; }
            }
        }
    }

    return true;
}

bool ArrayTest::Fill() noexcept
{
    //Fill(const T& value)

    {
        Array<size_t, 5> array(0);
        for (size_t i = 0; i < array.Size(); ++i)
        {
            if (array[i] != 0) { return false; }
        }
    }
    {
        Array<std::string, 5> array(std::string("test"));
        for (size_t i = 0; i < array.Size(); ++i)
        {
            if (array[i] != std::string("test")) { return false; }
        }
    }
    {
        Array<TestStruct, 5> array(TestStruct(1.0f, 2.0f, 3.0f));
        for (size_t i = 0; i < array.Size(); ++i)
        {
            if (array[i] != TestStruct(1.0f, 2.0f, 3.0f)) { return false; }
        }
    }
    {
        Array<std::shared_ptr<TestStruct>, 5> array(std::make_shared<TestStruct>(1.0f, 2.0f, 3.0f));
        for (size_t i = 0; i < array.Size(); ++i)
        {
            if (*array[i] != TestStruct(1.0f, 2.0f, 3.0f)) { return false; }
        }
    }
    return true;
}

bool ArrayTest::Swap() noexcept
{
    //Swap(Array& other) noexcept

    {
        Array<size_t, 5> array0(0);
        Array<size_t, 5> array1(1);

        array0.Swap(array1);

        for (const size_t& element : array0)
        {
            if (element != 1) { return false; }
        }
    }
    {
        Array<std::string, 5> array0(std::string("test0"));
        Array<std::string, 5> array1(std::string("test1"));

        array0.Swap(array1);

        for (const std::string& element : array0)
        {
            if (element != std::string("test1")) { return false; }
        }
    }
    {
        Array<TestStruct, 5> array0(TestStruct(0.0f));
        Array<TestStruct, 5> array1(TestStruct(1.0f));

        array0.Swap(array1);

        for (const TestStruct& element : array0)
        {
            if (element != TestStruct(1.0f)) { return false; }
        }
    }
    {
        Array<std::shared_ptr<TestStruct>, 5> array0;
        Array<std::shared_ptr<TestStruct>, 5> array1;
        for (size_t i = 0; i < array0.Size(); ++i)
        {
            array0[i] = std::make_shared<TestStruct>((float)i);
            array1[i] = std::make_shared<TestStruct>((float)(5 + i));
        }
        array0.Swap(array1);

        for (size_t i = 0; i < array0.Size(); ++i)
        {
            if (*array0[i] != TestStruct((float)(5 + i))) { return false; }
            if (*array1[i] != TestStruct((float)i)) { return false; }
        }
    }

    return true;
}

bool ArrayTest::Operators() noexcept
{
    //operator==(const Array& other) noexcept
    //operator!=(const Array & other) noexcept

    Array<size_t, 5> array0{ 0, 1, 2, 3, 4 };
    Array<size_t, 5> array1{ 0, 1, 2, 3, 4 };
    Array<size_t, 5> array2{ 5, 6, 7, 8, 9 };

    if (array1 == array2) { return false; }
    if (array0 != array1) { return false; }

    return true;
}
