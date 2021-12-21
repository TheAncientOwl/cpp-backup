#pragma once
#include <cstdlib>
#include <iostream>
#include <type_traits>

#include "Timer.h"
#include "Widget.h"

#include <list>
#include "LinkedList.h"
#include <deque>

#include <stack>
#include <queue>
#include "Queue.h"

#include <vector>
#include "Vector.h"

namespace benchmark
{
	template<typename Container>
	void push_back(const char* name, size_t max_elements)
	{
		std::cout << name;
		Container c;

		if constexpr (std::is_same<std::vector<Vector2>, Container>::value)
			c.reserve(max_elements);

		Timer t;
		for (size_t i = 0; i < max_elements; ++i)
			c.push_back(Vector2(4, 5));
	}

	template<typename Container>
	void PushBack(const char* name, size_t max_elements)
	{
		std::cout << name;
		Container c;

		if constexpr (std::is_same<Vector<Vector2>, Container>::value)
			c.Reserve(max_elements);

		Timer t;
		for (size_t i = 0; i < max_elements; ++i)
			c.PushBack(Vector2(4, 5));
	}


	template<typename Container>
	void emplace_back(const char* name, size_t max_elements)
	{
		std::cout << name;
		Container c;

		if constexpr (std::is_same<std::vector<Vector2>, Container>::value)
			c.reserve(max_elements);

		Timer t;
		for (size_t i = 0; i < max_elements; ++i)
			c.emplace_back(4, 5);
	}

	template<typename Container>
	void EmplaceBack(const char* name, size_t max_elements)
	{
		std::cout << name;
		Container c;

		if constexpr (std::is_same<Vector<Vector2>, Container>::value)
			c.Reserve(max_elements);

		Timer t;
		for (size_t i = 0; i < max_elements; ++i)
			c.EmplaceBack(4, 5);
	}

	template<typename Container>
	void push(const char* name, size_t max_elements)
	{
		std::cout << name;
		Container c;

		Timer t;
		for (size_t i = 0; i < max_elements; ++i)
			c.push(Vector2(4, 5));
	}

	template<typename Container>
	void Push(const char* name, size_t max_elements)
	{
		std::cout << name;
		Container c;

		Timer t;
		for (size_t i = 0; i < max_elements; ++i)
			c.Push(Vector2(4, 5));
	}

	template<typename Container>
	void emplace(const char* name, size_t max_elements)
	{
		std::cout << name;
		Container c;

		Timer t;
		for (size_t i = 0; i < max_elements; ++i)
			c.emplace(4, 5);
	}

	template<typename Container>
	void Emplace(const char* name, size_t max_elements)
	{
		std::cout << name;
		Container c;

		Timer t;
		for (size_t i = 0; i < max_elements; ++i)
			c.Emplace(4, 5);
	}

	void TestContainers()
	{
		const size_t MAX_ELEMENTS = 100000000;
		const size_t TESTS = 5;

		using vec2 = Vector2;

		for (size_t i = 0; i < TESTS; ++i)
		{
			std::cout << "[TEST " << i + 1 << " ]\n";
			{
				std::cout << "[Push Back]:\n";
				std::cout << "Vector:\n";
				benchmark::push_back<std::vector<vec2>>("STL: ", MAX_ELEMENTS);
				benchmark::PushBack<Vector<vec2>>("RMK: ", MAX_ELEMENTS);

				std::cout << "\nList:\n";
				benchmark::push_back<std::list<vec2>>("STL: ", MAX_ELEMENTS);
				benchmark::PushBack<LinkedList<vec2>>("RMK: ", MAX_ELEMENTS);

				/*std::cout << '\n';
				benchmark::push_back<std::deque<vec2>>("Deque: ", MAX_ELEMENTS);
				benchmark::push<std::stack<vec2, std::list<vec2>>>("Stack: ", MAX_ELEMENTS);*/

				std::cout << "\nQueue:\n";
				benchmark::push<std::queue<vec2, std::list < vec2>>>("STL: ", MAX_ELEMENTS);
				benchmark::Push<Queue<vec2>>("RMK: ", MAX_ELEMENTS);
			}

			std::cout << '\n';

			{
				std::cout << "[Emplace Back]:\n";
				std::cout << "Vector:\n";
				benchmark::emplace_back<std::vector<vec2>>("STL: ", MAX_ELEMENTS);
				benchmark::EmplaceBack<Vector<vec2>>("RMK: ", MAX_ELEMENTS);

				std::cout << "\nList:\n";
				benchmark::emplace_back<std::list<vec2>>("STL: ", MAX_ELEMENTS);
				benchmark::EmplaceBack<LinkedList<vec2>>("RMK: ", MAX_ELEMENTS);

				/*std::cout << '\n';
				benchmark::emplace_back<std::deque<vec2>>("Deque: ", MAX_ELEMENTS);
				benchmark::emplace<std::stack<vec2, std::list<vec2>>>("Stack: ", MAX_ELEMENTS);*/

				std::cout << "\nQueue:\n";
				benchmark::emplace<std::queue<vec2, std::list < vec2>>>("STL: ", MAX_ELEMENTS);
				benchmark::Emplace<Queue<vec2>>("RMK: ", MAX_ELEMENTS);
			}

			std::cout << "\n---------------------------------\n";
		}
	}

	void TestReverseVector()
	{
		const size_t VECTOR_SIZE = 10000;
		const size_t NUMBER_OF_TESTS = 100;
		std::vector<int> vector;
		vector.reserve(VECTOR_SIZE);
		for (int i = 0; i < VECTOR_SIZE; ++i)
			vector.push_back(i);

		{
			std::cout << "Stack: ";
			Timer t;
			for (size_t test = 0; test < NUMBER_OF_TESTS; ++test)
			{
				std::vector<int> v(vector);
				std::stack<int, std::list<int>> s;

				for (const auto& x : v)
					s.push(x);

				size_t i = 0;
				while (!s.empty())
				{
					v[i++] = s.top();
					s.pop();
				}

			}
		}

		{
			std::cout << "Optimized: ";
			Timer t;
			for (size_t test = 0; test < NUMBER_OF_TESTS; ++test)
			{
				std::vector<int> v(vector);

				size_t left = 0;
				size_t right = v.size() - 1;

				while (left < right)
				{
					int aux = v[left];
					v[left] = v[right];
					v[right] = aux;
					++left;
					--right;
				}

			}
		}

		std::cout << "\n\n";
	}

	bool Prime1(size_t x)
	{
		for (size_t i = 2; i * i <= x; ++i)
			if (x % i == 0)
				return false;
		return true;
	}

	bool Prime2(size_t x)
	{
		if (x <= 0)
			return false;
		
		if (x % 2 == 0)
			return false;

		for (size_t d = 3; d * d <= x; d += 2)
			if (x % d == 0)
				return false;

		return true;
	}

	void TestPrime()
	{
		const int MAX_NUMBERS = 30000000;
		std::vector<size_t> v;
		v.reserve(MAX_NUMBERS);
		for (size_t i = 0; i < MAX_NUMBERS; ++i)
			v.push_back(std::abs(rand() % 800));

		for (int i = 0; i < 10; ++i)
		{
			{
				std::cout << "Version 1: ";
				Timer t;
				for (const auto& x : v)
					Prime1(x);
			}

			{
				std::cout << "Version 2: ";
				Timer t;
				for (const auto& x : v)
					Prime2(x);
			}

			std::cout << '\n';
		}
		
	}
}