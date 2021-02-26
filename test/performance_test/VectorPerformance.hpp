#pragma once

/*
* Author: Luis Poveda Cano.
* luispovedacano@gmail.com
*/

/*
* This class is for test the performance of the Vector vs std::vector.
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

#include "../Serializer.hpp"
#include "../TestStruct.hpp"
#include "../Timer.hpp"

#include <sstream>  //For stringstream

#include <vector>
#include "Vector.hpp"

class VectorPerformance
{
    static constexpr size_t ITERATIONS = 10;
    static constexpr size_t ELEMENTS = 5000000;

public:
    static void RunAllTest();

public:
    static void PushBack();
    static void EmplaceBack();
    static void InsertFront();
    static void InsertMiddle();
    static void InsertRandom();
    static void EmplaceFront();
    static void EmplaceMiddle();
    static void EmplaceRandom();

private:
    template <typename Predicate1, typename Predicate2>
    static void Test(std::stringstream& stream, const std::string& test_name,
        Predicate1 std_predicate, Predicate2 predicate, size_t elements = ELEMENTS)
    {
        double std_time = 0.0;
        double vector_time = 0.0;

        double std_vector_best = (double)INFINITY;
        double std_vector_worst = 0.0;
        double std_vector_average = 0.0;
        double vector_best = (double)INFINITY;
        double vector_worst = 0.0;
        double vector_average = 0.0;

        Timer timer;
        {
            for (size_t i = 0; i < ITERATIONS; ++i)
            {
                std::vector<TestStruct> std_vector;
                timer.Start();
                std_predicate(std_vector);
                std_time = timer.Stop();

                if (std_time < std_vector_best) { std_vector_best = std_time; }
                if (std_time > std_vector_worst) { std_vector_worst = std_time; }
                std_vector_average += std_time;

                Vector<TestStruct> vector;
                timer.Start();
                predicate(vector);
                vector_time = timer.Stop();

                if (vector_time < vector_best) { vector_best = vector_time; }
                if (vector_time > vector_worst) { vector_worst = vector_time; }
                vector_average += vector_time;
            }

            std_vector_average /= (double)ITERATIONS;
            vector_average /= (double)ITERATIONS;

            Serializer::WriteResults(stream, "std::vector", "Vector", test_name, "TestStruct", elements, ITERATIONS, std_vector_best, std_vector_worst, std_vector_average, vector_best, vector_worst, vector_average);
        }
    }
};
