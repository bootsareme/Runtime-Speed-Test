// vector2d.h
//
// Copyright © 2020 VJZ Corporation. All rights reserved.
//
// Base class for the C++ Vector2d Library, used for 
// manipulating 2 dimensional vectors (matrices). This 
// library is a standalone file and is not part of any 
// other file system.
//
// This file is subjected to the terms and conditions defined in
// 'LICENSE.txt', which is part of the following source code file.

#pragma once

#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>
#include <vector>
#include <map>
#include <string>

template <class _Ty>
class Vector2d final
{
public:
	Vector2d<_Ty>(size_t _rows, size_t _columns)
		: m_rows(_rows), m_columns(_columns)
	{
		std::vector<std::vector<_Ty>> _vector;

		for (size_t i = 0; i < _rows; i++)
		{
			std::vector<_Ty> _col_vector;

			for (size_t j = 0; j < _columns; j++)
			{
				if (typeid(_Ty) == typeid(std::string) || typeid(_Ty) == typeid(char)) 
					_col_vector.push_back('0');
				else
					_col_vector.push_back(NULL);
			}

			_vector.push_back(_col_vector);
		}

		this->m_data = _vector;
	}

	~Vector2d()
	{
		this->m_data.clear();
		this->m_data.shrink_to_fit();
	}

	[[nodiscard]] std::string get_rawstring() const
	{
		std::string raw_s_ = "{ ";

		for (auto i : this->m_data)
		{
			raw_s_ += "{ ";

			for (auto j : i)
				raw_s_ = raw_s_ + std::to_string(j) + ", ";

			raw_s_ += "} ";
		}

		raw_s_ += "}";
		return raw_s_;
	}

	void printf() const
	{
		for (auto& i : m_data)
		{
			for (auto& j : i) 
				std::cout << j << ' ';

			std::cout << '\n';
		}
	}

	[[nodiscard]] size_t get_rows() const
	{
		return this->m_rows;
	}

	[[nodiscard]] size_t get_columns() const
	{
		return this->m_columns;
	}

	void set_value(size_t xpos, size_t ypos, _Ty value)
	{
		this->m_data[ypos][xpos] = value;
	}

	[[nodiscard]] std::vector<std::vector<_Ty>> get_rawdata() const
	{
		return this->m_data;
	}

	void set_rawdata(std::vector<std::vector<_Ty>> raw)
	{
		this->m_data = raw;
	}

	_Ty value_at(size_t xpos, size_t ypos)
	{
		return this->m_data[ypos][xpos];
	}

	void rotate_square(unsigned short degrees)
	{
		if (m_rows != m_columns)
			throw std::runtime_error("Vector2d object is not a square matrix.");

		size_t _acw_4f;
		const size_t N = m_data.size();

		switch (degrees)
		{
		case 270:
			_acw_4f = 1;
			break;
		case 180:
			_acw_4f = 2;
			break;
		case 90:
			_acw_4f = 3;
			break;
		default:
			throw std::runtime_error("Cannot rotate Vector2d object by " + std::to_string(degrees) + " degrees.");
		}

		for (size_t k = 0; k < _acw_4f; k++)
		{
			for (size_t x = 0; x < N / 2; x++)
			{
				for (size_t y = x; y < N - x - 1; y++)
				{
					_Ty tmp = m_data[x][y];
					m_data[x][y] = m_data[y][N - 1 - x];
					m_data[y][N - 1 - x] = m_data[N - 1 - x][N - 1 - y];
					m_data[N - 1 - x][N - 1 - y] = m_data[N - 1 - y][x];
					m_data[N - 1 - y][x] = tmp;
				}
			}
		}
	}

	friend Vector2d<_Ty> operator+(Vector2d<_Ty>& _vec_2d_1, Vector2d<_Ty>& _vec_2d_2)
	{
		Vector2d<_Ty> res_vec2d = Vector2d<_Ty>(_vec_2d_1.get_rows(), _vec_2d_1.get_columns());

		for (size_t i = 0; i < _vec_2d_1.get_rows(); i++)
			for (size_t j = 0; j < _vec_2d_1.get_columns(); j++)
				res_vec2d.set_value(i, j, _vec_2d_1.value_at(i, j) + _vec_2d_2.value_at(i, j));

		return res_vec2d;
	}

	void operator+=(Vector2d<_Ty>& _vec_2d_2)
	{
		Vector2d<_Ty> res_vec2d = Vector2d<_Ty>(this->get_rows(), this->get_columns());

		for (size_t i = 0; i < this->get_rows(); i++)
			for (size_t j = 0; j < this->get_columns(); j++)
				res_vec2d.set_value(i, j, this->value_at(i, j) + _vec_2d_2.value_at(i, j));

		for (size_t i = 0; i < this->get_rows(); i++)
			for (size_t j = 0; j < this->get_columns(); j++)
				this->m_data[i][j] = res_vec2d.value_at(i, j);
	}

