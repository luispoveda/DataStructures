#pragma once
/*
* Author: Luis Poveda Cano.
* luispovedacano@gmail.com
*/

/*
* Single header class.
* Vector class is a sequence container that encapsulates dynamic size Vectors.
* The storage of the vector is handled automatically, being expanded and contracted as needed.
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

template<typename T>
class Vector
{
public:
    template<typename ValueType>
    class Iterator
    {
        friend class Vector;
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
        friend class Vector;
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

    //Modifiers
public:
    /**
    * @brief: Resizes the container to the new capacity.
    * @details: Causes reallocation, if the current size is greater than count, the container is reduced to its first capacity elements.
    * Can throw exceptions (Typically std::bad_alloc)
    * If an exception is thrown, this function has no effect
    *
    * @param: size_t -> New capacity.
    * 
    * @return: void.
    */
    void Resize(size_t capacity)
    {
        if (capacity > m_Capacity) { return Reserve(capacity); }
        if (capacity == 0) { return Nullify(); }
        if (capacity == m_Capacity) { return; }

        T* new_block = AllocateNewBlock(capacity);

        if (capacity < m_Elements)
        {
            iterator it = begin();
            it += capacity;

            for (; it != end(); ++it)
            {
                (*it).~T();
            }

            m_Elements = capacity;
        }

        TransferData(new_block);

        m_Capacity = capacity;
        m_Data = new_block;
    }

    /**
    * @brief: Inserts a new element at the end of the container.
    * @details: If an exception is thrown (which can be due to Reserve or element copy/move constructor/assignment), this function has no effect.
    *
    * @param: const T& -> Element.
    * 
    * @return: void.
    */
    void PushBack(const T& element)
    {
        if (IsFull() || !m_Data) { Reserve(m_Capacity << 1); }
        new (&m_Data[m_Elements++]) T(element);
    }

    /**
    * @brief: Inserts a new element at the end of the container.
    * @details: If an exception is thrown (which can be due to Reserve or element copy/move constructor/assignment), this function has no effect.
    *
    * @param: T&& -> Element.
    * 
    * @return: void.
    */
    void PushBack(T&& element)
    {
        if (IsFull() || !m_Data) { Reserve(m_Capacity << 1); }
        new (&m_Data[m_Elements++]) T(std::move(element));
    }

    /**
    * @brief: Inserts a new element into the container directly before index.
    * @details: If an exception is thrown (which can be due to Reserve or element copy/move constructor/assignment), this function has no effect.
    *
    * @param: size_t -> Index.
    * @param: const T& -> Element.
    * 
    * @return: Iterator -> Iterator to the new element.
    */
    iterator Insert(size_t index, const T& element)
    {
        if (IsEmpty() || (index >= m_Elements))
        {
            PushBack(element);
            iterator it = end();
            return --it;
        }
        if (IsFull()) { Reserve(m_Capacity << 1); }

        iterator it = begin();
        it += index;
        RightMoveVectorData(it.m_Ptr);
        *it = element;
        ++m_Elements;

        return it;
    }

    /**
    * @brief: Inserts a new element into the container directly before index.
    * @details: If an exception is thrown (which can be due to Reserve or element copy/move constructor/assignment), this function has no effect.
    *
    * @param: Iterator -> Position.
    * @param: const T& -> Element.
    * 
    * @return: Iterator -> Iterator to the new element.
    */
    iterator Insert(iterator it, const T& element)
    {
        if (IsEmpty())
        {
            PushBack(element);
            return begin();
        }
        if (IsFull())
        {
            size_t distance = it.Distance(begin());
            Reserve(m_Capacity << 1);
            it = begin();
            it += distance;
        }

        RightMoveVectorData(it.m_Ptr);
        *it = element;
        ++m_Elements;

        return it;
    }

    /**
    * @brief: Inserts a new element into the container directly before index.
    * @details: If an exception is thrown (which can be due to Reserve or element copy/move constructor/assignment), this function has no effect.
    *
    * @param: ReverseIterator -> Position.
    * @param: const T& -> Element.
    * 
    * @return: ReverseIterator -> Iterator to the new element.
    */
    reverse_iterator Insert(reverse_iterator it, const T& element)
    {
        if (IsEmpty())
        {
            PushBack(element);
            return rbegin();
        }
        if (IsFull())
        {
            size_t distance = it.Distance(rbegin());
            Reserve(m_Capacity << 1);
            it = rbegin();
            it += distance;
        }

        RightMoveVectorData(it);
        *it = element;
        ++m_Elements;

        return it;
    }

    /**
    * @brief: Inserts a new element into the container directly before index.
    * @details: If an exception is thrown (which can be due to Reserve or element copy/move constructor/assignment), this function has no effect.
    *
    * @param: size_t -> Index.
    * @param: T&& -> Element.
    * 
    * @return: Iterator -> Iterator to the new element.
    */
    iterator Insert(size_t index, T&& element)
    {
        if (IsEmpty() || (index >= m_Elements))
        {
            PushBack(element);
            iterator it = end();
            return --it;
        }
        if (IsFull()) { Reserve(m_Capacity << 1); }

        iterator it = begin();
        it += index;
        RightMoveVectorData(it.m_Ptr);
        *it = std::move(element);
        ++m_Elements;

        return it;
    }

    /**
    * @brief: Inserts a new element into the container directly before index.
    * @details: If an exception is thrown (which can be due to Reserve or element copy/move constructor/assignment), this function has no effect.
    *
    * @param: Iterator -> Position.
    * @param: T&& -> Element.
    * 
    * @return: Iterator -> Iterator to the new element.
    */
    iterator Insert(iterator it, T&& element)
    {
        if (IsEmpty())
        {
            PushBack(std::move(element));
            return begin();
        }
        if (IsFull())
        {
            size_t distance = it.Distance(begin());
            Reserve(m_Capacity << 1);
            it = begin();
            it += distance;
        }

        RightMoveVectorData(it.m_Ptr);
        *it = std::move(element);
        ++m_Elements;

        return it;
    }

    /**
    * @brief: Inserts a new element into the container directly before index.
    * @details: If an exception is thrown (which can be due to Reserve or element copy/move constructor/assignment), this function has no effect.
    *
    * @param: ReverseIterator -> Position.
    * @param: T&& -> Element.
    * 
    * @return: ReverseIterator -> Iterator to the new element.
    */
    reverse_iterator Insert(reverse_iterator it, T&& element)
    {
        if (IsEmpty())
        {
            PushBack(element);
            return rbegin();
        }
        if (IsFull())
        {
            size_t distance = it.Distance(rbegin());
            Reserve(m_Capacity << 1);
            it = rbegin();
            it += distance;
        }

        RightMoveVectorData(it.m_Ptr);
        *it = std::move(element);
        ++m_Elements;

        return it;
    }

    /**
    * @brief: Inserts a new element at the end of the container.
    * @details: The element is constructed in place.
    * If an exception is thrown (which can be due to Reserve or element copy/move constructor/assignment), this function has no effect.
    *
    * @param: Args -> Arguments needed to create the element.
    * 
    * @return: iterator -> Iterator to the new element.
    */
    template<typename... Args>
    iterator EmplaceBack(Args&&... args)
    {
        if (IsFull() || !m_Data) { Reserve(m_Capacity << 1); }
        iterator it = end();
        new (&m_Data[m_Elements++]) T(std::forward<Args>(args)...);
        return it;
    }

    /**
    * @brief: Inserts a new element into the container directly before index.
    * @details: The element is constructed in place.
    * If an exception is thrown (which can be due to Reserve or element copy/move constructor/assignment), this function has no effect.
    *
    * @param: size_t -> Index.
    * @param: Args -> Arguments needed to create the element.
    * 
    * @return: Iterator -> Iterator to the new element.
    */
    template<typename... Args>
    iterator Emplace(size_t index, Args&&... args)
    {
        if (IsEmpty() || (index >= m_Elements))
        {
            EmplaceBack(std::forward<Args>(args)...);
            iterator it = end();
            return --it;
        }
        if (IsFull()) { Reserve(m_Capacity << 1); }

        iterator it = begin();
        it += index;
        RightMoveVectorData(it.m_Ptr);
        (*it).~T();
        new (it.m_Ptr) T(std::forward<Args>(args)...);
        ++m_Elements;

        return it;
    }

    /**
    * @brief: Inserts a new element into the container directly before index.
    * @details: The element is constructed in place.
    * If an exception is thrown (which can be due to Reserve or element copy/move constructor/assignment), this function has no effect.
    * 
    * @param: Iterator -> Position.
    * @param: Args -> Arguments needed to create the element.
    * 
    * @return: Iterator -> Iterator to the new element.
    */
    template<typename... Args>
    iterator Emplace(iterator it, Args&&... args)
    {
        if (IsEmpty())
        {
            EmplaceBack(std::forward<Args>(args)...);
            return begin();
        }
        if (IsFull())
        {
            size_t distance = it.Distance(begin());
            Reserve(m_Capacity << 1);
            it = begin();
            it += distance;
        }

        RightMoveVectorData(it.m_Ptr);
        (*it).~T();
        new (it.m_Ptr) T(std::forward<Args>(args)...);
        ++m_Elements;

        return it;
    }

    /**
    * @brief: Inserts a new element into the container directly before index.
    * @details: The element is constructed in place.
    * If an exception is thrown (which can be due to Reserve or element copy/move constructor/assignment), this function has no effect.
    *
    * @param: ReverseIterator -> Position.
    * @param: Args -> Arguments needed to create the element.
    * 
    * @return: ReverseIterator -> Iterator to the new element.
    */
    template<typename... Args>
    reverse_iterator Emplace(reverse_iterator it, Args&&... args)
    {
        if (IsEmpty())
        {
            EmplaceBack(std::forward<Args>(args)...);
            return rbegin();
        }
        if (IsFull())
        {
            size_t distance = it.Distance(rbegin());
            Reserve(m_Capacity << 1);
            it = rbegin();
            it += distance;
        }

        RightMoveVectorData(it.m_Ptr);
        (*it).~T();
        new (it.m_Ptr) T(std::forward<Args>(args)...);
        ++m_Elements;

        return it;
    }

    /**
    * @brief: Delete the last element of the container.
    * @details: No reallocations are performed.
    *
    * @return: void.
    */
    void PopBack() noexcept
    {
        if (IsEmpty()) { return; }
        reverse_iterator it = rbegin();
        (*it).~T();
        --m_Elements;
    }

    /**
    * @brief: Delete the element at the given index.
    * @details: No reallocations are performed.
    *
    * @param: size_t -> Index.
    * 
    * @return: Iterator -> Iterator to the element at the index position after deleting.
    */
    iterator Erase(size_t index) noexcept
    {
        if (IsEmpty()) { return iterator(); }
        if (index == m_Elements - 1)
        {
            PopBack();
            return end();
        }

        iterator it = begin();
        it += index;
        (*it).~T();

        LeftMoveVectorData(it.m_Ptr);
        --m_Elements;
        (*end()).~T();

        return it;
    }

    /**
    * @brief: Delete the element at the given iterator.
    * @details: No reallocations are performed.
    *
    * @param: Ierator -> Position.
    * 
    * @return: Iterator -> Iterator to the element at the index position after deleting.
    */
    iterator Erase(iterator it) noexcept
    {
        if (IsEmpty()) { return iterator(); }
        if (it < begin() || it >= end()) { return iterator(); }
        iterator aux = end();
        --aux;
        if (it == aux)
        {
            PopBack();
            aux = end();
            return --aux;
        }

        (*it).~T();
        LeftMoveVectorData(it.m_Ptr);
        --m_Elements;
        (*end()).~T();

        return it;
    }

    /**
    * @brief: Delete the element at the given iterator.
    * @details: No reallocations are performed.
    *
    * @param: ReverseIterator -> Position.
    * @return: ReverseIterator -> Iterator to the element at the index position after deleting.
    */
    reverse_iterator Erase(reverse_iterator it) noexcept
    {
        if (IsEmpty()) { return reverse_iterator(); }
        if (it < rbegin() || it >= rend()) { return reverse_iterator(); }
        if (it == rbegin())
        { 
            PopBack();
            reverse_iterator aux = rbegin();
            return aux;
        }

        (*it).~T();
        LeftMoveVectorData(it.m_Ptr);
        --m_Elements;
        (*end()).~T();

        return it;
    }

    /**
    * @brief: Clears the content of the container.
    * @details: By clearing the container, no reallocations are performed.
    *
    * @return: void.
    */
    void Clear() noexcept
    {
        if (!m_Data) { return; }
        for (iterator it = begin(); it != end(); ++it)
        {
            (*it).~T();
        }
        m_Elements = 0;
    }

    /**
    * @brief: Appends other vector at the end of the container.
    * @details: The elements are copied from the given vector.
    * If the container is the same as the given, no action will be performed.
    *
    * @param: Vector& -> Vector to append.
    * 
    * @return: void.
    */
    void Append(const Vector& other)
    {
        if (this == &other) { return; }
        if (other.IsEmpty()) { return; }

        Reserve(m_Capacity + other.m_Capacity);
        CopyFromVector(other);
    }

    /**
    * @brief: Appends other vector at the end of the container.
    * @details: The elements are moved from the given vector.
    * If the container is the same as the given, no action will be performed.
    *
    * @param: Vector&& -> Vector to append.
    * 
    * @return: void.
    */
    void Append(Vector&& other)
    {
        if (this == &other) { return; }
        if (other.IsEmpty()) { return; }

        Reserve(m_Capacity + other.m_Capacity);
        for (iterator it = other.begin(); it != other.end(); ++it)
        {
            PushBack(std::move(*it));
        }
        other.Nullify();
    }

    /**
    * @brief: Swaps the content of two Vectors.
    * @details: If the container is the same as the given, no action will be performed.
    *
    * @param: Vector& -> Vector to swap.
    * 
    * @return: void.
    */
    void Swap(Vector& other) noexcept
    {
        if (this == &other) { return; }

        T* aux_data = m_Data;
        size_t aux_capacity = m_Capacity;
        size_t aux_elements = m_Elements;

        m_Data = other.m_Data;
        m_Capacity = other.m_Capacity;
        m_Elements = other.m_Elements;

        other.m_Data = aux_data;
        other.m_Capacity = aux_capacity;
        other.m_Elements = aux_elements;
    }

    //Capacity
