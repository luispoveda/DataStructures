#pragma once

/*
* Author: Luis Poveda Cano.
* luispovedacano@gmail.com
*/

/*
* Single header class.
* Array class is a container that encapsulates fixed size arrays.
* Array has a very low overhead.
* Combines the performance and accessibility of a C-style array with the benefits of C++ features.
*
* There is a special case for a zero-length array (S == 0).
* The effect of calling front() or back() on a zero-sized array is undefined.
*/

/*
MIT License

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Copyright (c) 2020 Luis Poveda Cano
*/

#include <initializer_list>

template <typename T, size_t S>
class Array
{
public:
    template<typename ValueType>
    class Iterator
    {
        //Modifiers
    public:
        /**
        * @brief: Moves the iterator to the next element.
        * @details: Pre increment.
        *
        * @return: Iterator& -> Iterator.
        */
        _CONSTEXPR17 Iterator& operator++() noexcept
        {
            ++m_Ptr;
            return *this;
        }

        /**
        * @brief: Moves the iterator to the next element.
        * @details: Post increment.
        *
        * @return: Iterator -> Iterator at previous position.
        */
        _NODISCARD _CONSTEXPR17 Iterator operator++(int) noexcept
        {
            Iterator it(m_Ptr);
            ++m_Ptr;
            return it;
        }

        /**
        * @brief: Moves the iterator forwards by the given distance.
        *
        * @param: size_t -> Distance to move.
        *
        * @return: Iterator& -> Iterator.
        */
        _CONSTEXPR17 Iterator& operator+=(size_t distance) noexcept
        {
            m_Ptr += distance;
            return *this;
        }

        /**
        * @brief: Moves the iterator forwards by the given distance.
        * @details: By giving a negative number, the iterator will move backwards instead.
        *
        * @param: int -> Distance to move.
        *
        * @return: Iterator& -> Iterator.
        */
        _CONSTEXPR17 Iterator& operator+=(int distance) noexcept
        {
            m_Ptr += distance;
            return *this;
        }

        /**
        * @brief: Moves the iterator forwards by the given distance.
        * @details: By default the distance is 1.
        * If the iterator is not valid, throws std::exception.
        *
        * @param: size_t -> Distance to move.
        *
        * @return: void.
        */
        _CONSTEXPR17 void Advance(size_t distance = 1)
        {
            if (!m_Ptr) { throw std::exception("Invalid iterator"); }
            m_Ptr += distance;
        }

        /**
        * @brief: Moves the iterator forwards by the given distance.
        * @details: By giving a negative number, the iterator will move backwards instead.
        * By default the distance is 1.
        * If the iterator is not valid, throws std::exception.
        *
        * @param: int -> Distance to move.
        *
        * @return: void.
        */
        _CONSTEXPR17 void Advance(int distance = 1)
        {
            if (!m_Ptr) { throw std::exception("Invalid iterator"); }
            m_Ptr += distance;
        }

        /**
        * @brief: Moves the iterator to the previous element.
        * @details: Pre increment.
        *
        * @return: Iterator& -> Iterator.
        */
        _CONSTEXPR17 Iterator& operator--() noexcept
        {
            --m_Ptr;
            return *this;
        }

        /**
        * @brief: Moves the iterator to the previous element.
        * @details: Post increment.
        *
        * @return: Iterator -> Iterator at previous position.
        */
        _NODISCARD _CONSTEXPR17 Iterator operator--(int) noexcept
        {
            Iterator it(m_Ptr);
            --m_Ptr;
            return it;
        }

        /**
        * @brief: Moves the iterator backwards by the given distance.
        *
        * @param: size_t -> Distance to move.
        *
        * @return: Iterator& -> Iterator.
        */
        _CONSTEXPR17 Iterator& operator-=(size_t distance) noexcept
        {
            m_Ptr -= distance;
            return *this;
        }

        /**
        * @brief: Moves the iterator backwards by the given distance.
        * @details: By giving a negative number, the iterator will move forwards instead.
        *
        * @param: int -> Distance to move.
        *
        * @return: Iterator& -> Iterator.
        */
        _CONSTEXPR17 Iterator& operator-=(int distance) noexcept
        {
            m_Ptr -= distance;
            return *this;
        }

        /**
        * @brief: Moves the iterator backwards by the given distance.
        * @details: By default the distance is 1.
        * If the iterator is not valid, throws std::exception.
        *
        * @param: size_t -> Distance to move.
        *
        * @return: void.
        */
        _CONSTEXPR17 void Retreat(size_t distance = 1)
        {
            if (!m_Ptr) { throw std::exception("Invalid iterator"); }
            m_Ptr -= distance;
        }

        /**
        * @brief: Moves the iterator backwards by the given distance.
        * @details: By giving a negative number, the iterator will move forwards instead.
        * By default the distance is 1.
        * If the iterator is not valid, throws std::exception.
        *
        * @param: int -> Distance to move.
        *
        * @return: void.
        */
        _CONSTEXPR17 void Retreat(int distance = 1)
        {
            if (!m_Ptr) { throw std::exception("Invalid iterator"); }
            m_Ptr -= distance;
        }

        /**
        * @brief: Returns an iterator to the forward given distance.
        *
        * @param: size_t -> Distance to move.
        *
        * @return: Iterator -> Iterator in the resulting position.
        */
        _NODISCARD _CONSTEXPR17 Iterator operator+(size_t distance) const noexcept
        {
            Iterator it(m_Ptr);
            it += distance;
            return it;
        }

