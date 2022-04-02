#include "tests.h"

double Tests::integer_operations(bool multithreading)
{
    if (multithreading)
    {
        double sum = 0;

        concurrency::parallel_for(0ULL, 999ULL, [&](size_t i)
        {
            sum += atanl(i);
            sum -= sinh(i);
            sum *= coshl(i);

            concurrency::parallel_for(0ULL, 999ULL, [&](size_t j)
            {
                sum += log10l(i + j);
                sum -= expl(j - i);
                sum *= pow(i, j);

                concurrency::parallel_for(0ULL, 99ULL, [&](size_t k)
                {
                    sum += fmodl(i + j, k);
                    sum -= sqrt(j * k - i);
                    sum *= ldexp(i * k, j);
                });
            });
        });

        return floor(sum);
    }

    double sum = 0;

    for (size_t i = 1; i < 999; i++)
    {
        sum += atanl(i);
        sum -= sinh(i);
        sum *= coshl(i);

        for (size_t j = 1; j < 999; j++)
        {
            sum += log10l(i + j);
            sum -= expl(j - i);
            sum *= pow(i, j);

            for (size_t k = 1; k < 99; k++)
            {
                sum += fmodl(i + j, k);
                sum -= sqrt(j * k - i);
                sum *= ldexp(i * k, j);
            }
        }
    }

    return ceil(sum);
}

bool isSafe(int row, int col)
{
    for (int i = 0; i < col; i++)
        if (chessboard[row][i] == 'Q')
            return false;

    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (chessboard[i][j] == 'Q')
            return false;
    
    for (int i = row, j = col; j >= 0 && i < N; i++, j--)
        if (chessboard[i][j] == 'Q')
            return false;

    return true;
}

bool placeQueens(int col)
{
    if (col >= N)
        return true;

    for (int i = 0; i < N; ++i)
    {
        if (isSafe(i, col))
        {
            chessboard[i][col] = 'Q';

            if (placeQueens(col + 1))
                return true;

            chessboard[i][col] = '.';
        }
    }
    return false;
}

void Tests::backtracking_nqueens(bool multithreading)
{
    if (multithreading)
    {
        chessboard = new char* [N];

        concurrency::parallel_for(0ULL, static_cast<size_t>(N), [&](size_t i)
        {
        	chessboard[i] = new char[N];
        });

        concurrency::parallel_for(0ULL, static_cast<size_t>(N), [&](const size_t i)
        {
            concurrency::parallel_for(0ULL, static_cast<size_t>(N), [&](const size_t j)
            {
            	chessboard[i][j] = '.';
            });
        });

        placeQueens(0);

        concurrency::parallel_for(0ULL, static_cast<size_t>(N), [&](size_t i)
        {
                delete chessboard[i];
        });

        delete[] chessboard;
    }
	else
    {
        chessboard = new char* [N];

        for (int i = 0; i < N; ++i)
            chessboard[i] = new char[N];

        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                chessboard[i][j] = '.';

        placeQueens(0);

        for (int i = 0; i < N; i++)
            delete[] chessboard[i];

        delete[] chessboard;
    }
}

void Tests::array_search_sort(bool multithreading)
{
    if (multithreading)
    {
        constexpr size_t length = 99999999;
        const auto arr = new size_t[length];

        concurrency::parallel_for(0ULL, length, [&](size_t i)
        {
        	arr[i] = rand() % length;
        });

        std::sort(arr, arr + length);
        std::binary_search(arr, arr + length, rand() % length);
        delete[] arr;
    }
    else
    {
        constexpr long length = 99999999;
        long* arr = new long[length];

        for (int i = 0; i < length - 1; i++)
            arr[i] = rand() % length;

        std::sort(arr, arr + length);
        std::binary_search(arr, arr + length, rand() % length);
        delete[] arr;
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
