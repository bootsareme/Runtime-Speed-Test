#pragma once

#include <ppl.h>
#include <cmath>
#include <fstream>

#include "vector2d.h"

inline int N = 29;
inline char** chessboard;

namespace Tests
{
	double integer_operations(bool multithreading);
	void backtracking_nqueens(bool multithreading);
	void array_search_sort(bool multithreading);
	void console_io(bool multithreading);
	void matrix_operations(bool multithreading);
}