        /**
        * @brief: Returns an iterator to the forward given distance.
        * @details: By giving a negative number, the iterator will move backwards instead.
        *
        * @param: int -> Distance to move.
        *
        * @return: Iterator -> Iterator in the resulting position.
        */
        _NODISCARD _CONSTEXPR17 Iterator operator+(int distance) const noexcept
        {
            Iterator it(m_Ptr);
            it += distance;
            return it;
        }

        /**
        * @brief: Returns an iterator to the forward given distance.
        * @details: By default the distance is 1.
        * If the iterator is not valid, throws std::exception.
        *
        * @param: size_t -> Distance to move.
        *
        * @return: Iterator -> Iterator in the resulting position.
        */
        _NODISCARD _CONSTEXPR17 Iterator Next(size_t distance = 1) const
        {
            if (!m_Ptr) { throw std::exception("Invalid iterator"); }
            Iterator it(m_Ptr);
            it += distance;
            return it;
        }

        /**
        * @brief: Returns an iterator to the forward given distance.
        * @details: By giving a negative number, the iterator will move backward instead.
        * By default the distance is 1.
        * If the iterator is not valid, throws std::exception.
        *
        * @param: int -> Distance to move.
        *
        * @return: Iterator -> Iterator in the resulting position.
        */
        _NODISCARD _CONSTEXPR17 Iterator Next(int distance = 1) const
        {
            if (!m_Ptr) { throw std::exception("Invalid iterator"); }
            Iterator it(m_Ptr);
            it += distance;
            return it;
        }

        /**
        * @brief: Returns an iterator to the backward given distance.
        *
        * @param: size_t -> Distance to move.
        *
        * @return: Iterator -> Iterator in the resulting position.
        */
        _NODISCARD _CONSTEXPR17 Iterator operator-(size_t distance) const noexcept
        {
            Iterator it(m_Ptr);
            it -= distance;
            return it;
        }

        /**
        * @brief: Returns an iterator to the backward given distance.
        * @details: By giving a negative number, the iterator will move forwards instead.
        *
        * @param: int -> Distance to move.
        *
        * @return: Iterator -> Iterator in the resulting position.
        */
        _NODISCARD _CONSTEXPR17 Iterator operator-(int distance) const noexcept
        {
            Iterator it(m_Ptr);
            it -= distance;
            return it;
        }

        /**
        * @brief: Returns an iterator to the backward given distance.
        * @details: By default the distance is 1.
        * If the iterator is not valid, throws std::exception.
        *
        * @param: size_t -> Distance to move.
        *
        * @return: Iterator -> Iterator in the resulting position.
        */
        _NODISCARD _CONSTEXPR17 Iterator Prev(size_t distance = 1) const
        {
            if (!m_Ptr) { throw std::exception("Invalid iterator"); }
            Iterator it(m_Ptr);
            it -= distance;
            return it;
        }

        /**
        * @brief: Returns an iterator to the backward given distance.
        * @details: By giving a negative number, the iterator will move forward instead.
        * By default the distance is 1.
        * If the iterator is not valid, throws std::exception.
        *
        * @param: int -> Distance to move.
        *
        * @return: Iterator -> Iterator in the resulting position.
        */
        _NODISCARD _CONSTEXPR17 Iterator Prev(int distance = 1) const
        {
            if (!m_Ptr) { throw std::exception("Invalid iterator"); }
            Iterator it(m_Ptr);
            it -= distance;
            return it;
        }

        //Element access
    public:
        /**
        * @brief: Returns the element to the forward given distance.
        *
        * @param: size_t -> Distance from the Iterator.
        *
        * @return: ValueType& -> Element.
        */
        _NODISCARD _CONSTEXPR17 ValueType& operator[](size_t index) const noexcept { return *(operator+(index)); }

        /**
        * @brief: Returns the element to the forward given distance.
        * @details: By giving a negative number, the iterator will move backwards instead.
        *
        * @param: int -> Distance from the Iterator.
        *
        * @return: ValueType& -> Element.
        */
        _NODISCARD _CONSTEXPR17 ValueType& operator[](int index) const noexcept { return *(operator+(index)); }

        /**
        * @brief: Returns the element to the forward given distance.
        * @details: If the iterator is not valid, throws std::exception.
        * 
        * @param: size_t -> Distance from the Iterator.
        *
        * @return: ValueType& -> Element.
        */
        _NODISCARD _CONSTEXPR17 ValueType& At(size_t index) const { return *(Next(index)); }

        /**
        * @brief: Returns the element to the forward given distance.
        * @details: By giving a negative number, the iterator will move backwards instead.
        * If the iterator is not valid, throws std::exception.
        *
        * @param: int -> Distance from the Iterator.
        *
        * @return: ValueType& -> Element.
        */
        _NODISCARD _CONSTEXPR17 ValueType& At(int index) const { return *(Next(index)); }

        /**
        * @brief: Returns the data of the iterator.
        *
        * @return: ValueType& -> Data.
        */
        _NODISCARD _CONSTEXPR17 ValueType& operator*() const noexcept { return *m_Ptr; }

        /**
        * @brief: Returns the data of the iterator.
        * @details: If the iterator is not valid, throws std::exception.
        *
        * @return: ValueType& -> Data.
        */
        _NODISCARD _CONSTEXPR17 ValueType& Data() const
        {
            if (!m_Ptr) { throw std::exception("Invalid iterator"); }
            return *m_Ptr;
        }