	friend Vector2d<_Ty> operator-(Vector2d<_Ty>& _vec_2d_1, Vector2d<_Ty>& _vec_2d_2)
	{
		Vector2d<_Ty> res_vec2d = Vector2d<_Ty>(_vec_2d_1.get_rows(), _vec_2d_1.get_columns());

		for (size_t i = 0; i < _vec_2d_1.get_rows(); i++)
			for (size_t j = 0; j < _vec_2d_1.get_columns(); j++)
				res_vec2d.set_value(i, j, _vec_2d_1.value_at(i, j) - _vec_2d_2.value_at(i, j));

		return res_vec2d;
	}

	void operator-=(Vector2d<_Ty>& _vec_2d_2)
	{
		Vector2d<_Ty> res_vec2d = Vector2d<_Ty>(this->get_rows(), this->get_columns());

		for (size_t i = 0; i < this->get_rows(); i++)
			for (size_t j = 0; j < this->get_columns(); j++)
				res_vec2d.set_value(i, j, this->value_at(i, j) - _vec_2d_2.value_at(i, j));

		for (size_t i = 0; i < this->get_rows(); i++)
			for (size_t j = 0; j < this->get_columns(); j++)
				this->m_data[i][j] = res_vec2d.value_at(i, j);
	}

	Vector2d& operator=(Vector2d<_Ty> _vec_2d_2)
	{
		this->m_data = _vec_2d_2.m_data;
		return *this;
	}

	Vector2d<_Ty> scmutiply(_Ty scalar)
	{
		Vector2d<_Ty> res = Vector2d<_Ty>(this->m_rows, this->m_columns);

		for (size_t i = 0; i < this->m_rows; i++)
			for (size_t j = 0; j < this->m_columns; j++)
				res.m_data[i][j] = this->m_data[i][j] * scalar;

		return res;
	}

	Vector2d<_Ty> scdivide(_Ty scalar)
	{
		Vector2d<_Ty> res = Vector2d<_Ty>(this->m_rows, this->m_columns);

		for (size_t i = 0; i < this->m_rows; i++)
			for (size_t j = 0; j < this->m_columns; j++)
				res.m_data[i][j] = this->m_data[i][j] * scalar;

		return res;
	}

	Vector2d<_Ty> transpose()
	{
		std::vector<std::vector<_Ty>> _vector;

		for (size_t i = 0; i < m_columns; i++)
		{
			std::vector<_Ty> _col_vector;

			for (size_t j = 0; j < m_rows; j++)
			{
				if (typeid(_Ty) == typeid(std::string) || typeid(_Ty) == typeid(char))
					_col_vector.push_back('0');
				else
					_col_vector.push_back(NULL);
			}

			_vector.push_back(_col_vector);
		}

		for (size_t i = 0; i < m_columns; i++)
			for (size_t j = 0; j < m_rows; j++)
				_vector[j][i] = m_data[i][j];

		Vector2d<_Ty> res = Vector2d<_Ty>(m_columns, m_rows);
		res.m_data = _vector;
		return res;
	}

	std::pair<int, int> search_for(_Ty Val)
	{
		std::pair<int, int> _loc_;
		size_t m = 0; size_t n = 0;

		for (size_t i = 0; i < this->m_rows; i++)
		{
			for (size_t j = 0; j < this->m_columns; j++)
			{
				if (m_data[i][j] == Val)
				{
					_loc_.first = j;
					_loc_.second = i;
					return _loc_;
				}
			}
		}

		_loc_.first = -1;
		_loc_.second = -1;
		return _loc_;
	}


	[[nodiscard]] _Ty trace() const /* The sum along the diagonal of the matrix. */
	{
		if (m_rows != m_columns)
			throw std::runtime_error("Vector2d object is not a square matrix.");

		_Ty sum = NULL;

		for (size_t i = 0; i < m_rows; i++)
			sum += m_data[i][i];

		return sum;
	}

	[[nodiscard]] double norm() const /* Norm is the square root of the sum of all the elements. */
	{
		if (m_rows != m_columns)
			throw std::runtime_error("Vector2d object is not a square matrix.");

		_Ty sum = NULL;

		for (size_t i = 0; i < m_rows; i++)
			for (size_t j = 0; j < m_rows; j++)
				sum += m_data[i][j] * m_data[i][j];

		return sqrt(sum);
	}

	Vector2d<_Ty> unique_sort()
	{
		Vector2d<_Ty> sort_matrix_7f = Vector2d<_Ty>(m_rows, m_columns);
		std::map<_Ty, std::vector<_Ty>> t_55g_Heap;
		size_t rows = 0;

		for (const auto& i : t_55g_Heap)
		{
			sort_matrix_7f.m_data[rows] = i.second;
			rows++;
		}

		return sort_matrix_7f;
	}

	Vector2d<_Ty> unique_rsort()
	{
		Vector2d<_Ty> sort_matrix_7f = Vector2d<_Ty>(m_rows, m_columns);
		std::map<_Ty, std::vector<_Ty>, std::greater<_Ty>> t_55g_Heap_Rev;
		size_t rows = 0;

		for (const auto& i : t_55g_Heap_Rev)
		{
			sort_matrix_7f.m_data[rows] = i.second;
			rows++;
		}

		return sort_matrix_7f;
	}

private:
	const size_t m_rows;
	const size_t m_columns;
	std::vector<std::vector<_Ty>> m_data;
};

#endif // VECTOR2D_H