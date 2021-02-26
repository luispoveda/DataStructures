#pragma once

class ArrayTest
{
public:
    static bool RunAllTest() noexcept;

public:
    static bool Iterators() noexcept;
    static bool Copy() noexcept;
    static bool Move() noexcept;
    static bool Fill() noexcept;
    static bool Swap() noexcept;
    static bool Operators() noexcept;
};
