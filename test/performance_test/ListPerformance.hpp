#pragma once

/*
* Author: Luis Poveda Cano.
* luispovedacano@gmail.com
*/

/*
* This class is for test the performance of the List vs std::list.
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

#include <list>
#include "List.hpp"

class ListPerformance
{
    static constexpr size_t ITERATIONS = 10;
    static constexpr size_t ELEMENTS = 5000;

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
        Predicate1 std_predicate, Predicate2 predicate)
    {
        double std_time = 0.0;
        double list_time = 0.0;

        double std_list_best = (double)INFINITY;
        double std_list_worst = 0.0;
        double std_list_average = 0.0;
        double list_best = (double)INFINITY;
        double list_worst = 0.0;
        double list_average = 0.0;

        Timer timer;
        {
            for (size_t i = 0; i < ITERATIONS; ++i)
            {
                std::list<TestStruct> std_list;
                timer.Start();
                std_predicate(std_list);
                std_time = timer.Stop();

                if (std_time < std_list_best) { std_list_best = std_time; }
                if (std_time > std_list_worst) { std_list_worst = std_time; }
                std_list_average += std_time;

                List<TestStruct> list;
                timer.Start();
                predicate(list);
                list_time = timer.Stop();

                if (list_time < list_best) { list_best = list_time; }
                if (list_time > list_worst) { list_worst = list_time; }
                list_average += list_time;
            }

            std_list_average /= (double)ITERATIONS;
            list_average /= (double)ITERATIONS;

            Serializer::WriteResults(stream, "std::list", "List", test_name, "TestStruct", ELEMENTS, ITERATIONS, std_list_best, std_list_worst, std_list_average, list_best, list_worst, list_average);
        }
    }
};
