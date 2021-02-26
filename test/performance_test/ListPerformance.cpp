#include "ListPerformance.hpp"

#include <iostream> //For std::cout

static std::stringstream s_FileBuffer;

void ListPerformance::RunAllTest()
{
    s_FileBuffer << "list Performance Test:" << std::endl;

    PushBack();
    EmplaceBack();
    InsertFront();
    InsertMiddle();
    InsertRandom();
    EmplaceFront();
    EmplaceMiddle();
    EmplaceRandom();
}

/*
* PRIVATE IMPLEMENTATIONS
*/

void ListPerformance::PushBack()
{
    auto std_predicate = [](std::list<TestStruct>& list) -> void
    {
        for (size_t i = 0; i < ELEMENTS; ++i)
        {
            TestStruct aux((float)i);
            list.push_back(aux);
        }
    };
    auto predicate = [](List<TestStruct>& list) -> void
    {
        for (size_t i = 0; i < ELEMENTS; ++i)
        {
            TestStruct aux((float)i);
            list.PushBack(aux);
        }
    };

    std::cout << "Testing PushBack Performance" << std::endl;
    ListPerformance::Test(s_FileBuffer, "PushBack", std_predicate, predicate);
    Serializer::SerializePerformance("List_Results.txt", s_FileBuffer);
}

void ListPerformance::EmplaceBack()
{
    auto std_predicate = [](std::list<TestStruct>& list) -> void
    {
        for (size_t i = 0; i < ELEMENTS; ++i)
        {
            list.emplace_back();
        }
    };
    auto predicate = [](List<TestStruct>& list) -> void
    {
        for (size_t i = 0; i < ELEMENTS; ++i)
        {
            list.EmplaceBack((float)i);
        }
    };

    std::cout << "Testing EmplaceBack Performance" << std::endl;
    ListPerformance::Test(s_FileBuffer, "EmplaceBack", std_predicate, predicate);
    Serializer::SerializePerformance("List_Results.txt", s_FileBuffer);
}

void ListPerformance::InsertFront()
{
    auto std_predicate = [](std::list<TestStruct>& list) -> void
    {
        for (size_t i = 0; i < ELEMENTS; ++i)
        {
            TestStruct aux((float)i);
            list.insert(list.begin(), aux);
        }
    };
    auto predicate = [](List<TestStruct>& list) -> void
    {
        for (size_t i = 0; i < ELEMENTS; ++i)
        {
            TestStruct aux((float)i);
            list.Insert(list.begin(), aux);
        }
    };

    std::cout << "Testing Insert Front Performance" << std::endl;
    ListPerformance::Test(s_FileBuffer, "InsertFront", std_predicate, predicate);
    Serializer::SerializePerformance("List_Results.txt", s_FileBuffer);
}

void ListPerformance::InsertMiddle()
{
    auto std_predicate = [](std::list<TestStruct>& list) -> void
    {
        for (size_t i = 0; i < ELEMENTS; ++i)
        {
            TestStruct aux((float)i);
            size_t middle = list.size() / 2;
            std::list<TestStruct>::iterator list_iterator = list.begin();
            for (size_t tmp = 0; tmp < middle; ++tmp, ++list_iterator) {}
            list.insert(list_iterator, aux);
        }
    };
    auto predicate = [](List<TestStruct>& list) -> void
    {
        for (size_t i = 0; i < ELEMENTS; ++i)
        {
            TestStruct aux((float)i);
            size_t middle = list.Size() / 2;
            list.Insert(list.begin() + middle, aux);
        }
    };

    std::cout << "Testing Insert Middle Performance" << std::endl;
    ListPerformance::Test(s_FileBuffer, "InsertMiddle", std_predicate, predicate);
    Serializer::SerializePerformance("List_Results.txt", s_FileBuffer);
}

