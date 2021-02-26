#pragma once

/*
* Author: Luis Poveda Cano.
* luispovedacano@gmail.com
*/

/*
* Single header class.
* Lists are sequence containers that allow constant time insert and erase operations anywhere within the sequence, and iteration in both directions.
* List containers are implemented as doubly-linked lists.
* Doubly linked lists can store each of the elements they contain in different and unrelated storage locations.
* The ordering is kept internally by the association to each element of a link to the element preceding it and a link to the element following it.
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
class List
{
    struct Node
    {
        //Modifiers
    public:
        __forceinline void SetData(const T& data) noexcept
        {
            if (Data) { *Data = data; }
            else
            {
                GenerateData();
                new (Data) T(data);
            }
        }

        __forceinline void SetData(T&& data) noexcept
        {
            if (Data) { *Data = std::move(data); }
            else
            {
                GenerateData();
                new (Data) T(std::move(data));
            }
        }

        template<typename... Args>
        __forceinline void SetData(Args&&... args) noexcept
        {
            if (Data) { new (Data) T(std::forward<Args>(args)...); }
            else
            {
                GenerateData();
                new (Data) T(std::forward<Args>(args)...);
            }
        }

        __forceinline void ClearData() noexcept
        {
            if (Data)
            {
                Data->~T();
                Data = nullptr;
            }
        }

        //Member functions
    public:
        Node() noexcept = default;

        Node(Node* prev, Node* next) noexcept :
            Data(nullptr),
            Prev(prev),
            Next(next) {}

        Node(const T& data) noexcept
        {
            GenerateData();
            new (Data) T(data);
        }

        Node(T&& data) noexcept
        {
            GenerateData();
            new (Data) T(std::move(data));
        }

        template<typename... Args>
        Node(Args&&... args) noexcept
        {
            GenerateData();
            new (Data) T(std::forward<Args>(args)...);
        }

        ~Node() noexcept
        {
            ClearData();
            Prev = nullptr;
            Next = nullptr;
        }

    private:
        __forceinline void GenerateData() noexcept
        {
            Node* aux = this;
            ++aux;
            Data = reinterpret_cast<T*>(aux);
        }

    public:
        T* Data = nullptr;
        Node* Prev = nullptr;
        Node* Next = nullptr;
    };

public:
    template<typename ValueType>
    class Iterator
    {
        friend class List;
        //Modifiers
    public:
        /**
        * @brief: Moves the iterator to the next element.
        * @details: Pre increment.
        *
        * @return: Iterator& -> Current iterator.
        */
        __forceinline Iterator& operator++() noexcept
        {
            m_Ptr = m_Ptr->Next;
            return *this;
        }

        /**
        * @brief: Moves the iterator to the next element.
        * @details: Post increment.
        *
        * @return: Iterator -> Iterator at previous position.
        */
        _NODISCARD __forceinline Iterator operator++(int) noexcept
        {
            Iterator it(m_Ptr);
            m_Ptr = m_Ptr->Next;
            return it;
        }

        /**
        * @brief: Moves the iterator forwards by the given distance.
        *
        * @param: size_t -> distance to move.
        * @return: Iterator& -> Current iterator.
        */
        __forceinline Iterator& operator+=(size_t distance) noexcept
        {
            for (size_t i = 0; i < distance; ++i)
            {
                m_Ptr = m_Ptr->Next;
            }

            return *this;
        }

        /**
        * @brief: Moves the iterator forwards by the given distance.
        * @details: By giving a negative number, the iterator will move backwards instead.
        *
        * @param: int -> distance to move.
        * @return: Iterator& -> Current iterator.
        */
        Iterator& operator+=(int distance) noexcept
        {
            if (distance < 0)
            {
                distance *= -1;
                for (int i = 0; i < distance; ++i)
                {
                    m_Ptr = m_Ptr->Prev;
                }
            }
            else
            {
                for (int i = 0; i < distance; ++i)
                {
                    m_Ptr = m_Ptr->Next;
                }
            }
            return *this;
        }

        /**
        * @brief: Moves the iterator forwards by the given distance.
        * @details: By default the distance is 1.
        * If the iterator is not valid, throws std::exception.
        *
        * @param: size_t -> distance to move.
        * @return: void.
        */
        void Advance(size_t distance = 1)
        {
            if (!m_Ptr) { throw std::exception("Invalid iterator"); }
            for (size_t i = 0; i < distance; ++i)
            {
                m_Ptr = m_Ptr->Next;
            }
        }

        /**
        * @brief: Moves the iterator forwards by the given distance.
        * @details: By giving a negative number, the iterator will move backwards instead.
        * By default the distance is 1.
        * If the iterator is not valid, throws std::exception.
        *
        * @param: int -> distance to move.
        * @return: void.
        */
        void Advance(int distance = 1)
        {
            if (!m_Ptr) { throw std::exception("Invalid iterator"); }
            if (distance < 0)
            {
                distance *= -1;
                for (int i = 0; i < distance; ++i)
                {
                    m_Ptr = m_Ptr->Prev;
                }
            }
            else
            {
                for (int i = 0; i < distance; ++i)
                {
                    m_Ptr = m_Ptr->Next;
                }
            }
        }

        /**
        * @brief: Moves the iterator to the previous element.
        * @details: Pre increment.
        *
        * @return: Iterator& -> Current iterator.
        */
        __forceinline Iterator& operator--() noexcept
        {
            m_Ptr = m_Ptr->Prev;
            return *this;
        }

        /**
        * @brief: Moves the iterator to the previous element.
        * @details: Post increment.
        *
        * @return: Iterator -> Iterator at previous position.
        */
        _NODISCARD __forceinline Iterator operator--(int) noexcept
        {
            Iterator it(m_Ptr);
            m_Ptr = m_Ptr->Prev;
            return it;
        }

        /**
        * @brief: Moves the iterator backwards by the given distance.
        *
        * @param: size_t -> distance to move.
        * @return: Iterator& -> Current iterator.
        */
        __forceinline Iterator& operator-=(size_t distance) noexcept
        {
            for (size_t i = 0; i < distance; ++i)
            {
                m_Ptr = m_Ptr->Prev;
            }
            return *this;
        }

        /**
        * @brief: Moves the iterator backwards by the given distance.
        * @details: By giving a negative number, the iterator will move forwards instead.
        *
        * @param: int -> distance to move.
        * @return: Iterator& -> Current iterator.
        */
        __forceinline Iterator& operator-=(int distance) noexcept
        {
            if (distance < 0)
            {
                distance *= -1;
                for (int i = 0; i < distance; ++i)
                {
                    m_Ptr = m_Ptr->Next;
                }
            }
            else
            {
                for (int i = 0; i < distance; ++i)
                {
                    m_Ptr = m_Ptr->Prev;
                }
            }
            return *this;
        }

        /**
        * @brief: Moves the iterator backwards by the given distance.
        * @details: By default the distance is 1.
        * If the iterator is not valid, throws std::exception.
        *
        * @param: size_t -> distance to move.
        * @return: void.
        */
        __forceinline void Retreat(size_t distance = 1)
        {
            if (!m_Ptr) { throw std::exception("Invalid iterator"); }
            for (size_t i = 0; i < distance; ++i)
            {
                m_Ptr = m_Ptr->Prev;
            }
        }

        /**
        * @brief: Moves the iterator backwards by the given distance.
        * @details: By giving a negative number, the iterator will move forwards instead.
        * By default the distance is 1.
        * If the iterator is not valid, throws std::exception.
        *
        * @param: int -> distance to move.
        * @return: void.
        */
        __forceinline void Retreat(int distance = 1)
        {
            if (!m_Ptr) { throw std::exception("Invalid iterator"); }
            if (distance < 0)
            {
                distance *= -1;
                for (int i = 0; i < distance; ++i)
                {
                    m_Ptr = m_Ptr->Next;
                }
            }
            else
            {
                for (int i = 0; i < distance; ++i)
                {
                    m_Ptr = m_Ptr->Prev;
                }
            }
        }

        /**
        * @brief: Returns an iterator to the forward distance given from the current iterator.
        *
        * @param: size_t -> distance to move.
        * @return: Iterator -> Iterator in the resulting position.
        */
        _NODISCARD __forceinline Iterator operator+(size_t distance) const noexcept
        {
            Iterator it(m_Ptr);
            it += distance;
            return it;
        }

        /**
        * @brief: Returns an iterator to the forward distance given from the current iterator.
        * @details: By giving a negative number, the iterator will move backwards instead.
        *
        * @param: int -> distance to move.
        * @return: Iterator -> Iterator in the resulting position.
        */
        _NODISCARD __forceinline Iterator operator+(int distance) const noexcept
        {
            Iterator it(m_Ptr);
            it += distance;
            return it;
        }

        /**
        * @brief: Return an iterator pointing to the element after being advanced by certain number of positions.
        * @details: By default the distance is 1.
        * If the iterator is not valid, throws std::exception.
        *
        * @param: size_t -> Number of elements to advance.
        * @return: Iterator -> Iterator at new position.
        */
        _NODISCARD __forceinline Iterator Next(size_t distance = 1) const
        {
            if (!m_Ptr) { throw std::exception("Invalid iterator"); }
            Iterator it(m_Ptr);
            it += distance;
            return it;
        }

        /**
        * @brief: Return an iterator pointing to the element after being advanced by certain number of positions.
        * @details: By giving a negative number, the iterator will move backwards instead.
        * By default the distance is 1.
        * If the iterator is not valid, throws std::exception.
        *
        * @param: size_t -> Number of elements to advance.
        * @return: Iterator -> Iterator at new position.
        */
        _NODISCARD __forceinline Iterator Next(int distance = 1) const
        {
            if (!m_Ptr) { throw std::exception("Invalid iterator"); }
            Iterator it(m_Ptr);
            it += distance;
            return it;
        }

        /**
        * @brief: Returns an iterator to the backward distance given from the current iterator.
        *
        * @param: size_t -> distance to move.
        * @return: Iterator -> Iterator in the resulting position.
        */
        _NODISCARD __forceinline Iterator operator-(size_t distance) const noexcept
        {
            Iterator it(m_Ptr);
            it -= distance;
            return it;
        }

        /**
        * @brief: Returns an iterator to the backward distance given from the current iterator.
        * @details: By giving a negative number, the iterator will move forwards instead.
        *
        * @param: int -> distance to move.
        * @return: Iterator -> Iterator in the resulting position.
        */
        _NODISCARD __forceinline Iterator operator-(int distance) const noexcept
        {
            Iterator it(m_Ptr);
            it -= distance;
            return it;
        }

        /**
        * @brief: Return an iterator pointing to the element after being moved back by certain number of positions.
        * @details: By default the distance is 1.
        * If the iterator is not valid, throws std::exception.
        *
        * @param: size_t -> Number of elements to retreat.
        * @return: Iterator -> Iterator at new position.
        */
        _NODISCARD __forceinline Iterator Prev(size_t distance = 1) const
        {
            if (!m_Ptr) { throw std::exception("Invalid iterator"); }
            Iterator it(m_Ptr);
            it -= distance;
            return it;
        }

        /**
        * @brief: Return an iterator pointing to the element after being moved back by certain number of positions.
        * @details: By giving a negative number, the iterator will move forwards instead.
        * By default the distance is 1.
        * If the iterator is not valid, throws std::exception.
        *
        * @param: int -> Number of elements to retreat.
        * @return: Iterator -> Iterator at new position.
        */
        _NODISCARD __forceinline Iterator Prev(int distance = 1) const
        {
            if (!m_Ptr) { throw std::exception("Invalid iterator"); }
            Iterator it(m_Ptr);
            it -= distance;
            return it;
        }

        //Element access
    public:
        /**
        * @brief: Returns the element at the given distance from the current iterator.
        *
        * @param: size_t -> distance to move.
        * @return: ValueType& -> Element in the resulting position.
        */
        _NODISCARD __forceinline ValueType& operator[](size_t index) const noexcept { return *(operator+(index)); }

        /**
        * @brief: Returns the element at the given distance from the current iterator.
        * @details: By giving a negative number, the iterator will move backwards instead.
        *
        * @param: int -> distance to move.
        * @return: ValueType& -> Element in the resulting position.
        */
        _NODISCARD __forceinline ValueType& operator[](int index) const noexcept { return *(operator+(index)); }

        /**
        * @brief: Returns the element at the given distance from the current iterator.
        * @details: If the iterator is not valid, throws std::exception.
        *
        * @param: size_t -> distance to move.
        * @return: ValueType& -> Element in the resulting position.
        */
        _NODISCARD __forceinline ValueType& At(size_t index) const { return *(Next(index)); }

        /**
        * @brief: Returns the element at the given distance from the current iterator.
        * @details: By giving a negative number, the iterator will move backwards instead.
        * If the iterator is not valid, throws std::exception.
        *
        * @param: int -> distance to move.
        * @return: ValueType& -> Element in the resulting position.
        */
        _NODISCARD __forceinline ValueType& At(int index) const { return *(Next(index)); }

        /**
        * @brief: Returns the element of the current iterator.
        *
        * @return: ValueType& -> Element of the iterator.
        */
        _NODISCARD __forceinline ValueType& operator*() const noexcept { return *m_Ptr->Data; }

        /**
        * @brief: Returns the element of the current iterator.
        * @details: If the iterator is not valid, throws std::exception.
        *
        * @return: ValueType& -> Element of the iterator.
        */
        _NODISCARD __forceinline ValueType& Data() const
        {
            if (!m_Ptr) { throw std::exception("Invalid iterator"); }
            return *m_Ptr->Data;
        }

        /**
        * @brief: Returns the current iterator.
        *
        * @return: ValueType* -> Current iterator.
        */
        _NODISCARD __forceinline ValueType* operator->() const noexcept { return m_Ptr->Data; }

        /**
        * @brief: Returns the current iterator.
        * @details: If the iterator is not valid, throws std::exception.
        *
        * @return: ValueType* -> Current iterator.
        */
        _NODISCARD __forceinline ValueType* Get() const
        {
            if (!m_Ptr) { throw std::exception("Invalid iterator"); }
            return m_Ptr->Data;
        }

        //Non member functions
    public:
        /**
        * @brief: Returns the distance between the current and the given iterators.
        * @details: The result is always a positive number.
        * If the iterator is not valid, throws std::exception.
        *
        * @param: const Iterator& -> Given iterator.
        * @return: size_t -> Distance.
        */
        _NODISCARD __forceinline size_t Distance(const Iterator& other) const
        {
            if (!m_Ptr) { throw std::exception("Invalid iterator"); }
            if (!other) { throw std::exception("Invalid iterator"); }
            size_t distance = 0;

            const Node* prev = m_Ptr;
            const Node* next = m_Ptr;

            do
            {
                if (prev == other.m_Ptr) { break; }
                if (next == other.m_Ptr) { break; }
                if (!prev && !next) { return size_t(-1); }
                if (prev) { prev = prev->Prev; }
                if (next) { next = next->Next; }

                ++distance;
            } while (true);

            return distance;
        }

        /**
        * @brief: Compares if two iterators are equal.
        *
        * @param: const Iterator& -> Given iterator.
        * @return: bool -> True if both are equal.
        */
        _NODISCARD __forceinline bool operator==(const Iterator& other) const noexcept { return m_Ptr == other.m_Ptr; }

        /**
        * @brief: Compares if the given T* and the iterator have the same value.
        *
        * @param: const T* -> T*.
        * @return: bool -> True if both are equal.
        */
        _NODISCARD __forceinline bool operator==(ValueType* other) const noexcept { return m_Ptr->Data == other; }

        /**
        * @brief: Compares if two iterators are not equal.
        *
        * @param: const Iterator& -> Given iterator.
        * @return: bool -> True if both are not equal.
        */
        _NODISCARD __forceinline bool operator!=(const Iterator& other) const noexcept { return !(operator==(other)); }

        /**
        * @brief: Compares if the given T* and the iterator have the same value.
        *
        * @param: const T* -> T*.
        * @return: bool -> True if both are not equal.
        */
        _NODISCARD __forceinline bool operator!=(ValueType* other) const noexcept { return !(operator==(other)); }

        /**
        * @brief: Compares if the current iterator is lesser than the given iterator.
        *
        * @param: const Iterator& -> Other iterator.
        * @return: bool -> True if the current iterator is lesser.
        */
        _NODISCARD __forceinline bool operator<(const Iterator& other) const noexcept
        {
            if (!m_Ptr) { return false; }
            if (!other) { return true; }

            const Node* prev = m_Ptr->Prev;
            const Node* next = m_Ptr->Next;

            do
            {
                if (prev == other.m_Ptr) { return false; }
                if (next == other.m_Ptr) { return true; }
                if (!prev && !next) { return false; }
                if (prev) { prev = prev->Prev; }
                if (next) { next = next->Next; }
            } while (true);

            return false;
        }

        /**
        * @brief: Compares if the current iterator is lesser or equal than the given iterator.
        *
        * @param: const Iterator& -> Other iterator.
        * @return: bool -> True if the current iterator is lesser or equal.
        */
        _NODISCARD __forceinline bool operator<=(const Iterator& other) const noexcept { return !(operator>(other)); }

        /**
        * @brief: Compares if the current iterator is greater than the given iterator.
        *
        * @param: const Iterator& -> Other iterator.
        * @return: bool -> True if the current iterator is greater.
        */
        _NODISCARD __forceinline bool operator>(const Iterator& other) const noexcept
        {
            if (!m_Ptr) { return false; }
            if (!other) { return true; }

            const Node* prev = m_Ptr->Prev;
            const Node* next = m_Ptr->Next;

            do
            {
                if (prev == other.m_Ptr) { return true; }
                if (next == other.m_Ptr) { return false; }
                if (!prev && !next) { return false; }
                if (prev) { prev = prev->Prev; }
                if (next) { next = next->Next; }
            } while (true);

            return false;
        }

        /**
        * @brief: Compares if the current iterator is greater or equal than the given iterator.
        *
        * @param: const Iterator& -> Other iterator.
        * @return: bool -> True if the current iterator is greater or equal.
        */
        _NODISCARD __forceinline bool operator>=(const Iterator& other) const noexcept { return !(operator<(other)); }

        /**
        * @brief: Compares if the current iterator has a valid T*.
        *
        * @return: bool -> True if the current iterator is valid.
        */
        _NODISCARD __forceinline operator bool() const noexcept { return m_Ptr; }

        /**
        * @brief: Compares if the current iterator has a valid T*.
        *
        * @return: bool -> True if the current iterator is valid.
        */
        _NODISCARD __forceinline bool IsValid() const noexcept { return m_Ptr; }

        //Member functions
    public:
        __forceinline Iterator(Node* ptr = nullptr) noexcept :
            m_Ptr(ptr) {}

        __forceinline Iterator(const Iterator& other) noexcept :
            m_Ptr(other.m_Ptr) {}

        __forceinline Iterator(Iterator&& other) noexcept :
            m_Ptr(other.m_Ptr)
        {
            other.m_Ptr = nullptr;
        }

        ~Iterator() noexcept
        {
            m_Ptr = nullptr;
        }

        __forceinline Iterator& operator=(const Iterator& other) noexcept
        {
            m_Ptr = other.m_Ptr;
            return *this;
        }

        __forceinline Iterator& operator=(Iterator&& other) noexcept
        {
            m_Ptr = other.m_Ptr;
            other.m_Ptr = nullptr;
            return *this;
        }

        __forceinline Iterator& operator=(Node* other) noexcept
        {
            m_Ptr = other;
            return *this;
        }

    private:
        Node* m_Ptr;
    };

    template<typename ValueType>
    class ReverseIterator
    {
        friend class List;
        //Modifiers
    public:
        /**
        * @brief: Moves the iterator to the next element.
        * @details: Pre increment.
        *
        * @return: ReverseIterator& -> Current iterator.
        */
        __forceinline ReverseIterator& operator++() noexcept
        {
            m_Ptr = m_Ptr->Prev;
            return *this;
        }

        /**
        * @brief: Moves the iterator to the next element.
        * @details: Post increment.
        *
        * @return: ReverseIterator -> Iterator at previous position.
        */
        _NODISCARD __forceinline ReverseIterator operator++(int) noexcept
        {
            ReverseIterator it(m_Ptr);
            m_Ptr = m_Ptr->Prev;
            return it;
        }

        /**
        * @brief: Moves the iterator forwards by the given distance.
        *
        * @param: size_t -> distance to move.
        * @return: ReverseIterator& -> Current iterator.
        */
        __forceinline ReverseIterator& operator+=(size_t distance) noexcept
        {
            for (size_t i = 0; i < distance; ++i)
            {
                m_Ptr = m_Ptr->Prev;
            }
            return *this;
        }

        /**
        * @brief: Moves the iterator forwards by the given distance.
        * @details: By giving a negative number, the iterator will move backwards instead.
        *
        * @param: int -> distance to move.
        * @return: ReverseIterator& -> Current iterator.
        */
        __forceinline ReverseIterator& operator+=(int distance) noexcept
        {
            if (distance < 0)
            {
                distance *= -1;
                for (int i = 0; i < distance; ++i)
                {
                    m_Ptr = m_Ptr->Next;
                }
            }
            else
            {
                for (int i = 0; i < distance; ++i)
                {
                    m_Ptr = m_Ptr->Prev;
                }
            }
            return *this;
        }

        /**
        * @brief: Moves the iterator forwards by the given distance.
        * @details: By default the distance is 1.
        * If the iterator is not valid, throws std::exception.
        *
        * @param: size_t -> distance to move.
        * @return: void.
        */
        __forceinline void Advance(size_t distance = 1)
        {
            if (!m_Ptr) { throw std::exception("Invalid iterator"); }
            for (size_t i = 0; i < distance; ++i)
            {
                m_Ptr = m_Ptr->Prev;
            }
        }

        /**
        * @brief: Moves the iterator forwards by the given distance.
        * @details: By giving a negative number, the iterator will move backwards instead.
        * By default the distance is 1.
        * If the iterator is not valid, throws std::exception.
        *
        * @param: int -> distance to move.
        * @return: void.
        */
        __forceinline void Advance(int distance = 1)
        {
            if (!m_Ptr) { throw std::exception("Invalid iterator"); }
            if (distance < 0)
            {
                distance *= -1;
                for (int i = 0; i < distance; ++i)
                {
                    m_Ptr = m_Ptr->Next;
                }
            }
            else
            {
                for (int i = 0; i < distance; ++i)
                {
                    m_Ptr = m_Ptr->Prev;
                }
            }
        }

        /**
        * @brief: Moves the iterator to the previous element.
        * @details: Pre increment.
        *
        * @return: ReverseIterator& -> Current iterator.
        */
        __forceinline ReverseIterator& operator--() noexcept
        {
            m_Ptr = m_Ptr->Next;
            return *this;
        }

        /**
        * @brief: Moves the iterator to the previous element.
        * @details: Post increment.
        *
        * @return: ReverseIterator -> Iterator at previous position.
        */
        _NODISCARD __forceinline ReverseIterator operator--(int) noexcept
        {
            ReverseIterator it(m_Ptr);
            m_Ptr = m_Ptr->Next;
            return it;
        }

        /**
        * @brief: Moves the iterator backwards by the given distance.
        *
        * @param: size_t -> distance to move.
        * @return: ReverseIterator& -> Current iterator.
        */
        __forceinline ReverseIterator& operator-=(size_t distance) noexcept
        {
            for (size_t i = 0; i < distance; ++i)
            {
                m_Ptr = m_Ptr->Next;
            }
            return *this;
        }

        /**
        * @brief: Moves the iterator backwards by the given distance.
        * @details: By giving a negative number, the iterator will move forwards instead.
        *
        * @param: int -> distance to move.
        * @return: ReverseIterator& -> Current iterator.
        */
        __forceinline ReverseIterator& operator-=(int distance) noexcept
        {
            if (distance < 0)
            {
                distance *= -1;
                for (int i = 0; i < distance; ++i)
                {
                    m_Ptr = m_Ptr->Prev;
                }
            }
            else
            {
                for (int i = 0; i < distance; ++i)
                {
                    m_Ptr = m_Ptr->Next;
                }
            }
            return *this;
        }

        /**
        * @brief: Moves the iterator backwards by the given distance.
        * @details: By default the distance is 1.
        * If the iterator is not valid, throws std::exception.
        *
        * @param: size_t -> distance to move.
        * @return: void.
        */
        __forceinline void Retreat(size_t distance = 1)
        {
            if (!m_Ptr) { throw std::exception("Invalid iterator"); }
            for (size_t i = 0; i < distance; ++i)
            {
                m_Ptr = m_Ptr->Next;
            }
        }

        /**
        * @brief: Moves the iterator backwards by the given distance.
        * @details: By giving a negative number, the iterator will move forwards instead.
        * By default the distance is 1.
        * If the iterator is not valid, throws std::exception.
        *
        * @param: int -> distance to move.
        * @return: void.
        */
        __forceinline void Retreat(int distance = 1)
        {
            if (!m_Ptr) { throw std::exception("Invalid iterator"); }
            if (distance < 0)
            {
                distance *= -1;
                for (int i = 0; i < distance; ++i)
                {
                    m_Ptr = m_Ptr->Prev;
                }
            }
            else
            {
                for (int i = 0; i < distance; ++i)
                {
                    m_Ptr = m_Ptr->Next;
                }
            }
        }

        /**
        * @brief: Returns an iterator to the forward distance given from the current iterator.
        *
        * @param: size_t -> distance to move.
        * @return: ReverseIterator -> Iterator in the resulting position.
        */
        _NODISCARD __forceinline ReverseIterator operator+(size_t distance) const noexcept
        {
            ReverseIterator it(m_Ptr);
            it += distance;
            return it;
        }

        /**
        * @brief: Returns an iterator to the forward distance given from the current iterator.
        * @details: By giving a negative number, the iterator will move backwards instead.
        *
        * @param: int -> distance to move.
        * @return: ReverseIterator -> Iterator in the resulting position.
        */
        _NODISCARD __forceinline ReverseIterator operator+(int distance) const noexcept
        {
            ReverseIterator it(m_Ptr);
            it += distance;
            return it;
        }

        /**
        * @brief: Return an iterator pointing to the element after being advanced by certain number of positions.
        * @details: By default the distance is 1.
        * If the iterator is not valid, throws std::exception.
        * 
        * @param: size_t -> Number of elements to advance.
        * @return: ReverseIterator -> Iterator at new position.
        */
        _NODISCARD __forceinline ReverseIterator Next(size_t distance = 1) const
        {
            if (!m_Ptr) { throw std::exception("Invalid iterator"); }
            ReverseIterator it(m_Ptr);
            it += distance;
            return it;
        }

        /**
        * @brief: Return an iterator pointing to the element after being advanced by certain number of positions.
        * @details: By giving a negative number, the iterator will move backwards instead.
        * By default the distance is 1.
        * If the iterator is not valid, throws std::exception.
        *
        * @param: int -> Number of elements to advance.
        * @return: ReverseIterator -> Iterator at new position.
        */
        _NODISCARD __forceinline ReverseIterator Next(int distance = 1) const
        {
            if (!m_Ptr) { throw std::exception("Invalid iterator"); }
            ReverseIterator it(m_Ptr);
            it += distance;
            return it;
        }

        /**
        * @brief: Returns an iterator to the backward distance given from the current iterator.
        *
        * @param: size_t -> distance to move.
        * @return: ReverseIterator -> Iterator in the resulting position.
        */
        _NODISCARD __forceinline ReverseIterator operator-(size_t distance) const noexcept
        {
            ReverseIterator it(m_Ptr);
            it -= distance;
            return it;
        }

        /**
        * @brief: Returns an iterator to the backward distance given from the current iterator.
        * @details: By giving a negative number, the iterator will move forwards instead.
        *
        * @param: int -> distance to move.
        * @return: ReverseIterator -> Iterator in the resulting position.
        */
        _NODISCARD __forceinline ReverseIterator operator-(int distance) const noexcept
        {
            ReverseIterator it(m_Ptr);
            it -= distance;
            return it;
        }

        /**
        * @brief: Return an iterator pointing to the element after being moved back by certain number of positions.
        * @details: By default the distance is 1.
        * If the iterator is not valid, throws std::exception.
        *
        * @param: size_t -> Number of elements to retreat.
        * @return: ReverseIterator -> Iterator at new position.
        */
        _NODISCARD __forceinline ReverseIterator Prev(size_t distance = 1) const
        {
            if (!m_Ptr) { throw std::exception("Invalid iterator"); }
            ReverseIterator it(m_Ptr);
            it -= distance;
            return it;
        }

        /**
        * @brief: Return an iterator pointing to the element after being moved back by certain number of positions.
        * @details: By giving a negative number, the iterator will move forwards instead.
        * By default the distance is 1.
        * If the iterator is not valid, throws std::exception.
        *
        * @param: int -> Number of elements to retreat.
        * @return: ReverseIterator -> Iterator at new position.
        */
        _NODISCARD __forceinline ReverseIterator Prev(int distance = 1) const
        {
            if (!m_Ptr) { throw std::exception("Invalid iterator"); }
            ReverseIterator it(m_Ptr);
            it -= distance;
            return it;
        }

        //Element access
    public:
        /**
        * @brief: Returns the element at the given distance from the current iterator.
        *
        * @param: size_t -> distance to move.
        * @return: ValueType& -> Element in the resulting position.
        */
        _NODISCARD __forceinline ValueType& operator[](size_t index) const noexcept { return *(operator+(index)); }

        /**
        * @brief: Returns the element at the given distance from the current iterator.
        * @details: By giving a negative number, the iterator will move forwards instead.
        *
        * @param: int -> distance to move.
        * @return: ValueType& -> Element in the resulting position.
        */
        _NODISCARD __forceinline ValueType& operator[](int index) const noexcept { return *(operator+(index)); }

        /**
        * @brief: Returns the element at the given distance from the current iterator.
        * @details: If the iterator is not valid, throws std::exception.
        *
        * @param: size_t -> distance to move.
        * @return: ValueType& -> Element in the resulting position.
        */
        _NODISCARD __forceinline ValueType& At(size_t index) const { return *(Next(index)); }

        /**
        * @brief: Returns the element at the given distance from the current iterator.
        * @details: By giving a negative number, the iterator will move forwards instead.
        * If the iterator is not valid, throws std::exception.
        *
        * @param: int -> distance to move.
        * @return: ValueType& -> Element in the resulting position.
        */
        _NODISCARD __forceinline ValueType& At(int index) const { return *(Next(index)); }

        /**
        * @brief: Returns the element of the current iterator.
        *
        * @return: ValueType& -> Element of the iterator.
        */
        _NODISCARD __forceinline ValueType& operator*() const noexcept { return *m_Ptr->Data; }

        /**
        * @brief: Returns the element of the current iterator.
        * @details: If the iterator is not valid, throws std::exception.
        *
        * @return: ValueType& -> Element of the iterator.
        */
        _NODISCARD __forceinline ValueType& Data() const
        {
            if (!m_Ptr) { throw std::exception("Invalid iterator"); }
            return *m_Ptr->Data;
        }

        /**
        * @brief: Returns the current iterator.
        *
        * @return: ValueType* -> Current iterator.
        */
        _NODISCARD __forceinline ValueType* operator->() const noexcept { return m_Ptr->Data; }

        /**
        * @brief: Returns the current iterator.
        * @details: If the iterator is not valid, throws std::exception.
        *
        * @return: ValueType* -> Current iterator.
        */
        _NODISCARD __forceinline ValueType* Get() const
        {
            if (!m_Ptr) { throw std::exception("Invalid iterator"); }
            return m_Ptr->Data;
        }

        //Non member functions
    public:
        /**
        * @brief: Returns the distance between the current and the given iterators.
        * @details: The result is always a positive number.
        * If the iterator is not valid, throws std::exception.
        *
        * @param: const ReverseIterator& -> Given iterator.
        * @return: size_t -> Distance.
        */
        _NODISCARD __forceinline size_t Distance(const ReverseIterator& other) const
        {
            if (!m_Ptr) { throw std::exception("Invalid iterator"); }
            if (!other) { throw std::exception("Invalid iterator"); }

            size_t distance = 0;
            const Node* prev = m_Ptr;
            const Node* next = m_Ptr;

            do
            {
                if (prev == other.m_Ptr) { break; }
                if (next == other.m_Ptr) { break; }
                if (!prev && !next) { return size_t(-1); }
                if (prev) { prev = prev->Prev; }
                if (next) { next = next->Next; }

                ++distance;
            } while (true);

            return distance;
        }

        /**
        * @brief: Compares if two iterators are equal.
        *
        * @param: const ReverseIterator& -> Given iterator.
        * @return: bool -> True if both are equal.
        */
        _NODISCARD __forceinline bool operator==(const ReverseIterator& other) const noexcept { return m_Ptr == other.m_Ptr; }

        /**
        * @brief: Compares if the given T* and the iterator have the same value.
        *
        * @param: const T* -> T*.
        * @return: bool -> True if both are equal.
        */
        _NODISCARD __forceinline bool operator==(ValueType* other) const noexcept { return m_Ptr->Data == other; }

        /**
        * @brief: Compares if two iterators are not equal.
        *
        * @param: const ReverseIterator& -> Given iterator.
        * @return: bool -> True if both are not equal.
        */
        _NODISCARD __forceinline bool operator!=(const ReverseIterator& other) const noexcept { return !(operator==(other)); }

        /**
        * @brief: Compares if the given T* and the iterator have the same value.
        *
        * @param: const T* -> T*.
        * @return: bool -> True if both are not equal.
        */
        _NODISCARD __forceinline bool operator!=(ValueType* other) const noexcept { return !(operator==(other)); }

        /**
        * @brief: Compares if the current iterator is lesser than the given iterator.
        *
        * @param: const ReverseIterator& -> Other iterator.
        * @return: bool -> True if the current iterator is lesser.
        */
        _NODISCARD __forceinline bool operator<(const ReverseIterator& other) const noexcept
        {
            if (!m_Ptr) { return false; }
            if (!other) { return true; }

            const Node* prev = m_Ptr->Prev;
            const Node* next = m_Ptr->Next;

            do
            {
                if (prev == other.m_Ptr) { return true; }
                if (next == other.m_Ptr) { return false; }
                if (!prev && !next) { return false; }
                if (prev) { prev = prev->Prev; }
                if (next) { next = next->Next; }
            } while (true);

            return false;
        }

        /**
        * @brief: Compares if the current iterator is lesser or equal than the given iterator.
        *
        * @param: const ReverseIterator& -> Other iterator.
        * @return: bool -> True if the current iterator is lesser or equal.
        */
        _NODISCARD __forceinline bool operator<=(const ReverseIterator& other) const noexcept { return !(operator>(other)); }

        /**
        * @brief: Compares if the current iterator is greater than the given iterator.
        *
        * @param: const ReverseIterator& -> Other iterator.
        * @return: bool -> True if the current iterator is greater.
        */
        _NODISCARD __forceinline bool operator>(const ReverseIterator& other) const noexcept
        {
            if (!m_Ptr) { return false; }
            if (!other) { return true; }

            const Node* prev = m_Ptr->Prev;
            const Node* next = m_Ptr->Next;

            do
            {
                if (prev == other.m_Ptr) { return false; }
                if (next == other.m_Ptr) { return true; }
                if (!prev && !next) { return false; }
                if (prev) { prev = prev->Prev; }
                if (next) { next = next->Next; }
            } while (true);

            return false;
        }

        /**
        * @brief: Compares if the current iterator is greater or equal than the given iterator.
        *
        * @param: const ReverseIterator& -> Other iterator.
        * @return: bool -> True if the current iterator is greater or equal.
        */
        _NODISCARD __forceinline bool operator>=(const ReverseIterator& other) const noexcept { return !(operator<(other)); }

        /**
        * @brief: Compares if the current iterator has a valid T*.
        *
        * @return: bool -> True if the current iterator is valid.
        */
        _NODISCARD __forceinline operator bool() const noexcept { return m_Ptr; }

        /**
        * @brief: Compares if the current iterator has a valid T*.
        *
        * @return: bool -> True if the current iterator is valid.
        */
        _NODISCARD __forceinline bool IsValid() const noexcept { return m_Ptr; }

        //Member functions
    public:
        __forceinline ReverseIterator(Node* ptr = nullptr) noexcept :
            m_Ptr(ptr) {}

        __forceinline ReverseIterator(const ReverseIterator& other) noexcept :
            m_Ptr(other.m_Ptr) {}

        __forceinline ReverseIterator(ReverseIterator&& other) noexcept :
            m_Ptr(other.m_Ptr)
        {
            other.m_Ptr = nullptr;
        }

        ~ReverseIterator() noexcept
        {
            m_Ptr = nullptr;
        }

        __forceinline ReverseIterator& operator=(const ReverseIterator& other) noexcept
        {
            m_Ptr = other.m_Ptr;
            return *this;
        }

        __forceinline ReverseIterator& operator=(ReverseIterator&& other) noexcept
        {
            m_Ptr = other.m_Ptr;
            other.m_Ptr = nullptr;
            return *this;
        }

        __forceinline ReverseIterator& operator=(Node* other) noexcept
        {
            m_Ptr = other;
            return *this;
        }

    private:
        Node* m_Ptr;
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
    * If an exception is thrown (which can be due to Reserve or element copy/move constructor/assignment), this function has no effect.
    *
    * @param: size_t -> New capacity.
    * @return: void.
    */
    void Resize(size_t capacity)
    {
        if (capacity > m_Capacity) { Reserve(capacity); }
        if (capacity == m_Capacity) { return; }
        if (capacity == 0) { return Nullify(); }
        if (capacity >= m_Elements)
        {
            size_t diff = m_Capacity - capacity;
            for (size_t i = 0; i < diff; ++i)
            {
                Node* current = m_Unused;
                m_Unused = m_Unused->Next;
                (*current).~Node();
                ::operator delete(current, sizeof(Node) + sizeof(T));
            }
            m_Capacity = capacity;
            return;
        }

        size_t diff = m_Elements - capacity;
        reverse_iterator it = rbegin();
        it.m_Ptr->Next = m_Unused;

        for (size_t i = 0; i < diff; ++i, ++it)
        {
            it.m_Ptr->ClearData();
        }

        m_Unused = it.m_Ptr;
        ++it;
        m_Unused->Prev = nullptr;
        m_LastElement = it.m_Ptr;
        m_LastElement->Next = m_Tail;
        m_Tail->Prev = m_LastElement;

        Shrink();

        m_Elements = capacity;
        m_Capacity = capacity;
    }

    /**
    * @brief: Inserts a new element at the end of the container.
    * @details: If an exception is thrown (which can be due to Reserve or element copy/move constructor/assignment), this function has no effect.
    *
    * @param: const T& -> Element.
    * @return: void.
    */
    void PushBack(const T& element)
    {
        if (IsEmpty())
        {
            PushEmpty(element);
            return;
        }

        if (m_Unused)
        {
            m_LastElement->Next = GetNodeFromUnused();
            UpdateLastNode();
            Assign(m_LastElement, element);
        }
        else
        {
            m_LastElement->Next = CreateNode(element);
            UpdateLastNode();
        }
    }

    /**
    * @brief: Inserts a new element at the end of the container.
    *
    * @param: T&& -> Element.
    * @return: void.
    */
    void PushBack(T&& element)
    {
        if (IsEmpty())
        {
            PushEmpty(std::move(element));
            return;
        }

        if (m_Unused)
        {
            m_LastElement->Next = GetNodeFromUnused();
            UpdateLastNode();
            Assign(m_LastElement, std::move(element));
        }
        else
        {
            m_LastElement->Next = CreateNode(std::move(element));
            UpdateLastNode();
        }
    }

    /**
    * @brief: Inserts a new element at the beginning of the container.
    *
    * @param: const T& -> Element.
    * @return: void.
    */
    void PushFront(const T& element)
    {
        if (IsEmpty())
        {
            PushEmpty(element);
            return;
        }

        if (m_Unused)
        {
            m_FirstElement->Prev = GetNodeFromUnused();
            UpdateFirstNode();
            Assign(m_FirstElement, element);
        }
        else
        {
            m_FirstElement->Prev = CreateNode(element);
            UpdateFirstNode();
        }
    }

    /**
    * @brief: Inserts a new element at the beginning of the container.
    *
    * @param: T&& -> Element.
    * @return: void.
    */
    void PushFront(T&& element)
    {
        if (IsEmpty())
        {
            PushEmpty(std::move(element));
            return;
        }

        if (m_Unused)
        {
            m_FirstElement->Prev = GetNodeFromUnused();
            UpdateFirstNode();
            Assign(m_FirstElement, std::move(element));
        }
        else
        {
            m_FirstElement->Prev = CreateNode(std::move(element));
            UpdateFirstNode();
        }
    }

    /**
    * @brief: Inserts a new element into the container directly before index.
    *
    * @param: size_t -> Index.
    * @param: const T& -> Element.
    * @return: Iterator -> Iterator to the new element.
    */
    iterator Insert(size_t index, const T& element)
    {
        if (IsEmpty() || index == 0)
        {
            PushEmpty(element);
            return begin();
        }
        if (index >= m_Elements)
        {
            PushBack(element);
            return end();
        }

        iterator existing_node = GetIteratorAtIndex(index);
        InsertNode(existing_node.m_Ptr, element);
        return --existing_node;
    }

    /**
    * @brief: Inserts a new element into the container directly before index.
    *
    * @param: Iterator -> Position.
    * @param: const T& -> Element.
    * @return: Iterator -> Iterator to the new element.
    */
    iterator Insert(iterator it, const T& element)
    {
        if (IsEmpty())
        {
            PushEmpty(element);
            return begin();
        }
        if (it == begin())
        {
            PushFront(element);
            return begin();
        }
        if (it == m_Tail)
        {
            PushBack(element);
            return end();
        }

        InsertNode(it.m_Ptr, element);
        return --it;
    }

    /**
    * @brief: Inserts a new element into the container directly before index.
    *
    * @param: ReverseIterator -> Position.
    * @param: const T& -> Element.
    * @return: ReverseIterator -> Iterator to the new element.
    */
    reverse_iterator Insert(reverse_iterator it, const T& element)
    {
        if (IsEmpty())
        {
            PushEmpty(element);
            return rbegin();
        }
        if (it == m_Head)
        {
            PushFront(element);
            return reverse_iterator(m_FirstElement);
        }
        if (it == m_Tail)
        {
            PushBack(element);
            return rbegin();
        }
        if (m_Elements == 1 && it == rbegin())
        {
            PushBack(element);
            return rbegin();
        }

        InsertNode(it.m_Ptr, element);
        return ++it;
    }

    /**
    * @brief: Inserts a new element into the container directly before index.
    *
    * @param: size_t -> Index.
    * @param: T&& -> Element.
    * @return: Iterator -> Iterator to the new element.
    */
    iterator Insert(size_t index, T&& element)
    {
        if (IsEmpty() || index == 0)
        {
            PushEmpty(std::move(element));
            return begin();
        }
        if (index >= m_Elements)
        {
            PushBack(std::move(element));
            return end();
        }

        iterator existing_node = GetIteratorAtIndex(index);
        InsertNode(existing_node.m_Ptr, std::move(element));
        return --existing_node;
    }

    /**
    * @brief: Inserts a new element into the container directly before index.
    *
    * @param: Iterator -> Position.
    * @param: T&& -> Element.
    * @return: Iterator -> Iterator to the new element.
    */
    iterator Insert(iterator it, T&& element)
    {
        if (IsEmpty())
        {
            PushEmpty(std::move(element));
            return begin();
        }
        if (it == begin())
        {
            PushFront(std::move(element));
            return begin();
        }
        if (it == m_Tail)
        {
            PushBack(std::move(element));
            return end();
        }

        InsertNode(it.m_Ptr, std::move(element));

        return --it;
    }

    /**
    * @brief: Inserts a new element into the container directly before index.
    *
    * @param: ReverseIterator -> Position.
    * @param: T&& -> Element.
    * @return: ReverseIterator -> Iterator to the new element.
    */
    reverse_iterator Insert(reverse_iterator it, T&& element)
    {
        if (IsEmpty())
        {
            PushEmpty(std::move(element));
            return rbegin();
        }
        if (it == m_Head)
        {
            PushFront(std::move(element));
            return reverse_iterator(m_FirstElement);
        }
        if (it == m_Tail)
        {
            PushBack(std::move(element));
            return rbegin();
        }
        if (m_Elements == 1 && it == rbegin())
        {
            PushBack(std::move(element));
            return rbegin();
        }

        InsertNode(it.m_Ptr, std::move(element));

        return ++it;
    }

    /**
    * @brief: Inserts a new element at the end of the container.
    * @details: The element is constructed in place.
    *
    * @param: Args -> Arguments needed to create the element.
    * @return: ValueType& -> New constructed element.
    */
    template<typename... Args>
    T& EmplaceBack(Args&&... args)
    {
        if (IsEmpty())
        {
            EmplaceEmpty(std::forward<Args>(args)...);
            return *m_LastElement->Data;
        }

        if (m_Unused)
        {
            m_LastElement->Next = GetNodeFromUnused();
            UpdateLastNode();
            Assign(m_LastElement, std::forward<Args>(args)...);
        }
        else
        {
            m_LastElement->Next = CreateNode(std::forward<Args>(args)...);
            UpdateLastNode();
        }

        return *m_LastElement->Data;
    }

    /**
    * @brief: Inserts a new element at the beginning of the container.
    * @details: The element is constructed in place.
    *
    * @param: Args -> Arguments needed to create the element.
    * @return: ValueType& -> New constructed element.
    */
    template<typename... Args>
    T& EmplaceFront(Args&&... args)
    {
        if (IsEmpty())
        {
            EmplaceEmpty(std::forward<Args>(args)...);
            return *m_FirstElement->Data;
        }

        if (m_Unused)
        {
            m_FirstElement->Prev = GetNodeFromUnused();
            UpdateFirstNode();
            Assign(m_FirstElement, std::forward<Args>(args)...);
        }
        else
        {
            m_FirstElement->Prev = CreateNode(std::forward<Args>(args)...);
            UpdateFirstNode();
        }

        return *m_FirstElement->Data;
    }

    /**
    * @brief: Inserts a new element into the container directly before index.
    * @details: The element is constructed in place.
    *
    * @param: size_t -> Index.
    * @param: Args -> Arguments needed to create the element.
    * @return: Iterator -> Iterator to the new element.
    */
    template<typename... Args>
    T& Emplace(size_t index, Args&&... args)
    {
        if (IsEmpty() || index == 0)
        {
            EmplaceEmpty(std::forward<Args>(args)...);
            return *m_FirstElement->Data;
        }
        if (index >= m_Elements)
        {
            EmplaceBack(std::forward<Args>(args)...);
            return *m_LastElement->Data;
        }

        iterator existing_node = GetIteratorAtIndex(index);
        EmplaceNode(existing_node.m_Ptr, std::forward<Args>(args)...);
        return (--existing_node).Data();
    }

    /**
    * @brief: Inserts a new element into the container directly before index.
    * @details: The element is constructed in place.
    *
    * @param: Iterator -> Position.
    * @param: Args -> Arguments needed to create the element.
    * @return: Iterator -> Iterator to the new element.
    */
    template<typename... Args>
    T& Emplace(iterator it, Args&&... args)
    {
        if (IsEmpty())
        {
            EmplaceEmpty(std::forward<Args>(args)...);
            return *m_FirstElement->Data;
        }
        if (it == begin())
        {
            EmplaceFront(std::forward<Args>(args)...);
            return *m_FirstElement->Data;
        }
        if (it == m_Tail)
        {
            EmplaceBack(std::forward<Args>(args)...);
            return *m_LastElement->Data;
        }

        EmplaceNode(it.m_Ptr, std::forward<Args>(args)...);

        return (--it).Data();
    }

    /**
    * @brief: Inserts a new element into the container directly before index.
    * @details: The element is constructed in place.
    *
    * @param: ReverseIterator -> Position.
    * @param: Args -> Arguments needed to create the element.
    * @return: ReverseIterator -> Iterator to the new element.
    */
    template<typename... Args>
    T& Emplace(reverse_iterator it, Args&&... args)
    {
        if (IsEmpty())
        {
            EmplaceEmpty(std::forward<Args>(args)...);
            return *m_LastElement->Data;
        }
        if (it == m_Head)
        {
            EmplaceFront(std::forward<Args>(args)...);
            return *m_FirstElement->Data;
        }
        if (it == m_Tail)
        {
            EmplaceBack(std::forward<Args>(args)...);
            return *m_LastElement->Data;
        }

        if (m_Elements == 1 && it == rbegin())
        {
            EmplaceBack(std::forward<Args>(args)...);
            return *m_LastElement->Data;
        }

        EmplaceNode(it.m_Ptr, std::forward<Args>(args)...);
        return (++it).Data();
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

        --m_Elements;
        m_LastElement->ClearData();

        m_LastElement->Next = m_Unused;
        m_Unused = m_LastElement;

        if (IsEmpty())
        {
            m_Head->Next = nullptr;
            m_Tail->Prev = nullptr;
            m_FirstElement = nullptr;
            m_LastElement = nullptr;
        }
        else
        {
            m_LastElement = m_LastElement->Prev;
            m_Unused->Prev = nullptr;

            m_LastElement->Next = m_Tail;
            m_Tail->Prev = m_LastElement;
        }
    }

    /**
    * @brief: Delete the first element of the container.
    * @details: No reallocations are performed.
    *
    * @return: void.
    */
    void PopFront() noexcept
    {
        if (IsEmpty()) { return; }

        --m_Elements;
        m_FirstElement->ClearData();

        Node* tmp = m_FirstElement->Next;

        m_FirstElement->Next = m_Unused;
        m_Unused = m_FirstElement;

        if (IsEmpty())
        {
            m_Head->Next = nullptr;
            m_Tail->Prev = nullptr;
            m_FirstElement = nullptr;
            m_LastElement = nullptr;
        }
        else
        {
            m_FirstElement = tmp;
            m_Unused->Prev = nullptr;

            m_FirstElement->Prev = m_Head;
            m_Head->Next = m_FirstElement;
        }
    }

    /**
    * @brief: Delete the element at the given index.
    * @details: No reallocations are performed.
    *
    * @param: size_t -> Index.
    * @return: Iterator -> Iterator to the element at the index position after deleting.
    */
    iterator Erase(size_t index) noexcept
    {
        if (IsEmpty()) { return iterator(); }
        if (index == 0)
        {
            PopFront();
            return begin();
        }
        if (index >= m_Elements - 1)
        {
            PopBack();
            return end();
        }
        iterator it = GetIteratorAtIndex(index);
        it.m_Ptr->ClearData();

        --m_Elements;
        it.m_Ptr->Prev->Next = it.m_Ptr->Next;
        it.m_Ptr->Next->Prev = it.m_Ptr->Prev;

        iterator aux(it.m_Ptr->Next);

        it.m_Ptr->Prev = nullptr;
        it.m_Ptr->Next = m_Unused;
        m_Unused = it.m_Ptr;

        return aux;
    }

    /**
    * @brief: Delete the element at the given index.
    * @details: No reallocations are performed.
    *
    * @param: Iterator -> position.
    * @return: Iterator -> Iterator to the element at the index position after deleting.
    */
    iterator Erase(iterator it) noexcept
    {
        if (IsEmpty()) { return iterator(); }
        if (it == m_FirstElement)
        {
            PopFront();
            return begin();
        }
        if (it == m_LastElement || it == m_Tail)
        {
            PopBack();
            return end();
        }

        it.m_Ptr->ClearData();

        --m_Elements;
        it.m_Ptr->Prev->Next = it.m_Ptr->Next;
        it.m_Ptr->Next->Prev = it.m_Ptr->Prev;

        iterator aux(it.m_Ptr->Next);

        it.m_Ptr->Prev = nullptr;
        it.m_Ptr->Next = m_Unused;
        m_Unused = it.m_Ptr;

        return aux;
    }

    /**
    * @brief: Delete the element at the given index.
    * @details: No reallocations are performed.
    *
    * @param: ReverseIterator -> position.
    * @return: ReverseIterator -> Iterator to the element at the index position after deleting..
    */
    reverse_iterator Erase(reverse_iterator it) noexcept
    {
        if (IsEmpty()) { return reverse_iterator(); }
        if (it == m_FirstElement || it == m_Head)
        {
            PopFront();
            return reverse_iterator(m_FirstElement);
        }
        if (it == m_LastElement)
        {
            PopBack();
            return rbegin();
        }

        it.m_Ptr->ClearData();

        --m_Elements;
        it.m_Ptr->Prev->Next = it.m_Ptr->Next;
        it.m_Ptr->Next->Prev = it.m_Ptr->Prev;

        reverse_iterator aux(it.m_Ptr->Next);

        it.m_Ptr->Prev = nullptr;
        it.m_Ptr->Next = m_Unused;
        m_Unused = it.m_Ptr;

        return aux;
    }

    /**
    * @brief: Clears the content of the container.
    * @details: By clearing the container, no reallocations are performed.
    *
    * @return: void.
    */
    void Clear() noexcept
    {
        if (IsEmpty()) { return; }

        for (iterator it = begin(); it != end(); ++it)
        {
            it.m_Ptr->ClearData();
        }

        m_LastElement->Next = m_Unused;
        m_Unused = m_FirstElement;

        m_FirstElement = nullptr;
        m_LastElement = nullptr;
        m_Head->Next = nullptr;
        m_Tail->Prev = nullptr;
        m_Elements = 0;
    }

    /**
    * @brief: Swaps the content of two Lists.
    * @details: If the container is the same as the given, no action will be performed.
    *
    * @param: List& -> Other list.
    * @return: void.
    */
    void Swap(List& other) noexcept
    {
        if (&other == this) { return; }

        Node* aux_FirstElement = m_FirstElement;
        Node* aux_LastElement = m_LastElement;
        Node* aux_Head = m_Head;
        Node* aux_Tail = m_Tail;
        Node* aux_Unused = m_Unused;
        size_t aux_Elements = m_Elements;
        size_t aux_Capacity = m_Capacity;

        m_FirstElement = other.m_FirstElement;
        m_LastElement = other.m_LastElement;
        m_Head = other.m_Head;
        m_Tail = other.m_Tail;
        m_Unused = other.m_Unused;
        m_Elements = other.m_Elements;
        m_Capacity = other.m_Capacity;

        other.m_FirstElement = aux_FirstElement;
        other.m_LastElement = aux_LastElement;
        other.m_Head = aux_Head;
        other.m_Tail = aux_Tail;
        other.m_Unused = aux_Unused;
        other.m_Elements = aux_Elements;
        other.m_Capacity = aux_Capacity;
    }

    /**
    * @brief: Append one list to the end of the current list.
    * @details: The elements are copied from the given list.
    *
    * @param: List& -> Other list.
    * @return: void.
    */
    void Append(const List& other) noexcept
    {
        if (&other == this) { return; }

        CopyFromList(other);
    }

    /**
    * @brief: Append one list to the end of the current list.
    * @details: The elements are moved from the given list.
    *
    * @param: List&& -> Other list.
    * @return: void.
    */
    void Append(List&& other) noexcept
    {
        if (&other == this) { return; }

        delete other.m_Head;
        delete m_Tail;

        other.m_FirstElement->Prev = m_LastElement;
        m_LastElement->Next = other.m_FirstElement;
        m_Tail = other.m_Tail;
        m_Elements += other.m_Elements;
        m_Capacity += other.m_Capacity;

        Node* aux = m_Unused;
        Node* prev = nullptr;
        while (aux)
        {
            prev = aux;
            aux = aux->Next;
        }
        aux = other.m_Unused;
        if (prev) { prev->Next = aux; }

        other.Default();
    }

    //Capacity
public:
    /**
    * @brief: Requests the removal of unused capacity.
    * @details: Frees memory.
    *
    * @return: void.
    */
    void Shrink() noexcept
    {
        while (m_Unused)
        {
            Node* current = m_Unused;
            m_Unused = m_Unused->Next;
            --m_Capacity;
            (*current).~Node();
            ::operator delete(current, sizeof(Node) + sizeof(T));
        };
    }

    /**
    * @brief: Resizes the container to the new capacity.
    * @details: Causes memory allocations, the new capacity must be greater than the current capacity.
    *
    * @param: size_t -> New capacity.
    * @return: void.
    */
    void Reserve(size_t capacity)
    {
        if (capacity > s_MaxListSize)
        {
            ListMaxLenghtError();
            return;
        }
        if (capacity <= m_Capacity) { return; }

        size_t diff = capacity - m_Capacity;

        Node* new_node = CreateNode();
        Node* start = new_node;

        for (size_t i = 1; i < diff; ++i)
        {
            new_node->Next = CreateNode();
            new_node = new_node->Next;
        }

        if (m_Unused)
        {
            new_node->Next = m_Unused;
        }
        m_Unused = start;
    }

    /**
    * @brief: Checks if the container is empty.
    *
    * @return: bool -> True if the container has no elements.
    */
    _NODISCARD __forceinline bool IsEmpty() const noexcept { return m_Elements == 0; }

    /**
    * @brief: Number of elements in the container.
    *
    * @return: size_t -> Elements.
    */
    _NODISCARD __forceinline size_t Size() const noexcept { return m_Elements; }

    /**
    * @brief: Current capacity of the container.
    *
    * @return: size_t -> Capacity.
    */
    _NODISCARD __forceinline size_t Capacity() const noexcept { return m_Capacity; }

    //Element Access
public:
    /**
    * @brief: Returns a reference to the first element in the container.
    * @details: Calling Front in a empty container is undefined.
    *
    * @return: ValueType& -> Element.
    */
    _NODISCARD T& Front() noexcept { return *m_FirstElement->Data; }

    /**
    * @brief: Returns a const reference to the first element in the container.
    * @details: Calling Front in a empty container is undefined.
    *
    * @return: const T& -> Element.
    */
    _NODISCARD const T& Front() const noexcept { return  *m_FirstElement->Data; }

    /**
    * @brief: Returns a reference to the last element in the container.
    * @details: Calling Back in a empty container is undefined.
    *
    * @return: ValueType& -> Element.
    */
    _NODISCARD T& Back() noexcept { return *m_LastElement->Data; }

    /**
    * @brief: Returns a const reference to the last element in the container.
    * @details: Calling Back in a empty container is undefined.
    *
    * @return: const T& -> Element.
    */
    _NODISCARD const T& Back() const noexcept { return *m_LastElement->Data; }

    /**
    * @brief: Returns a reference to the element at the given position.
    * @details: Calling [] in a empty container is undefined.
    *
    * @return: ValueType& -> Element.
    */
    _NODISCARD T& operator[](size_t index) noexcept { return *GetIteratorAtIndex(index); }

    /**
    * @brief: Returns a const reference to the element at the given position.
    * @details: Calling [] in a empty container is undefined.
    *
    * @return: const T& -> Element.
    */
    _NODISCARD const T& operator[](size_t index) const noexcept { return *GetIteratorAtIndex(index); }

    /**
    * @brief: Returns the element of the container at the given index.
    * @details: std::exception execption will be thrown if the index is out of range.
    *
    * @return: ValueType& -> Element.
    */
    _NODISCARD T& At(size_t index)
    {
        if (index >= m_Elements) { ListOutOfRangeError(); }
        return *GetIteratorAtIndex(index);
    }

    /**
    * @brief: Returns the element of the container at the given index.
    * @details: std::exception execption will be thrown if the index is out of range.
    *
    * @return: ValueType& -> Element.
    */
    _NODISCARD const T& At(size_t index) const
    {
        if (index >= m_Elements) { ListOutOfRangeError(); }
        return *GetIteratorAtIndex(index);
    }

    /**
    * @brief: Returns an iterator at the given index.
    * @details: std::exception execption will be thrown if the index is out of range.
    *
    * @return: Iterator -> Iterator.
    */
    _NODISCARD iterator GetIteratorAtIndex(size_t index)
    {
        iterator it;
        if (index < (m_Elements >> 1))
        {
            it = begin();
            it += index;
        }
        else
        {
            if (index >= m_Elements) { ListOutOfRangeError(); }

            size_t diff = m_Elements - index;
            it = end();
            it -= diff;
        }

        return it;
    }

    /**
    * @brief: Returns a pointer to the container data.
    *
    * @return: ValueType* -> Data.
    */
    _NODISCARD Node* Data() noexcept { return m_FirstElement; }

    /**
    * @brief: Returns a const pointer to the container data.
    *
    * @return: ValueType* -> Data.
    */
    _NODISCARD const Node* Data() const noexcept { return m_FirstElement; }

    //Iterators
public:
    /**
    * @brief: Returns an iterator to the begin of the container.
    *
    * @return: Iterator -> Iterator.
    */
    _NODISCARD __forceinline iterator begin() noexcept { return iterator(m_FirstElement); }

    /**
    * @brief: Returns a const iterator to the begin of the container.
    *
    * @return: ConstIterator -> Iterator.
    */
    _NODISCARD __forceinline const_iterator begin() const noexcept { return const_iterator(m_FirstElement); }

    /**
    * @brief: Returns a const iterator to the begin of the container.
    *
    * @return: ConstIterator -> Iterator.
    */
    _NODISCARD __forceinline const_iterator cbegin() const noexcept { return const_iterator(m_FirstElement); }

    /**
    * @brief: Returns an iterator to the end of the container.
    * @details: The iterator does not point to the last element, points outside the container instead.
    *
    * @return: Iterator -> Iterator.
    */
    _NODISCARD __forceinline iterator end() noexcept { return iterator(m_Tail); }

    /**
    * @brief: Returns an iterator to the end of the container.
    * @details: The iterator does not point to the last element, points outside the container instead.
    *
    * @return: ConstIterator -> Iterator.
    */
    _NODISCARD __forceinline const_iterator end() const noexcept { return const_iterator(m_Tail); }

    /**
    * @brief: Returns an iterator to the end of the container.
    * @details: The iterator does not point to the last element, points outside the container instead.
    *
    * @return: ConstIterator -> Iterator.
    */
    _NODISCARD __forceinline const_iterator cend() const noexcept { return const_iterator(m_Tail); }

    /**
    * @brief: Returns a reverse iterator to the end of the container.
    * @details: The iterator points to the last element.
    *
    * @return: ReverseIterator -> Iterator.
    */
    _NODISCARD __forceinline reverse_iterator rbegin() noexcept { return reverse_iterator(m_LastElement); }

    /**
    * @brief: Returns a const reverse iterator to the end of the container.
    * @details: The iterator points to the last element.
    *
    * @return: ConstReverseIterator -> Iterator.
    */
    _NODISCARD __forceinline const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(m_LastElement); }

    /**
    * @brief: Returns a const reverse iterator to the end of the container.
    * @details: The iterator points to the last element.
    *
    * @return: ConstReverseIterator -> Iterator.
    */
    _NODISCARD __forceinline const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(m_LastElement); }

    /**
    * @brief: Returns a reverse iterator to the begin of the container.
    * @details: The iterator does not point to the first element, points outside the container instead.
    *
    * @return: ReverseIterator -> Iterator.
    */
    _NODISCARD __forceinline reverse_iterator rend() noexcept { return reverse_iterator(m_Head); }

    /**
    * @brief: Returns a const reverse iterator to the begin of the container.
    * @details: The iterator does not point to the first element, points outside the container instead.
    *
    * @return: ConstReverseIterator -> Iterator.
    */
    _NODISCARD __forceinline const_reverse_iterator rend() const noexcept { return const_reverse_iterator(m_Head); }

    /**
    * @brief: Returns a const reverse iterator to the begin of the container.
    * @details: The iterator does not point to the first element, points outside the container instead.
    *
    * @return: ConstReverseIterator -> Iterator.
    */
    _NODISCARD __forceinline const_reverse_iterator crend() const noexcept { return const_reverse_iterator(m_Head); }

    //Member functions
