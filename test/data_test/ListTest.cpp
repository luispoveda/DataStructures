#include "ListTest.hpp"
#include "List.hpp"
#include "../TestStruct.hpp"
#include "../Serializer.hpp"

#include <iostream> //For std::cout and std::fixed
#include <string>
#include <sstream>  //For std::stringstream

static std::stringstream s_FileBuffer;

bool ListTest::RunAllTest()
{
    std::stringstream test_results_buffer;
    bool test_result = true;
    size_t passed = 18;
    s_FileBuffer << "List Bug Tests:" << std::endl;
    s_FileBuffer << "Total test executed: " << passed << std::endl;

    if (!Iterators()) { test_results_buffer << std::endl << "Iterator Test Failed" << std::endl; test_result = false; --passed; }
    if (!Copy()) { test_results_buffer << std::endl << "Copy Test Failed" << std::endl; test_result = false; --passed; }
    if (!Move()) { test_results_buffer << std::endl << "Move Test Failed" << std::endl; test_result = false; --passed; }
    if (!Swap()) { test_results_buffer << std::endl << "Swap Test Failed" << std::endl; test_result = false; --passed; }
    if (!PushBack()) { test_results_buffer << std::endl << "PushBack Test Failed" << std::endl; test_result = false; --passed; }
    if (!PushFront()) { test_results_buffer << std::endl << "PushFront Test Failed" << std::endl; test_result = false; --passed; }
    if (!Insert()) { test_results_buffer << std::endl << "Insert Test Failed" << std::endl; test_result = false; --passed; }
    if (!EmplaceBack()) { test_results_buffer << std::endl << "EmplaceBack Test Failed" << std::endl; test_result = false; --passed; }
    if (!EmplaceFront()) { test_results_buffer << std::endl << "EmplaceFront Test Failed" << std::endl; test_result = false; --passed; }
    if (!Emplace()) { test_results_buffer << std::endl << "Emplace Test Failed" << std::endl; test_result = false; --passed; }
    if (!PopBack()) { test_results_buffer << std::endl << "PopBack Test Failed" << std::endl; test_result = false; --passed; }
    if (!PopFront()) { test_results_buffer << std::endl << "PopFront Test Failed" << std::endl; test_result = false; --passed; }
    if (!Erase()) { test_results_buffer << std::endl << "Erase Test Failed" << std::endl; test_result = false; --passed; }
    if (!Clear()) { test_results_buffer << std::endl << "Clear Test Failed" << std::endl; test_result = false; --passed; }
    if (!Append()) { test_results_buffer << std::endl << "Append Test Failed" << std::endl; test_result = false; --passed; }
    if (!Reserve()) { test_results_buffer << std::endl << "Reserve Test Failed" << std::endl; test_result = false; --passed; }
    if (!Resize()) { test_results_buffer << std::endl << "Resize Test Failed" << std::endl; test_result = false; --passed; }
    if (!Shrink()) { test_results_buffer << std::endl << "Shrink Test Failed" << std::endl; test_result = false; --passed; }

    s_FileBuffer << "Total test passed: " << passed << std::endl << std::endl;
    if (test_result) { s_FileBuffer << "No errors found" << std::endl; }
    else { s_FileBuffer << test_results_buffer.str(); }
    s_FileBuffer << std::endl << std::endl;
    Serializer::SerializeResults("List_Results.txt", s_FileBuffer);

    return test_result;
}