        /**
        * @brief: Returns the Iterator.
        *
        * @return: ValueType* -> Iterator.
        */
        _NODISCARD _CONSTEXPR17 ValueType* operator->() const noexcept { return m_Ptr; }

        /**
        * @brief: Returns the Iterator.
        * @details: If the iterator is not valid, throws std::exception.
        *
        * @return: ValueType* -> Iterator.
        */
        _NODISCARD _CONSTEXPR17 ValueType* Get() const
        {
            if (!m_Ptr) { throw std::exception("Invalid iterator"); }
            return m_Ptr;
        }

        //Non member functions
    public:
        /**
        * @brief: Returns the distance between the iterator and other.
        * @details: The result is always a positive number.
        * If the iterator is not valid, throws std::exception.
        *
        * @param: const Iterator& -> Iterator to compare.
        *
        * @return: size_t -> Distance.
        */
        _NODISCARD _CONSTEXPR17 size_t Distance(const Iterator& other) const
        {
            if (!m_Ptr) { throw std::exception("Invalid iterator"); }
            if (!other) { throw std::exception("Invalid parameter"); }
            if (m_Ptr > other.m_Ptr) { return m_Ptr - other.m_Ptr; }
            return other.m_Ptr - m_Ptr;
        }

        /**
        * @brief: Compares if two iterators are equal.
        *
        * @param: const Iterator& -> Iterator to compare.
        *
        * @return: bool -> True if both are equal.
        */
        _NODISCARD _CONSTEXPR17 bool operator==(const Iterator& other) const noexcept { return m_Ptr == other.m_Ptr; }

        /**
        * @brief: Compares if the given pointer and the iterator are pointing to the same memory address.
        *
        * @param: ValueType* -> Pointer to compare.
        *
        * @return: bool -> True if both are pointing to the same memory address.
        */
        _NODISCARD _CONSTEXPR17 bool operator==(ValueType* other) const noexcept { return m_Ptr == other; }

        /**
        * @brief: Compares if two iterators are not equal.
        *
        * @param: const Iterator& -> Iterator to compare.
        *
        * @return: bool -> True if both are not equal.
        */
        _NODISCARD _CONSTEXPR17 bool operator!=(const Iterator& other) const noexcept { return !(operator==(other)); }

        /**
        * @brief: Compares if the given pointer and the iterator are pointing to the same memory address.
        *
        * @param: ValueType* -> Pointer to compare.
        *
        * @return: bool -> True if both are pointing to the same memory address.
        */
        _NODISCARD _CONSTEXPR17 bool operator!=(ValueType* other) const noexcept { return !(operator==(other)); }

        /**
        * @brief: Compares if the iterator is lesser than the other.
        *
        * @param: const Iterator& -> Iterator to compare.
        *
        * @return: bool -> True if the iterator is lesser.
        */
        _NODISCARD _CONSTEXPR17 bool operator<(const Iterator& other) const noexcept { return m_Ptr < other.m_Ptr; }

        /**
        * @brief: Compares if the iterator is lesser or equal than the other.
        *
        * @param: const Iterator& -> Iterator to compare.
        *
        * @return: bool -> True if the iterator is lesser or equal.
        */
        _NODISCARD _CONSTEXPR17 bool operator<=(const Iterator& other) const noexcept { return !(operator>(other)); }

        /**
        * @brief: Compares if the iterator is greater than the other.
        *
        * @param: const Iterator& -> Iterator to compare.
        *
        * @return: bool -> True if the iterator is greater.
        */
        _NODISCARD _CONSTEXPR17 bool operator>(const Iterator& other) const noexcept { return m_Ptr > other.m_Ptr; }

        /**
        * @brief: Compares if the iterator is greater or equal than the other.
        *
        * @param: const Iterator& -> Iterator to compare.
        *
        * @return: bool -> True if the iterator is greater or equal.
        */
        _NODISCARD _CONSTEXPR17 bool operator>=(const Iterator& other) const noexcept { return !(operator<(other)); }

        /**
        * @brief: Returns the comparison with the pointer.
        *
        * @return: bool -> True if the pointer is not nullptr.
        */
        _NODISCARD _CONSTEXPR17 operator bool() const noexcept { return m_Ptr; }

        /**
        * @brief: Returns the comparison with the pointer.
        *
        * @return: bool -> True if the pointer is not nullptr.
        */
        _NODISCARD _CONSTEXPR17 bool IsValid() const noexcept { return m_Ptr; }

        //Member functions
    public:
        _CONSTEXPR17 Iterator(ValueType* ptr = nullptr) noexcept :
            m_Ptr(ptr) {}

        _CONSTEXPR17 Iterator(const Iterator& other) noexcept :
            m_Ptr(other.m_Ptr) {}

        _CONSTEXPR17 Iterator(Iterator&& other) noexcept :
            m_Ptr(other.m_Ptr)
        {
            other.m_Ptr = nullptr;
        }

        _CONSTEXPR17 Iterator& operator=(const Iterator& other) noexcept
        {
            m_Ptr = other.m_Ptr;
            return *this;
        }

        _CONSTEXPR17 Iterator& operator=(Iterator&& other) noexcept
        {
            m_Ptr = other.m_Ptr;
            other.m_Ptr = nullptr;
            return *this;
        }

        _CONSTEXPR17 Iterator& operator=(ValueType* other) noexcept
        {
            m_Ptr = other;
            return *this;
        }

