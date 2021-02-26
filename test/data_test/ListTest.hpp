#pragma once

class ListTest
{
public:
    static bool RunAllTest();

public:
    static bool Iterators();
    static bool Copy();
    static bool Move();
    static bool Swap();
    static bool PushBack();
    static bool PushFront();
    static bool Insert();
    static bool EmplaceBack();
    static bool EmplaceFront();
    static bool Emplace();
    static bool PopBack();
    static bool PopFront();
    static bool Erase();
    static bool Clear();
    static bool Append();
    static bool Reserve();
    static bool Resize();
    static bool Shrink();
};