public:
    /**
    * @brief: Requests the removal of unused capacity.
    * @details: Causes reallocation.
    * Can throw exceptions (Typically std::bad_alloc)
    * If an exception is thrown, this function has no effect
    *
    * @return: void.
    */
    void Shrink()
    {
        if (!m_Data) { return; }
        if (m_Elements == 0) { return DeleteStorage(); }
        if (m_Capacity <= m_Elements) { return; }

        T* new_block = AllocateNewBlock(m_Elements);
        TransferData(new_block);

        m_Capacity = m_Elements;
        m_Data = new_block;
    }

    /**
    * @brief: Resizes the container to the new capacity.
    * @details: Causes reallocation, the new capacity must be greater than the current capacity.
    * Can throw exceptions (Typically std::bad_alloc)
    * If an exception is thrown, this function has no effect
    *
    * @param: size_t -> New capacity.
    * 
    * @return: void.
    */
    void Reserve(size_t capacity)
    {
        if (capacity > s_MaxVectorSize)
        {
            VectorMaxLenghtError();
            return;
        }
        if (capacity <= m_Capacity)
        {
            if (m_Data) { return; }
            capacity = 8;
        }

        T* new_block = AllocateNewBlock(capacity);
        if (m_Data) { TransferData(new_block); }

        m_Capacity = capacity;
        m_Data = new_block;
    }

    /**
    * @brief: Checks if the container is empty.
    *
    * @return: bool -> True if the container has no elements.
    */
    _NODISCARD __forceinline bool IsEmpty() const noexcept { return m_Elements == 0; }

    /**
    * @brief: Checks if the container is full.
    *
    * @return: bool -> True if the container is full.
    */
    _NODISCARD __forceinline bool IsFull() const noexcept { return m_Elements == m_Capacity; }

    /**
    * @brief: Current capacity of the container.
    *
    * @return: size_t -> Capacity.
    */
    _NODISCARD __forceinline size_t Capacity() const noexcept { return m_Capacity; }

    /**
    * @brief: Number of elements in the container.
    *
    * @return: size_t -> Elements.
    */
    _NODISCARD __forceinline size_t Size() const noexcept { return m_Elements; }

    //Element Access
