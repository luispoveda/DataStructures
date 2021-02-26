#pragma once

#include <iostream>

struct TestStruct
{
public:
    TestStruct()
    {
        p = new int[5];

#ifdef __PRINT_CONSTRUCT_INFO__
        std::cout << "Created" << std::endl;
#endif
    }

    TestStruct(float scalar) :
        x(scalar),
        y(scalar),
        z(scalar)
    {
        p = new int[5];

#ifdef __PRINT_CONSTRUCT_INFO__
        std::cout << "Created" << std::endl;
#endif
    }

    TestStruct(float x, float y, float z) :
        x(x),
        y(y),
        z(z)
    {
        p = new int[5];

#ifdef __PRINT_CONSTRUCT_INFO__
        std::cout << "Created" << std::endl;
#endif
    }

    TestStruct(const TestStruct& other) :
        x(other.x),
        y(other.y),
        z(other.z)
    {
        p = new int[5];

        for (size_t i = 0; i < 5; ++i)
        {
            p[i] = other.p[i];
        }

#ifdef __PRINT_CONSTRUCT_INFO__
        std::cout << "Copied" << std::endl;
#endif
    }

    TestStruct(TestStruct&& other) noexcept :
        x(other.x),
        y(other.y),
        z(other.z)
    {
        p = other.p;
        other.x = 0.0f;
        other.y = 0.0f;
        other.z = 0.0f;
        other.p = nullptr;

#ifdef __PRINT_CONSTRUCT_INFO__
        std::cout << "Moved" << std::endl;
#endif
    }

    ~TestStruct()
    {
        delete[] p;
        p = nullptr;

#ifdef __PRINT_CONSTRUCT_INFO__
        std::cout << "Destroyed" << std::endl;
#endif
    }

    TestStruct& operator=(const TestStruct& other)
    {
        if (this == &other) { return *this; }
        delete[] p;
        x = other.x;
        y = other.y;
        z = other.z;

        p = new int[5];

        for (size_t i = 0; i < 5; ++i)
        {
            p[i] = other.p[i];
        }

#ifdef __PRINT_CONSTRUCT_INFO__
        std::cout << "Copied" << std::endl;
#endif

        return *this;
    }

    TestStruct& operator=(TestStruct&& other)
    {
        if (this == &other) { return *this; }
        delete[] p;
        x = other.x;
        y = other.y;
        z = other.z;
        p = other.p;

        other.x = 0.0f;
        other.y = 0.0f;
        other.z = 0.0f;
        other.p = nullptr;

#ifdef __PRINT_CONSTRUCT_INFO__
        std::cout << "Moved" << std::endl;
#endif

        return *this;
    }

public:
    bool operator==(const TestStruct& other) const noexcept
    {
        if (fabs(x - other.x) > DBL_EPSILON) { return false; }
        if (fabs(y - other.y) > DBL_EPSILON) { return false; }
        if (fabs(z - other.z) > DBL_EPSILON) { return false; }

        return true;
    }

    bool operator!=(const TestStruct& other) const noexcept { return !(*this == other); }

public:
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    int* p = nullptr;
};