    public:
        ~Iterator() noexcept { m_Ptr = nullptr; }

    private:
        ValueType* m_Ptr;
    };

    template<typename ValueType>
    class ReverseIterator
    {
        //Modifiers
    public:
        /**
        * @brief: Moves the iterator to the next element.
        * @details: Pre increment.
        *
        * @return: ReverseIterator& -> Iterator.
        */
        _CONSTEXPR17 ReverseIterator& operator++() noexcept
        {
            --m_Ptr;
            return *this;
        }

        /**
        * @brief: Moves the iterator to the next element.
        * @details: Post increment.
        *
        * @return: ReverseIterator -> Iterator at previous position.
        */
        _NODISCARD _CONSTEXPR17 ReverseIterator operator++(int) noexcept
        {
            ReverseIterator it(m_Ptr);
            --m_Ptr;
            return it;
        }

        /**
        * @brief: Moves the iterator forwards by the given distance.
        *
        * @param: size_t -> Distance to move.
        *
        * @return: ReverseIterator& -> Iterator.
        */
        _CONSTEXPR17 ReverseIterator& operator+=(size_t distance) noexcept
        {
            m_Ptr -= distance;
            return *this;
        }

        /**
        * @brief: Moves the iterator forwards by the given distance.
        * @details: By giving a negative number, the iterator will move backwards instead.
        *
        * @param: int -> Distance to move.
        *
        * @return: ReverseIterator& -> Iterator.
        */
        _CONSTEXPR17 ReverseIterator& operator+=(int distance) noexcept
        {
            m_Ptr -= distance;
            return *this;
        }

        /**
        * @brief: Moves the iterator forwards by the given distance.
        * @details: By default the distance is 1.
        * If the iterator is not valid, throws std::exception.
        *
        * @param: size_t -> Distance to move.
        *
        * @return: void.
        */
        _CONSTEXPR17 void Advance(size_t distance = 1)
        {
            if (!m_Ptr) { throw std::exception("Invalid iterator"); }
            m_Ptr -= distance;
        }

        /**
        * @brief: Moves the iterator forwards by the given distance.
        * @details: By giving a negative number, the iterator will move backwards instead.
        * By default the distance is 1.
        * If the iterator is not valid, throws std::exception.
        *
        * @param: int -> Distance to move.
        *
        * @return: void.
        */
        _CONSTEXPR17 void Advance(int distance = 1)
        {
            if (!m_Ptr) { throw std::exception("Invalid iterator"); }
            m_Ptr -= distance;
        }

        /**
        * @brief: Moves the iterator to the previous element.
        * @details: Pre increment.
        *
        * @return: ReverseIterator& -> Iterator.
        */
        _CONSTEXPR17 ReverseIterator& operator--() noexcept
        {
            ++m_Ptr;
            return *this;
        }

        /**
        * @brief: Moves the iterator to the previous element.
        * @details: Post increment.
        *
        * @return: ReverseIterator -> Iterator at previous position.
        */
        _NODISCARD _CONSTEXPR17 ReverseIterator operator--(int) noexcept
        {
            ReverseIterator it(m_Ptr);
            ++m_Ptr;
            return it;
        }

        /**
        * @brief: Moves the iterator backwards by the given distance.
        *
        * @param: size_t -> Distance to move.
        *
        * @return: ReverseIterator& -> Iterator.
        */
        _CONSTEXPR17 ReverseIterator& operator-=(size_t distance) noexcept
        {
            m_Ptr += distance;
            return *this;
        }

        /**
        * @brief: Moves the iterator backwards by the given distance.
        * @details: By giving a negative number, the iterator will move forwards instead.
        *
        * @param: int -> Distance to move.
        *
        * @return: ReverseIterator& -> Iterator.
        */
        _CONSTEXPR17 ReverseIterator& operator-=(int distance) noexcept
        {
            m_Ptr += distance;
            return *this;
        }

        /**
        * @brief: Moves the iterator backwards by the given distance.
        * @details: By default the distance is 1.
        * If the iterator is not valid, throws std::exception.
        *
        * @param: size_t -> Distance to move.
        *
        * @return: void.
        */
        _CONSTEXPR17 void Retreat(size_t distance = 1)
        {
            if (!m_Ptr) { throw std::exception("Invalid iterator"); }
            m_Ptr += distance;
        }

        /**
        * @brief: Moves the iterator backwards by the given distance.
        * @details: By giving a negative number, the iterator will move backwards instead.
        * By default the distance is 1.
        * If the iterator is not valid, throws std::exception.
        *
        * @param: int -> Distance to move.
        *
        * @return: void.
        */
        _CONSTEXPR17 void Retreat(int distance = 1)
        {
            if (!m_Ptr) { throw std::exception("Invalid iterator"); }
            m_Ptr += distance;
        }

        /**
        * @brief: Returns an iterator to the forward given distance.
        *
        * @param: size_t -> Distance to move.
        *
        * @return: ReverseIterator -> Iterator in the resulting position.
        */
        _NODISCARD _CONSTEXPR17 ReverseIterator operator+(size_t distance) const noexcept
        {
            ReverseIterator it(m_Ptr);
            it += distance;
            return it;
        }

        /**
        * @brief: Returns an iterator to the forward given distance.
        * @details: By giving a negative number, the iterator will move backwards instead.
        *
        * @param: int -> Distance to move.
        *
        * @return: ReverseIterator -> Iterator in the resulting position.
        */
        _NODISCARD _CONSTEXPR17 ReverseIterator operator+(int distance) const noexcept
        {
            ReverseIterator it(m_Ptr);
            it += distance;
            return it;
        }