public:
    /**
    * @brief: Return the first element in the container.
    * @details: Calling Front in a empty container is undefined.
    *
    * @return: T& -> Element.
    */
    _NODISCARD __forceinline T& Front() noexcept { return m_Data[0]; }

    /**
    * @brief: Return the first element in the container.
    * @details: Calling Front in a empty container is undefined.
    *
    * @return: const T& -> Element.
    */
    _NODISCARD __forceinline const T& Front() const noexcept { return m_Data[0]; }

    /**
    * @brief: Return the last element in the container.
    * @details: Calling Back in a empty container is undefined.
    *
    * @return: T& -> Element.
    */
    _NODISCARD __forceinline T& Back() noexcept { return m_Data[m_Elements - 1]; }

    /**
    * @brief: Return the last element in the container.
    * @details: Calling Back in a empty container is undefined.
    *
    * @return: const T& -> Element.
    */
    _NODISCARD __forceinline const T& Back() const noexcept { return m_Data[m_Elements - 1]; }

    /**
    * @brief: Return the element at the given index.
    * @details: Calling [] in a empty container is undefined.
    *
    * @param: size_t -> Position.
    * 
    * @return: T& -> Element.
    */
    _NODISCARD __forceinline T& operator[](size_t index) noexcept { return m_Data[index]; }

    /**
    * @brief: Return the element at the given index.
    * @details: Calling [] in a empty container is undefined.
    *
    * @param: size_t -> Position.
    * 
    * @return: const T& -> Element.
    */
    _NODISCARD __forceinline const T& operator[](size_t index) const noexcept { return m_Data[index]; }

    /**
    * @brief: Return the element of the container at the given index.
    * @details: If the index is out of range, throws std::exception.
    *
    * @param: size_t -> Position.
    * 
    * @return: T& -> Element.
    */
    _NODISCARD __forceinline T& At(size_t index)
    {
        if (index >= m_Elements) { VectorOutOfRangeError(); }
        return m_Data[index];
    }

    /**
    * @brief: Return the element of the container at the given index.
    * @details: If the index is out of range, throws std::exception.
    *
    * @param: size_t -> Position.
    * 
    * @return: const T& -> Element.
    */
    _NODISCARD __forceinline const T& At(size_t index) const
    {
        if (index >= m_Elements) { VectorOutOfRangeError(); }
        return m_Data[index];
    }

    /**
    * @brief: Return a pointer to the container data.
    *
    * @return: T* -> Data.
    */
    _NODISCARD __forceinline T* Data() noexcept { return m_Data; }

    /**
    * @brief: Return a pointer to the container data.
    *
    * @return: const T* -> Data.
    */
    _NODISCARD __forceinline const T* Data() const noexcept { return m_Data; }

    //Iterators
