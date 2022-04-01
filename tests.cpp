#include "tests.h"

void Tests::integer_operations(bool multithreading)
{
    if (multithreading)
    {

    }
    else
    {
        
    }
}

void Tests::array_search_sort(bool multithreading)
{
    if (multithreading)
    {

    }
    else
    {

    }
}

void Tests::console_io(bool multithreading)
{
    if (multithreading)
    {
        std::ofstream out{ "NUL" };
        concurrency::parallel_for(0ULL, 999999ULL, [&](size_t i)
        {
            out << 36969 * (i & 65535) + (i >> 16) << 16;
            out.flush();
        });
        out.close();
    }
    else
    {
        std::ofstream out{ "NUL" };
	    for (size_t i = 0; i < 9999999; i++)
	    {
            out << 36969 * (i & 65535) + (i >> 16) << 16;
            out.flush();
	    }
        out.close();
    }
}

void Tests::matrix_operations(bool multithreading)
{
    if (multithreading)
    {
        Vector2d<unsigned long long> matrix = Vector2d<unsigned long long>(100, 100);

        concurrency::parallel_for(0ULL, matrix.get_rows(), [&](const size_t i)
        {
        	concurrency::parallel_for(0ULL, matrix.get_columns(), [&](const size_t j)
        	{
                matrix.set_value(i, j, i + j * i - j & 0x6ADF9B27ULL << 18000 * (i & 0xFFFF) + (j >> 0xF) & 0xFFFF);
                matrix.rotate_square(270);
                matrix.transpose();
                matrix.scmutiply(log10l(i - j * matrix.value_at(i, j) + j * i) + matrix.norm());
                matrix.scdivide(matrix.trace() * asinhl(i - j + i * matrix.value_at(i, j)) + coshl(matrix.norm()));
                matrix.unique_sort();
                matrix.unique_rsort();
        	});
        });
    }
    else
    {
        Vector2d<unsigned long long> matrix = Vector2d<unsigned long long>(100, 100);

        for (size_t i = 0; i < matrix.get_rows(); i++)
        {
            for (size_t j = 0; j < matrix.get_columns(); j++)
            {
                matrix.set_value(i, j, i + j * i - j & 0x6ADF9B27ULL << 18000 * (i & 0xFFFF) + (j >> 0xF) & 0xFFFF);
                matrix.rotate_square(270);
                matrix.transpose();
                matrix = matrix.scmutiply(log10l(i - j * matrix.value_at(i, j) + j * i) + matrix.norm());
                matrix = matrix.scdivide(matrix.trace() * asinhl(i - j + i * matrix.value_at(i, j)) + coshl(matrix.norm()));
                matrix = matrix.unique_sort();
                matrix = matrix.unique_rsort();
            }
        }
    }
}
