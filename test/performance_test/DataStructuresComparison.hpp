#pragma once

/*
* Author: Luis Poveda Cano.
* luispovedacano@gmail.com
*/

/*
* This class is for test the performance of the different data structures.
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
#include "Vector.hpp"
#include "List.hpp"

#include <iostream> //For std::fixed
#include <iomanip>  //For std::setprecision
#include <string>
#include <sstream>  //For std::stringstream

class DataStructuresComparison
{
    static constexpr size_t ITERATIONS = 10;
    static constexpr size_t ELEMENTS = 5000000;
public:
    static void RunAllTest();

public:
    static void PushBack();
    static void InsertFront();
    static void InsertMiddle();
    static void InsertRandom();

private:
    template <typename Predicate1, typename Predicate2>
    static void Test(std::stringstream& stream, const std::string& test_name,
        Predicate1 vector_predicate, Predicate2 list_predicate, size_t elements = ELEMENTS)
    {
        double vector_time = 0.0;
        double list_time = 0.0;

        double vector_best = (double)INFINITY;
        double vector_worst = 0.0;
        double vector_average = 0.0;
        double list_best = (double)INFINITY;
        double list_worst = 0.0;
        double list_average = 0.0;

        Timer timer;
        {
            for (size_t i = 0; i < ITERATIONS; ++i)
            {
                Vector<TestStruct> vector(elements);
                timer.Start();
                vector_predicate(vector);
                vector_time = timer.Stop();

                if (vector_time < vector_best) { vector_best = vector_time; }
                if (vector_time > vector_worst) { vector_worst = vector_time; }
                vector_average += vector_time;

                List<TestStruct> list(elements);
                timer.Start();
                list_predicate(list);
                list_time = timer.Stop();

                if (list_time < list_best) { list_best = list_time; }
                if (list_time > list_worst) { list_worst = list_time; }
                list_average += list_time;
            }

            vector_average /= (double)ITERATIONS;
            list_average /= (double)ITERATIONS;
        }

        Serializer::WriteResults(stream, test_name, "TestStruct", elements, ITERATIONS, vector_best, vector_worst, vector_average, list_best, list_worst, list_average);
    }
};