public:
    /**
    * @brief: Return an iterator to the begin of the container.
    *
    * @return: Iterator -> Iterator.
    */
    _NODISCARD __forceinline iterator begin() noexcept { return iterator(m_Data); }

    /**
    * @brief: Return an iterator to the begin of the container.
    *
    * @return: ConstIterator -> Iterator.
    */
    _NODISCARD __forceinline const_iterator begin() const noexcept { return const_iterator(m_Data); }

    /**
    * @brief: Return an iterator to the begin of the container.
    *
    * @return: ConstIterator -> Iterator.
    */
    _NODISCARD __forceinline const_iterator cbegin() const noexcept { return const_iterator(m_Data); }

    /**
    * @brief: Return an iterator to the end of the container.
    * @details: The iterator does not point to the last element, points outside the container instead.
    *
    * @return: Iterator -> Iterator.
    */
    _NODISCARD __forceinline iterator end() noexcept { return iterator(m_Data + m_Elements); }

    /**
    * @brief: Return an iterator to the end of the container.
    * @details: The iterator does not point to the last element, points outside the container instead.
    *
    * @return: ConstIterator -> Iterator.
    */
    _NODISCARD __forceinline const_iterator end() const noexcept { return const_iterator(m_Data + m_Elements); }

    /**
    * @brief: Return an iterator to the end of the container.
    * @details: The iterator does not point to the last element, points outside the container instead.
    *
    * @return: ConstIterator -> Iterator.
    */
    _NODISCARD __forceinline const_iterator cend() const noexcept { return const_iterator(m_Data + m_Elements); }

    /**
    * @brief: Return an iterator to the end of the container.
    * @details: The iterator points to the last element.
    *
    * @return: ReverseIterator -> Iterator.
    */
    _NODISCARD __forceinline reverse_iterator rbegin() noexcept { return reverse_iterator(m_Data + m_Elements - 1); }

    /**
    * @brief: Return an iterator to the end of the container.
    * @details: The iterator points to the last element.
    *
    * @return: ConstReverseIterator -> Iterator.
    */
    _NODISCARD __forceinline const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(m_Data + m_Elements - 1); }

    /**
    * @brief: Return an iterator to the end of the container.
    * @details: The iterator points to the last element.
    *
    * @return: ConstReverseIterator -> Iterator.
    */
    _NODISCARD __forceinline const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(m_Data + m_Elements - 1); }

    /**
    * @brief: Return an iterator to the begin of the container.
    * @details: The iterator does not point to the first element, points outside the container instead.
    *
    * @return: ReverseIterator -> Iterator.
    */
    _NODISCARD __forceinline reverse_iterator rend() noexcept { return reverse_iterator(m_Data - 1); }

    /**
    * @brief: Return an iterator to the begin of the container.
    * @details: The iterator does not point to the first element, points outside the container instead.
    *
    * @return: ConstReverseIterator -> Iterator.
    */
    _NODISCARD __forceinline const_reverse_iterator rend() const noexcept { return const_reverse_iterator(m_Data - 1); }

    /**
    * @brief: Return an iterator to the begin of the container.
    * @details: The iterator does not point to the first element, points outside the container instead.
    *
    * @return: ConstReverseIterator -> Iterator.
    */
    _NODISCARD __forceinline const_reverse_iterator crend() const noexcept { return const_reverse_iterator(m_Data - 1); }

    //Member functions
