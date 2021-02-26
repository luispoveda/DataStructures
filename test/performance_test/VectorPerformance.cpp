#include "VectorPerformance.hpp"

#include <iostream> //For std::cout

static std::stringstream s_FileBuffer;

void VectorPerformance::RunAllTest()
{
    s_FileBuffer << "Vector Performance Test:" << std::endl;

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

void VectorPerformance::PushBack()
{
    auto std_predicate = [](std::vector<TestStruct>& vector) -> void
    {
        for (size_t i = 0; i < ELEMENTS; ++i)
        {
            TestStruct aux((float)i);
            vector.push_back(aux);
        }
    };
    auto predicate = [](Vector<TestStruct>& vector) -> void
    {
        for (size_t i = 0; i < ELEMENTS; ++i)
        {
            TestStruct aux((float)i);
            vector.PushBack(aux);
        }
    };

    std::cout << "Testing PushBack Performance" << std::endl;
    VectorPerformance::Test(s_FileBuffer, "PushBack", std_predicate, predicate);
    Serializer::SerializePerformance("Vector_Results.txt", s_FileBuffer);
}

void VectorPerformance::EmplaceBack()
{
    auto std_predicate = [](std::vector<TestStruct>& vector) -> void
    {
        for (size_t i = 0; i < ELEMENTS; ++i)
        {
            vector.emplace_back();
        }
    };
    auto predicate = [](Vector<TestStruct>& vector) -> void
    {
        for (size_t i = 0; i < ELEMENTS; ++i)
        {
            vector.EmplaceBack((float)i);
        }
    };

    std::cout << "Testing EmplaceBack Performance" << std::endl;
    VectorPerformance::Test(s_FileBuffer, "EmplaceBack", std_predicate, predicate);
    Serializer::SerializePerformance("Vector_Results.txt", s_FileBuffer);
}

void VectorPerformance::InsertFront()
{
    const size_t elements = ELEMENTS / 10000;
    auto std_predicate = [elements](std::vector<TestStruct>& vector) -> void
    {
        for (size_t i = 0; i < elements; ++i)
        {
            TestStruct aux((float)i);
            vector.insert(vector.begin(), aux);
        }
    };
    auto predicate = [elements](Vector<TestStruct>& vector) -> void
    {
        for (size_t i = 0; i < elements; ++i)
        {
            TestStruct aux((float)i);
            vector.Insert(vector.begin(), aux);
        }
    };

    std::cout << "Testing Insert Front Performance" << std::endl;
    VectorPerformance::Test(s_FileBuffer, "InsertFront", std_predicate, predicate, elements);
    Serializer::SerializePerformance("Vector_Results.txt", s_FileBuffer);
}

void VectorPerformance::InsertMiddle()
{
    const size_t elements = ELEMENTS / 10000;
    auto std_predicate = [elements](std::vector<TestStruct>& vector) -> void
    {
        for (size_t i = 0; i < elements; ++i)
        {
            TestStruct aux((float)i);
            size_t middle = vector.size() / 2;
            vector.insert(vector.begin() + middle, aux);
        }
    };
    auto predicate = [elements](Vector<TestStruct>& vector) -> void
    {
        for (size_t i = 0; i < elements; ++i)
        {
            TestStruct aux((float)i);
            size_t middle = vector.Size() / 2;
            vector.Insert(vector.begin() + middle, aux);
        }
    };

    std::cout << "Testing Insert Middle Performance" << std::endl;
    VectorPerformance::Test(s_FileBuffer, "InsertMiddle", std_predicate, predicate, elements);
    Serializer::SerializePerformance("Vector_Results.txt", s_FileBuffer);
}

void VectorPerformance::InsertRandom()
{
    const size_t elements = ELEMENTS / 10000;
    Vector<size_t> random_numbers(elements);
    random_numbers.PushBack(0);
    random_numbers.PushBack(0);
    for (size_t i = 2; i < random_numbers.Capacity(); ++i)
    {
        random_numbers.PushBack(rand() % i);
    }

    auto std_predicate = [&random_numbers, elements](std::vector<TestStruct>& vector) -> void
    {
        Vector<size_t>::const_iterator it = random_numbers.cbegin();
        for (size_t i = 0; i < elements; ++i, ++it)
        {
            TestStruct aux((float)i);
            vector.insert(vector.begin() + *it, aux);
        }
    };
    auto predicate = [&random_numbers, elements](Vector<TestStruct>& vector) -> void
    {
        Vector<size_t>::const_iterator it = random_numbers.cbegin();
        for (size_t i = 0; i < elements; ++i, ++it)
        {
            TestStruct aux((float)i);
            vector.Insert(vector.begin() + *it, aux);
        }
    };

    std::cout << "Testing Insert Random Performance" << std::endl;
    VectorPerformance::Test(s_FileBuffer, "InsertRandom", std_predicate, predicate, elements);
    Serializer::SerializePerformance("Vector_Results.txt", s_FileBuffer);
}

void VectorPerformance::EmplaceFront()
{
    const size_t elements = ELEMENTS / 10000;
    auto std_predicate = [elements](std::vector<TestStruct>& vector) -> void
    {
        for (size_t i = 0; i < elements; ++i)
        {
            vector.emplace(vector.begin(), (float)i);
        }
    };
    auto predicate = [elements](Vector<TestStruct>& vector) -> void
    {
        for (size_t i = 0; i < elements; ++i)
        {
            vector.Emplace(vector.begin(), (float)i);
        }
    };

    std::cout << "Testing Emplace Front Performance" << std::endl;
    VectorPerformance::Test(s_FileBuffer, "EmplaceFront", std_predicate, predicate, elements);
    Serializer::SerializePerformance("Vector_Results.txt", s_FileBuffer);
}

void VectorPerformance::EmplaceMiddle()
{
    const size_t elements = ELEMENTS / 10000;
    auto std_predicate = [elements](std::vector<TestStruct>& vector) -> void
    {
        for (size_t i = 0; i < elements; ++i)
        {
            size_t middle = vector.size() / 2;
            vector.emplace(vector.begin() + middle, (float)i);
        }
    };
    auto predicate = [elements](Vector<TestStruct>& vector) -> void
    {
        for (size_t i = 0; i < elements; ++i)
        {
            size_t middle = vector.Size() / 2;
            vector.Emplace(vector.begin() + middle, (float)i);
        }
    };

    std::cout << "Testing Emplace Middle Performance" << std::endl;
    VectorPerformance::Test(s_FileBuffer, "EmplaceMiddle", std_predicate, predicate, elements);
    Serializer::SerializePerformance("Vector_Results.txt", s_FileBuffer);
}

void VectorPerformance::EmplaceRandom()
{
    const size_t elements = ELEMENTS / 10000;
    Vector<size_t> random_numbers(elements);
    random_numbers.PushBack(0);
    random_numbers.PushBack(0);
    for (size_t i = 2; i < random_numbers.Capacity(); ++i)
    {
        random_numbers.PushBack(rand() % i);
    }

    auto std_predicate = [&random_numbers, elements](std::vector<TestStruct>& vector) -> void
    {
        Vector<size_t>::const_iterator it = random_numbers.cbegin();
        for (size_t i = 0; i < elements; ++i, ++it)
        {
            vector.emplace(vector.begin() + *it, (float)i);
        }
    };
    auto predicate = [&random_numbers, elements](Vector<TestStruct>& vector) -> void
    {
        Vector<size_t>::const_iterator it = random_numbers.cbegin();
        for (size_t i = 0; i < elements; ++i, ++it)
        {
            vector.Emplace(vector.begin() + *it, (float)i);
        }
    };

    std::cout << "Testing Emplace Random Performance" << std::endl;
    VectorPerformance::Test(s_FileBuffer, "EmplaceRandom", std_predicate, predicate, elements);
    Serializer::SerializePerformance("Vector_Results.txt", s_FileBuffer);
}