public:
    explicit List()
    {
        Init();
    }

    explicit List(size_t capacity)
    {
        Init();
        Reserve(capacity);
    }

    List(const List& other)
    {
        Init();

        if (other.IsEmpty()) { return; }

        Reserve(other.m_Elements);
        CopyFromList(other);
    }

    List(List&& other) :
        m_FirstElement(other.m_FirstElement),
        m_LastElement(other.m_LastElement),
        m_Head(other.m_Head),
        m_Tail(other.m_Tail),
        m_Unused(other.m_Unused),
        m_Elements(other.m_Elements),
        m_Capacity(other.m_Capacity)
    {
        other.Default();
    }

    List(std::initializer_list<T>&& list)
    {
        Init();
        Reserve(list.size());

        for (auto it = list.begin(); it != list.end(); ++it)
        {
            PushBack(std::move(*it));
        }
    }

    ~List() noexcept
    {
        Nullify();
    }

    List& operator=(const List& other) noexcept
    {
        Clear();

        if (other.IsEmpty()) { return *this; }

        if (other.m_Elements > m_Capacity)
        {
            Reserve(other.m_Elements - m_Capacity);
        }

        CopyFromList(other);

        m_Head->Next = m_FirstElement;
        m_FirstElement->Prev = m_Head;

        return *this;
    }

    List& operator=(List&& other) noexcept
    {
        Nullify();

        if (other.IsEmpty()) { return *this; }

        m_FirstElement = other.m_FirstElement;
        m_LastElement = other.m_LastElement;
        m_Head = other.m_Head;
        m_Tail = other.m_Tail;
        m_Unused = other.m_Unused;
        m_Elements = other.m_Elements;
        m_Capacity = other.m_Capacity;

        other.Default();

        return *this;
    }

    List& operator=(std::initializer_list<T>&& list) noexcept
    {
        Clear();

        if (list.size() > m_Capacity)
        {
            Reserve(list.size() - m_Capacity);
        }

        for (auto it = list.begin(); it != list.end(); ++it)
        {
            PushBack(std::move(*it));
        }

        return *this;
    }

    //Non-member functions