public:
    explicit Vector() noexcept = default;

    explicit Vector(size_t capacity) noexcept
    {
        Reserve(capacity);
    }

    Vector(const Vector& other) noexcept
    {
        if (!other.m_Data || other.m_Capacity == 0) { return; }

        Reserve(other.m_Capacity);
        CopyFromVector(other);
    }

    Vector(Vector&& other) noexcept :
        m_Capacity(other.m_Capacity),
        m_Elements(other.m_Elements),
        m_Data(other.m_Data)
    {
        other.m_Capacity = 0;
        other.m_Elements = 0;
        other.m_Data = nullptr;
    }

    Vector(std::initializer_list<T>&& list) noexcept
    {
        Reserve(list.size());
        for (auto it = list.begin(); it != list.end(); ++it)
        {
            PushBack(std::move(*it));
        }
    }

    ~Vector() noexcept
    {
        Nullify();
    }

    Vector& operator=(const Vector& other) noexcept
    {
        if (&other == this) { return *this; }
        
        Nullify();
        if (!other.m_Data) { return *this; }

        Reserve(other.m_Capacity);
        CopyFromVector(other);

        return *this;
    }

    Vector& operator=(Vector&& other) noexcept
    {
        if (this == &other) { return *this; }
        Nullify();
        if (!other.m_Data) { return *this; }

        m_Capacity = other.m_Capacity;
        m_Elements = other.m_Elements;
        m_Data = other.m_Data;

        other.m_Capacity = 0;
        other.m_Elements = 0;
        other.m_Data = nullptr;

        return *this;
    }

    Vector& operator=(std::initializer_list<T>&& list) noexcept
    {
        Nullify();
        Reserve(list.size());

        for (auto list_it = list.begin(); list_it != list.end(); ++list_it)
        {
            T temp(std::move(*list_it));
            PushBack(std::move(temp));
        }

        return *this;
    }

    //Non-member functions