        /**
        * @brief: Returns an iterator to the forward given distance.
        * @details: By default the distance is 1.
        * If the iterator is not valid, throws std::exception.
        *
        * @param: size_t -> Distance to move.
        *
        * @return: ReverseIterator -> Iterator in the resulting position.
        */
        _NODISCARD _CONSTEXPR17 ReverseIterator Next(size_t distance = 1) const
        {
            if (!m_Ptr) { throw std::exception("Invalid iterator"); }
            ReverseIterator it(m_Ptr);
            it += distance;
            return it;
        }

        /**
        * @brief: Returns an iterator to the forward given distance.
        * @details: By giving a negative number, the iterator will move backward instead.
        * By default the distance is 1.
        * If the iterator is not valid, throws std::exception.
        *
        * @param: int -> Distance to move.
        *
        * @return: ReverseIterator -> Iterator in the resulting position.
        */
        _NODISCARD _CONSTEXPR17 ReverseIterator Next(int distance = 1) const
        {
            if (!m_Ptr) { throw std::exception("Invalid iterator"); }
            ReverseIterator it(m_Ptr);
            it += distance;
            return it;
        }

        /**
        * @brief: Returns an iterator to the backward given distance.
        *
        * @param: size_t -> Distance to move.
        *
        * @return: ReverseIterator -> Iterator in the resulting position.
        */
        _NODISCARD _CONSTEXPR17 ReverseIterator operator-(size_t distance) const noexcept
        {
            ReverseIterator it(m_Ptr);
            it -= distance;
            return it;
        }

        /**
        * @brief: Returns an iterator to the backward given distance.
        * @details: By giving a negative number, the iterator will move forwards instead.
        *
        * @param: int -> Distance to move.
        *
        * @return: ReverseIterator -> Iterator in the resulting position.
        */
        _NODISCARD _CONSTEXPR17 ReverseIterator operator-(int distance) const noexcept
        {
            ReverseIterator it(m_Ptr);
            it -= distance;
            return it;
        }

        /**
        * @brief: Returns an iterator to the backward given distance.
        * @details: By default the distance is 1.
        * If the iterator is not valid, throws std::exception.
        *
        * @param: size_t -> Distance to move.
        *
        * @return: ReverseIterator -> Iterator in the resulting position.
        */
        _NODISCARD _CONSTEXPR17 ReverseIterator Prev(size_t distance = 1) const
        {
            if (!m_Ptr) { throw std::exception("Invalid iterator"); }
            ReverseIterator it(m_Ptr);
            it -= distance;
            return it;
        }

        /**
        * @brief: Returns an iterator to the backward given distance.
        * @details: By giving a negative number, the iterator will move forward instead.
        * By default the distance is 1.
        * If the iterator is not valid, throws std::exception.
        *
        * @param: int -> Distance to move.
        *
        * @return: ReverseIterator -> Iterator in the resulting position.
        */
        _NODISCARD _CONSTEXPR17 ReverseIterator Prev(int distance = 1) const
        {
            if (!m_Ptr) { throw std::exception("Invalid iterator"); }
            ReverseIterator it(m_Ptr);
            it -= distance;
            return it;
        }

        //Element access
    public:
        /**
        * @brief: Returns the element to the forward given distance.
        *
        * @param: size_t -> Distance from the Iterator.
        *
        * @return: ValueType& -> Element.
        */
        _NODISCARD _CONSTEXPR17 ValueType& operator[](size_t index) const noexcept { return *(operator+(index)); }

        /**
        * @brief: Returns the element to the forward given distance.
        * @details: By giving a negative number, the iterator will move backwards instead.
        *
        * @param: int -> Distance from the Iterator.
        *
        * @return: ValueType& -> Element.
        */
        _NODISCARD _CONSTEXPR17 ValueType& operator[](int index) const noexcept { return *(operator+(index)); }

        /**
        * @brief: Returns the element to the forward given distance.
        * @details: If the iterator is not valid, throws std::exception.
        *
        * @param: size_t -> Distance from the Iterator.
        *
        * @return: ValueType& -> Element.
        */
        _NODISCARD _CONSTEXPR17 ValueType& At(size_t index) const { return*(Next(index)); }

        /**
        * @brief: Returns the element to the forward given distance.
        * @details: By giving a negative number, the iterator will move backwards instead.
        * If the iterator is not valid, throws std::exception.
        *
        * @param: int -> Distance from the Iterator.
        *
        * @return: ValueType& -> Element.
        */
        _NODISCARD _CONSTEXPR17 ValueType& At(int index) const { return *(Next(index)); }

        /**
        * @brief: Returns the data of the iterator.
        *
        * @return: ValueType& -> Data.
        */
        _NODISCARD _CONSTEXPR17 ValueType& operator*() const noexcept { return *m_Ptr; }

        /**
        * @brief: Returns the data of the iterator.
        * @details: If the iterator is not valid, throws std::exception.
        *
        * @return: ValueType& -> Data.
        */
        _NODISCARD _CONSTEXPR17 ValueType& Data() const
        {
            if (!m_Ptr) { throw std::exception("Invalid iterator"); }
            return *m_Ptr;
        }

