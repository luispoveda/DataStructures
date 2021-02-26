#include "VectorTest.hpp"
#include "Vector.hpp"
#include "../TestStruct.hpp"
#include "../Serializer.hpp"

#include <iostream> //For std::cout and std::fixed
#include <string>
#include <sstream>  //For std::stringstream

static std::stringstream s_FileBuffer;

bool VectorTest::RunAllTest()
{
    std::stringstream test_results_buffer;
    bool test_result = true;
    size_t passed = 16;
    s_FileBuffer << "Vector Bug Tests:" << std::endl;
    s_FileBuffer << "Total test executed: " << passed << std::endl;

    if (!Iterators()) { test_results_buffer << std::endl << "Iterator Test Failed" << std::endl; test_result = false; --passed; }
    if (!Copy()) { test_results_buffer << std::endl << "Copy Test Failed" << std::endl; test_result = false; --passed;}
    if (!Move()) { test_results_buffer << std::endl << "Move Test Failed" << std::endl; test_result = false; --passed;}
    if (!Operators()) { test_results_buffer << std::endl << "Operator Test Failed" << std::endl; test_result = false; --passed;}
    if (!Reserve()) { test_results_buffer << std::endl << "Reserve Test Failed" << std::endl; test_result = false; --passed;}
    if (!Shrink()) { test_results_buffer << std::endl << "Shrink Test Failed" << std::endl; test_result = false; --passed;}
    if (!Resize()) { test_results_buffer << std::endl << "Resize Test Failed" << std::endl; test_result = false; --passed;}
    if (!PushBack()) { test_results_buffer << std::endl << "PushBack Test Failed" << std::endl; test_result = false; --passed;}
    if (!Insert()) { test_results_buffer << std::endl << "Insert Test Failed" << std::endl; test_result = false; --passed;}
    if (!EmplaceBack()) { test_results_buffer << std::endl << "EmplaceBack Test Failed" << std::endl; test_result = false; --passed;}
    if (!Emplace()) { test_results_buffer << std::endl << "Emplace Test Failed" << std::endl; test_result = false; --passed;}
    if (!PopBack()) { test_results_buffer << std::endl << "PopBack Test Failed" << std::endl; test_result = false; --passed;}
    if (!Erase()) { test_results_buffer << std::endl << "Erase Test Failed" << std::endl; test_result = false; --passed;}
    if (!Clear()) { test_results_buffer << std::endl << "Clear Test Failed" << std::endl; test_result = false; --passed;}
    if (!Append()) { test_results_buffer << std::endl << "Append Test Failed" << std::endl; test_result = false; --passed;}
    if (!Swap()) { test_results_buffer << std::endl << "Swap Test Failed" << std::endl; test_result = false; --passed;}

    s_FileBuffer << "Total test passed: " << passed << std::endl << std::endl;
    if (test_result) { s_FileBuffer << "No errors found" << std::endl; }
    else { s_FileBuffer << test_results_buffer.str(); }
    s_FileBuffer << std::endl << std::endl;
    Serializer::SerializeResults("Vector_Results.txt", s_FileBuffer);

    return test_result;
}