public:
    /**
    * @brief: Compares the content of two Vectors.
    *
    * @return: bool -> True if the content of both containers are equal.
    */
    _NODISCARD __forceinline bool operator==(const Vector& other) const noexcept
    {
        if (this == &other) { return true; }

        const_iterator other_it = other.cbegin();
        for (const_iterator this_it = cbegin(); this_it != cend(); ++this_it, ++other_it)
        {
            if (*this_it != *other_it) { return false; }
        }

        return true;
    }

    /**
    * @brief: Compares the content of two Vectors.
    *
    * @return: bool -> True if the content of both containers are not equal.
    */
    _NODISCARD __forceinline bool operator!=(const Vector& other) const noexcept { return !(operator==(other)); }

    /**
    * @brief: Compares the size of the Vector with other.
    *
    * @return: bool -> True if the Vector size is smaller than other.
    */
    _NODISCARD __forceinline bool operator<(const Vector& other) const noexcept { return Size() < other.Size() ? true : false; }

    /**
    * @brief: Compares the size of the Vector with other.
    *
    * @return: bool -> True if the Vector size is smaller or equal than other.
    */
    _NODISCARD __forceinline bool operator<=(const Vector& other) const noexcept { return Size() <= other.Size() ? true : false; }

    /**
    * @brief: Compares the size of the Vector with other.
    *
    * @return: bool -> True if the Vector size is bigger than other.
    */
    _NODISCARD __forceinline bool operator>(const Vector& other) const noexcept { return Size() > other.Size() ? true : false; }

    /**
    * @brief: Compares the size of the Vector with other.
    *
    * @return: bool -> True if the Vector size is bigger or equal than other.
    */
    _NODISCARD __forceinline bool operator>=(const Vector& other) const noexcept { return Size() >= other.Size() ? true : false; }