void ListPerformance::InsertRandom()
{
    List<size_t> random_numbers(ELEMENTS);
    random_numbers.PushBack(0);
    random_numbers.PushBack(0);
    for (size_t i = 2; i < random_numbers.Capacity(); ++i)
    {
        random_numbers.PushBack(rand() % i);
    }

    auto std_predicate = [&random_numbers](std::list<TestStruct>& list) -> void
    {
        List<size_t>::const_iterator it = random_numbers.cbegin();
        for (size_t i = 0; i < ELEMENTS; ++i, ++it)
        {
            TestStruct aux((float)i);
            std::list<TestStruct>::iterator list_iterator = list.begin();
            for (size_t tmp = 0; tmp < *it; ++tmp, ++list_iterator) {}
            list.insert(list_iterator, aux);
        }
    };
    auto predicate = [&random_numbers](List<TestStruct>& list) -> void
    {
        List<size_t>::const_iterator it = random_numbers.cbegin();
        for (size_t i = 0; i < ELEMENTS; ++i, ++it)
        {
            TestStruct aux((float)i);
            list.Insert(list.begin() + *it, aux);
        }
    };

    std::cout << "Testing Insert Random Performance" << std::endl;
    ListPerformance::Test(s_FileBuffer, "InsertRandom", std_predicate, predicate);
    Serializer::SerializePerformance("List_Results.txt", s_FileBuffer);
}

void ListPerformance::EmplaceFront()
{
    auto std_predicate = [](std::list<TestStruct>& list) -> void
    {
        for (size_t i = 0; i < ELEMENTS; ++i)
        {
            list.emplace(list.begin(), (float)i);
        }
    };
    auto predicate = [](List<TestStruct>& list) -> void
    {
        for (size_t i = 0; i < ELEMENTS; ++i)
        {
            list.Emplace(list.begin(), (float)i);
        }
    };

    std::cout << "Testing Emplace Front Performance" << std::endl;
    ListPerformance::Test(s_FileBuffer, "EmplaceFront", std_predicate, predicate);
    Serializer::SerializePerformance("List_Results.txt", s_FileBuffer);
}

void ListPerformance::EmplaceMiddle()
{
    auto std_predicate = [](std::list<TestStruct>& list) -> void
    {
        for (size_t i = 0; i < ELEMENTS; ++i)
        {
            size_t middle = list.size() / 2;
            std::list<TestStruct>::iterator list_iterator = list.begin();
            for (size_t tmp = 0; tmp < middle; ++tmp, ++list_iterator) {}
            list.emplace(list_iterator, (float)i);
        }
    };
    auto predicate = [](List<TestStruct>& list) -> void
    {
        for (size_t i = 0; i < ELEMENTS; ++i)
        {
            size_t middle = list.Size() / 2;
            list.Emplace(list.begin() + middle, (float)i);
        }
    };

    std::cout << "Testing Emplace Middle Performance" << std::endl;
    ListPerformance::Test(s_FileBuffer, "EmplaceMiddle", std_predicate, predicate);
    Serializer::SerializePerformance("List_Results.txt", s_FileBuffer);
}

void ListPerformance::EmplaceRandom()
{
    List<size_t> random_numbers(ELEMENTS);
    random_numbers.PushBack(0);
    random_numbers.PushBack(0);
    for (size_t i = 2; i < random_numbers.Capacity(); ++i)
    {
        random_numbers.PushBack(rand() % i);
    }

    auto std_predicate = [&random_numbers](std::list<TestStruct>& list) -> void
    {
        List<size_t>::const_iterator it = random_numbers.cbegin();
        for (size_t i = 0; i < ELEMENTS; ++i, ++it)
        {
            std::list<TestStruct>::iterator list_iterator = list.begin();
            for (size_t tmp = 0; tmp < *it; ++tmp, ++list_iterator) {}
            list.emplace(list_iterator, (float)i);
        }
    };
    auto predicate = [&random_numbers](List<TestStruct>& list) -> void
    {
        List<size_t>::const_iterator it = random_numbers.cbegin();
        for (size_t i = 0; i < ELEMENTS; ++i, ++it)
        {
            list.Emplace(list.begin() + *it, (float)i);
        }
    };

    std::cout << "Testing Emplace Random Performance" << std::endl;
    ListPerformance::Test(s_FileBuffer, "EmplaceRandom", std_predicate, predicate);
    Serializer::SerializePerformance("List_Results.txt", s_FileBuffer);
}