bool VectorTest::Iterators()
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
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::iterator it(vector.begin());

            for (size_t i = 0; i < vector.Size(); ++i)
            {
                if (*it != TestStruct((float)i)) { return false; }
                ++it;
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::iterator it(vector.begin());

            for (size_t i = 0; i < vector.Size(); ++i)
            {
                if (*it++ != TestStruct((float)i)) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 0; i < vector.Size(); ++i)
            {
                Vector<TestStruct>::iterator it(vector.begin());
                it += i;
                if (*it != TestStruct((float)i)) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 1; i <= (int)vector.Size(); ++i)
            {
                Vector<TestStruct>::iterator it(vector.end());
                it += -i;
                if (*it != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::iterator it;

            for (size_t i = 0; i < vector.Size(); ++i)
            {
                it = vector.begin();
                it.Advance(i);
                if (*it != TestStruct((float)i)) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::iterator it(vector.end());

            for (size_t i = 0; i < vector.Size(); ++i)
            {
                if (*--it != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::iterator it(vector.end());

            --it;
            for (size_t i = 0; i < vector.Size(); ++i)
            {
                if (*it-- != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 1; i <= vector.Size(); ++i)
            {
                Vector<TestStruct>::iterator it(vector.end());
                it -= i;
                if (*it != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 0; i < (int)vector.Size(); ++i)
            {
                Vector<TestStruct>::iterator it(vector.begin());
                it -= -i;
                if (*it != TestStruct((float)i)) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::iterator it;

            for (size_t i = 1; i <= vector.Size(); ++i)
            {
                it = vector.end();
                it.Retreat(i);
                if (*it != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 0; i < vector.Size(); ++i)
            {
                Vector<TestStruct>::iterator it(vector.begin());
                if (*(it + i) != TestStruct((float)i)) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 1; i <= (int)vector.Size(); ++i)
            {
                Vector<TestStruct>::iterator it(vector.end());
                if (*(it + -i) != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::iterator it;

            for (size_t i = 0; i < vector.Size(); ++i)
            {
                it = vector.begin();
                if (*it.Next(i) != TestStruct((float)i)) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 1; i <= vector.Size(); ++i)
            {
                Vector<TestStruct>::iterator it(vector.end());
                if (*(it - i) != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 0; i < (int)vector.Size(); ++i)
            {
                Vector<TestStruct>::iterator it(vector.begin());
                if (*(it - -i) != TestStruct((float)i)) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::iterator it;

            for (size_t i = 1; i <= vector.Size(); ++i)
            {
                it = vector.end();
                if (*it.Prev(i) != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::iterator it(vector.begin());

            for (size_t i = 0; i < vector.Size(); ++i)
            {
                if (it[i] != TestStruct((float)i)) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::iterator it(vector.end());

            for (int i = 1; i <= (int)vector.Size(); ++i)
            {
                if (it[-i] != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::iterator it(vector.begin());

            for (size_t i = 0; i < vector.Size(); ++i)
            {
                if (it.At(i) != TestStruct((float)i)) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::iterator it(vector.end());

            for (int i = 1; i <= (int)vector.Size(); ++i)
            {
                if (it.At(-i) != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::iterator it(vector.begin());

            for (size_t i = 0; i < vector.Size(); ++i, ++it)
            {
                auto& aux = *it;
                if (aux != TestStruct((float)i)) { return false; }
                aux.x += 5.0f;
            }
            it = vector.begin();
            for (size_t i = 0; i < vector.Size(); ++i, ++it)
            {
                if ((*it).x != (float)(5 + i)) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::iterator it(vector.begin());

            for (size_t i = 0; i < vector.Size(); ++i, ++it)
            {
                auto& aux = it.Data();
                if (aux != TestStruct((float)i)) { return false; }
                aux.x += 5.0f;
            }
            it = vector.begin();
            for (size_t i = 0; i < vector.Size(); ++i, ++it)
            {
                if ((*it).x != (float)(5 + i)) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::iterator it(vector.begin());

            for (size_t i = 0; i < vector.Size(); ++i, ++it)
            {
                float& aux = it->x;
                if (aux != (float)i) { return false; }
                aux += 5.0f;
            }
            it = vector.begin();
            for (size_t i = 0; i < vector.Size(); ++i, ++it)
            {
                if ((*it).x != (float)(5 + i)) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::iterator it(vector.begin());

            for (size_t i = 0; i < vector.Size(); ++i, ++it)
            {
                auto& aux = it.Get()->x;
                if (aux != (float)i) { return false; }
                aux += 5.0f;
            }
            it = vector.begin();
            for (size_t i = 0; i < vector.Size(); ++i, ++it)
            {
                if ((*it).x != (float)(5 + i)) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::iterator it(vector.begin());

            for (size_t i = 0; i < vector.Size(); ++i, ++it)
            {
                auto& aux = *it;
                if (aux != TestStruct((float)i)) { return false; }
                aux.x += 5.0f;
            }
            it = vector.begin();
            for (size_t i = 0; i < vector.Size(); ++i, ++it)
            {
                if ((*it).x != (float)(5 + i)) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::iterator it(vector.begin());

            for (size_t i = 0; i < vector.Size(); ++i, ++it)
            {
                auto& aux = it.Data();
                if (aux != TestStruct((float)i)) { return false; }
                aux.x += 5.0f;
            }
            it = vector.begin();
            for (size_t i = 0; i < vector.Size(); ++i, ++it)
            {
                if ((*it).x != (float)(5 + i)) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::iterator it(vector.begin());

            for (size_t i = 0; i < vector.Size(); ++i, ++it)
            {
                auto aux = &it;
                if (**aux != TestStruct((float)i)) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::iterator it(vector.begin());

            for (size_t i = 0; i < vector.Size(); ++i, ++it)
            {
                Vector<TestStruct>::iterator aux(vector.begin());
                if (it.Distance(aux) != i) { return false; }
                if (aux.Distance(it) != i) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::iterator it;
            if (it) { return false; }
            if (it.IsValid()) { return false; }
            it = vector.end();
            if (it == vector.begin()) { return false; }
            if (it == &vector[0]) { return false; }
            it = vector.begin();
            if (it != vector.begin()) { return false; }
            if (it != &vector[0]) { return false; }
            if (vector.end() < vector.begin()) { return false; }
            if (vector.begin() > vector.end()) { return false; }
            if (!(it <= vector.begin())) { return false; }
            if (!(it >= vector.begin())) { return false; }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::iterator it0(&vector[3]);
            if (*it0 != TestStruct(3.0f)) { return false; }
            Vector<TestStruct>::iterator it1(vector.begin());
            if (*it1 != TestStruct(0.0f)) { return false; }
            Vector<TestStruct>::iterator aux(&vector[2]);
            Vector<TestStruct>::iterator it2(std::move(aux));
            if (aux) { return false; }
            if (*it2 != TestStruct(2.0f)) { return false; }
            it0 = &vector[4];
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
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::const_iterator it(vector.cbegin());

            for (size_t i = 0; i < vector.Size(); ++i)
            {
                if (*it != TestStruct((float)i)) { return false; }
                ++it;
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::const_iterator it(vector.cbegin());

            for (size_t i = 0; i < vector.Size(); ++i)
            {
                if (*it++ != TestStruct((float)i)) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 0; i < vector.Size(); ++i)
            {
                Vector<TestStruct>::const_iterator it(vector.cbegin());
                it += i;
                if (*it != TestStruct((float)i)) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 1; i <= (int)vector.Size(); ++i)
            {
                Vector<TestStruct>::const_iterator it(vector.cend());
                it += -i;
                if (*it != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::const_iterator it;

            for (size_t i = 0; i < vector.Size(); ++i)
            {
                it = vector.cbegin();
                it.Advance(i);
                if (*it != TestStruct((float)i)) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::const_iterator it(vector.cend());
            --it;

            for (size_t i = 0; i < vector.Size(); ++i)
            {
                if (*it-- != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::const_iterator it(vector.cend());

            for (size_t i = 0; i < vector.Size(); ++i)
            {
                if (*--it != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 1; i <= vector.Size(); ++i)
            {
                Vector<TestStruct>::const_iterator it(vector.cend());
                it -= i;
                if (*it != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 0; i < (int)vector.Size(); ++i)
            {
                Vector<TestStruct>::const_iterator it(vector.cbegin());
                it -= -i;
                if (*it != TestStruct((float)i)) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::const_iterator it;

            for (size_t i = 1; i <= vector.Size(); ++i)
            {
                it = vector.cend();
                it.Retreat(i);
                if (*it != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 0; i < vector.Size(); ++i)
            {
                Vector<TestStruct>::const_iterator it(vector.cbegin());
                if (*(it + i) != TestStruct((float)i)) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 1; i <= (int)vector.Size(); ++i)
            {
                Vector<TestStruct>::const_iterator it(vector.cend());
                if (*(it + -i) != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::const_iterator it;

            for (size_t i = 0; i < vector.Size(); ++i)
            {
                it = vector.cbegin();
                if (*it.Next(i) != TestStruct((float)i)) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 1; i <= vector.Size(); ++i)
            {
                Vector<TestStruct>::const_iterator it(vector.cend());
                if (*(it - i) != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 0; i < (int)vector.Size(); ++i)
            {
                Vector<TestStruct>::const_iterator it(vector.cbegin());
                if (*(it - -i) != TestStruct((float)i)) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::const_iterator it;

            for (size_t i = 1; i <= vector.Size(); ++i)
            {
                it = vector.cend();
                if (*it.Prev(i) != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::const_iterator it(vector.cbegin());

            for (size_t i = 0; i < vector.Size(); ++i)
            {
                if (it[i] != TestStruct((float)i)) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::const_iterator it(vector.cend());

            for (int i = 1; i <= (int)vector.Size(); ++i)
            {
                if (it[-i] != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::const_iterator it(vector.cbegin());

            for (size_t i = 0; i < vector.Size(); ++i)
            {
                if (it.At(i) != TestStruct((float)i)) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::const_iterator it(vector.cend());

            for (int i = 1; i <= (int)vector.Size(); ++i)
            {
                if (it.At(-i) != TestStruct((float)(5 - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::const_iterator it(vector.cbegin());

            for (size_t i = 0; i < vector.Size(); ++i, ++it)
            {
                const auto& aux = *it;
                if (aux != TestStruct((float)i)) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::const_iterator it(vector.cbegin());

            for (size_t i = 0; i < vector.Size(); ++i, ++it)
            {
                const auto& aux = it.Data();
                if (aux != TestStruct((float)i)) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::const_iterator it(vector.cbegin());

            for (size_t i = 0; i < vector.Size(); ++i, ++it)
            {
                const float& aux = it->x;
                if (aux != (float)i) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::const_iterator it(vector.cbegin());

            for (size_t i = 0; i < vector.Size(); ++i, ++it)
            {
                const auto& aux = it.Get()->x;
                if (aux != (float)i) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::const_iterator it(vector.cbegin());

            for (size_t i = 0; i < vector.Size(); ++i, ++it)
            {
                const auto& aux = *it;
                if (aux != TestStruct((float)i)) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::const_iterator it(vector.cbegin());

            for (size_t i = 0; i < vector.Size(); ++i, ++it)
            {
                auto& aux = it.Data();
                if (aux != TestStruct((float)i)) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::const_iterator it(vector.cbegin());

            for (size_t i = 0; i < vector.Size(); ++i, ++it)
            {
                const auto aux = &it;
                if (**aux != TestStruct((float)i)) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::const_iterator it(vector.cbegin());

            for (size_t i = 0; i < vector.Size(); ++i, ++it)
            {
                Vector<TestStruct>::const_iterator aux(vector.cbegin());
                if (it.Distance(aux) != i) { return false; }
                if (aux.Distance(it) != i) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::const_iterator it;
            if (it) { return false; }
            if (it.IsValid()) { return false; }
            it = vector.cend();
            if (it == vector.cbegin()) { return false; }
            if (it == &vector[0]) { return false; }
            it = vector.cbegin();
            if (it != vector.cbegin()) { return false; }
            if (it != &vector[0]) { return false; }
            if (vector.cend() < vector.cbegin()) { return false; }
            if (vector.cbegin() > vector.cend()) { return false; }
            if (!(it <= vector.cbegin())) { return false; }
            if (!(it >= vector.cbegin())) { return false; }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::const_iterator it0(&vector[3]);
            if (*it0 != TestStruct(3.0f)) { return false; }
            Vector<TestStruct>::const_iterator it1(vector.cbegin());
            if (*it1 != TestStruct(0.0f)) { return false; }
            Vector<TestStruct>::const_iterator aux(&vector[2]);
            Vector<TestStruct>::const_iterator it2(std::move(aux));
            if (aux) { return false; }
            if (*it2 != TestStruct(2.0f)) { return false; }
            it0 = &vector[4];
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
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::reverse_iterator it(vector.rbegin());

            for (size_t i = 0; i < vector.Size(); ++i)
            {
                if (*it != TestStruct((float)(4 - i))) { return false; }
                ++it;
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::reverse_iterator it(vector.rbegin());

            for (size_t i = 0; i < vector.Size(); ++i)
            {
                if (*it++ != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 0; i < vector.Size(); ++i)
            {
                Vector<TestStruct>::reverse_iterator it(vector.rbegin());
                it += i;
                if (*it != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 1; i <= (int)vector.Size(); ++i)
            {
                Vector<TestStruct>::reverse_iterator it(vector.rend());
                it += -i;
                if (*it != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::reverse_iterator it;

            for (size_t i = 0; i < vector.Size(); ++i)
            {
                it = vector.rbegin();
                it.Advance(i);
                if (*it != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::reverse_iterator it(vector.rend());

            for (size_t i = 0; i < vector.Size(); ++i)
            {
                if (*--it != TestStruct((float)i)) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::reverse_iterator it(vector.rend());
            --it;

            for (size_t i = 0; i < vector.Size(); ++i)
            {
                if (*it-- != TestStruct((float)i)) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 1; i <= vector.Size(); ++i)
            {
                Vector<TestStruct>::reverse_iterator it(vector.rend());
                it -= i;
                if (*it != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 0; i < (int)vector.Size(); ++i)
            {
                Vector<TestStruct>::reverse_iterator it(vector.rbegin());
                it -= -i;
                if (*it != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::reverse_iterator it;

            for (size_t i = 1; i <= vector.Size(); ++i)
            {
                it = vector.rend();
                it.Retreat(i);
                if (*it != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 0; i < vector.Size(); ++i)
            {
                Vector<TestStruct>::reverse_iterator it(vector.rbegin());
                auto a = *(it + i);
                if (a != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 1; i <= (int)vector.Size(); ++i)
            {
                Vector<TestStruct>::reverse_iterator it(vector.rend());
                if (*(it + -i) != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::reverse_iterator it;

            for (size_t i = 0; i < vector.Size(); ++i)
            {
                it = vector.rbegin();
                if (*it.Next(i) != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 1; i <= vector.Size(); ++i)
            {
                Vector<TestStruct>::reverse_iterator it(vector.rend());
                if (*(it - i) != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 0; i < (int)vector.Size(); ++i)
            {
                Vector<TestStruct>::reverse_iterator it(vector.rbegin());
                if (*(it - -i) != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::reverse_iterator it;

            for (size_t i = 1; i <= vector.Size(); ++i)
            {
                it = vector.rend();
                if (*it.Prev(i) != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::reverse_iterator it(vector.rbegin());

            for (size_t i = 0; i < vector.Size(); ++i)
            {
                if (it[i] != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::reverse_iterator it(vector.rend());

            for (int i = 1; i <= (int)vector.Size(); ++i)
            {
                if (it[-i] != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::reverse_iterator it(vector.rbegin());

            for (size_t i = 0; i < vector.Size(); ++i)
            {
                if (it.At(i) != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::reverse_iterator it(vector.rend());

            for (int i = 1; i <= (int)vector.Size(); ++i)
            {
                if (it.At(-i) != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::reverse_iterator it(vector.rbegin());

            for (size_t i = 0; i < vector.Size(); ++i, ++it)
            {
                auto& aux = *it;
                if (aux != TestStruct((float)(4 - i))) { return false; }
                aux.x += 5.0f;
            }
            it = vector.rbegin();
            for (size_t i = 0; i < vector.Size(); ++i, ++it)
            {
                if ((*it).x != (float)(9 - i)) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::reverse_iterator it(vector.rbegin());

            for (size_t i = 0; i < vector.Size(); ++i, ++it)
            {
                auto& aux = it.Data();
                if (aux != TestStruct((float)(4 - i))) { return false; }
                aux.x += 5.0f;
            }
            it = vector.rbegin();
            for (size_t i = 0; i < vector.Size(); ++i, ++it)
            {
                if ((*it).x != (float)(9 - i)) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::reverse_iterator it(vector.rbegin());

            for (size_t i = 0; i < vector.Size(); ++i, ++it)
            {
                float& aux = it->x;
                if (aux != (float)(4 - i)) { return false; }
                aux += 5.0f;
            }
            it = vector.rbegin();
            for (size_t i = 0; i < vector.Size(); ++i, ++it)
            {
                if ((*it).x != (float)(9 - i)) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::reverse_iterator it(vector.rbegin());

            for (size_t i = 0; i < vector.Size(); ++i, ++it)
            {
                auto& aux = it.Get()->x;
                if (aux != (float)(4 - i)) { return false; }
                aux += 5.0f;
            }
            it = vector.rbegin();
            for (size_t i = 0; i < vector.Size(); ++i, ++it)
            {
                if ((*it).x != (float)(9 - i)) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::reverse_iterator it(vector.rbegin());

            for (size_t i = 0; i < vector.Size(); ++i, ++it)
            {
                auto& aux = *it;
                if (aux != TestStruct((float)(4 - i))) { return false; }
                aux.x += 5.0f;
            }
            it = vector.rbegin();
            for (size_t i = 0; i < vector.Size(); ++i, ++it)
            {
                if ((*it).x != (float)(9 - i)) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::reverse_iterator it(vector.rbegin());

            for (size_t i = 0; i < vector.Size(); ++i, ++it)
            {
                auto& aux = it.Data();
                if (aux != TestStruct((float)(4 - i))) { return false; }
                aux.x += 5.0f;
            }
            it = vector.rbegin();
            for (size_t i = 0; i < vector.Size(); ++i, ++it)
            {
                if ((*it).x != (float)(9 - i)) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::reverse_iterator it(vector.rbegin());

            for (size_t i = 0; i < vector.Size(); ++i, ++it)
            {
                auto aux = &it;
                if (**aux != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::reverse_iterator it(vector.rbegin());

            for (size_t i = 0; i < vector.Size(); ++i, ++it)
            {
                Vector<TestStruct>::reverse_iterator aux(vector.rbegin());
                if (it.Distance(aux) != i) { return false; }
                if (aux.Distance(it) != i) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::reverse_iterator it;
            if (it) { return false; }
            if (it.IsValid()) { return false; }
            it = vector.rend();
            if (it == vector.rbegin()) { return false; }
            if (it == &vector[0]) { return false; }
            it = vector.rbegin();
            if (it != vector.rbegin()) { return false; }
            if (it != &vector[4]) { return false; }
            if (vector.rend() < vector.rbegin()) { return false; }
            if (vector.rbegin() > vector.rend()) { return false; }
            if (!(it <= vector.rbegin())) { return false; }
            if (!(it >= vector.rbegin())) { return false; }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::reverse_iterator it0(&vector[3]);
            if (*it0 != TestStruct(3.0f)) { return false; }
            Vector<TestStruct>::reverse_iterator it1(vector.rbegin());
            if (*it1 != TestStruct(4.0f)) { return false; }
            Vector<TestStruct>::reverse_iterator aux(&vector[2]);
            Vector<TestStruct>::reverse_iterator it2(std::move(aux));
            if (aux) { return false; }
            if (*it2 != TestStruct(2.0f)) { return false; }
            it0 = &vector[4];
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
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::const_reverse_iterator it(vector.crbegin());

            for (size_t i = 0; i < vector.Size(); ++i)
            {
                if (*it != TestStruct((float)(4 - i))) { return false; }
                ++it;
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::const_reverse_iterator it(vector.crbegin());

            for (size_t i = 0; i < vector.Size(); ++i)
            {
                if (*it++ != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 0; i < vector.Size(); ++i)
            {
                Vector<TestStruct>::const_reverse_iterator it(vector.crbegin());
                it += i;
                if (*it != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 1; i <= (int)vector.Size(); ++i)
            {
                Vector<TestStruct>::const_reverse_iterator it(vector.crend());
                it += -i;
                if (*it != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::const_reverse_iterator it;

            for (size_t i = 0; i < vector.Size(); ++i)
            {
                it = vector.crbegin();
                it.Advance(i);
                if (*it != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::const_reverse_iterator it(vector.crend());

            for (size_t i = 0; i < vector.Size(); ++i)
            {
                if (*--it != TestStruct((float)i)) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::const_reverse_iterator it(vector.crend());
            --it;

            for (size_t i = 0; i < vector.Size(); ++i)
            {
                if (*it-- != TestStruct((float)i)) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 1; i <= vector.Size(); ++i)
            {
                Vector<TestStruct>::const_reverse_iterator it(vector.crend());
                it -= i;
                if (*it != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 0; i < (int)vector.Size(); ++i)
            {
                Vector<TestStruct>::const_reverse_iterator it(vector.crbegin());
                it -= -i;
                if (*it != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::const_reverse_iterator it;

            for (size_t i = 1; i <= vector.Size(); ++i)
            {
                it = vector.crend();
                it.Retreat(i);
                if (*it != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 0; i < vector.Size(); ++i)
            {
                Vector<TestStruct>::const_reverse_iterator it(vector.crbegin());
                const auto a = *(it + i);
                if (a != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 1; i <= (int)vector.Size(); ++i)
            {
                Vector<TestStruct>::const_reverse_iterator it(vector.crend());
                if (*(it + -i) != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::const_reverse_iterator it;

            for (size_t i = 0; i < vector.Size(); ++i)
            {
                it = vector.crbegin();
                if (*it.Next(i) != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (size_t i = 1; i <= vector.Size(); ++i)
            {
                Vector<TestStruct>::const_reverse_iterator it(vector.crend());
                if (*(it - i) != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

            for (int i = 0; i < (int)vector.Size(); ++i)
            {
                Vector<TestStruct>::const_reverse_iterator it(vector.crbegin());
                if (*(it - -i) != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::const_reverse_iterator it;

            for (size_t i = 1; i <= vector.Size(); ++i)
            {
                it = vector.crend();
                if (*it.Prev(i) != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::const_reverse_iterator it(vector.crbegin());

            for (size_t i = 0; i < vector.Size(); ++i)
            {
                if (it[i] != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::const_reverse_iterator it(vector.crend());

            for (int i = 1; i <= (int)vector.Size(); ++i)
            {
                if (it[-i] != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::const_reverse_iterator it(vector.crbegin());

            for (size_t i = 0; i < vector.Size(); ++i)
            {
                if (it.At(i) != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::const_reverse_iterator it(vector.crend());

            for (int i = 1; i <= (int)vector.Size(); ++i)
            {
                if (it.At(-i) != TestStruct((float)(i - 1))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::const_reverse_iterator it(vector.crbegin());

            for (size_t i = 0; i < vector.Size(); ++i, ++it)
            {
                const auto& aux = *it;
                if (aux != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::const_reverse_iterator it(vector.crbegin());

            for (size_t i = 0; i < vector.Size(); ++i, ++it)
            {
                const auto& aux = it.Data();
                if (aux != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::const_reverse_iterator it(vector.crbegin());

            for (size_t i = 0; i < vector.Size(); ++i, ++it)
            {
                const float& aux = it->x;
                if (aux != (float)(4 - i)) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::const_reverse_iterator it(vector.crbegin());

            for (size_t i = 0; i < vector.Size(); ++i, ++it)
            {
                const auto& aux = it.Get()->x;
                if (aux != (float)(4 - i)) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::const_reverse_iterator it(vector.crbegin());

            for (size_t i = 0; i < vector.Size(); ++i, ++it)
            {
                const auto& aux = *it;
                if (aux != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::const_reverse_iterator it(vector.crbegin());

            for (size_t i = 0; i < vector.Size(); ++i, ++it)
            {
                const auto& aux = it.Data();
                if (aux != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::const_reverse_iterator it(vector.crbegin());

            for (size_t i = 0; i < vector.Size(); ++i, ++it)
            {
                auto aux = &it;
                if (**aux != TestStruct((float)(4 - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::const_reverse_iterator it(vector.crbegin());

            for (size_t i = 0; i < vector.Size(); ++i, ++it)
            {
                Vector<TestStruct>::const_reverse_iterator aux(vector.crbegin());
                if (it.Distance(aux) != i) { return false; }
                if (aux.Distance(it) != i) { return false; }
            }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::const_reverse_iterator it;
            if (it) { return false; }
            if (it.IsValid()) { return false; }
            it = vector.crend();
            if (it == vector.crbegin()) { return false; }
            if (it == &vector[0]) { return false; }
            it = vector.crbegin();
            if (it != vector.crbegin()) { return false; }
            if (it != &vector[4]) { return false; }
            if (vector.crend() < vector.crbegin()) { return false; }
            if (vector.crbegin() > vector.crend()) { return false; }
            if (!(it <= vector.crbegin())) { return false; }
            if (!(it >= vector.crbegin())) { return false; }
        }
        {
            Vector<TestStruct> vector{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
            Vector<TestStruct>::const_reverse_iterator it0(&vector[3]);
            if (*it0 != TestStruct(3.0f)) { return false; }
            Vector<TestStruct>::const_reverse_iterator it1(vector.crbegin());
            if (*it1 != TestStruct(4.0f)) { return false; }
            Vector<TestStruct>::const_reverse_iterator aux(&vector[2]);
            Vector<TestStruct>::const_reverse_iterator it2(std::move(aux));
            if (aux) { return false; }
            if (*it2 != TestStruct(2.0f)) { return false; }
            it0 = &vector[4];
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

bool VectorTest::Copy()
{
    //Vector(const Vector& other)
    //operator=(const Vector& other)

    {
        Vector<size_t> vector0 { };
        Vector<size_t> vector1(vector0);

        if (vector1.Capacity() != 0) { return false; }
        if (vector1.Data()) { return false; }

        vector0 = vector1;

        if (vector0.Capacity() != 0) { return false; }
        if (vector0.Data()) { return false; }
    }
    {
        Vector<size_t> vector0{ 0, 1, 2, 3, 4 };
        Vector<size_t> vector1(vector0);

        for (size_t i = 0; i < vector1.Size(); ++i)
        {
            if (vector1[i] != vector0[i]) { return false; }
        }

        Vector<size_t> vector2{ 5, 6, 7, 8, 9 };
        vector1 = vector2;

        for (size_t i = 0; i < vector1.Size(); ++i)
        {
            if (vector1[i] != vector2[i]) { return false; }
        }
    }
    {
        Vector<std::string> vector0{ "0", "1", "2", "3", "4" };
        Vector<std::string> vector1(vector0);

        for (size_t i = 0; i < vector1.Size(); ++i)
        {
            if (vector1[i] != vector0[i]) { return false; }
        }

        Vector<std::string> vector2{ "5", "6", "7", "8", "9" };
        vector1 = vector2;

        for (size_t i = 0; i < vector1.Size(); ++i)
        {
            if (vector1[i] != vector2[i]) { return false; }
        }
    }
    {
        Vector<TestStruct> vector0{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
        Vector<TestStruct> vector1(vector0);

        for (size_t i = 0; i < vector1.Size(); ++i)
        {
            if (vector1[i] != vector0[i]) { return false; }
        }

        Vector<TestStruct> vector2{ TestStruct(5.0f), TestStruct(6.0f), TestStruct(7.0f), TestStruct(8.0f), TestStruct(9.0f) };
        vector1 = vector2;

        for (size_t i = 0; i < vector1.Size(); ++i)
        {
            if (vector1[i] != vector2[i]) { return false; }
        }
    }

    return true;
}

bool VectorTest::Move()
{
    //Vector(Vector&& other)
    //operator=(Vector&& other)

    {
        Vector<size_t> vector0{ };
        Vector<size_t> vector1(std::move(vector0));

        if (vector1.Capacity() != 0) { return false; }
        if (vector1.Data()) { return false; }

        vector0 = std::move(vector1);

        if (vector0.Capacity() != 0) { return false; }
        if (vector0.Data()) { return false; }
    }
    {
        Vector<size_t> vector0{ 0, 1, 2, 3, 4 };
        Vector<size_t> vector1(std::move(vector0));

        if (!vector0.IsEmpty()) { return false; }
        if (vector0.Capacity() != 0) { return false; }
        if (vector0.Data()) { return false; }

        for (size_t i = 0; i < vector1.Size(); ++i)
        {
            if (vector1[i] != i) { return false; }
        }

        Vector<size_t> vector2{ 5, 6, 7, 8, 9 };
        vector0 = std::move(vector2);

        if (!vector2.IsEmpty()) { return false; }
        if (vector2.Capacity() != 0) { return false; }
        if (vector2.Data()) { return false; }

        for (size_t i = 0; i < vector2.Size(); ++i)
        {
            if (vector0[i] != i + 5) { return false; }
        }
    }
    {
        Vector<std::string> vector0{ "0", "1", "2", "3", "4" };
        Vector<std::string> vector1(std::move(vector0));

        if (!vector0.IsEmpty()) { return false; }
        if (vector0.Capacity() != 0) { return false; }
        if (vector0.Data()) { return false; }

        for (size_t i = 0; i < vector1.Size(); ++i)
        {
            if (vector1[i] != std::to_string(i)) { return false; }
        }

        Vector<std::string> vector2{ "5", "6", "7", "8", "9" };
        vector0 = std::move(vector2);

        if (!vector2.IsEmpty()) { return false; }
        if (vector2.Capacity() != 0) { return false; }
        if (vector2.Data()) { return false; }

        for (size_t i = 0; i < vector0.Size(); ++i)
        {
            if (vector0[i] != std::to_string(i + 5)) { return false; }
        }
    }
    {
        Vector<TestStruct> vector0{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
        Vector<TestStruct> vector1(std::move(vector0));

        if (!vector0.IsEmpty()) { return false; }
        if (vector0.Capacity() != 0) { return false; }
        if (vector0.Data()) { return false; }

        for (size_t i = 0; i < vector0.Size(); ++i)
        {
            if (vector1[i] != TestStruct((float)i)) { return false; }
        }

        Vector<TestStruct> vector2{ TestStruct(5.0f), TestStruct(6.0f), TestStruct(7.0f), TestStruct(8.0f), TestStruct(9.0f) };
        vector0 = std::move(vector2);

        if (!vector2.IsEmpty()) { return false; }
        if (vector2.Capacity() != 0) { return false; }
        if (vector2.Data()) { return false; }

        for (size_t i = 0; i < vector0.Size(); ++i)
        {
            if (vector0[i] != TestStruct((float)(i + 5))) { return false; }
        }
    }

    return true;
}

bool VectorTest::Operators()
{
    //operator==(const Vector& other) const
    //operator!=(const Vector& other) const
    //operator<(const Vector& other) const
    //operator<=(const Vector& other) const
    //operator>(const Vector& other) const
    //operator>=(const Vector& other) const

    {
        Vector<size_t> vector0{ 0, 1, 2, 3, 4 };
        Vector<size_t> vector1{ 0, 1, 2, 3, 4 };

        if (vector0 != vector1) { return false; }
        if (vector0 < vector1) { return false; }
        if (vector0 > vector1) { return false; }
        if (!(vector0 <= vector1)) { return false; }
        if (!(vector0 >= vector1)) { return false; }
    }
    {
        Vector<std::string> vector0{ "0", "1", "2", "3", "4" };
        Vector<std::string> vector1{ "0", "1", "2", "3", "4" };

        if (vector0 != vector1) { return false; }
        if (vector0 < vector1) { return false; }
        if (vector0 > vector1) { return false; }
        if (!(vector0 <= vector1)) { return false; }
        if (!(vector0 >= vector1)) { return false; }
    }
    {
        Vector<TestStruct> vector0{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };
        Vector<TestStruct> vector1{ TestStruct(0.0f), TestStruct(1.0f), TestStruct(2.0f), TestStruct(3.0f), TestStruct(4.0f) };

        if (vector0 != vector1) { return false; }
        if (vector0 < vector1) { return false; }
        if (vector0 > vector1) { return false; }
        if (!(vector0 <= vector1)) { return false; }
        if (!(vector0 >= vector1)) { return false; }
    }

    return true;
}

bool VectorTest::Reserve()
{
    //Reserve(size_t capacity)

    {
        Vector<size_t> vector(10);
        if (vector.Capacity() != 10) { return false; }

        vector.Reserve(5);
        if (vector.Capacity() != 10) { return false; }

        for (size_t i = 0; i < 11; ++i)
        {
            vector.PushBack(i);
        }
        if (vector.Capacity() != 20) { return false; }
        
        vector.Reserve(35);
        if (vector.Capacity() != 35) { return false; }
    }
    {
        Vector<std::string> vector(10);
        if (vector.Capacity() != 10) { return false; }

        vector.Reserve(5);
        if (vector.Capacity() != 10) { return false; }

        for (size_t i = 0; i < 11; ++i)
        {
            vector.PushBack(std::to_string(i));
        }
        if (vector.Capacity() != 20) { return false; }

        vector.Reserve(35);
        if (vector.Capacity() != 35) { return false; }
    }
    {
        Vector<TestStruct> vector(10);
        if (vector.Capacity() != 10) { return false; }

        vector.Reserve(5);
        if (vector.Capacity() != 10) { return false; }

        for (size_t i = 0; i < 11; ++i)
        {
            vector.PushBack(TestStruct((float)i));
        }
        if (vector.Capacity() != 20) { return false; }

        vector.Reserve(35);
        if (vector.Capacity() != 35) { return false; }
    }

    return true;
}

bool VectorTest::Shrink()
{
    //Shrink()

    {
        Vector<size_t> vector;
        vector.Shrink();

        vector.PushBack(0);
        vector.Shrink();
        if (vector.Capacity() != 1) { return false; }

        vector.PushBack(1);
        if (vector.Capacity() != 2) { return false; }
        vector.PushBack(2);
        if (vector.Capacity() != 4) { return false; }

        vector.Clear();
        vector.Shrink();
        if (vector.Capacity() > 0) { return false; }
    }
    {
        Vector<std::string> vector;
        vector.Shrink();

        vector.PushBack("0");
        vector.Shrink();
        if (vector.Capacity() != 1) { return false; }

        vector.PushBack("1");
        if (vector.Capacity() != 2) { return false; }
        vector.PushBack("2");
        if (vector.Capacity() != 4) { return false; }

        vector.Clear();
        vector.Shrink();
        if (vector.Capacity() > 0) { return false; }
    }
    {
        Vector<TestStruct> vector;
        vector.Shrink();

        vector.PushBack(0.0f);
        vector.Shrink();
        if (vector.Capacity() != 1) { return false; }

        vector.PushBack(1.0f);
        if (vector.Capacity() != 2) { return false; }
        vector.PushBack(2.0f);
        if (vector.Capacity() != 4) { return false; }

        vector.Clear();
        vector.Shrink();
        if (vector.Capacity() > 0) { return false; }
    }

    return true;
}

bool VectorTest::Resize()
{
    //Resize(size_t capacity)

    {
        Vector<size_t> vector;
        vector.Resize(10);

        if (vector.Capacity() != 10) { return false; }
        if (!vector.Data()) { return false; }

        for (size_t i = 0; i < vector.Capacity(); ++i)
        {
            vector.PushBack(i);
        }

        size_t* data = vector.Data();
        vector.Resize(10);
        if (data != vector.Data()) { return false; }

        vector.Resize(5);
        for (size_t i = 0; i < vector.Size(); ++i)
        {
            if (vector[i] != i) { return false; }
        }

        vector.Resize(10);
        for (size_t i = 0; i < 5; ++i)
        {
            vector.PushBack(5 + i);
        }
        for (size_t i = 0; i < vector.Size(); ++i)
        {
            if (vector[i] != i) { return false; }
        }

        vector.Resize(0);
        if (vector.Capacity() != 0) { return false; }
        if (vector.Data()) { return false; }
    }
    {
        Vector<std::string> vector;
        vector.Resize(10);

        if (vector.Capacity() != 10) { return false; }
        if (!vector.Data()) { return false; }

        for (size_t i = 0; i < vector.Capacity(); ++i)
        {
            vector.PushBack(std::to_string(i));
        }

        std::string* data = vector.Data();
        vector.Resize(10);
        if (data != vector.Data()) { return false; }

        vector.Resize(5);
        for (size_t i = 0; i < vector.Size(); ++i)
        {
            if (vector[i] != std::to_string(i)) { return false; }
        }

        vector.Resize(10);
        for (size_t i = 0; i < 5; ++i)
        {
            vector.PushBack(std::to_string(5 + i));
        }
        for (size_t i = 0; i < vector.Size(); ++i)
        {
            if (vector[i] != std::to_string(i)) { return false; }
        }

        vector.Resize(0);
        if (vector.Capacity() != 0) { return false; }
        if (vector.Data()) { return false; }
    }
    {
        Vector<TestStruct> vector;
        vector.Resize(10);

        if (vector.Capacity() != 10) { return false; }
        if (!vector.Data()) { return false; }

        for (size_t i = 0; i < vector.Capacity(); ++i)
        {
            vector.PushBack(TestStruct((float)i));
        }

        TestStruct* data = vector.Data();
        vector.Resize(10);
        if (data != vector.Data()) { return false; }

        vector.Resize(5);
        for (size_t i = 0; i < vector.Size(); ++i)
        {
            if (vector[i] != TestStruct((float)i)) { return false; }
        }

        vector.Resize(10);
        for (size_t i = 0; i < 5; ++i)
        {
            vector.PushBack(TestStruct((float)(5 + i)));
        }
        for (size_t i = 0; i < vector.Size(); ++i)
        {
            if (vector[i] != TestStruct((float)i)) { return false; }
        }

        vector.Resize(0);
        if (vector.Capacity() != 0) { return false; }
        if (vector.Data()) { return false; }
    }

    return true;
}

bool VectorTest::PushBack()
{
    //PushBack(const T& element)
    //PushBack(T&& element)

    {
        Vector<size_t> vector;
        for (size_t i = 0; i < 10; ++i)
        {
            vector.PushBack(i);
        }
        for (size_t i = 0; i < vector.Size(); ++i)
        {
            if (vector[i] != i) { return false; }
        }

        for (size_t i = 0; i < 10; ++i)
        {
            size_t aux = i + 10;
            vector.PushBack(std::move(aux));
        }
        for (size_t i = 0; i < vector.Size(); ++i)
        {
            if (vector[i] != i) { return false; }
        }
    }
    {
        Vector<std::string> vector;
        for (size_t i = 0; i < 10; ++i)
        {
            vector.PushBack(std::to_string(i));
        }
        for (size_t i = 0; i < vector.Size(); ++i)
        {
            if (vector[i] != std::to_string(i)) { return false; }
        }

        for (size_t i = 0; i < 10; ++i)
        {
            std::string tmp = std::to_string(i);
            vector.PushBack(std::move(tmp));
        }
        for (size_t i = 10; i < vector.Size(); ++i)
        {
            if (vector[i] != std::to_string(i - 10)) { return false; }
        }
    }
    {
        Vector<TestStruct> vector;
        for (size_t i = 0; i < 10; ++i)
        {
            vector.PushBack(TestStruct((float)i));
        }
        for (size_t i = 0; i < vector.Size(); ++i)
        {
            if (vector[i] != TestStruct((float)i)) { return false; }
        }

        for (size_t i = 0; i < 10; ++i)
        {
            TestStruct tmp((float)i);
            vector.PushBack(std::move(tmp));
        }
        for (size_t i = 10; i < vector.Size(); ++i)
        {
            if (vector[i] != TestStruct((float)(i - 10))) { return false; }
        }
    }

    return true;
}

bool VectorTest::Insert()
{
    //Insert(size_t index, const T& element)
    //Insert(size_t index, T&& element)
    //Insert(iterator position, const T& element)
    //Insert(iterator position, T&& element)
    //Insert(reverse_iterator position, const T& element)
    //Insert(reverse_iterator position, T&& element)

    {
        {
            Vector<size_t> vector;
            for (size_t i = 0; i < 10; ++i)
            {
                size_t aux = i;
                vector.Insert(1, aux);
            }
            if (vector.Front() != 0) { return false; }
            for (size_t i = 1; i < vector.Size(); ++i)
            {
                if (vector[i] != vector.Size() - i) { return false; }
            }
        }
        {
            Vector<size_t> vector;
            for (size_t i = 0; i < 10; ++i)
            {
                size_t aux = i;
                vector.Insert(1, std::move(aux));
            }

            if (vector.Front() != 0) { return false; }
            for (size_t i = 1; i < vector.Size(); ++i)
            {
                if (vector[i] != vector.Size() - i) { return false; }
            }
        }
        {
            Vector<size_t> vector;
            vector.PushBack(0);
            vector.PushBack(1);
            Vector<size_t>::iterator it = vector.begin();
            ++it;
            for (size_t i = 2; i < 10; ++i)
            {
                size_t aux = i;
                it = vector.Insert(it, aux);
            }
            if (vector.Front() != 0) { return false; }
            for (size_t i = 1; i < vector.Size(); ++i)
            {
                if (vector[i] != vector.Size() - i) { return false; }
            }
        }
        {
            Vector<size_t> vector;
            vector.PushBack(0);
            vector.PushBack(1);
            Vector<size_t>::iterator it = vector.begin();
            ++it;
            for (size_t i = 2; i < 10; ++i)
            {
                size_t aux = i;
                it = vector.Insert(it, std::move(aux));
            }

            if (vector.Front() != 0) { return false; }
            for (size_t i = 1; i < vector.Size(); ++i)
            {
                if (vector[i] != vector.Size() - i) { return false; }
            }
        }
        {
            Vector<size_t> vector;
            vector.PushBack(0);
            vector.PushBack(1);
            Vector<size_t>::reverse_iterator it = vector.rbegin();
            for (size_t i = 2; i < 10; ++i)
            {
                size_t aux = i;
                it = vector.Insert(it, aux);
            }
            if (vector.Front() != 0) { return false; }
            for (size_t i = 1; i < vector.Size(); ++i)
            {
                if (vector[i] != vector.Size() - i) { return false; }
            }
        }
        {
            Vector<size_t> vector;
            vector.PushBack(0);
            vector.PushBack(1);
            Vector<size_t>::reverse_iterator it = vector.rbegin();
            for (size_t i = 2; i < 10; ++i)
            {
                size_t aux = i;
                it = vector.Insert(it, std::move(aux));
            }
            if (vector.Front() != 0) { return false; }
            for (size_t i = 1; i < vector.Size(); ++i)
            {
                if (vector[i] != vector.Size() - i) { return false; }
            }
        }
    }
    {
        {
            Vector<std::string> vector;
            for (size_t i = 0; i < 10; ++i)
            {
                size_t aux = i;
                vector.Insert(1, std::to_string(aux));
            }
            if (vector.Front() != "0") { return false; }
            for (size_t i = 1; i < vector.Size(); ++i)
            {
                if (vector[i] != std::to_string(vector.Size() - i)) { return false; }
            }
        }
        {
            Vector<std::string> vector;
            for (size_t i = 0; i < 10; ++i)
            {
                size_t aux = i;
                vector.Insert(1, std::move(std::to_string(aux)));
            }

            if (vector.Front() != "0") { return false; }
            for (size_t i = 1; i < vector.Size(); ++i)
            {
                if (vector[i] != std::to_string(vector.Size() - i)) { return false; }
            }
        }
        {
            Vector<std::string> vector;
            vector.PushBack("0");
            vector.PushBack("1");
            Vector<std::string>::iterator it = vector.begin();
            ++it;
            for (size_t i = 2; i < 10; ++i)
            {
                size_t aux = i;
                it = vector.Insert(it, std::to_string(aux));
            }

            if (vector.Front() != "0") { return false; }
            for (size_t i = 1; i < vector.Size(); ++i)
            {
                if (vector[i] != std::to_string(vector.Size() - i)) { return false; }
            }
        }
        {
            Vector<std::string> vector;
            vector.PushBack("0");
            vector.PushBack("1");
            Vector<std::string>::iterator it = vector.begin();
            ++it;
            for (size_t i = 2; i < 10; ++i)
            {
                size_t aux = i;
                it = vector.Insert(it, std::to_string(std::move(aux)));
            }

            if (vector.Front() != "0") { return false; }
            for (size_t i = 1; i < vector.Size(); ++i)
            {
                if (vector[i] != std::to_string(vector.Size() - i)) { return false; }
            }
        }
        {
            Vector<std::string> vector;
            vector.PushBack("0");
            vector.PushBack("1");
            Vector<std::string>::reverse_iterator it = vector.rbegin();
            for (size_t i = 2; i < 10; ++i)
            {
                size_t aux = i;
                it = vector.Insert(it, std::to_string(aux));
            }
            if (vector.Front() != "0") { return false; }
            for (size_t i = 1; i < vector.Size(); ++i)
            {
                if (vector[i] != std::to_string(vector.Size() - i)) { return false; }
            }
        }
        {
            Vector<std::string> vector;
            vector.PushBack("0");
            vector.PushBack("1");
            Vector<std::string>::reverse_iterator it = vector.rbegin();
            for (size_t i = 2; i < 10; ++i)
            {
                size_t aux = i;
                it = vector.Insert(it, std::to_string(std::move(aux)));
            }
            if (vector.Front() != "0") { return false; }
            for (size_t i = 1; i < vector.Size(); ++i)
            {
                if (vector[i] != std::to_string(vector.Size() - i)) { return false; }
            }
        }
    }
    {
        {
            Vector<TestStruct> vector;
            for (size_t i = 0; i < 10; ++i)
            {
                size_t aux = i;
                vector.Insert(1, TestStruct((float)aux));
            }
            if (vector.Front() != 0) { return false; }
            for (size_t i = 1; i < vector.Size(); ++i)
            {
                if (vector[i] != TestStruct((float)(vector.Size() - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector;
            for (size_t i = 0; i < 10; ++i)
            {
                size_t aux = i;
                vector.Insert(1, std::move(TestStruct((float)aux)));
            }

            if (vector.Front() != 0) { return false; }
            for (size_t i = 1; i < vector.Size(); ++i)
            {
                if (vector[i] != TestStruct((float)(vector.Size() - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector;
            vector.PushBack(TestStruct(0.0f));
            vector.PushBack(TestStruct(1.0f));
            Vector<TestStruct>::iterator it = vector.begin();
            ++it;
            for (size_t i = 2; i < 10; ++i)
            {
                size_t aux = i;
                it = vector.Insert(it, TestStruct((float)aux));
            }

            if (vector.Front() != 0) { return false; }
            for (size_t i = 1; i < vector.Size(); ++i)
            {
                if (vector[i] != TestStruct((float)(vector.Size() - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector;
            vector.PushBack(TestStruct(0.0f));
            vector.PushBack(TestStruct(1.0f));
            Vector<TestStruct>::iterator it = vector.begin();
            ++it;
            for (size_t i = 2; i < 10; ++i)
            {
                size_t aux = i;
                it = vector.Insert(it, std::move(TestStruct((float)aux)));
            }

            if (vector.Front() != 0) { return false; }
            for (size_t i = 1; i < vector.Size(); ++i)
            {
                if (vector[i] != TestStruct((float)(vector.Size() - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector;
            vector.PushBack(TestStruct(0.0f));
            vector.PushBack(TestStruct(1.0f));
            Vector<TestStruct>::reverse_iterator it = vector.rbegin();
            for (size_t i = 2; i < 10; ++i)
            {
                size_t aux = i;
                it = vector.Insert(it, TestStruct((float)aux));
            }
            if (vector.Front() != 0) { return false; }
            for (size_t i = 1; i < vector.Size(); ++i)
            {
                if (vector[i] != TestStruct((float)(vector.Size() - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector;
            vector.PushBack(TestStruct(0.0f));
            vector.PushBack(TestStruct(1.0f));
            Vector<TestStruct>::reverse_iterator it = vector.rbegin();
            for (size_t i = 2; i < 10; ++i)
            {
                size_t aux = i;
                it = vector.Insert(it, std::move(TestStruct((float)aux)));
            }
            if (vector.Front() != 0) { return false; }
            for (size_t i = 1; i < vector.Size(); ++i)
            {
                if (vector[i] != TestStruct((float)(vector.Size() - i))) { return false; }
            }
        }
    }

    return true;
}

bool VectorTest::EmplaceBack()
{
    //EmplaceBack(Args&&... args)

    {
        Vector<size_t> vector;
        for (size_t i = 0; i < 10; ++i)
        {
            vector.EmplaceBack(i);
        }
        for (size_t i = 0; i < vector.Size(); ++i)
        {
            if (vector[i] != i) { return false; }
        }
    }
    {
        Vector<std::string> vector;
        for (size_t i = 0; i < 10; ++i)
        {
            char n[5];
            _itoa_s((int)i, n, 10);
            vector.EmplaceBack(n);
        }
        for (size_t i = 0; i < vector.Size(); ++i)
        {
            if (vector[i] != std::to_string(i)) { return false; }
        }
    }
    {
        Vector<TestStruct> vector;
        for (size_t i = 0; i < 10; ++i)
        {
            float value = (float)i;
            vector.EmplaceBack(value, value, value);
        }
        for (size_t i = 0; i < vector.Size(); ++i)
        {
            if (vector[i] != TestStruct((float)i)) { return false; }
        }
    }

    return true;
}

bool VectorTest::Emplace()
{
    //Emplace(size_t index, Args&&... args)
    //Emplace(iterator position, Args&&... args)
    //Emplace(reverse_iterator position, Args&&... args)

    {
        {
            Vector<size_t> vector;
            for (size_t i = 0; i < 10; ++i)
            {
                size_t aux = i;
                vector.Emplace(1, aux);
            }
            if (vector.Front() != 0) { return false; }
            for (size_t i = 1; i < vector.Size(); ++i)
            {
                if (vector[i] != vector.Size() - i) { return false; }
            }
        }
        {
            Vector<size_t> vector;
            vector.PushBack(0);
            vector.PushBack(1);
            Vector<size_t>::iterator it = vector.begin();
            ++it;
            for (size_t i = 2; i < 10; ++i)
            {
                size_t aux = i;
                it = vector.Emplace(it, aux);
            }
            if (vector.Front() != 0) { return false; }
            for (size_t i = 1; i < vector.Size(); ++i)
            {
                if (vector[i] != vector.Size() - i) { return false; }
            }
        }
        {
            Vector<size_t> vector;
            vector.PushBack(0);
            vector.PushBack(1);
            Vector<size_t>::reverse_iterator it = vector.rbegin();
            for (size_t i = 2; i < 10; ++i)
            {
                size_t aux = i;
                it = vector.Emplace(it, aux);
            }
            if (vector.Front() != 0) { return false; }
            for (size_t i = 1; i < vector.Size(); ++i)
            {
                if (vector[i] != vector.Size() - i) { return false; }
            }
        }
    }
    {
        {
            Vector<std::string> vector;
            for (size_t i = 0; i < 10; ++i)
            {
                size_t aux = i;
                vector.Emplace(1, std::to_string(aux));
            }
            if (vector.Front() != "0") { return false; }
            for (size_t i = 1; i < vector.Size(); ++i)
            {
                if (vector[i] != std::to_string(vector.Size() - i)) { return false; }
            }
        }
        {
            Vector<std::string> vector;
            vector.PushBack("0");
            vector.PushBack("1");
            Vector<std::string>::iterator it = vector.begin();
            ++it;
            for (size_t i = 2; i < 10; ++i)
            {
                size_t aux = i;
                it = vector.Emplace(it, std::to_string(aux));
            }

            if (vector.Front() != "0") { return false; }
            for (size_t i = 1; i < vector.Size(); ++i)
            {
                if (vector[i] != std::to_string(vector.Size() - i)) { return false; }
            }
        }
        {
            Vector<std::string> vector;
            vector.PushBack("0");
            vector.PushBack("1");
            Vector<std::string>::reverse_iterator it = vector.rbegin();
            for (size_t i = 2; i < 10; ++i)
            {
                size_t aux = i;
                it = vector.Emplace(it, std::to_string(aux));
            }
            if (vector.Front() != "0") { return false; }
            for (size_t i = 1; i < vector.Size(); ++i)
            {
                if (vector[i] != std::to_string(vector.Size() - i)) { return false; }
            }
        }
    }
    {
        {
            Vector<TestStruct> vector;
            for (size_t i = 0; i < 10; ++i)
            {
                size_t aux = i;
                vector.Emplace(1, (float)aux);
            }
            if (vector.Front() != 0) { return false; }
            for (size_t i = 1; i < vector.Size(); ++i)
            {
                if (vector[i] != TestStruct((float)(vector.Size() - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector;
            vector.PushBack(TestStruct(0.0f));
            vector.PushBack(TestStruct(1.0f));
            Vector<TestStruct>::iterator it = vector.begin();
            ++it;
            for (size_t i = 2; i < 10; ++i)
            {
                size_t aux = i;
                it = vector.Emplace(it, (float)aux);
            }

            if (vector.Front() != 0) { return false; }
            for (size_t i = 1; i < vector.Size(); ++i)
            {
                if (vector[i] != TestStruct((float)(vector.Size() - i))) { return false; }
            }
        }
        {
            Vector<TestStruct> vector;
            vector.PushBack(TestStruct(0.0f));
            vector.PushBack(TestStruct(1.0f));
            Vector<TestStruct>::reverse_iterator it = vector.rbegin();
            for (size_t i = 2; i < 10; ++i)
            {
                size_t aux = i;
                it = vector.Emplace(it, (float)aux);
            }
            if (vector.Front() != 0) { return false; }
            for (size_t i = 1; i < vector.Size(); ++i)
            {
                if (vector[i] != TestStruct((float)(vector.Size() - i))) { return false; }
            }
        }
    }

    return true;
}

bool VectorTest::PopBack()
{
    //PopBack()

    {
        Vector<size_t> vector;
        for (size_t i = 0; i < 10; ++i)
        {
            vector.PushBack(i);
        }
        vector.PopBack();

        if (vector.Back() != 8) { return false; }
        if (vector.Size() != 9) { return false; }

        for (size_t i = 0; i < 10; ++i)
        {
            vector.PopBack();
        }
        if (vector.Size() != 0) { return false; }
    }
    {
        Vector<std::string> vector;
        for (size_t i = 0; i < 10; ++i)
        {
            vector.PushBack(std::to_string(i));
        }
        vector.PopBack();

        if (vector.Back() !="8") { return false; }
        if (vector.Size() != 9) { return false; }

        for (size_t i = 0; i < 10; ++i)
        {
            vector.PopBack();
        }
        if (vector.Size() != 0) { return false; }
    }
    {
        Vector<TestStruct> vector;
        for (size_t i = 0; i < 10; ++i)
        {
            vector.PushBack(TestStruct((float)i));
        }
        vector.PopBack();

        if (vector.Back() != TestStruct((float)8)) { return false; }
        if (vector.Size() != 9) { return false; }

        for (size_t i = 0; i < 10; ++i)
        {
            vector.PopBack();
        }
        if (vector.Size() != 0) { return false; }
    }

    return true;
}

bool VectorTest::Erase()
{
    //Erase(size_t index)
    //Erase(iterator position)
    //Erase(reverse_iterator position)
    {
        {
            Vector<size_t> vector;
            for (size_t i = 0; i < 10; ++i)
            {
                vector.PushBack(i);
            }
            vector.Erase(0);
            if (vector.Front() == 0) { return false; }
            size_t vector_size = vector.Size();
            for (size_t i = 0; i < vector_size; ++i)
            {
                Vector<size_t>::iterator it = vector.Erase(1);
                if (it == vector.end()) { break; }
                if (vector[1] != (3 + i)) { return false; }
            }
            vector.Erase(0);
            if (!vector.IsEmpty()) { return false; }
        }
        {
            Vector<size_t> vector;
            for (size_t i = 0; i < 10; ++i)
            {
                vector.PushBack(i);
            }
            vector.Erase(0);
            if (vector.Front() == 0) { return false; }
            size_t vector_size = vector.Size();
            for (size_t i = 0; i < vector_size; ++i)
            {
                Vector<size_t>::iterator it(vector.begin());
                vector.Erase(++it);
                if (it == vector.end()) { break; }
                if (vector[1] != (3 + i)) { return false; }
            }
            vector.Erase(0);
            if (!vector.IsEmpty()) { return false; }
        }
        {
            Vector<size_t> vector;
            for (size_t i = 0; i < 10; ++i)
            {
                vector.PushBack(i);
            }
            vector.Erase(0);
            if (vector.Front() == 0) { return false; }
            size_t vector_size = vector.Size();
            for (size_t i = 0; i < vector_size; ++i)
            {
                Vector<size_t>::reverse_iterator it(vector.rbegin());
                it = vector.Erase(++it);
                if (++it == vector.rend()) { break; }
                if (vector[vector.Size() - 2] != (7 - i)) { return false; }
            }
            vector.Erase(0);
            if (!vector.IsEmpty()) { return false; }
        }
    }
    {
        {
            Vector<std::string> vector;
            for (size_t i = 0; i < 10; ++i)
            {
                vector.PushBack(std::to_string(i));
            }
            vector.Erase(0);
            if (vector.Front() == "0") { return false; }
            size_t vector_size = vector.Size();
            for (size_t i = 0; i < vector_size; ++i)
            {
                Vector<std::string>::iterator it = vector.Erase(1);
                if (it == vector.end()) { break; }
                if (vector[1] != std::to_string(3 + i)) { return false; }
            }
            vector.Erase(0);
            if (!vector.IsEmpty()) { return false; }
        }
        {
            Vector<std::string> vector;
            for (size_t i = 0; i < 10; ++i)
            {
                vector.PushBack(std::to_string(i));
            }
            vector.Erase(0);
            if (vector.Front() == "0") { return false; }
            size_t vector_size = vector.Size();
            for (size_t i = 0; i < vector_size; ++i)
            {
                Vector<std::string>::iterator it(vector.begin());
                vector.Erase(++it);
                if (it == vector.end()) { break; }
                if (vector[1] != std::to_string(3 + i)) { return false; }
            }
            vector.Erase(0);
            if (!vector.IsEmpty()) { return false; }
        }
        {
            Vector<std::string> vector;
            for (size_t i = 0; i < 10; ++i)
            {
                vector.PushBack(std::to_string(i));
            }
            vector.Erase(0);
            if (vector.Front() == "0") { return false; }
            size_t vector_size = vector.Size();
            for (size_t i = 0; i < vector_size; ++i)
            {
                Vector<std::string>::reverse_iterator it(vector.rbegin());
                it = vector.Erase(++it);
                if (++it == vector.rend()) { break; }
                if (vector[vector.Size() - 2] != std::to_string(7 - i)) { return false; }
            }
            vector.Erase(0);
            if (!vector.IsEmpty()) { return false; }
        }
    }
    {
        {
            Vector<TestStruct> vector;
            for (size_t i = 0; i < 10; ++i)
            {
                vector.PushBack(TestStruct((float)i));
            }
            vector.Erase(0);
            if (vector.Front() == TestStruct()) { return false; }
            size_t vector_size = vector.Size();
            for (size_t i = 0; i < vector_size; ++i)
            {
                Vector<TestStruct>::iterator it = vector.Erase(1);
                if (it == vector.end()) { break; }
                if (vector[1] != TestStruct((float)(3 + i))) { return false; }
            }
            vector.Erase(0);
            if (!vector.IsEmpty()) { return false; }
        }
        {
            Vector<TestStruct> vector;
            for (size_t i = 0; i < 10; ++i)
            {
                vector.PushBack(TestStruct((float)i));
            }
            vector.Erase(0);
            if (vector.Front() == TestStruct()) { return false; }
            size_t vector_size = vector.Size();
            for (size_t i = 0; i < vector_size; ++i)
            {
                Vector<TestStruct>::iterator it(vector.begin());
                vector.Erase(++it);
                if (it == vector.end()) { break; }
                if (vector[1] != TestStruct((float)(3 + i))) { return false; }
            }
            vector.Erase(0);
            if (!vector.IsEmpty()) { return false; }
        }
        {
            Vector<TestStruct> vector;
            for (size_t i = 0; i < 10; ++i)
            {
                vector.PushBack(TestStruct((float)i));
            }
            vector.Erase(0);
            if (vector.Front() == TestStruct()) { return false; }
            size_t vector_size = vector.Size();
            for (size_t i = 0; i < vector_size; ++i)
            {
                Vector<TestStruct>::reverse_iterator it(vector.rbegin());
                it = vector.Erase(++it);
                if (++it == vector.rend()) { break; }
                if (vector[vector.Size() - 2] != TestStruct((float)(7 - i))) { return false; }
            }
            vector.Erase(0);
            if (!vector.IsEmpty()) { return false; }
        }
    }

    return true;
}

bool VectorTest::Clear()
{
    //void Clear()

    {
        Vector<size_t> vector;
        vector.Clear();
        for (size_t i = 0; i < 10; ++i)
        {
            vector.PushBack(i);
        }
        vector.Clear();
        if (!vector.IsEmpty()) { return false; }
    }
    {
        Vector<std::string> vector;
        vector.Clear();
        for (size_t i = 0; i < 10; ++i)
        {
            vector.PushBack(std::to_string(i));
        }
        vector.Clear();
        if (!vector.IsEmpty()) { return false; }
    }
    {
        Vector<TestStruct> vector;
        vector.Clear();
        for (size_t i = 0; i < 10; ++i)
        {
            vector.PushBack(TestStruct((float)i));
        }
        vector.Clear();
        if (!vector.IsEmpty()) { return false; }
    }

    return true;
}

bool VectorTest::Append()
{
    //Append(const Vector& other)
    //Append(Vector&& other)

    {
        {
            Vector<size_t> vector0;
            Vector<size_t> vector1;
            Vector<size_t> vector2;
            Vector<size_t> vector3;

            for (size_t i = 0; i < 10; ++i)
            {
                vector1.PushBack(i);
                vector2.PushBack(10 + i);
            }

            vector0.Append(vector1);
            vector0.Append(vector2);
            vector0.Append(vector3);

            if (vector0.Size() != 20) { return false; }
            if (vector1.Size() != 10) { return false; }
            if (vector2.Size() != 10) { return false; }
            if (vector3.Size() != 0) { return false; }

            for (size_t i = 0; i < vector0.Size(); ++i)
            {
                if (vector0[i] != i) { return false; }
            }
        }
        {
            Vector<size_t> vector0;
            Vector<size_t> vector1;
            Vector<size_t> vector2;
            Vector<size_t> vector3;

            for (size_t i = 0; i < 10; ++i)
            {
                vector1.PushBack(i);
                vector2.PushBack(10 + i);
            }

            vector0.Append(std::move(vector1));
            vector0.Append(std::move(vector2));
            vector0.Append(std::move(vector3));

            if (vector0.Size() != 20) { return false; }
            if (vector1.Size() != 0) { return false; }
            if (vector2.Size() != 0) { return false; }
            if (vector3.Size() != 0) { return false; }

            for (size_t i = 0; i < vector0.Size(); ++i)
            {
                if (vector0[i] != i) { return false; }
            }
        }
    }
    {
        {
            Vector<std::string> vector0;
            Vector<std::string> vector1;
            Vector<std::string> vector2;
            Vector<std::string> vector3;

            for (size_t i = 0; i < 10; ++i)
            {
                vector1.PushBack(std::to_string(i));
                vector2.PushBack(std::to_string(10 + i));
            }

            vector0.Append(vector1);
            vector0.Append(vector2);
            vector0.Append(vector3);

            if (vector0.Size() != 20) { return false; }
            if (vector1.Size() != 10) { return false; }
            if (vector2.Size() != 10) { return false; }
            if (vector3.Size() != 0) { return false; }

            for (size_t i = 0; i < vector0.Size(); ++i)
            {
                if (vector0[i] != std::to_string(i)) { return false; }
            }
        }
        {
            Vector<std::string> vector0;
            Vector<std::string> vector1;
            Vector<std::string> vector2;
            Vector<std::string> vector3;

            for (size_t i = 0; i < 10; ++i)
            {
                vector1.PushBack(std::to_string(i));
                vector2.PushBack(std::to_string(10 + i));
            }

            vector0.Append(std::move(vector1));
            vector0.Append(std::move(vector2));
            vector0.Append(std::move(vector3));

            if (vector0.Size() != 20) { return false; }
            if (vector1.Size() != 0) { return false; }
            if (vector2.Size() != 0) { return false; }
            if (vector3.Size() != 0) { return false; }

            for (size_t i = 0; i < vector0.Size(); ++i)
            {
                if (vector0[i] != std::to_string(i)) { return false; }
            }
        }
    }
    {
        {
            Vector<TestStruct> vector0;
            Vector<TestStruct> vector1;
            Vector<TestStruct> vector2;
            Vector<TestStruct> vector3;

            for (size_t i = 0; i < 10; ++i)
            {
                vector1.PushBack(TestStruct((float)i));
                vector2.PushBack(TestStruct((float)(10 + i)));
            }

            vector0.Append(vector1);
            vector0.Append(vector2);
            vector0.Append(vector3);

            if (vector0.Size() != 20) { return false; }
            if (vector1.Size() != 10) { return false; }
            if (vector2.Size() != 10) { return false; }
            if (vector3.Size() != 0) { return false; }

            for (size_t i = 0; i < vector0.Size(); ++i)
            {
                if (vector0[i] != TestStruct((float)i)) { return false; }
            }
        }
        {
            Vector<TestStruct> vector0;
            Vector<TestStruct> vector1;
            Vector<TestStruct> vector2;
            Vector<TestStruct> vector3;

            for (size_t i = 0; i < 10; ++i)
            {
                vector1.PushBack(TestStruct((float)i));
                vector2.PushBack(TestStruct((float)(10 + i)));
            }

            vector0.Append(std::move(vector1));
            vector0.Append(std::move(vector2));
            vector0.Append(std::move(vector3));

            if (vector0.Size() != 20) { return false; }
            if (vector1.Size() != 0) { return false; }
            if (vector2.Size() != 0) { return false; }
            if (vector3.Size() != 0) { return false; }

            for (size_t i = 0; i < vector0.Size(); ++i)
            {
                if (vector0[i] != TestStruct((float)i)) { return false; }
            }
        }
    }

    return true;
}

bool VectorTest::Swap()
{
    //Swap(Vector& other)

    {
        Vector<size_t> vector0;
        Vector<size_t> vector1;

        for (size_t i = 0; i < 10; ++i)
        {
            vector0.PushBack(i);
            vector1.PushBack(9 - i);
        }
        vector0.Swap(vector1);

        for (size_t i = 0; i < 10; ++i)
        {
            if (vector0[i] != (9 - i)) { return false; }
            if (vector1[i] != i) { return false; }
        }
    }
    {
        Vector<std::string> vector0;
        Vector<std::string> vector1;

        for (size_t i = 0; i < 10; ++i)
        {
            vector0.PushBack(std::to_string(i));
            vector1.PushBack(std::to_string(9 - i));
        }

        vector0.Swap(vector1);

        for (size_t i = 0; i < 10; ++i)
        {
            if (vector0[i] != std::to_string(9 - i)) { return false; }
            if (vector1[i] != std::to_string(i)) { return false; }
        }
    }
    {
        Vector<TestStruct> vector0;
        Vector<TestStruct> vector1;

        for (size_t i = 0; i < 10; ++i)
        {
            vector0.PushBack(TestStruct((float)i));
            vector1.PushBack(TestStruct((float)(9 - i)));
        }

        vector0.Swap(vector1);

        for (size_t i = 0; i < 10; ++i)
        {
            if (vector0[i] != TestStruct((float)(9 - i))) { return false; }
            if (vector1[i] != TestStruct((float)i)) { return false; }
        }
    }

    return true;
}