        /**
        * @brief: Returns the Iterator.
        *
        * @return: ValueType* -> Iterator.
        */
        _NODISCARD _CONSTEXPR17 ValueType* operator->() const noexcept { return m_Ptr; }

        /**
        * @brief: Returns the Iterator.
        * @details: If the iterator is not valid, throws std::exception. 
        *
        * @return: ValueType* -> Iterator.
        */
        _NODISCARD _CONSTEXPR17 ValueType* Get() const
        {
            if (!m_Ptr) { throw std::exception("Invalid iterator"); }
            return m_Ptr;
        }

        //Non member functions
    public:
        /**
        * @brief: Returns the distance between the iterator and other.
        * @details: The result is always a positive number.
        * If the iterator is not valid, throws std::exception.
        *
        * @param: const ReverseIterator& -> Iterator to compare.
        *
        * @return: size_t -> Distance.
        */
        _NODISCARD _CONSTEXPR17 size_t Distance(const ReverseIterator& other) const
        {
            if (!m_Ptr) { throw std::exception("Invalid iterator"); }
            if (!other) { throw std::exception("Invalid iterator"); }
            if (m_Ptr > other.m_Ptr) { return m_Ptr - other.m_Ptr; }
            return other.m_Ptr - m_Ptr;
        }

        /**
        * @brief: Compares if two iterators are equal.
        *
        * @param: const ReverseIterator& -> Iterator to compare.
        *
        * @return: bool -> True if both are equal.
        */
        _NODISCARD _CONSTEXPR17 bool operator==(const ReverseIterator& other) const noexcept { return m_Ptr == other.m_Ptr; }

        /**
        * @brief: Compares if the given pointer and the iterator are pointing to the same memory address.
        *
        * @param: ValueType* -> Pointer to compare.
        *
        * @return: bool -> True if both are pointing to the same memory address.
        */
        _NODISCARD _CONSTEXPR17 bool operator==(ValueType* other) const noexcept { return m_Ptr == other; }

        /**
        * @brief: Compares if two iterators are not equal.
        *
        * @param: const ReverseIterator& -> Iterator to compare.
        *
        * @return: bool -> True if both are not equal.
        */
        _NODISCARD _CONSTEXPR17 bool operator!=(const ReverseIterator& other) const noexcept { return !(operator==(other)); }

        /**
        * @brief: Compares if the given pointer and the iterator are pointing to the same memory address.
        *
        * @param: ValueType* -> Pointer to compare.
        *
        * @return: bool -> True if both are pointing to the same memory address.
        */
        _NODISCARD _CONSTEXPR17 bool operator!=(ValueType* other) const noexcept { return !(operator==(other)); }

        /**
        * @brief: Compares if the iterator is lesser than the other.
        *
        * @param: const ReverseIterator& -> Iterator to compare.
        *
        * @return: bool -> True if the iterator is lesser.
        */
        _NODISCARD _CONSTEXPR17 bool operator<(const ReverseIterator& other) const noexcept { return m_Ptr > other.m_Ptr; }

        /**
        * @brief: Compares if the iterator is lesser or equal than the other.
        *
        * @param: const ReverseIterator& -> Iterator to compare.
        *
        * @return: bool -> True if the iterator is lesser or equal.
        */
        _NODISCARD _CONSTEXPR17 bool operator<=(const ReverseIterator& other) const noexcept { return !(operator>(other)); }

        /**
        * @brief: Compares if the iterator is greater than the other.
        *
        * @param: const IteraReverseIteratortor& -> Iterator to compare.
        *
        * @return: bool -> True if the iterator is greater.
        */
        _NODISCARD _CONSTEXPR17 bool operator>(const ReverseIterator& other) const noexcept { return m_Ptr < other.m_Ptr; }

        /**
        * @brief: Compares if the iterator is greater or equal than the other.
        *
        * @param: const ReverseIterator& -> Iterator to compare.
        *
        * @return: bool -> True if the iterator is greater or equal.
        */
        _NODISCARD _CONSTEXPR17 bool operator>=(const ReverseIterator& other) const noexcept { return !(operator<(other)); }

        /**
        * @brief: Returns the comparison with the pointer.
        *
        * @return: bool -> True if the pointer is not nullptr.
        */
        _NODISCARD _CONSTEXPR17 operator bool() const noexcept { return m_Ptr; }

        /**
        * @brief: Returns the comparison with the pointer.
        *
        * @return: bool -> True if the pointer is not nullptr.
        */
        _NODISCARD _CONSTEXPR17 bool IsValid() const noexcept { return m_Ptr; }

        //Member functions
    public:
        _CONSTEXPR17 ReverseIterator(ValueType* ptr = nullptr) noexcept :
            m_Ptr(ptr) {}

        _CONSTEXPR17 ReverseIterator(const ReverseIterator& other) noexcept :
            m_Ptr(other.m_Ptr) {}

        _CONSTEXPR17 ReverseIterator(ReverseIterator&& other) noexcept :
            m_Ptr(other.m_Ptr)
        {
            other.m_Ptr = nullptr;
        }

        _CONSTEXPR17 ReverseIterator& operator=(const ReverseIterator& other) noexcept
        {
            m_Ptr = other.m_Ptr;
            return *this;
        }

        _CONSTEXPR17 ReverseIterator& operator=(ReverseIterator&& other) noexcept
        {
            m_Ptr = other.m_Ptr;
            other.m_Ptr = nullptr;
            return *this;
        }

        _CONSTEXPR17 ReverseIterator& operator=(ValueType* other) noexcept
        {
            m_Ptr = other;
            return *this;
        }