public:
    _NODISCARD __forceinline bool operator==(const List& other) const noexcept
    {
        const_iterator other_it = other.cbegin();
        for (const_iterator this_it = cbegin(); this_it != cend(); ++this_it, ++other_it)
        {
            if (*this_it != *other_it) { return false; }
        }

        return true;
    }

    _NODISCARD __forceinline bool operator!=(const List& other) const noexcept { return !(this == other); }

    _NODISCARD __forceinline bool operator<(const List& other) const noexcept { return Size() < other.Size() ? true : false; }

    _NODISCARD __forceinline bool operator<=(const List& other) const noexcept { return Size() <= other.Size() ? true : false; }

    _NODISCARD __forceinline bool operator>(const List& other) const noexcept { return Size() > other.Size() ? true : false; }

    _NODISCARD __forceinline bool operator>=(const List& other) const noexcept { return Size() >= other.Size() ? true : false; }

private:
    __forceinline void CopyFromList(const List& other) noexcept
    {
        for (List::const_iterator it = other.cbegin(); it != other.cend(); ++it)
        {
            PushBack(*it);
        }
    }

    Node* CreateNode()
    {
        Node* memory_block = nullptr;
        try { memory_block = (Node*)::operator new(sizeof(Node) + sizeof(T)); }
        catch (...)
        {
            ListBadAllocationError();
            return memory_block;
        }
        new (memory_block) Node();
        ++m_Capacity;
        return memory_block;
    }

    Node* CreateNode(const T& element)
    {
        Node* memory_block = nullptr;
        try { memory_block = (Node*)::operator new(sizeof(Node) + sizeof(T)); }
        catch (...)
        {
            ListBadAllocationError();
            return memory_block;
        }
        new (memory_block) Node(element);
        ++m_Capacity;
        ++m_Elements;
        return memory_block;
    }

    Node* CreateNode(T&& element)
    {
        Node* memory_block = nullptr;
        try { memory_block = (Node*)::operator new(sizeof(Node) + sizeof(T)); }
        catch (...)
        {
            ListBadAllocationError();
            return memory_block;
        }
        new (memory_block) Node(std::move(element));
        ++m_Capacity;
        ++m_Elements;
        return memory_block;
    }

    template<typename... Args>
    Node* CreateNode(Args&&... args)
    {
        Node* memory_block = nullptr;
        try { memory_block = (Node*)::operator new(sizeof(Node) + sizeof(T)); }
        catch (...)
        {
            ListBadAllocationError();
            return memory_block;
        }
        new (memory_block) Node(std::forward<Args>(args)...);
        ++m_Capacity;
        ++m_Elements;
        return memory_block;
    }

    __forceinline void DeleteNode(Node* node) noexcept
    {
        node->Prev->Next = node->Next;
        node->Next->Prev = node->Prev;
        --m_Elements;
        --m_Capacity;

        (*node).~Node();
        ::operator delete(node, sizeof(Node) + sizeof(T));
    }

    __forceinline void Assign(Node* node, const T& element) noexcept
    {
        node->SetData(element);
        ++m_Elements;
    }

    __forceinline void Assign(Node* node, T&& element) noexcept
    {
        node->SetData(std::move(element));
        ++m_Elements;
    }

    template<typename... Args>
    __forceinline void Assign(Node* node, Args&&... args) noexcept
    {
        node->SetData(std::forward<Args>(args)...);
        ++m_Elements;
    }

    __forceinline void Nullify() noexcept
    {
        if (!IsEmpty())
        {
            while (m_FirstElement != m_Tail)
            {
                Node* node = m_FirstElement;
                m_FirstElement = m_FirstElement->Next;
                (*node).~Node();
                ::operator delete(node, sizeof(Node) + sizeof(T));
            }
        }

        while (m_Unused)
        {
            Node* node = m_Unused;
            m_Unused = m_Unused->Next;
            (*node).~Node();
            ::operator delete(node, sizeof(Node) + sizeof(T));
        }

        delete m_Head;
        delete m_Tail;

        Default();
    }

    __forceinline void Default() noexcept
    {
        m_FirstElement = nullptr;
        m_LastElement = nullptr;
        m_Head = nullptr;
        m_Tail = nullptr;
        m_Unused = nullptr;
        m_Elements = 0;
        m_Capacity = 0;
    }

    void Init()
    {
        try
        {
            m_Head = new Node();
            m_Tail = new Node();
        }
        catch (...)
        {
            ListBadAllocationError();
        }
    }

    __forceinline Node* GetNodeFromUnused() noexcept
    {
        Node* node = m_Unused;
        m_Unused = m_Unused->Next;
        node->Next = nullptr;
        return node;
    }

    __forceinline void UpdateLastNode() noexcept
    {
        m_LastElement->Next->Prev = m_LastElement;
        m_LastElement = m_LastElement->Next;
        m_LastElement->Next = m_Tail;
        m_Tail->Prev = m_LastElement;
    }

    __forceinline void UpdateFirstNode() noexcept
    {
        m_FirstElement->Prev->Next = m_FirstElement;
        m_FirstElement = m_FirstElement->Prev;
        m_FirstElement->Prev = m_Head;
        m_Head->Next = m_FirstElement;
    }

    /**
    * @brief: Updates the connections of node b, to be inserted before node a.
    *
    * @param: Node* -> Old node.
    * @param: Node* -> Inserted node.
    * @return void.
    */
    __forceinline void UpdateNode(Node* a, Node* b) noexcept
    {
        a->Prev->Next = b;
        b->Prev = a->Prev;
        b->Next = a;
        a->Prev = b;
    }

    __forceinline void SetUnusedFromEmpty() noexcept
    {
        m_FirstElement = m_Unused;
        m_Unused = m_Unused->Next;

        SetControlPointers();
    }

    __forceinline void SetControlPointers() noexcept
    {
        m_FirstElement->Prev = m_Head;
        m_Head->Next = m_FirstElement;
        m_FirstElement->Next = m_Tail;
        m_Tail->Prev = m_FirstElement;
        m_LastElement = m_FirstElement;
    }

    __forceinline void InsertNode(Node* node, const T& element)
    {
        Node* new_node = nullptr;

        if (m_Unused)
        {
            new_node = GetNodeFromUnused();
            UpdateNode(node, new_node);
            Assign(new_node, element);
        }
        else
        {
            new_node = CreateNode(element);
            UpdateNode(node, new_node);
        }
    }

    __forceinline void InsertNode(Node* node, T&& element)
    {
        Node* new_node = nullptr;

        if (m_Unused)
        {
            new_node = GetNodeFromUnused();
            UpdateNode(node, new_node);
            Assign(new_node, std::move(element));
        }
        else
        {
            new_node = CreateNode(std::move(element));
            UpdateNode(node, new_node);
        }
    }

    __forceinline void PushEmpty(const T& element)
    {
        if (m_Unused)
        {
            SetUnusedFromEmpty();
            Assign(m_FirstElement, element);
        }
        else
        {
            m_FirstElement = CreateNode(element);
            SetControlPointers();
        }
    }

    __forceinline void PushEmpty(T&& element)
    {
        if (m_Unused)
        {
            SetUnusedFromEmpty();
            Assign(m_FirstElement, std::move(element));
        }
        else
        {
            m_FirstElement = CreateNode(std::move(element));
            SetControlPointers();
        }
    }

    template<typename... Args>
    __forceinline void EmplaceEmpty(Args&&... args)
    {
        if (m_Unused)
        {
            SetUnusedFromEmpty();
            Assign(m_FirstElement, std::forward<Args>(args)...);
        }
        else
        {
            m_FirstElement = CreateNode(std::forward<Args>(args)...);
            SetControlPointers();
        }
    }

    template<typename... Args>
    __forceinline void EmplaceNode(Node* node, Args&&... args)
    {
        Node* new_node = nullptr;

        if (m_Unused)
        {
            new_node = GetNodeFromUnused();
            UpdateNode(node, new_node);
            Assign(new_node, std::forward<Args>(args)...);
        }
        else
        {
            new_node = CreateNode(std::forward<Args>(args)...);
            UpdateNode(node, new_node);
        }
    }

    [[noreturn]] __forceinline static void ListOutOfRangeError() {
        throw std::exception("List index out of range");
    }

    [[noreturn]] __forceinline static void ListMaxLenghtError() {
        throw std::exception("List too long");
    }

    [[noreturn]] __forceinline static void ListBadAllocationError() {
        throw std::exception("Bad allocation");
    }

private:
    Node* m_FirstElement = nullptr;
    Node* m_LastElement = nullptr;
    Node* m_Head = nullptr;
    Node* m_Tail = nullptr;
    Node* m_Unused = nullptr;
    size_t m_Elements = 0;
    size_t m_Capacity = 0;

    static _CONSTEXPR17 size_t s_MaxListSize = 10000000;
};
