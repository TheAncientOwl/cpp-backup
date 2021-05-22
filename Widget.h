#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
//#define __VECTOR2_DEBUG
#define MAX_SIZE 10
class Vector2
{
private:
	float x, y;
	std::array<int, MAX_SIZE> v;

public:
	Vector2() : x(0), y(0) { std::fill(v.begin(), v.end(), 100); }
	Vector2(float x, float y) : x(x), y(y) { std::fill(v.begin(), v.end(), 100); }

	bool operator<(const Vector2& other) const
	{
		return (x < other.x || (x == other.x && y < other.y));
	}

	bool operator>(const Vector2& other) const
	{
		return (x > other.x || (x == other.x && y > other.y));
	}

	bool operator==(const Vector2& other) const
	{
		return (x == other.x && y == other.y);
	}

	Vector2(const Vector2& other) : v(other.v)
	{
#ifdef __VECTOR2_DEBUG
		std::cout << "[V2] Copy ()\n";
#endif // __VECTOR2_DEBUG

		this->x = other.x;
		this->y = other.y;
	}

	Vector2& operator=(const Vector2& other)
	{
#ifdef __VECTOR2_DEBUG
		std::cout << "[V2] Copy =\n";
#endif // __VECTOR2_DEBUG

		this->x = other.x;
		this->y = other.y;
		this->v = other.v;
		return *this;
	}

	Vector2(Vector2&& other) noexcept
	{
#ifdef __VECTOR2_DEBUG
		std::cout << "[V2] Move ()\n";
#endif // __VECTOR2_DEBUG

		this->x = std::move(other.x);
		this->y = std::move(other.y);
		this->v = std::move(other.v);
	}

	Vector2& operator=(Vector2&& other) noexcept
	{
#ifdef __VECTOR2_DEBUG
		std::cout << "[V2] Move =\n";
#endif // __VECTOR2_DEBUG

		this->x = std::move(other.x);
		this->y = std::move(other.y);
		this->v = std::move(other.v);
		return *this;
	}

	~Vector2()
	{
#ifdef __VECTOR2_DEBUG
		std::cout << "[V2] Destroy\n";
#endif // __VECTOR2_DEBUG
	}

	friend std::ostream& operator<<(std::ostream& out, const Vector2& v);
}; 

std::ostream& operator<<(std::ostream& out, const Vector2& v)
{
	out << "(" << v.x << ", " << v.y << ")";
	return out;
}