    public:
        ~ReverseIterator() noexcept { m_Ptr = nullptr; }

    private:
        ValueType* m_Ptr;
    };

    using iterator = Iterator<T>;
    using const_iterator = Iterator<const T>;
    using reverse_iterator = ReverseIterator<T>;
    using const_reverse_iterator = ReverseIterator<const T>;

    //Operations
public:
    /**
    * @brief: Fills the container with the given value.
    * @details: The container will clear the values before filling it with the new value.
    * 
    * @param: ValueType& -> Value.
    * 
    * @return: void.
    */
    void Fill(const T& value) noexcept
    {
        Clear();

        for (iterator it = begin(); it != end(); ++it)
        {
            *it = value;
        }
    }

    /**
    * @brief: Swaps the content of two Arrays.
    *
    * @param: Array& -> Array to swap.
    * 
    * @return: void.
    */
    void Swap(Array& other) noexcept
    {
        if (this == &other) { return; }

        iterator other_it = other.begin();
        for (iterator it = begin(); it != end(); ++it, ++other_it)
        {
            T temp(std::move(*it));
            *it = std::move(*other_it);
            *other_it = std::move(temp);
        }
    }

    /**
    * @brief: Clears the content of the container.
    *
    * @return: void.
    */
    void Clear() noexcept
    {
        for (iterator it = begin(); it != end(); ++it)
        {
            (*it).~T();
        }
    }

    //Capacity
public:
    /**
    * @brief: Returns the size of the container.
    *
    * @return: size_t -> Size
    */
    _NODISCARD _CONSTEXPR17 size_t Size() const noexcept { return S; }

    //Element Access
public:
    /**
    * @brief: Returns the first element of the container.
    * @details: The effect of calling Front() on a zero-sized array is undefined.
    *
    * @return: T& -> First element.
    */
    _NODISCARD _CONSTEXPR17 T& Front() noexcept { return m_Data[0]; }

    /**
    * @brief: Returns the first element of the container.
    * @details: The effect of calling Front() on a zero-sized array is undefined.
    *
    * @return: ValueType& -> First element.
    */
    _NODISCARD _CONSTEXPR17 const T& Front() const noexcept { return m_Data[0]; }

    /**
    * @brief: Returns the last element of the container.
    * @details: The effect of calling Back() on a zero-sized array is undefined.
    *
    * @return: T& -> Last element.
    */
    _NODISCARD _CONSTEXPR17 T& Back() noexcept { return m_Data[S - 1]; }

    /**
    * @brief: Returns the last element of the container.
    * @details: The effect of calling Back() on a zero-sized array is undefined.
    *
    * @return: ValueType& -> Last element.
    */
    _NODISCARD _CONSTEXPR17 const T& Back() const noexcept { return m_Data[S - 1]; }

    /**
    * @brief: Returns the element of the container at the given index.
    * @details: No bounds checks are performed.
    *
    * @param: size_t -> Index.
    * 
    * @return: T& -> Element.
    */
    _NODISCARD _CONSTEXPR17 T& operator[](size_t index) noexcept { return m_Data[index]; }

    /**
    * @brief: Returns the element of the container at the given index.
    * @details: No bounds checks are performed.
    *
    * @param: size_t -> Index.
    * 
    * @return: ValueType& -> Element.
    */
    _NODISCARD _CONSTEXPR17 const T& operator[](size_t index) const noexcept { return m_Data[index]; }

    /**
    * @brief: Returns the element of the container at the given index.
    * @details: If the index is out of range, throws std::exception.
    *
    * @param: size_t -> Index.
    * 
    * @return: T& -> Element.
    */
    _NODISCARD _CONSTEXPR17 T& At(size_t index)
    {
        if (index >= S) { ArrayOutOfRangeError(); }
        return m_Data[index];
    }

    /**
    * @brief: Returns the element of the container at the given index.
    * @details: If the index is out of range, throws std::exception.
    *
    * @param: size_t -> Index.
    * 
    * @return: ValueType& -> Element.
    */
    _NODISCARD _CONSTEXPR17 const T& At(size_t index) const
    {
        if (index >= S) { ArrayOutOfRangeError(); }
        return m_Data[index];
    }

    /**
    * @brief: Returns a pointer to the container data.
    *
    * @return: T* -> Data.
    */
    _NODISCARD _CONSTEXPR17 T* Data() noexcept { return m_Data; }

    /**
    * @brief: Returns a pointer to the container data.
    *
    * @return: ValueType* -> Data.
    */
    _NODISCARD _CONSTEXPR17 const T* Data() const noexcept { return m_Data; }

    //Iterators
public:
    /**
    * @brief: Returns an iterator to the begin of the container.
    *
    * @return: Iterator -> iterator.
    */
    _NODISCARD _CONSTEXPR17 iterator begin() noexcept { return iterator(m_Data); }

    /**
    * @brief: Returns an iterator to the begin of the container.
    *
    * @return: ConstIterator -> const_iterator.
    */
    _NODISCARD _CONSTEXPR17 const_iterator begin() const noexcept { return const_iterator(m_Data); }

    /**
    * @brief: Returns an iterator to the begin of the container.
    *
    * @return: ConstIterator -> const_iterator.
    */
    _NODISCARD _CONSTEXPR17 const_iterator cbegin() const noexcept { return const_iterator(m_Data); }

