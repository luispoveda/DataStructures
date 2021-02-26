#pragma once

#include <iostream> //For std::fixed
#include <iomanip>  //For std::setprecision
#include <string>
#include <sstream>  //For std::stringstream
#include <fstream>  //For std::ofstream

class Serializer
{
public:
    static void SerializeResults(const std::string& name, std::stringstream& stream) noexcept
    {
        std::ofstream file;
        const std::string filename("data/" + name);
        file.open(filename, std::ios::out | std::ios::trunc);
        file << stream.str();
        file.close();
        stream.clear();
        stream.flush();
        stream.str("");
    }

    static void SerializePerformance(const std::string& name, std::stringstream& stream) noexcept
    {
        std::ofstream file;
        const std::string filename("data/" + name);
        file.open(filename, std::ios::out | std::ios::app);
        file << stream.str();
        file.close();
        stream.clear();
        stream.flush();
        stream.str("");
    }

    static void WriteSeparator(const size_t line_size, std::stringstream& stream) noexcept
    {
        for (size_t i = 0; i < line_size; ++i)
        {
            stream << "*";
        }
        stream << std::endl;
    }

    static void WriteSpaceUntilEndOfLine(const size_t spaces, std::stringstream& stream) noexcept
    {
        for (size_t i = 1; i < spaces; ++i)
        {
            stream << " ";
        }
        stream << "*" << std::endl;
    }

    static void WriteResults(std::stringstream& stream, const std::string& std_container_type, const std::string& container_type,
        const std::string& name, const std::string& data_type,
        const size_t elements, const size_t iterations,
        double std_vector_best, double std_vector_worst, double std_vector_average,
        double vector_best, double vector_worst, double vector_average)
    {
        size_t elements_size = 0;
        size_t iterations_size = 0;
        {
            size_t tmp = elements;
            while (tmp != 0)
            {
                ++elements_size;
                tmp /= 10;
            }

            tmp = iterations;
            while (tmp != 0)
            {
                ++iterations_size;
                tmp /= 10;
            }
        }
        const size_t line_size = 31 + elements_size;
        constexpr size_t precision = 20;

        WriteSeparator(line_size, stream);
        stream << "* " << name.c_str(); WriteSpaceUntilEndOfLine(line_size - (2 + name.size()), stream);
        stream << "* Number of elements tested: " << elements; WriteSpaceUntilEndOfLine(line_size - (29 + elements_size), stream);
        stream << "* Number of iterations: " << iterations; WriteSpaceUntilEndOfLine(line_size - (24 + iterations_size), stream);
        stream << "* Data type: " << data_type.c_str(); WriteSpaceUntilEndOfLine(line_size - (13 + data_type.size()), stream);
        WriteSeparator(line_size, stream);
        stream << std_container_type << " stats:" << std::endl;
        stream << "Best time:          " << std::fixed << std::setprecision(precision) << std_vector_best << " seconds" << std::endl;
        stream << "Worst time:         " << std::fixed << std::setprecision(precision) << std_vector_worst << " seconds" << std::endl;
        stream << "Average time:       " << std::fixed << std::setprecision(precision) << std_vector_average << " seconds" << std::endl;
        stream << "Time per operation: " << std::fixed << std::setprecision(precision) << std_vector_average / (double)elements << " seconds" << std::endl;
        stream << std::endl;
        stream << container_type << " stats:" << std::endl;
        stream << "Best time:          " << std::fixed << std::setprecision(precision) << vector_best << " seconds" << std::endl;
        stream << "Worst time:         " << std::fixed << std::setprecision(precision) << vector_worst << " seconds" << std::endl;
        stream << "Average time:       " << std::fixed << std::setprecision(precision) << vector_average << " seconds" << std::endl;
        stream << "Time per operation: " << std::fixed << std::setprecision(precision) << vector_average / (double)elements << " seconds" << std::endl;
        stream << std::endl;
        double percentage = 0.0;
        if (std_vector_average <= vector_average)
        {
            percentage = vector_average * 100.0 / std_vector_average;
            percentage = percentage - 100.0;
            stream << container_type << " was " << std::fixed << std::setprecision(2) << percentage << "% slower.";
        }
        else
        {
            percentage = std_vector_average * 100.0 / vector_average;
            percentage = percentage - 100.0;
            stream << std_container_type << " was " << std::fixed << std::setprecision(2) << percentage << "% slower.";
        }

        stream << std::endl;
        stream << std::endl;
    }

    static void WriteResults(std::stringstream& stream, const std::string& name, const std::string& data_type,
        const size_t elements, const size_t iterations,
        double vector_best, double vector_worst, double vector_average,
        double list_best, double list_worst, double list_average)
    {
        size_t elements_size = 0;
        size_t iterations_size = 0;
        {
            size_t tmp = elements;
            while (tmp != 0)
            {
                ++elements_size;
                tmp /= 10;
            }

            tmp = iterations;
            while (tmp != 0)
            {
                ++iterations_size;
                tmp /= 10;
            }
        }
        const size_t line_size = 31 + elements_size;
        constexpr size_t precision = 20;

        WriteSeparator(line_size, stream);
        stream << "* " << name.c_str(); WriteSpaceUntilEndOfLine(line_size - (2 + name.size()), stream);
        stream << "* Number of elements tested: " << elements; WriteSpaceUntilEndOfLine(line_size - (29 + elements_size), stream);
        stream << "* Number of iterations: " << iterations; WriteSpaceUntilEndOfLine(line_size - (24 + iterations_size), stream);
        stream << "* Data type: " << data_type.c_str(); WriteSpaceUntilEndOfLine(line_size - (13 + data_type.size()), stream);
        WriteSeparator(line_size, stream);
        stream << "Vector stats:" << std::endl;
        stream << "Best time:          " << std::fixed << std::setprecision(precision) << vector_best << " seconds" << std::endl;
        stream << "Worst time:         " << std::fixed << std::setprecision(precision) << vector_worst << " seconds" << std::endl;
        stream << "Average time:       " << std::fixed << std::setprecision(precision) << vector_average << " seconds" << std::endl;
        stream << "Time per operation: " << std::fixed << std::setprecision(precision) << vector_average / (double)elements << " seconds" << std::endl;
        stream << std::endl;
        stream << "List stats:" << std::endl;
        stream << "Best time:          " << std::fixed << std::setprecision(precision) << list_best << " seconds" << std::endl;
        stream << "Worst time:         " << std::fixed << std::setprecision(precision) << list_worst << " seconds" << std::endl;
        stream << "Average time:       " << std::fixed << std::setprecision(precision) << list_average << " seconds" << std::endl;
        stream << "Time per operation: " << std::fixed << std::setprecision(precision) << list_average / (double)elements << " seconds" << std::endl;
        stream << std::endl;
        double percentage = 0.0;
        if (vector_average <= list_average)
        {
            percentage = list_average * 100.0 / vector_average;
            percentage = percentage - 100.0;
            stream << "List was " << std::fixed << std::setprecision(2) << percentage << "% slower.";
        }
        else
        {
            percentage = vector_average * 100.0 / list_average;
            percentage = percentage - 100.0;
            stream << "Vector was " << std::fixed << std::setprecision(2) << percentage << "% slower.";
        }

        stream << std::endl;
        stream << std::endl;
    }
};