private:
    __forceinline void CopyFromVector(const Vector& other) noexcept
    {
        for (const_iterator it = other.cbegin(); it != other.cend(); ++it)
        {
            PushBack(*it);
        }
    }

    __forceinline void Nullify() noexcept
    {
        if (m_Data)
        {
            Clear();
            DeleteStorage();
        }
    }

    __forceinline void DeleteStorage() noexcept
    {
        ::operator delete(m_Data, sizeof(T) * m_Capacity);
        m_Capacity = 0;
        m_Data = nullptr;
    }

    void LeftMoveVectorData(iterator it) noexcept
    {
        if constexpr (std::is_trivially_copyable<T>::value)
        {
            size_t elements = it.Distance(end());
            iterator tmp(it);
            ++tmp;
            std::memmove(it.m_Ptr, tmp.m_Ptr, sizeof(T) * elements);
        }
        else
        {
            iterator to = it++;
            for (; it != end(); ++it, ++to)
            {
                *to = std::move(*it);
            }
        }
    }

    void RightMoveVectorData(reverse_iterator it) noexcept
    {
        if constexpr (std::is_trivially_copyable<T>::value)
        {
            size_t elements = it.Distance(rbegin());
            ++elements;
            reverse_iterator tmp(it);
            --it;
            std::memmove(it.m_Ptr, tmp.m_Ptr, sizeof(T) * elements);
        }
        else
        {
            reverse_iterator from(rbegin());
            reverse_iterator to(from);
            --to;
            new (to.m_Ptr) T(std::move(*from++));
            ++to;

            for (; to != it; ++from, ++to)
            {
                *to = std::move(*from);
            }
        }
    }

    _NODISCARD T* AllocateNewBlock(size_t size)
    {
        T* memory_block = nullptr;
        try
        {
            memory_block = (T*)::operator new(sizeof(T) * size);
        }
        catch (...)
        {
            throw std::exception("Bad allocation");
        }

        return memory_block;
    }

    __forceinline void TransferData(T* memory_block) noexcept
    {
        for (iterator it = begin(); it != end(); ++it, ++memory_block)
        {
            new (memory_block) T(std::move(*it));
            (*it).~T();
        }
        ::operator delete(m_Data, sizeof(T) * m_Capacity);
    }

    [[noreturn]] static __forceinline void VectorOutOfRangeError() {
        throw std::exception("Vector index out of range");
    }

    [[noreturn]] static __forceinline void VectorMaxLenghtError() {
        throw std::exception("Vector too long");
    }

    [[noreturn]] static __forceinline void VectorBadAllocationError() {
        throw std::exception("Bad allocation");
    }

private:
    size_t m_Capacity = 0;
    size_t m_Elements = 0;
    T* m_Data = nullptr;

    static _CONSTEXPR17 size_t s_MaxVectorSize = 10000000;
};
