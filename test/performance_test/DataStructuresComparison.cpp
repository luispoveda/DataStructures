#include "DataStructuresComparison.hpp"

static std::stringstream s_FileBuffer;

static void ClearFile()
{
    std::ofstream file;
    file.open("data/Comparison.txt", std::ios::out | std::ios::trunc);
    file.close();
}

void DataStructuresComparison::RunAllTest()
{
    ClearFile();

    s_FileBuffer << "Data Structures Comparison:" << std::endl;
    PushBack();
    InsertFront();
    InsertMiddle();
    InsertRandom();
}

void DataStructuresComparison::PushBack()
{
    auto vector_predicate = [](Vector<TestStruct>& vector) -> void
    {
        for (size_t i = 0; i < ELEMENTS; ++i)
        {
            TestStruct aux((float)i);
            vector.PushBack(aux);
        }
    };
    auto list_predicate = [](List<TestStruct>& list) -> void
    {
        for (size_t i = 0; i < ELEMENTS; ++i)
        {
            TestStruct aux((float)i);
            list.PushBack(aux);
        }
    };

    std::cout << "Testing PushBack Performance" << std::endl;
    DataStructuresComparison::Test(s_FileBuffer, "PushBack", vector_predicate, list_predicate);
    Serializer::SerializePerformance("Comparison.txt", s_FileBuffer);
}

void DataStructuresComparison::InsertFront()
{
    const size_t elements = ELEMENTS / 10000;
    auto vector_predicate = [elements](Vector<TestStruct>& vector) -> void
    {
        for (size_t i = 0; i < elements; ++i)
        {
            TestStruct aux((float)i);
            vector.Insert(vector.begin(), aux);
        }
    };
    auto list_predicate = [elements](List<TestStruct>& list) -> void
    {
        for (size_t i = 0; i < elements; ++i)
        {
            TestStruct aux((float)i);
            list.PushFront(aux);
        }
    };

    std::cout << "Testing Insert at Front Performance" << std::endl;
    DataStructuresComparison::Test(s_FileBuffer, "Insert Front", vector_predicate, list_predicate, elements);
    Serializer::SerializePerformance("Comparison.txt", s_FileBuffer);
}

void DataStructuresComparison::InsertMiddle()
{
    const size_t elements = ELEMENTS / 10000;
    auto vector_predicate = [elements](Vector<TestStruct>& vector) -> void
    {
        for (size_t i = 0; i < elements; ++i)
        {
            TestStruct aux((float)i);
            size_t middle = vector.Size() / 2;
            vector.Insert(vector.begin() + middle, aux);
        }
    };
    auto list_predicate = [elements](List<TestStruct>& list) -> void
    {
        for (size_t i = 0; i < elements; ++i)
        {
            TestStruct aux((float)i);
            size_t middle = list.Size() / 2;
            list.Insert(list.begin() + middle, aux);
        }
    };

    std::cout << "Testing Insert at Middle Performance" << std::endl;
    DataStructuresComparison::Test(s_FileBuffer, "Insert Middle", vector_predicate, list_predicate, elements);
    Serializer::SerializePerformance("Comparison.txt", s_FileBuffer);
}

void DataStructuresComparison::InsertRandom()
{
    const size_t elements = ELEMENTS / 10000;
    Vector<size_t> random_numbers(elements);
    random_numbers.PushBack(0);
    random_numbers.PushBack(0);
    for (size_t i = 2; i < random_numbers.Capacity(); ++i)
    {
        random_numbers.PushBack(rand() % i);
    }

    auto vector_predicate = [&random_numbers, elements](Vector<TestStruct>& vector) -> void
    {
        Vector<size_t>::const_iterator it = random_numbers.cbegin();
        for (size_t i = 0; i < elements; ++i, ++it)
        {
            TestStruct aux((float)i);
            vector.Insert(vector.begin() + *it, aux);
        }
    };
    auto list_predicate = [&random_numbers, elements](List<TestStruct>& list) -> void
    {
        Vector<size_t>::const_iterator it = random_numbers.cbegin();
        for (size_t i = 0; i < elements; ++i, ++it)
        {
            TestStruct aux((float)i);
            list.Insert(list.begin() + *it, aux);
        }
    };

    std::cout << "Testing Insert at Random Performance" << std::endl;
    DataStructuresComparison::Test(s_FileBuffer, "Insert Random", vector_predicate, list_predicate, elements);
    Serializer::SerializePerformance("Comparison.txt", s_FileBuffer);
}