    /**
    * @brief: Returns an iterator to the end of the container.
    * @details: The iterator does not point to the last element, points outside the container instead.
    *
    * @return: Iterator -> iterator.
    */
    _NODISCARD _CONSTEXPR17 iterator end() noexcept { return iterator(m_Data + S); }

    /**
    * @brief: Returns an iterator to the end of the container.
    * @details: The iterator does not point to the last element, points outside the container instead.
    *
    * @return: ConstIterator -> const_iterator.
    */
    _NODISCARD _CONSTEXPR17 const_iterator end() const noexcept { return const_iterator(m_Data + S); }

    /**
    * @brief: Returns an iterator to the end of the container.
    * @details: The iterator does not point to the last element, points outside the container instead.
    *
    * @return: ConstIterator -> const_iterator.
    */
    _NODISCARD _CONSTEXPR17 const_iterator cend() const noexcept { return const_iterator(m_Data + S); }

    /**
    * @brief: Returns an iterator to the end of the container.
    * @details: The iterator points to the last element.
    *
    * @return: ReverseIterator -> reverse_iterator.
    */
    _NODISCARD _CONSTEXPR17 reverse_iterator rbegin() noexcept { return reverse_iterator(m_Data + S - 1); }

    /**
    * @brief: Returns an iterator to the end of the container.
    * @details: The iterator points to the last element.
    *
    * @return: ConstReverseIterator -> const_reverse_iterator.
    */
    _NODISCARD _CONSTEXPR17 const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(m_Data + S - 1); }

    /**
    * @brief: Returns an iterator to the end of the container.
    * @details: The iterator points to the last element.
    *
    * @return: ConstReverseIterator -> const_reverse_iterator.
    */
    _NODISCARD _CONSTEXPR17 const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(m_Data + S - 1); }

    /**
    * @brief: Returns an iterator to the begin of the container.
    * @details: The iterator does not point to the first element, points outside the container instead.
    *
    * @return: ReverseIterator -> reverse_iterator.
    */
    _NODISCARD _CONSTEXPR17 reverse_iterator rend() noexcept { return reverse_iterator(m_Data - 1); }

    /**
    * @brief: Returns an iterator to the begin of the container.
    * @details: The iterator does not point to the first element, points outside the container instead.
    *
    * @return: ConstReverseIterator -> const_reverse_iterator.
    */
    _NODISCARD _CONSTEXPR17 const_reverse_iterator rend() const noexcept { return const_reverse_iterator(m_Data - 1); }

    /**
    * @brief: Returns an iterator to the begin of the container.
    * @details: The iterator does not point to the first element, points outside the container instead.
    *
    * @return: ConstReverseIterator -> const_reverse_iterator.
    */
    _NODISCARD _CONSTEXPR17 const_reverse_iterator crend() const noexcept { return const_reverse_iterator(m_Data - 1); }

    //Non-member Functions
public:
    /**
    * @brief: Compares the content of two Arrays.
    *
    * @param: const Array& -> Array to compare.
    * 
    * @return: bool -> True if both containers are equal.
    */
    _NODISCARD _CONSTEXPR17 bool operator==(const Array& other) noexcept
    {
        if (this == &other) { return true; }
        const_iterator other_it = other.cbegin();
        for (const_iterator it = cbegin(); it != cend(); ++it, ++other_it)
        {
            if (*it != *other_it) { return false; }
        }

        return true;
    }

    /**
    * @brief: Compares the content of two Arrays.
    *
    * @param: const Array& -> Array to compare.
    * 
    * @return: bool -> True if both containers are not equal.
    */
    _NODISCARD _CONSTEXPR17 bool operator!=(const Array& other) noexcept { return !(operator==(other)); }

    //Member Functions
public:
    explicit Array() noexcept = default;

    explicit Array(const T& value) noexcept { Fill(value); }

    Array(const Array& other) noexcept
    {
        CopyFromArray(other);
    }

    Array(Array&& other) noexcept
    {
        MoveFromArray(std::move(other));
    }

    Array(std::initializer_list<T>&& items) noexcept
    {
        auto other_it = items.begin();
        for (iterator it = begin(); it != end(); ++it, ++other_it)
        {
            *it = std::move(*other_it);
        }
    }

    ~Array() noexcept = default;

    Array& operator=(const Array& other) noexcept
    {
        if (this == &other) { return *this; }
        Clear();
        CopyFromArray(other);
        return *this;
    }

    Array& operator=(Array&& other) noexcept
    {
        if (this == &other) { return *this; }
        Clear();
        MoveFromArray(std::move(other));
        return *this;
    }

    Array& operator=(std::initializer_list<T>&& items) noexcept
    {
        Clear();

        auto other_it = items.begin();
        for (iterator it = begin(); it != end(); ++it, ++other_it)
        {
            *it = std::move(*other_it);
        }

        return *this;
    }

private:
    [[noreturn]] static __forceinline void ArrayOutOfRangeError() {
        throw std::exception("Array index out of range");
    }

    __forceinline void CopyFromArray(const Array& other) noexcept
    {
        const_iterator other_it = other.cbegin();
        for (iterator it = begin(); it != end(); ++it, ++other_it)
        {
            *it = *other_it;
        }
    }

    __forceinline void MoveFromArray(Array&& other) noexcept
    {
        iterator other_it = other.begin();
        for (iterator it = begin(); it != end(); ++it, ++other_it)
        {
            *it = std::move(*other_it);
        }
    }

private:
    T m_Data[S];
};
