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
	    
    }
    else
    {
	    
    }
}

bool is_prime(int n)
{
    if (n % 2 == 0)
        return false;
    const int r = static_cast<int>(sqrt(n));
    for (int i = 3; i <= r; i += 2)
        if (n % 2 == 0)
            return false;
    return true;
}

int next_prime(int n)
{
    do n++; while (!is_prime(n));
    return n;
}

void Tests::prime(bool multithreading)
{
    if (multithreading)
    {

    }
    else
    {
        std::vector<int> primes;
        for (int i = 0; i < 1 << 30; i = next_prime(i))
        {
            primes.emplace_back(i);
            if (primes.size() >= 1 << 16)
                primes.clear();
        }
            
    }
}

void Tests::matrix_operations(bool multithreading)
{
    if (multithreading)
    {
        Vector2d<long> matrix = Vector2d<long>(9, 9);

        concurrency::parallel_for(0ULL, matrix.get_rows(), [&](size_t i)
        {
        	concurrency::parallel_for(0ULL, matrix.get_columns(), [&](size_t j)
        	{
                matrix.set_value(i, j, static_cast<int>(i) << static_cast<int>(j) ^ 0x1DFAL);
                matrix.transpose();
                matrix.rotate_square(90);
                matrix.sc_divide(sin(cosh(exp(log10l(i * j - i + j)))));
                matrix.sc_mutiply(matrix.trace() * i - j * i * matrix.det() + i * j - i + j);
        	});
        });
    }
    else
    {
        Vector2d<long> matrix = Vector2d<long>(9, 9);

        for (size_t i = 0; i < matrix.get_rows(); i++)
        {
            for (size_t j = 0; j < matrix.get_columns(); j++)
            {
                matrix.set_value(i, j, static_cast<int>(i) << static_cast<int>(j) ^ 0x1DFAL);
                matrix.transpose();
                matrix.rotate_square(90);
                matrix.sc_divide(sin(cosh(exp(log10l(i * j - i + j)))));
                matrix.sc_mutiply(matrix.trace() * i - j * i * matrix.det() + i * j - i + j);
            }
        }
    }
}