bool ListTest::Iterators()
{
    //operator++()
    //operator++(int)
    //operator+=(size_t)
    //operator+=(int)
    //Advance(size_t)
    //operator--()
    //operator--(int)
    //operator-=(size_t)
    //operator-=(int)
    //Retreat(size_t)
    //operator+(size_t)
    //operator+(int)
    //Next(size_t) const
    //operator-(size_t)
    //operator-(int)
    //Prev(size_t) const
    //operator[](size_t) const
    //operator[](int) const
    //At(size_t) const
    //At(int) const
    //operator*() const
    //Data() const
    //operator->() const
    //Get() const
    //Distance(const Iterator&) const
    //operator==(const Iterator&) const
    //operator==(const T*) const
    //operator!=(const Iterator&) const
    //operator!=(const T*) const
    //operator<(const Iterator&) const
    //operator<=(const Iterator&) const
    //operator>(const Iterator&) const
    //operator>=(const Iterator&) const
    //operator bool() const
    //IsValid() const
    //Iterator(T*)
    //Iterator(const Iterator&)
    //Iterator(Iterator&&)
    //operator=(const Iterator&)
    //operator=(Iterator&&)
    //operator=(const T*)

    {
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::iterator it(list.begin());

            for (size_t i = 0; i < list.Size(); ++i)
            {
                if (*it != TestStruct((float)i)) { return false; }
                ++it;
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::iterator it(list.begin());

            for (size_t i = 0; i < list.Size(); ++i)
            {
                if (*it++ != TestStruct((float)i)) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 0; i < list.Size(); ++i)
            {
                List<TestStruct>::iterator it(list.begin());
                it += i;
                if (*it != TestStruct((float)i)) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 1; i <= (int)list.Size(); ++i)
            {
                List<TestStruct>::iterator it(list.end());
                it += -i;
                if (*it != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::iterator it;

            for (size_t i = 0; i < list.Size(); ++i)
            {
                it = list.begin();
                it.Advance(i);
                if (*it != TestStruct((float)i)) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::iterator it(list.end());

            for (size_t i = 0; i < list.Size(); ++i)
            {
                if (*--it != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::iterator it(list.end());

            --it;
            for (size_t i = 0; i < list.Size(); ++i)
            {
                if (*it-- != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 1; i <= list.Size(); ++i)
            {
                List<TestStruct>::iterator it(list.end());
                it -= i;
                if (*it != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 0; i < (int)list.Size(); ++i)
            {
                List<TestStruct>::iterator it(list.begin());
                it -= -i;
                if (*it != TestStruct((float)i)) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::iterator it;

            for (size_t i = 1; i <= list.Size(); ++i)
            {
                it = list.end();
                it.Retreat(i);
                if (*it != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 0; i < list.Size(); ++i)
            {
                List<TestStruct>::iterator it(list.begin());
                if (*(it + i) != TestStruct((float)i)) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 1; i <= (int)list.Size(); ++i)
            {
                List<TestStruct>::iterator it(list.end());
                if (*(it + -i) != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::iterator it;

            for (size_t i = 0; i < list.Size(); ++i)
            {
                it = list.begin();
                if (*it.Next(i) != TestStruct((float)i)) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 1; i <= list.Size(); ++i)
            {
                List<TestStruct>::iterator it(list.end());
                if (*(it - i) != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 0; i < (int)list.Size(); ++i)
            {
                List<TestStruct>::iterator it(list.begin());
                if (*(it - -i) != TestStruct((float)i)) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::iterator it;

            for (size_t i = 1; i <= list.Size(); ++i)
            {
                it = list.end();
                if (*it.Prev(i) != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::iterator it(list.begin());

            for (size_t i = 0; i < list.Size(); ++i)
            {
                if (it[i] != TestStruct((float)i)) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::iterator it(list.end());

            for (int i = 1; i <= (int)list.Size(); ++i)
            {
                if (it[-i] != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::iterator it(list.begin());

            for (size_t i = 0; i < list.Size(); ++i)
            {
                if (it.At(i) != TestStruct((float)i)) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::iterator it(list.end());

            for (int i = 1; i <= (int)list.Size(); ++i)
            {
                if (it.At(-i) != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::iterator it(list.begin());

            for (size_t i = 0; i < list.Size(); ++i, ++it)
            {
                auto& aux = *it;
                if (aux != TestStruct((float)i)) { return false; }
                aux.x += 5.0f;
            }
            it = list.begin();
            for (size_t i = 0; i < list.Size(); ++i, ++it)
            {
                if ((*it).x != (float)(5 + i)) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::iterator it(list.begin());

            for (size_t i = 0; i < list.Size(); ++i, ++it)
            {
                auto& aux = it.Data();
                if (aux != TestStruct((float)i)) { return false; }
                aux.x += 5.0f;
            }
            it = list.begin();
            for (size_t i = 0; i < list.Size(); ++i, ++it)
            {
                if ((*it).x != (float)(5 + i)) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::iterator it(list.begin());

            for (size_t i = 0; i < list.Size(); ++i, ++it)
            {
                float& aux = it->x;
                if (aux != (float)i) { return false; }
                aux += 5.0f;
            }
            it = list.begin();
            for (size_t i = 0; i < list.Size(); ++i, ++it)
            {
                if ((*it).x != (float)(5 + i)) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::iterator it(list.begin());

            for (size_t i = 0; i < list.Size(); ++i, ++it)
            {
                auto& aux = it.Get()->x;
                if (aux != (float)i) { return false; }
                aux += 5.0f;
            }
            it = list.begin();
            for (size_t i = 0; i < list.Size(); ++i, ++it)
            {
                if ((*it).x != (float)(5 + i)) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::iterator it(list.begin());

            for (size_t i = 0; i < list.Size(); ++i, ++it)
            {
                auto& aux = *it;
                if (aux != TestStruct((float)i)) { return false; }
                aux.x += 5.0f;
            }
            it = list.begin();
            for (size_t i = 0; i < list.Size(); ++i, ++it)
            {
                if ((*it).x != (float)(5 + i)) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::iterator it(list.begin());

            for (size_t i = 0; i < list.Size(); ++i, ++it)
            {
                auto& aux = it.Data();
                if (aux != TestStruct((float)i)) { return false; }
                aux.x += 5.0f;
            }
            it = list.begin();
            for (size_t i = 0; i < list.Size(); ++i, ++it)
            {
                if ((*it).x != (float)(5 + i)) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::iterator it(list.begin());

            for (size_t i = 0; i < list.Size(); ++i, ++it)
            {
                auto aux = &it;
                if (**aux != TestStruct((float)i)) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::iterator it(list.begin());

            for (size_t i = 0; i < list.Size(); ++i, ++it)
            {
                List<TestStruct>::iterator aux(list.begin());
                if (it.Distance(aux) != i) { return false; }
                if (aux.Distance(it) != i) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::iterator it;
            if (it) { return false; }
            if (it.IsValid()) { return false; }
            it = list.end();
            if (it == list.begin()) { return false; }
            if (it == &list[0]) { return false; }
            it = list.begin();
            if (it != list.begin()) { return false; }
            if (it != &list[0]) { return false; }
            if (list.end() < list.begin()) { return false; }
            if (list.begin() > list.end()) { return false; }
            if (!(it <= list.begin())) { return false; }
            if (!(it >= list.begin())) { return false; }
        }
    }
    {
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::const_iterator it(list.cbegin());

            for (size_t i = 0; i < list.Size(); ++i)
            {
                if (*it != TestStruct((float)i)) { return false; }
                ++it;
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::const_iterator it(list.cbegin());

            for (size_t i = 0; i < list.Size(); ++i)
            {
                if (*it++ != TestStruct((float)i)) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 0; i < list.Size(); ++i)
            {
                List<TestStruct>::const_iterator it(list.cbegin());
                it += i;
                if (*it != TestStruct((float)i)) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 1; i <= (int)list.Size(); ++i)
            {
                List<TestStruct>::const_iterator it(list.cend());
                it += -i;
                if (*it != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::const_iterator it;

            for (size_t i = 0; i < list.Size(); ++i)
            {
                it = list.cbegin();
                it.Advance(i);
                if (*it != TestStruct((float)i)) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::const_iterator it(list.cend());
            --it;

            for (size_t i = 0; i < list.Size(); ++i)
            {
                if (*it-- != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::const_iterator it(list.cend());

            for (size_t i = 0; i < list.Size(); ++i)
            {
                if (*--it != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 1; i <= list.Size(); ++i)
            {
                List<TestStruct>::const_iterator it(list.cend());
                it -= i;
                if (*it != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 0; i < (int)list.Size(); ++i)
            {
                List<TestStruct>::const_iterator it(list.cbegin());
                it -= -i;
                if (*it != TestStruct((float)i)) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::const_iterator it;

            for (size_t i = 1; i <= list.Size(); ++i)
            {
                it = list.cend();
                it.Retreat(i);
                if (*it != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 0; i < list.Size(); ++i)
            {
                List<TestStruct>::const_iterator it(list.cbegin());
                if (*(it + i) != TestStruct((float)i)) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 1; i <= (int)list.Size(); ++i)
            {
                List<TestStruct>::const_iterator it(list.cend());
                if (*(it + -i) != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::const_iterator it;

            for (size_t i = 0; i < list.Size(); ++i)
            {
                it = list.cbegin();
                if (*it.Next(i) != TestStruct((float)i)) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 1; i <= list.Size(); ++i)
            {
                List<TestStruct>::const_iterator it(list.cend());
                if (*(it - i) != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 0; i < (int)list.Size(); ++i)
            {
                List<TestStruct>::const_iterator it(list.cbegin());
                if (*(it - -i) != TestStruct((float)i)) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::const_iterator it;

            for (size_t i = 1; i <= list.Size(); ++i)
            {
                it = list.cend();
                if (*it.Prev(i) != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::const_iterator it(list.cbegin());

            for (size_t i = 0; i < list.Size(); ++i)
            {
                if (it[i] != TestStruct((float)i)) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::const_iterator it(list.cend());

            for (int i = 1; i <= (int)list.Size(); ++i)
            {
                if (it[-i] != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::const_iterator it(list.cbegin());

            for (size_t i = 0; i < list.Size(); ++i)
            {
                if (it.At(i) != TestStruct((float)i)) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::const_iterator it(list.cend());

            for (int i = 1; i <= (int)list.Size(); ++i)
            {
                if (it.At(-i) != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::const_iterator it(list.cbegin());

            for (size_t i = 0; i < list.Size(); ++i, ++it)
            {
                const auto& aux = *it;
                if (aux != TestStruct((float)i)) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::const_iterator it(list.cbegin());

            for (size_t i = 0; i < list.Size(); ++i, ++it)
            {
                const auto& aux = it.Data();
                if (aux != TestStruct((float)i)) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::const_iterator it(list.cbegin());

            for (size_t i = 0; i < list.Size(); ++i, ++it)
            {
                const float& aux = it->x;
                if (aux != (float)i) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::const_iterator it(list.cbegin());

            for (size_t i = 0; i < list.Size(); ++i, ++it)
            {
                const auto& aux = it.Get()->x;
                if (aux != (float)i) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::const_iterator it(list.cbegin());

            for (size_t i = 0; i < list.Size(); ++i, ++it)
            {
                const auto& aux = *it;
                if (aux != TestStruct((float)i)) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::const_iterator it(list.cbegin());

            for (size_t i = 0; i < list.Size(); ++i, ++it)
            {
                auto& aux = it.Data();
                if (aux != TestStruct((float)i)) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::const_iterator it(list.cbegin());

            for (size_t i = 0; i < list.Size(); ++i, ++it)
            {
                const auto aux = &it;
                if (**aux != TestStruct((float)i)) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::const_iterator it(list.cbegin());

            for (size_t i = 0; i < list.Size(); ++i, ++it)
            {
                List<TestStruct>::const_iterator aux(list.cbegin());
                if (it.Distance(aux) != i) { return false; }
                if (aux.Distance(it) != i) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::const_iterator it;
            if (it) { return false; }
            if (it.IsValid()) { return false; }
            it = list.cend();
            if (it == list.cbegin()) { return false; }
            if (it == &list[0]) { return false; }
            it = list.cbegin();
            if (it != list.cbegin()) { return false; }
            if (it != &list[0]) { return false; }
            if (list.cend() < list.cbegin()) { return false; }
            if (list.cbegin() > list.cend()) { return false; }
            if (!(it <= list.cbegin())) { return false; }
            if (!(it >= list.cbegin())) { return false; }
        }
    }
    {
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::reverse_iterator it(list.rbegin());

            for (size_t i = 0; i < list.Size(); ++i)
            {
                if (*it != TestStruct((float)(4 - i))) { return false; }
                ++it;
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::reverse_iterator it(list.rbegin());

            for (size_t i = 0; i < list.Size(); ++i)
            {
                if (*it++ != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 0; i < list.Size(); ++i)
            {
                List<TestStruct>::reverse_iterator it(list.rbegin());
                it += i;
                if (*it != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 1; i <= (int)list.Size(); ++i)
            {
                List<TestStruct>::reverse_iterator it(list.rend());
                it += -i;
                if (*it != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::reverse_iterator it;

            for (size_t i = 0; i < list.Size(); ++i)
            {
                it = list.rbegin();
                it.Advance(i);
                if (*it != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::reverse_iterator it(list.rend());

            for (size_t i = 0; i < list.Size(); ++i)
            {
                if (*--it != TestStruct((float)i)) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::reverse_iterator it(list.rend());
            --it;

            for (size_t i = 0; i < list.Size(); ++i)
            {
                if (*it-- != TestStruct((float)i)) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 1; i <= list.Size(); ++i)
            {
                List<TestStruct>::reverse_iterator it(list.rend());
                it -= i;
                if (*it != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 0; i < (int)list.Size(); ++i)
            {
                List<TestStruct>::reverse_iterator it(list.rbegin());
                it -= -i;
                if (*it != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::reverse_iterator it;

            for (size_t i = 1; i <= list.Size(); ++i)
            {
                it = list.rend();
                it.Retreat(i);
                if (*it != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 0; i < list.Size(); ++i)
            {
                List<TestStruct>::reverse_iterator it(list.rbegin());
                auto a = *(it + i);
                if (a != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 1; i <= (int)list.Size(); ++i)
            {
                List<TestStruct>::reverse_iterator it(list.rend());
                if (*(it + -i) != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::reverse_iterator it;

            for (size_t i = 0; i < list.Size(); ++i)
            {
                it = list.rbegin();
                if (*it.Next(i) != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 1; i <= list.Size(); ++i)
            {
                List<TestStruct>::reverse_iterator it(list.rend());
                if (*(it - i) != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 0; i < (int)list.Size(); ++i)
            {
                List<TestStruct>::reverse_iterator it(list.rbegin());
                if (*(it - -i) != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::reverse_iterator it;

            for (size_t i = 1; i <= list.Size(); ++i)
            {
                it = list.rend();
                if (*it.Prev(i) != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::reverse_iterator it(list.rbegin());

            for (size_t i = 0; i < list.Size(); ++i)
            {
                if (it[i] != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::reverse_iterator it(list.rend());

            for (int i = 1; i <= (int)list.Size(); ++i)
            {
                if (it[-i] != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::reverse_iterator it(list.rbegin());

            for (size_t i = 0; i < list.Size(); ++i)
            {
                if (it.At(i) != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::reverse_iterator it(list.rend());

            for (int i = 1; i <= (int)list.Size(); ++i)
            {
                if (it.At(-i) != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::reverse_iterator it(list.rbegin());

            for (size_t i = 0; i < list.Size(); ++i, ++it)
            {
                auto& aux = *it;
                if (aux != TestStruct((float)(4 - i))) { return false; }
                aux.x += 5.0f;
            }
            it = list.rbegin();
            for (size_t i = 0; i < list.Size(); ++i, ++it)
            {
                if ((*it).x != (float)(9 - i)) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::reverse_iterator it(list.rbegin());

            for (size_t i = 0; i < list.Size(); ++i, ++it)
            {
                auto& aux = it.Data();
                if (aux != TestStruct((float)(4 - i))) { return false; }
                aux.x += 5.0f;
            }
            it = list.rbegin();
            for (size_t i = 0; i < list.Size(); ++i, ++it)
            {
                if ((*it).x != (float)(9 - i)) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::reverse_iterator it(list.rbegin());

            for (size_t i = 0; i < list.Size(); ++i, ++it)
            {
                float& aux = it->x;
                if (aux != (float)(4 - i)) { return false; }
                aux += 5.0f;
            }
            it = list.rbegin();
            for (size_t i = 0; i < list.Size(); ++i, ++it)
            {
                if ((*it).x != (float)(9 - i)) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::reverse_iterator it(list.rbegin());

            for (size_t i = 0; i < list.Size(); ++i, ++it)
            {
                auto& aux = it.Get()->x;
                if (aux != (float)(4 - i)) { return false; }
                aux += 5.0f;
            }
            it = list.rbegin();
            for (size_t i = 0; i < list.Size(); ++i, ++it)
            {
                if ((*it).x != (float)(9 - i)) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::reverse_iterator it(list.rbegin());

            for (size_t i = 0; i < list.Size(); ++i, ++it)
            {
                auto& aux = *it;
                if (aux != TestStruct((float)(4 - i))) { return false; }
                aux.x += 5.0f;
            }
            it = list.rbegin();
            for (size_t i = 0; i < list.Size(); ++i, ++it)
            {
                if ((*it).x != (float)(9 - i)) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::reverse_iterator it(list.rbegin());

            for (size_t i = 0; i < list.Size(); ++i, ++it)
            {
                auto& aux = it.Data();
                if (aux != TestStruct((float)(4 - i))) { return false; }
                aux.x += 5.0f;
            }
            it = list.rbegin();
            for (size_t i = 0; i < list.Size(); ++i, ++it)
            {
                if ((*it).x != (float)(9 - i)) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::reverse_iterator it(list.rbegin());

            for (size_t i = 0; i < list.Size(); ++i, ++it)
            {
                auto aux = &it;
                if (**aux != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::reverse_iterator it(list.rbegin());

            for (size_t i = 0; i < list.Size(); ++i, ++it)
            {
                List<TestStruct>::reverse_iterator aux(list.rbegin());
                if (it.Distance(aux) != i) { return false; }
                if (aux.Distance(it) != i) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::reverse_iterator it;
            if (it) { return false; }
            if (it.IsValid()) { return false; }
            it = list.rend();
            if (it == list.rbegin()) { return false; }
            if (it == &list[0]) { return false; }
            it = list.rbegin();
            if (it != list.rbegin()) { return false; }
            if (it != &list[4]) { return false; }
            if (list.rend() < list.rbegin()) { return false; }
            if (list.rbegin() > list.rend()) { return false; }
            if (!(it <= list.rbegin())) { return false; }
            if (!(it >= list.rbegin())) { return false; }
        }
    }
    {
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::const_reverse_iterator it(list.crbegin());

            for (size_t i = 0; i < list.Size(); ++i)
            {
                if (*it != TestStruct((float)(4 - i))) { return false; }
                ++it;
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::const_reverse_iterator it(list.crbegin());

            for (size_t i = 0; i < list.Size(); ++i)
            {
                if (*it++ != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 0; i < list.Size(); ++i)
            {
                List<TestStruct>::const_reverse_iterator it(list.crbegin());
                it += i;
                if (*it != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 1; i <= (int)list.Size(); ++i)
            {
                List<TestStruct>::const_reverse_iterator it(list.crend());
                it += -i;
                if (*it != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::const_reverse_iterator it;

            for (size_t i = 0; i < list.Size(); ++i)
            {
                it = list.crbegin();
                it.Advance(i);
                if (*it != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::const_reverse_iterator it(list.crend());

            for (size_t i = 0; i < list.Size(); ++i)
            {
                if (*--it != TestStruct((float)i)) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::const_reverse_iterator it(list.crend());
            --it;

            for (size_t i = 0; i < list.Size(); ++i)
            {
                if (*it-- != TestStruct((float)i)) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 1; i <= list.Size(); ++i)
            {
                List<TestStruct>::const_reverse_iterator it(list.crend());
                it -= i;
                if (*it != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 0; i < (int)list.Size(); ++i)
            {
                List<TestStruct>::const_reverse_iterator it(list.crbegin());
                it -= -i;
                if (*it != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::const_reverse_iterator it;

            for (size_t i = 1; i <= list.Size(); ++i)
            {
                it = list.crend();
                it.Retreat(i);
                if (*it != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 0; i < list.Size(); ++i)
            {
                List<TestStruct>::const_reverse_iterator it(list.crbegin());
                const auto a = *(it + i);
                if (a != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 1; i <= (int)list.Size(); ++i)
            {
                List<TestStruct>::const_reverse_iterator it(list.crend());
                if (*(it + -i) != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::const_reverse_iterator it;

            for (size_t i = 0; i < list.Size(); ++i)
            {
                it = list.crbegin();
                if (*it.Next(i) != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 1; i <= list.Size(); ++i)
            {
                List<TestStruct>::const_reverse_iterator it(list.crend());
                if (*(it - i) != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 0; i < (int)list.Size(); ++i)
            {
                List<TestStruct>::const_reverse_iterator it(list.crbegin());
                if (*(it - -i) != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::const_reverse_iterator it;

            for (size_t i = 1; i <= list.Size(); ++i)
            {
                it = list.crend();
                if (*it.Prev(i) != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::const_reverse_iterator it(list.crbegin());

            for (size_t i = 0; i < list.Size(); ++i)
            {
                if (it[i] != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::const_reverse_iterator it(list.crend());

            for (int i = 1; i <= (int)list.Size(); ++i)
            {
                if (it[-i] != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::const_reverse_iterator it(list.crbegin());

            for (size_t i = 0; i < list.Size(); ++i)
            {
                if (it.At(i) != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::const_reverse_iterator it(list.crend());

            for (int i = 1; i <= (int)list.Size(); ++i)
            {
                if (it.At(-i) != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::const_reverse_iterator it(list.crbegin());

            for (size_t i = 0; i < list.Size(); ++i, ++it)
            {
                const auto& aux = *it;
                if (aux != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::const_reverse_iterator it(list.crbegin());

            for (size_t i = 0; i < list.Size(); ++i, ++it)
            {
                const auto& aux = it.Data();
                if (aux != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::const_reverse_iterator it(list.crbegin());

            for (size_t i = 0; i < list.Size(); ++i, ++it)
            {
                const float& aux = it->x;
                if (aux != (float)(4 - i)) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::const_reverse_iterator it(list.crbegin());

            for (size_t i = 0; i < list.Size(); ++i, ++it)
            {
                const auto& aux = it.Get()->x;
                if (aux != (float)(4 - i)) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::const_reverse_iterator it(list.crbegin());

            for (size_t i = 0; i < list.Size(); ++i, ++it)
            {
                const auto& aux = *it;
                if (aux != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::const_reverse_iterator it(list.crbegin());

            for (size_t i = 0; i < list.Size(); ++i, ++it)
            {
                const auto& aux = it.Data();
                if (aux != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::const_reverse_iterator it(list.crbegin());

            for (size_t i = 0; i < list.Size(); ++i, ++it)
            {
                auto aux = &it;
                if (**aux != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::const_reverse_iterator it(list.crbegin());

            for (size_t i = 0; i < list.Size(); ++i, ++it)
            {
                List<TestStruct>::const_reverse_iterator aux(list.crbegin());
                if (it.Distance(aux) != i) { return false; }
                if (aux.Distance(it) != i) { return false; }
            }
        }
        {
            List<TestStruct> list{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            List<TestStruct>::const_reverse_iterator it;
            if (it) { return false; }
            if (it.IsValid()) { return false; }
            it = list.crend();
            if (it == list.crbegin()) { return false; }
            if (it == &list[0]) { return false; }
            it = list.crbegin();
            if (it != list.crbegin()) { return false; }
            if (it != &list[4]) { return false; }
            if (list.crend() < list.crbegin()) { return false; }
            if (list.crbegin() > list.crend()) { return false; }
            if (!(it <= list.crbegin())) { return false; }
            if (!(it >= list.crbegin())) { return false; }
        }
    }

    return true;
}

bool ListTest::Copy()
{
    //list(const list& other)
    //operator=(const list& other)

    {
        List<size_t> list0{ };
        List<size_t> list1(list0);

        if (list1.Capacity() != 0) { return false; }
        if (list1.Data()) { return false; }

        list0 = list1;

        if (list0.Capacity() != 0) { return false; }
        if (list0.Data()) { return false; }
    }
    {
        List<size_t> list0{ 0, 1, 2, 3, 4 };
        List<size_t> list1(list0);

        for (size_t i = 0; i < list1.Size(); ++i)
        {
            if (list1[i] != list0[i]) { return false; }
        }

        List<size_t> list2{ 5, 6, 7, 8, 9 };
        list1 = list2;
        for (size_t i = 0; i < list1.Size(); ++i)
        {
            if (list1[i] != list2[i]) { return false; }
        }
    }
    {
        List<std::string> list0{ "0", "1", "2", "3", "4" };
        List<std::string> list1(list0);

        for (size_t i = 0; i < list1.Size(); ++i)
        {
            if (list1[i] != list0[i]) { return false; }
        }

        List<std::string> list2{ "5", "6", "7", "8", "9" };
        list1 = list2;

        for (size_t i = 0; i < list1.Size(); ++i)
        {
            if (list1[i] != list2[i]) { return false; }
        }
    }
    {
        List<TestStruct> list0{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
        List<TestStruct> list1(list0);

        for (size_t i = 0; i < list1.Size(); ++i)
        {
            if (list1[i] != list0[i]) { return false; }
        }

        List<TestStruct> list2{ TestStruct(5.0f), TestStruct(6.0f), TestStruct(7.0f), TestStruct(8.0f), TestStruct(9.0f) };
        list1 = list2;

        for (size_t i = 0; i < list1.Size(); ++i)
        {
            if (list1[i] != list2[i]) { return false; }
        }
    }

    return true;
}

bool ListTest::Move()
{
    //list(list&& other)
    //operator=(list&& other)

    {
        List<size_t> list0{ };
        List<size_t> list1(std::move(list0));

        if (list1.Capacity() != 0) { return false; }
        if (list1.Data()) { return false; }

        list0 = std::move(list1);

        if (list0.Capacity() != 0) { return false; }
        if (list0.Data()) { return false; }
    }
    
    {
        List<size_t> list0{ 0, 1, 2, 3, 4 };
        List<size_t> list1(std::move(list0));

        for (size_t i = 0; i < list1.Size(); ++i)
        {
            try
            {
                if (list1.At(i) != i) { return false; }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
        List<size_t> list2{ 5, 6, 7, 8, 9 };
        list1 = std::move(list2);
        for (size_t i = 0; i < list1.Size(); ++i)
        {
            try
            {
                if (list1.At(i) != (5 + i)) { return false; }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
    }
    {
        List<std::string> list0{ "0", "1", "2", "3", "4" };
        List<std::string> list1(std::move(list0));

        for (size_t i = 0; i < list1.Size(); ++i)
        {
            try
            {
                if (list1.At(i) != std::to_string(i)) { return false; }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
        }

        List<std::string> list2{ "5", "6", "7", "8", "9" };
        list1 = std::move(list2);

        for (size_t i = 0; i < list1.Size(); ++i)
        {
            try
            {
                if (list1.At(i) != std::to_string(5 + i)) { return false; }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
    }
    {
        List<TestStruct> list0{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
        List<TestStruct> list1(std::move(list0));

        for (size_t i = 0; i < list1.Size(); ++i)
        {
            try
            {
                if (list1.At(i) != TestStruct((float)i)) { return false; }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
        }

        List<TestStruct> list2{ TestStruct(5.0f), TestStruct(6.0f), TestStruct(7.0f), TestStruct(8.0f), TestStruct(9.0f) };
        list1 = std::move(list2);

        for (size_t i = 0; i < list1.Size(); ++i)
        {
            try
            {
                if (list1.At(i) != TestStruct((float)(5 + i))) { return false; }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
    }

    return true;
}

bool ListTest::Swap()
{
    //Swap(list& other)

    {
        List<size_t> list0;
        List<size_t> list1;

        for (size_t i = 0; i < 10; ++i)
        {
            list0.PushBack(i);
            list1.PushBack(9 - i);
        }

        list0.Swap(list0);
        list0.Swap(list1);

        for (size_t i = 0; i < 10; ++i)
        {
            if (list0[i] != (9 - i)) { return false; }
            if (list1[i] != i) { return false; }
        }
    }
    {
        List<std::string> list0;
        List<std::string> list1;

        for (size_t i = 0; i < 10; ++i)
        {
            list0.PushBack(std::to_string(i));
            list1.PushBack(std::to_string(9 - i));
        }

        list0.Swap(list0);
        list0.Swap(list1);

        for (size_t i = 0; i < 10; ++i)
        {
            if (list0[i] != std::to_string(9 - i)) { return false; }
            if (list1[i] != std::to_string(i)) { return false; }
        }
    }
    {
        List<TestStruct> list0;
        List<TestStruct> list1;

        for (size_t i = 0; i < 10; ++i)
        {
            list0.PushBack(TestStruct((float)i));
            list1.PushBack(TestStruct((float)(9 - i)));
        }

        list0.Swap(list0);
        list0.Swap(list1);

        for (size_t i = 0; i < 10; ++i)
        {
            if (list0[i] != TestStruct((float)(9 - i))) { return false; }
            if (list1[i] != TestStruct((float)i)) { return false; }
        }
    }

    return true;
}

bool ListTest::PushBack()
{
    //void PushBack(const T& element)
    //void PushBack(T&& element)

    {
        List<size_t> list;
        for (size_t i = 0; i < 10; ++i)
        {
            size_t aux(i);
            list.PushBack(aux);
        }
        for (size_t i = 0; i < list.Size(); ++i)
        {
            try
            {
                if (list.At(i) != i) { return false; }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
        for (size_t i = 10; i < 20; ++i)
        {
            size_t aux(i);
            list.PushBack(std::move(aux));
        }
        for (size_t i = 0; i < list.Size(); ++i)
        {
            try
            {
                if (list.At(i) != i) { return false; }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
    }
    {
        List<size_t> list(20);
        for (size_t i = 0; i < 10; ++i)
        {
            size_t aux(i);
            list.PushBack(std::move(aux));
        }
        for (size_t i = 0; i < list.Size(); ++i)
        {
            try
            {
                if (list.At(i) != i) { return false; }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
        for (size_t i = 10; i < 20; ++i)
        {
            size_t aux(i);
            list.PushBack(aux);
        }
        for (size_t i = 0; i < list.Size(); ++i)
        {
            try
            {
                if (list.At(i) != i) { return false; }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
    }
    {
        List<std::string> list;
        for (size_t i = 0; i < 10; ++i)
        {
            std::string aux(std::to_string(i));
            list.PushBack(aux);
        }
        for (size_t i = 0; i < list.Size(); ++i)
        {
            try
            {
                if (list.At(i) != std::to_string(i)) { return false; }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
        for (size_t i = 10; i < 20; ++i)
        {
            std::string aux(std::to_string(i));
            list.PushBack(std::move(aux));
        }
        for (size_t i = 0; i < list.Size(); ++i)
        {
            try
            {
                if (list.At(i) != std::to_string(i)) { return false; }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
    }
    {
        List<std::string> list(20);
        for (size_t i = 0; i < 10; ++i)
        {
            std::string aux(std::to_string(i));
            list.PushBack(std::move(aux));
        }
        for (size_t i = 0; i < list.Size(); ++i)
        {
            try
            {
                if (list.At(i) != std::to_string(i)) { return false; }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
        for (size_t i = 10; i < 20; ++i)
        {
            std::string aux(std::to_string(i));
            list.PushBack(aux);
        }
        for (size_t i = 0; i < list.Size(); ++i)
        {
            try
            {
                if (list.At(i) != std::to_string(i)) { return false; }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
    }
    {
        List<TestStruct> list;
        for (size_t i = 0; i < 10; ++i)
        {
            TestStruct aux((float)i);
            list.PushBack(aux);
        }
        for (size_t i = 0; i < list.Size(); ++i)
        {
            try
            {
                if (list.At(i) != TestStruct((float)i)) { return false; }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
        for (size_t i = 10; i < 20; ++i)
        {
            TestStruct aux((float)i);
            list.PushBack(std::move(aux));
        }
        for (size_t i = 0; i < list.Size(); ++i)
        {
            try
            {
                if (list.At(i) != TestStruct((float)(i))) { return false; }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
    }
    {
        List<TestStruct> list(20);
        for (size_t i = 0; i < 10; ++i)
        {
            TestStruct aux((float)i);
            list.PushBack(std::move(aux));
        }
        for (size_t i = 0; i < list.Size(); ++i)
        {
            try
            {
                if (list.At(i) != TestStruct((float)i)) { return false; }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
        for (size_t i = 10; i < 20; ++i)
        {
            TestStruct aux((float)i);
            list.PushBack(aux);
        }
        for (size_t i = 0; i < list.Size(); ++i)
        {
            try
            {
                if (list.At(i) != TestStruct((float)(i))) { return false; }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
    }

    return true;
}

bool ListTest::PushFront()
{
    //void PushFront(const T& element)
    //void PushFront(T&& element)

    {
        List<size_t> list;
        for (size_t i = 0; i < 10; ++i)
        {
            size_t aux(19 - i);
            list.PushFront(aux);
        }
        for (size_t i = 0; i < list.Size(); ++i)
        {
            try
            {
                if (list.At(i) != 10 + i) { return false; }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
        for (size_t i = 0; i < 10; ++i)
        {
            size_t aux(9 - i);
            list.PushFront(std::move(aux));
        }
        for (size_t i = 0; i < list.Size(); ++i)
        {
            try
            {
                if (list.At(i) != i) { return false; }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
    }
    {
        List<size_t> list(20);
        for (size_t i = 0; i < 10; ++i)
        {
            size_t aux(19 - i);
            list.PushFront(std::move(aux));
        }
        for (size_t i = 0; i < list.Size(); ++i)
        {
            try
            {
                if (list.At(i) != 10 + i) { return false; }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
        for (size_t i = 0; i < 10; ++i)
        {
            size_t aux(9 - i);
            list.PushFront(aux);
        }
        for (size_t i = 0; i < list.Size(); ++i)
        {
            try
            {
                if (list.At(i) != i) { return false; }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
    }
    {
        List<std::string> list;
        for (size_t i = 0; i < 10; ++i)
        {
            std::string aux(std::to_string(19 - i));
            list.PushFront(aux);
        }
        for (size_t i = 0; i < list.Size(); ++i)
        {
            try
            {
                if (list.At(i) != std::to_string(10 + i)) { return false; }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
        for (size_t i = 0; i < 10; ++i)
        {
            std::string aux(std::to_string(9 - i));
            list.PushFront(std::move(aux));
        }
        for (size_t i = 0; i < list.Size(); ++i)
        {
            try
            {
                if (list.At(i) != std::to_string(i)) { return false; }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
    }
    {
        List<std::string> list(20);
        for (size_t i = 0; i < 10; ++i)
        {
            std::string aux(std::to_string(19 - i));
            list.PushFront(std::move(aux));
        }
        for (size_t i = 0; i < list.Size(); ++i)
        {
            try
            {
                if (list.At(i) != std::to_string(10 + i)) { return false; }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
        for (size_t i = 0; i < 10; ++i)
        {
            std::string aux(std::to_string(9 - i));
            list.PushFront(aux);
        }
        for (size_t i = 0; i < list.Size(); ++i)
        {
            try
            {
                if (list.At(i) != std::to_string(i)) { return false; }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
    }
    {
        List<TestStruct> list;
        for (size_t i = 0; i < 10; ++i)
        {
            TestStruct aux((float)(19 - i));
            list.PushFront(aux);
        }
        for (size_t i = 0; i < list.Size(); ++i)
        {
            try
            {
                if (list.At(i) != TestStruct((float)(10 + i))) { return false; }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
        for (size_t i = 0; i < 10; ++i)
        {
            TestStruct aux((float)(9 - i));
            list.PushFront(std::move(aux));
        }
        for (size_t i = 0; i < list.Size(); ++i)
        {
            try
            {
                if (list.At(i) != TestStruct((float)i)) { return false; }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
    }
    {
        List<TestStruct> list(20);
        for (size_t i = 0; i < 10; ++i)
        {
            TestStruct aux((float)(19 - i));
            list.PushFront(std::move(aux));
        }
        for (size_t i = 0; i < list.Size(); ++i)
        {
            try
            {
                if (list.At(i) != TestStruct((float)(10 + i))) { return false; }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
        for (size_t i = 0; i < 10; ++i)
        {
            TestStruct aux((float)(9 - i));
            list.PushFront(aux);
        }
        for (size_t i = 0; i < list.Size(); ++i)
        {
            try
            {
                if (list.At(i) != TestStruct((float)i)) { return false; }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
    }

    return true;
}

bool ListTest::Insert()
{
    //iterator Insert(size_t, const T&)
    //iterator Insert(iterator, const T&)
    //iterator Insert(reverse_iterator, const T&)
    //iterator Insert(size_t, T&&)
    //iterator Insert(iterator, T&&)
    //iterator Insert(reverse_iterator, T&&)

    {
        {
            List<size_t> list;
            for (size_t i = 0; i < 10; ++i)
            {
                size_t aux = i;
                list.Insert(1, aux);
            }
            if (list.Front() != 0) { return false; }
            for (size_t i = 1; i < list.Size(); ++i)
            {
                if (list[i] != list.Size() - i) { return false; }
            }
        }
        {
            List<size_t> list;
            for (size_t i = 0; i < 10; ++i)
            {
                size_t aux = i;
                list.Insert(1, std::move(aux));
            }

            if (list.Front() != 0) { return false; }
            for (size_t i = 1; i < list.Size(); ++i)
            {
                if (list[i] != list.Size() - i) { return false; }
            }
        }
        {
            List<size_t> list;
            list.Insert(list.end(), 0);
            list.Insert(list.end(), 1);
            List<size_t>::iterator it = list.begin();
            ++it;
            for (size_t i = 2; i < 10; ++i)
            {
                size_t aux = i;
                it = list.Insert(it, aux);
            }
            if (list.Front() != 0) { return false; }
            for (size_t i = 1; i < list.Size(); ++i)
            {
                if (list[i] != list.Size() - i) { return false; }
            }
        }
        {
            List<size_t> list;
            list.Insert(list.end(), 0);
            list.Insert(list.end(), 1);
            List<size_t>::iterator it = list.begin();
            ++it;
            for (size_t i = 2; i < 10; ++i)
            {
                size_t aux = i;
                it = list.Insert(it, std::move(aux));
            }

            if (list.Front() != 0) { return false; }
            for (size_t i = 1; i < list.Size(); ++i)
            {
                if (list[i] != list.Size() - i) { return false; }
            }
        }
        {
            List<size_t> list;
            list.Insert(list.end(), 0);
            list.Insert(list.end(), 1);
            List<size_t>::reverse_iterator it = list.rbegin();
            for (size_t i = 2; i < 10; ++i)
            {
                size_t aux = i;
                it = list.Insert(it, aux);
            }
            if (list.Front() != 0) { return false; }
            for (size_t i = 1; i < list.Size(); ++i)
            {
                if (list[i] != list.Size() - i) { return false; }
            }
        }
        {
            List<size_t> list;
            list.Insert(list.end(), 0);
            list.Insert(list.end(), 1);
            List<size_t>::reverse_iterator it = list.rbegin();
            for (size_t i = 2; i < 10; ++i)
            {
                size_t aux = i;
                it = list.Insert(it, std::move(aux));
            }
            if (list.Front() != 0) { return false; }
            for (size_t i = 1; i < list.Size(); ++i)
            {
                if (list[i] != list.Size() - i) { return false; }
            }
        }
    }
    {
        {
            List<std::string> list;
            for (size_t i = 0; i < 10; ++i)
            {
                size_t aux = i;
                list.Insert(1, std::to_string(aux));
            }
            if (list.Front() != "0") { return false; }
            for (size_t i = 1; i < list.Size(); ++i)
            {
                if (list[i] != std::to_string(list.Size() - i)) { return false; }
            }
        }
        {
            List<std::string> list;
            for (size_t i = 0; i < 10; ++i)
            {
                size_t aux = i;
                list.Insert(1, std::move(std::to_string(aux)));
            }

            if (list.Front() != "0") { return false; }
            for (size_t i = 1; i < list.Size(); ++i)
            {
                if (list[i] != std::to_string(list.Size() - i)) { return false; }
            }
        }
        {
            List<std::string> list;
            list.Insert(list.end(), "0");
            list.Insert(list.end(), "1");
            List<std::string>::iterator it = list.begin();
            ++it;
            for (size_t i = 2; i < 10; ++i)
            {
                size_t aux = i;
                it = list.Insert(it, std::to_string(aux));
            }

            if (list.Front() != "0") { return false; }
            for (size_t i = 1; i < list.Size(); ++i)
            {
                if (list[i] != std::to_string(list.Size() - i)) { return false; }
            }
        }
        {
            List<std::string> list;
            list.Insert(list.end(), "0");
            list.Insert(list.end(), "1");
            List<std::string>::iterator it = list.begin();
            ++it;
            for (size_t i = 2; i < 10; ++i)
            {
                size_t aux = i;
                it = list.Insert(it, std::to_string(std::move(aux)));
            }

            if (list.Front() != "0") { return false; }
            for (size_t i = 1; i < list.Size(); ++i)
            {
                if (list[i] != std::to_string(list.Size() - i)) { return false; }
            }
        }
        {
            List<std::string> list;
            list.Insert(list.end(), "0");
            list.Insert(list.end(), "1");
            List<std::string>::reverse_iterator it = list.rbegin();
            for (size_t i = 2; i < 10; ++i)
            {
                size_t aux = i;
                it = list.Insert(it, std::to_string(aux));
            }
            if (list.Front() != "0") { return false; }
            for (size_t i = 1; i < list.Size(); ++i)
            {
                if (list[i] != std::to_string(list.Size() - i)) { return false; }
            }
        }
        {
            List<std::string> list;
            list.Insert(list.end(), "0");
            list.Insert(list.end(), "1");
            List<std::string>::reverse_iterator it = list.rbegin();
            for (size_t i = 2; i < 10; ++i)
            {
                size_t aux = i;
                it = list.Insert(it, std::to_string(std::move(aux)));
            }
            if (list.Front() != "0") { return false; }
            for (size_t i = 1; i < list.Size(); ++i)
            {
                if (list[i] != std::to_string(list.Size() - i)) { return false; }
            }
        }
    }
    {
        {
            List<TestStruct> list;
            for (size_t i = 0; i < 10; ++i)
            {
                size_t aux = i;
                list.Insert(1, TestStruct((float)aux));
            }
            if (list.Front() != 0) { return false; }
            for (size_t i = 1; i < list.Size(); ++i)
            {
                if (list[i] != TestStruct((float)(list.Size() - i))) { return false; }
            }
        }
        {
            List<TestStruct> list;
            for (size_t i = 0; i < 10; ++i)
            {
                size_t aux = i;
                list.Insert(1, std::move(TestStruct((float)aux)));
            }

            if (list.Front() != 0) { return false; }
            for (size_t i = 1; i < list.Size(); ++i)
            {
                if (list[i] != TestStruct((float)(list.Size() - i))) { return false; }
            }
        }
        {
            List<TestStruct> list;
            list.Insert(list.end(), TestStruct(0.0f));
            list.Insert(list.end(), TestStruct(1.0f));
            List<TestStruct>::iterator it = list.begin();
            ++it;
            for (size_t i = 2; i < 10; ++i)
            {
                size_t aux = i;
                it = list.Insert(it, TestStruct((float)aux));
            }

            if (list.Front() != 0) { return false; }
            for (size_t i = 1; i < list.Size(); ++i)
            {
                if (list[i] != TestStruct((float)(list.Size() - i))) { return false; }
            }
        }
        {
            List<TestStruct> list;
            list.Insert(list.end(), TestStruct(0.0f));
            list.Insert(list.end(), TestStruct(1.0f));
            List<TestStruct>::iterator it = list.begin();
            ++it;
            for (size_t i = 2; i < 10; ++i)
            {
                size_t aux = i;
                it = list.Insert(it, std::move(TestStruct((float)aux)));
            }

            if (list.Front() != 0) { return false; }
            for (size_t i = 1; i < list.Size(); ++i)
            {
                if (list[i] != TestStruct((float)(list.Size() - i))) { return false; }
            }
        }
        {
            List<TestStruct> list;
            list.Insert(list.end(), TestStruct(0.0f));
            list.Insert(list.end(), TestStruct(1.0f));
            List<TestStruct>::reverse_iterator it = list.rbegin();
            for (size_t i = 2; i < 10; ++i)
            {
                size_t aux = i;
                it = list.Insert(it, TestStruct((float)aux));
            }
            if (list.Front() != 0) { return false; }
            for (size_t i = 1; i < list.Size(); ++i)
            {
                if (list[i] != TestStruct((float)(list.Size() - i))) { return false; }
            }
        }
        {
            List<TestStruct> list;
            list.Insert(list.end(), TestStruct(0.0f));
            list.Insert(list.end(), TestStruct(1.0f));
            List<TestStruct>::reverse_iterator it = list.rbegin();
            for (size_t i = 2; i < 10; ++i)
            {
                size_t aux = i;
                it = list.Insert(it, std::move(TestStruct((float)aux)));
            }
            if (list.Front() != 0) { return false; }
            for (size_t i = 1; i < list.Size(); ++i)
            {
                if (list[i] != TestStruct((float)(list.Size() - i))) { return false; }
            }
        }
    }

    return true;
}

bool ListTest::EmplaceBack()
{
    //T& EmplaceBack(Args&&... args)

    {
        List<size_t> list(5);
        for (size_t i = 0; i < 10; ++i)
        {
            list.EmplaceBack(i);
        }
        for (size_t i = 0; i < list.Size(); ++i)
        {
            try
            {
                if (list.At(i) != i) { return false; }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
    }
    {
        List<std::string> list(5);
        for (size_t i = 0; i < 10; ++i)
        {
            list.EmplaceBack(std::to_string(i));
        }
        for (size_t i = 0; i < list.Size(); ++i)
        {
            try
            {
                if (list.At(i) != std::to_string(i)) { return false; }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
    }
    {
        List<TestStruct> list(5);
        for (size_t i = 0; i < 10; ++i)
        {
            list.EmplaceBack((float)i);
        }
        for (size_t i = 0; i < list.Size(); ++i)
        {
            try
            {
                if (list.At(i) != TestStruct((float)i)) { return false; }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
    }

    return true;
}

bool ListTest::EmplaceFront()
{
    //T& EmplaceFront(Args&&... args)

    {
        List<size_t> list(5);
        for (size_t i = 0; i < 10; ++i)
        {
            list.EmplaceFront(9 - i);
        }
        for (size_t i = 0; i < list.Size(); ++i)
        {
            try
            {
                if (list.At(i) != i) { return false; }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
    }
    {
        List<std::string> list(5);
        for (size_t i = 0; i < 10; ++i)
        {
            list.EmplaceFront(std::to_string(9 - i));
        }
        for (size_t i = 0; i < list.Size(); ++i)
        {
            try
            {
                if (list.At(i) != std::to_string(i)) { return false; }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
    }
    {
        List<TestStruct> list(5);
        for (size_t i = 0; i < 10; ++i)
        {
            list.EmplaceFront((float)(9 - i));
        }
        for (size_t i = 0; i < list.Size(); ++i)
        {
            try
            {
                if (list.At(i) != TestStruct((float)(i))) { return false; }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
    }

    return true;
}

bool ListTest::Emplace()
{
    //T& Emplace(size_t, Args&&...)
    //T& Emplace(iterator, Args&&...)
    //T& Emplace(reverse_iterator, Args&&...)

    {
        {
            List<size_t> list(5);
            for (size_t i = 0; i < 10; ++i)
            {
                list.Emplace(1, i);
            }
            try
            {
                if (list.Front() != 0) { return false; }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
            for (size_t i = 1; i < list.Size(); ++i)
            {
                try
                {
                    if (list.At(i) != 10 - i) { return false; }
                }
                catch (const std::exception& e)
                {
                    std::cout << e.what() << std::endl;
                }
            }
        }
        {
            List<size_t> list(5);
            for (size_t i = 0; i < 10; ++i)
            {
                switch (i)
                {
                case 0:
                    list.Emplace(list.begin(), i);
                    break;
                case 1:
                    list.Emplace(list.end(), i);
                    break;
                default:
                    List<size_t>::iterator it(list.begin());
                    ++it;
                    list.Emplace(it, i);
                    break;
                }
            }
            try
            {
                if (list.Front() != 0) { return false; }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
            for (size_t i = 1; i < list.Size(); ++i)
            {
                try
                {
                    if (list.At(i) != 10 - i) { return false; }
                }
                catch (const std::exception& e)
                {
                    std::cout << e.what() << std::endl;
                }
            }
        }
        {
            List<size_t> list(5);
            for (size_t i = 0; i < 10; ++i)
            {
                switch (i)
                {
                case 0:
                    list.Emplace(list.rend(), i);
                    break;
                case 1:
                    list.Emplace(list.rbegin(), i);
                    break;
                default:
                    List<size_t>::reverse_iterator it(list.rend());
                    it -= 2;
                    list.Emplace(it, i);
                    break;
                }
            }
            try
            {
                if (list.Front() != 0) { return false; }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
            for (size_t i = 1; i < list.Size(); ++i)
            {
                try
                {
                    if (list.At(i) != 10 - i) { return false; }
                }
                catch (const std::exception& e)
                {
                    std::cout << e.what() << std::endl;
                }
            }
        }
    }
    {
        {
            List<std::string> list(5);
            for (size_t i = 0; i < 10; ++i)
            {
                list.Emplace(1, std::to_string(i));
            }
            try
            {
                if (list.Front() != std::to_string(0)) { return false; }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
            for (size_t i = 1; i < list.Size(); ++i)
            {
                try
                {
                    if (list.At(i) != std::to_string(10 - i)) { return false; }
                }
                catch (const std::exception& e)
                {
                    std::cout << e.what() << std::endl;
                }
            }
        }
        {
            List<std::string> list(5);
            for (size_t i = 0; i < 10; ++i)
            {
                switch (i)
                {
                case 0:
                    list.Emplace(list.begin(), std::to_string(i));
                    break;
                case 1:
                    list.Emplace(list.end(), std::to_string(i));
                    break;
                default:
                    List<std::string>::iterator it(list.begin());
                    ++it;
                    list.Emplace(it, std::to_string(i));
                    break;
                }
            }
            try
            {
                if (list.Front() != std::to_string(0)) { return false; }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
            for (size_t i = 1; i < list.Size(); ++i)
            {
                try
                {
                    if (list.At(i) != std::to_string(10 - i)) { return false; }
                }
                catch (const std::exception& e)
                {
                    std::cout << e.what() << std::endl;
                }
            }
        }
        {
            List<std::string> list(5);
            for (size_t i = 0; i < 10; ++i)
            {
                switch (i)
                {
                case 0:
                    list.Emplace(list.rend(), std::to_string(i));
                    break;
                case 1:
                    list.Emplace(list.rbegin(), std::to_string(i));
                    break;
                default:
                    List<std::string>::reverse_iterator it(list.rend());
                    it -= 2;
                    list.Emplace(it, std::to_string(i));
                    break;
                }
            }
            try
            {
                if (list.Front() != std::to_string(0)) { return false; }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
            for (size_t i = 1; i < list.Size(); ++i)
            {
                try
                {
                    if (list.At(i) != std::to_string(10 - i)) { return false; }
                }
                catch (const std::exception& e)
                {
                    std::cout << e.what() << std::endl;
                }
            }
        }
    }
    {
        {
            List<TestStruct> list(5);
            for (size_t i = 0; i < 10; ++i)
            {
                list.Emplace(1, (float)i);
            }
            try
            {
                if (list.Front() != TestStruct()) { return false; }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
            for (size_t i = 1; i < list.Size(); ++i)
            {
                try
                {
                    if (list.At(i) != TestStruct((float)(10 - i))) { return false; }
                }
                catch (const std::exception& e)
                {
                    std::cout << e.what() << std::endl;
                }
            }
        }
        {
            List<TestStruct> list(5);
            for (size_t i = 0; i < 10; ++i)
            {
                switch (i)
                {
                case 0:
                    list.Emplace(list.begin(), (float)i);
                    break;
                case 1:
                    list.Emplace(list.end(), (float)i);
                    break;
                default:
                    List<TestStruct>::iterator it(list.begin());
                    ++it;
                    list.Emplace(it, (float)i);
                    break;
                }
            }
            try
            {
                if (list.Front() != 0) { return false; }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
            for (size_t i = 1; i < list.Size(); ++i)
            {
                try
                {
                    if (list.At(i) != TestStruct((float)(10 - i))) { return false; }
                }
                catch (const std::exception& e)
                {
                    std::cout << e.what() << std::endl;
                }
            }
        }
        {
            List<TestStruct> list(5);
            for (size_t i = 0; i < 10; ++i)
            {
                switch (i)
                {
                case 0:
                    list.Emplace(list.rend(), (float)i);
                    break;
                case 1:
                    list.Emplace(list.rbegin(), (float)i);
                    break;
                default:
                    List<TestStruct>::reverse_iterator it(list.rend());
                    it -= 2;
                    list.Emplace(it, (float)i);
                    break;
                }
            }
            try
            {
                if (list.Front() != TestStruct()) { return false; }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
            for (size_t i = 1; i < list.Size(); ++i)
            {
                try
                {
                    if (list.At(i) != TestStruct((float)(10 - i))) { return false; }
                }
                catch (const std::exception& e)
                {
                    std::cout << e.what() << std::endl;
                }
            }
        }
    }

    return true;
}

bool ListTest::PopBack()
{
    //void PopBack()

    {
        List<size_t> list;
        for (size_t i = 0; i < 10; ++i)
        {
            list.PushBack(i);
        }
        list.PopBack();
        try
        {
            if (list.Back() != 8) { return false; }
        }
        catch (const std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
        if (list.Size() != 9) { return false; }
        for (size_t i = 0; i < 10; ++i)
        {
            list.PopBack();
        }
        if (list.Size() != 0) { return false; }
    }
    {
        List<std::string> list;
        for (size_t i = 0; i < 10; ++i)
        {
            list.PushBack(std::to_string(i));
        }
        list.PopBack();
        try
        {
            if (list.Back() != std::to_string(8)) { return false; }
        }
        catch (const std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
        if (list.Size() != 9) { return false; }
        for (size_t i = 0; i < 10; ++i)
        {
            list.PopBack();
        }
        if (list.Size() != 0) { return false; }
    }
    {
        List<TestStruct> list;
        for (size_t i = 0; i < 10; ++i)
        {
            list.PushBack(TestStruct((float)i));
        }
        list.PopBack();
        try
        {
            if (list.Back() != TestStruct(8.0f)) { return false; }
        }
        catch (const std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
        if (list.Size() != 9) { return false; }
        for (size_t i = 0; i < 10; ++i)
        {
            list.PopBack();
        }
        if (list.Size() != 0) { return false; }
    }

    return true;
}

bool ListTest::PopFront()
{
    //void PopFront()

    {
        List<size_t> list;
        for (size_t i = 0; i < 10; ++i)
        {
            list.PushBack(i);
        }
        list.PopFront();
        try
        {
            if (list.Front() != 1) { return false; }
        }
        catch (const std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
        if (list.Size() != 9) { return false; }
        for (size_t i = 0; i < 10; ++i)
        {
            list.PopFront();
        }
        if (list.Size() != 0) { return false; }
    }
    {
        List<std::string> list;
        for (size_t i = 0; i < 10; ++i)
        {
            list.PushBack(std::to_string(i));
        }
        list.PopFront();
        try
        {
            if (list.Front() != std::to_string(1)) { return false; }
        }
        catch (const std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
        if (list.Size() != 9) { return false; }
        for (size_t i = 0; i < 10; ++i)
        {
            list.PopFront();
        }
        if (list.Size() != 0) { return false; }
    }
    {
        List<TestStruct> list;
        for (size_t i = 0; i < 10; ++i)
        {
            list.PushBack(TestStruct((float)i));
        }
        list.PopFront();
        try
        {
            if (list.Front() != TestStruct(1.0f)) { return false; }
        }
        catch (const std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
        if (list.Size() != 9) { return false; }
        for (size_t i = 0; i < 10; ++i)
        {
            list.PopFront();
        }
        if (list.Size() != 0) { return false; }
    }

    return true;
}

bool ListTest::Erase()
{
    //void Erase(size_t)
    //void Erase(iterator)
    //void Erase(reverse_iterator)

    {
        {
            List<size_t> list;
            for (size_t i = 0; i < 10; ++i)
            {
                list.PushBack(i);
            }
            list.Erase(0);
            if (list.Front() == 0) { return false; }
            size_t list_size = list.Size();
            for (size_t i = 0; i < list_size; ++i)
            {
                List<size_t>::iterator it = list.Erase(1);
                if (it == list.end()) { break; }
                if (list[1] != (3 + i)) { return false; }
            }
            list.Erase(0);
            if (!list.IsEmpty()) { return false; }
        }
        {
            List<size_t> list;
            for (size_t i = 0; i < 10; ++i)
            {
                list.PushBack(i);
            }
            list.Erase(0);
            if (list.Front() == 0) { return false; }
            size_t list_size = list.Size();
            for (size_t i = 0; i < list_size; ++i)
            {
                List<size_t>::iterator it(list.begin());
                it = list.Erase(++it);
                if (it == list.end()) { break; }
                if (list[1] != (3 + i)) { return false; }
            }
            list.Erase(0);
            if (!list.IsEmpty()) { return false; }
        }
        {
            List<size_t> list;
            for (size_t i = 0; i < 10; ++i)
            {
                list.PushBack(i);
            }
            list.Erase(0);
            if (list.Front() == 0) { return false; }
            size_t list_size = list.Size();
            for (size_t i = 0; i < list_size; ++i)
            {
                List<size_t>::reverse_iterator it(list.rbegin());
                it = list.Erase(++it);
                ++it;
                if (it == list.rend()) { break; }
                if (list[list.Size() - 2] != (7 - i)) { return false; }
            }
            list.Erase(0);
            if (!list.IsEmpty()) { return false; }
        }
    }
    {
        {
            List<std::string> list;
            for (size_t i = 0; i < 10; ++i)
            {
                list.PushBack(std::to_string(i));
            }
            list.Erase(0);
            if (list.Front() == "0") { return false; }
            size_t list_size = list.Size();
            for (size_t i = 0; i < list_size; ++i)
            {
                List<std::string>::iterator it = list.Erase(1);
                if (it == list.end()) { break; }
                if (list[1] != std::to_string(3 + i)) { return false; }
            }
            list.Erase(0);
            if (!list.IsEmpty()) { return false; }
        }
        {
            List<std::string> list;
            for (size_t i = 0; i < 10; ++i)
            {
                list.PushBack(std::to_string(i));
            }
            list.Erase(0);
            if (list.Front() == "0") { return false; }
            size_t list_size = list.Size();
            for (size_t i = 0; i < list_size; ++i)
            {
                List<std::string>::iterator it(list.begin());
                it = list.Erase(++it);
                if (it == list.end()) { break; }
                if (list[1] != std::to_string(3 + i)) { return false; }
            }
            list.Erase(0);
            if (!list.IsEmpty()) { return false; }
        }
        {
            List<std::string> list;
            for (size_t i = 0; i < 10; ++i)
            {
                list.PushBack(std::to_string(i));
            }
            list.Erase(0);
            if (list.Front() == "0") { return false; }
            size_t list_size = list.Size();
            for (size_t i = 0; i < list_size; ++i)
            {
                List<std::string>::reverse_iterator it(list.rbegin());
                it = list.Erase(++it);
                ++it;
                if (it == list.rend()) { break; }
                if (list[list.Size() - 2] != std::to_string(7 - i)) { return false; }
            }
            list.Erase(0);
            if (!list.IsEmpty()) { return false; }
        }
    }
    {
        {
            List<TestStruct> list;
            for (size_t i = 0; i < 10; ++i)
            {
                list.PushBack(TestStruct((float)i));
            }
            list.Erase(0);
            if (list.Front() == TestStruct()) { return false; }
            size_t list_size = list.Size();
            for (size_t i = 0; i < list_size; ++i)
            {
                List<TestStruct>::iterator it = list.Erase(1);
                if (it == list.end()) { break; }
                if (list[1] != TestStruct((float)(3 + i))) { return false; }
            }
            list.Erase(0);
            if (!list.IsEmpty()) { return false; }
        }
        {
            List<TestStruct> list;
            for (size_t i = 0; i < 10; ++i)
            {
                list.PushBack(TestStruct((float)i));
            }
            list.Erase(0);
            if (list.Front() == TestStruct()) { return false; }
            size_t list_size = list.Size();
            for (size_t i = 0; i < list_size; ++i)
            {
                List<TestStruct>::iterator it(list.begin());
                it = list.Erase(++it);
                if (it == list.end()) { break; }
                if (list[1] != TestStruct((float)(3 + i))) { return false; }
            }
            list.Erase(0);
            if (!list.IsEmpty()) { return false; }
        }
        {
            List<TestStruct> list;
            for (size_t i = 0; i < 10; ++i)
            {
                list.PushBack(TestStruct((float)i));
            }
            list.Erase(0);
            if (list.Front() == TestStruct()) { return false; }
            size_t list_size = list.Size();
            for (size_t i = 0; i < list_size; ++i)
            {
                List<TestStruct>::reverse_iterator it(list.rbegin());
                it = list.Erase(++it);
                ++it;
                if (it == list.rend()) { break; }
                if (list[list.Size() - 2] != TestStruct((float)(7 - i))) { return false; }
            }
            list.Erase(0);
            if (!list.IsEmpty()) { return false; }
        }
    }

    return true;
}

bool ListTest::Clear()
{
    //void Clear()

    {
        List<size_t> list;
        for (size_t i = 0; i < 10; ++i)
        {
            list.PushBack(i);
        }
        list.Clear();
        if (!list.IsEmpty()) { return false; }
    }
    {
        List<std::string> list;
        for (size_t i = 0; i < 10; ++i)
        {
            list.PushBack(std::to_string(i));
        }
        list.Clear();
        if (!list.IsEmpty()) { return false; }
    }
    {
        List<TestStruct> list;
        for (size_t i = 0; i < 10; ++i)
        {
            list.PushBack(TestStruct((float)i));
        }
        list.Clear();
        if (!list.IsEmpty()) { return false; }
    }

    return true;
}

bool ListTest::Append()
{
    //void Append(const List&)
    //void Append(List&&)

    {
        {
            List<size_t> list0(30);
            List<size_t> list1(30);

            for (size_t i = 0; i < 10; ++i)
            {
                list0.PushBack(i);
                list1.PushBack(10 + i);
            }
            list0.Append(list1);

            if (list0.Size() != 20) { return false; }
            if (list0.Capacity() != 30) { return false; }
            if (list1.Size() != 10) { return false; }
        }
        {
            List<std::string> list0(30);
            List<std::string> list1(30);

            for (size_t i = 0; i < 10; ++i)
            {
                list0.PushBack(std::to_string(i));
                list1.PushBack(std::to_string(10 + i));
            }
            list0.Append(list1);

            if (list0.Size() != 20) { return false; }
            if (list0.Capacity() != 30) { return false; }
            if (list1.Size() != 10) { return false; }
        }
        {
            List<TestStruct> list0(30);
            List<TestStruct> list1(30);

            for (size_t i = 0; i < 10; ++i)
            {
                list0.PushBack(TestStruct((float)i));
                list1.PushBack(TestStruct((float)(10 + i)));
            }
            list0.Append(list1);

            if (list0.Size() != 20) { return false; }
            if (list0.Capacity() != 30) { return false; }
            if (list1.Size() != 10) { return false; }
        }
    }
    {
        {
            List<size_t> list0(30);
            List<size_t> list1(30);

            for (size_t i = 0; i < 10; ++i)
            {
                list0.PushBack(i);
                list1.PushBack(10 + i);
            }
            list0.Append(std::move(list1));

            if (list0.Size() != 20) { return false; }
            if (list0.Capacity() != 60) { return false; }
            if (list1.Size() != 0) { return false; }
        }
        {
            List<std::string> list0(30);
            List<std::string> list1(30);

            for (size_t i = 0; i < 10; ++i)
            {
                list0.PushBack(std::to_string(i));
                list1.PushBack(std::to_string(10 + i));
            }
            list0.Append(std::move(list1));

            if (list0.Size() != 20) { return false; }
            if (list0.Capacity() != 60) { return false; }
            if (list1.Size() != 0) { return false; }
        }
        {
            List<TestStruct> list0(30);
            List<TestStruct> list1(30);

            for (size_t i = 0; i < 10; ++i)
            {
                list0.PushBack(TestStruct((float)i));
                list1.PushBack(TestStruct((float)(10 + i)));
            }
            list0.Append(std::move(list1));

            if (list0.Size() != 20) { return false; }
            if (list0.Capacity() != 60) { return false; }
            if (list1.Size() != 0) { return false; }
        }
    }

    return true;
}

bool ListTest::Resize()
{
    //void Resize(size_t)

    {
        List<size_t> list;
        list.Resize(20);
        if (list.Capacity() != 20) { return false; }
        list.Resize(10);
        if (list.Capacity() != 10) { return false; }
        for (size_t i = 0; i < list.Capacity(); ++i)
        {
            list.PushBack(i);
        }
        list.Resize(5);
        if (list.Size() != 5) { return false; }
        list.Resize(0);
        if (!list.IsEmpty()) { return false; }
    }
    {
        List<std::string> list;
        list.Resize(20);
        if (list.Capacity() != 20) { return false; }
        list.Resize(10);
        if (list.Capacity() != 10) { return false; }
        for (size_t i = 0; i < list.Capacity(); ++i)
        {
            list.PushBack(std::to_string(i));
        }
        list.Resize(5);
        if (list.Size() != 5) { return false; }
        list.Resize(0);
        if (!list.IsEmpty()) { return false; }
    }
    {
        List<TestStruct> list;
        list.Resize(20);
        if (list.Capacity() != 20) { return false; }
        list.Resize(10);
        if (list.Capacity() != 10) { return false; }
        for (size_t i = 0; i < list.Capacity(); ++i)
        {
            list.PushBack(TestStruct((float)i));
        }
        list.Resize(5);
        if (list.Size() != 5) { return false; }
        list.Resize(0);
        if (!list.IsEmpty()) { return false; }
    }

    return true;
}

bool ListTest::Reserve()
{
    //void Reserve(size_t)

    {
        List<size_t> list;
        list.Reserve(20);
        if (list.Capacity() != 20) { return false; }
        list.Reserve(10);
        if (list.Capacity() != 20) { return false; }
        for (size_t i = 0; i < list.Capacity(); ++i)
        {
            list.PushBack(i);
        }
        list.Reserve(25);
        if (list.Size() != 20) { return false; }
        if (list.Capacity() != 25) { return false; }
    }
    {
        List<std::string> list;
        list.Reserve(20);
        if (list.Capacity() != 20) { return false; }
        list.Reserve(10);
        if (list.Capacity() != 20) { return false; }
        for (size_t i = 0; i < list.Capacity(); ++i)
        {
            list.PushBack(std::to_string(i));
        }
        list.Reserve(25);
        if (list.Size() != 20) { return false; }
        if (list.Capacity() != 25) { return false; }
    }
    {
        List<TestStruct> list;
        list.Reserve(20);
        if (list.Capacity() != 20) { return false; }
        list.Reserve(10);
        if (list.Capacity() != 20) { return false; }
        for (size_t i = 0; i < list.Capacity(); ++i)
        {
            list.PushBack(TestStruct((float)i));
        }
        list.Reserve(25);
        if (list.Size() != 20) { return false; }
        if (list.Capacity() != 25) { return false; }
    }

    return true;
}

bool ListTest::Shrink()
{
    //void Shrink()

    {
        List<size_t> list;
        list.Reserve(20);
        list.Shrink();
        if (list.Capacity() != 0) { return false; }
        list.Reserve(20);
        for (size_t i = 0; i < 10; ++i)
        {
            list.PushBack(i);
        }
        list.Shrink();
        if (list.Size() != 10) { return false; }
        if (list.Capacity() != list.Size()) { return false; }
    }
    {
        List<std::string> list;
        list.Reserve(20);
        list.Shrink();
        if (list.Capacity() != 0) { return false; }
        list.Reserve(20);
        for (size_t i = 0; i < 10; ++i)
        {
            list.PushBack(std::to_string(i));
        }
        list.Shrink();
        if (list.Size() != 10) { return false; }
        if (list.Capacity() != list.Size()) { return false; }
    }
    {
        List<TestStruct> list;
        list.Reserve(20);
        list.Shrink();
        if (list.Capacity() != 0) { return false; }
        list.Reserve(20);
        for (size_t i = 0; i < 10; ++i)
        {
            list.PushBack(TestStruct((float)i));
        }
        list.Shrink();
        if (list.Size() != 10) { return false; }
        if (list.Capacity() != list.Size()) { return false; }
    }

    return true;
}
