#pragma once
#define __ARRAY_DEBUG
#include <iostream>

template<typename T, size_t size>
class Array
{
private:
	T m_Data[size];

public:
	void Cout();
	void Fill(const T& value);

public:
	constexpr const size_t Size() const;

	T& operator[](size_t index);
	const T& operator[](size_t index) const;

	T* Data();
	const T* Data() const;

public:
	Array() = default;

	Array(const Array& other);
	Array& operator=(const Array& other);

	Array(Array&& other) noexcept;
	Array& operator=(Array&& other) noexcept;
};

#pragma region Implementation

template<typename T, size_t size>
void Array<T, size>::Cout()
{
	for (size_t i = 0; i < size; ++i)
	{
		std::cout << m_Data[i] << '\n';
	}
	std::cout << "-------------\n";
}

template<typename T, size_t size>
inline void Array<T, size>::Fill(const T& value)
{
	for (size_t i = 0; i < size; ++i)
	{
		m_Data[i] = value;
	}
}

template<typename T, size_t size>
constexpr const size_t Array<T, size>::Size() const
{
	return size;
}

template<typename T, size_t size>
T& Array<T, size>::operator[](size_t index)
{
#ifdef __ARRAY_DEBUG
	if (index >= size) { std::cout << "[ERROR] ARRAY OUT OF BOUNDS!"; }
#endif // __ARRAY_DEBUG

	return m_Data[index];
}

template<typename T, size_t size>
const T& Array<T, size>::operator[](size_t index) const
{
#ifdef __ARRAY_DEBUG
	if (index >= size) { std::cout << "[ERROR] ARRAY OUT OF BOUNDS!"; }
#endif // __ARRAY_DEBUG

	return m_Data[index];
}

template<typename T, size_t size>
T* Array<T, size>::Data()
{
	return m_Data;
}

template<typename T, size_t size>
const T* Array<T, size>::Data() const
{
	return m_Data;
}

#pragma endregion

#pragma region Constructors

template<typename T, size_t size>
Array<T, size>::Array(const Array& other)
{
#ifdef __ARRAY_DEBUG
	std::cout << "[Array] Copy Constructor.\n";
#endif // __ARRAY_DEBUG

	for (size_t i = 0; i < size; ++i)
	{
		m_Data[i] = other.m_Data[i];
	}
}

template<typename T, size_t size>
Array<T, size>& Array<T, size>::operator=(const Array& other)
{
#ifdef __ARRAY_DEBUG
	std::cout << "[Array] Copy Operator.\n";
#endif // __ARRAY_DEBUG

	for (size_t i = 0; i < size; ++i)
	{
		m_Data[i] = other.m_Data[i];
	}

	return *this;
}

template<typename T, size_t size>
Array<T, size>::Array(Array&& other) noexcept
{
#ifdef __ARRAY_DEBUG
	std::cout << "[Array] Move Constructor.\n";
#endif // __ARRAY_DEBUG

	for (size_t i = 0; i < size; ++i)
	{
		m_Data[i] = std::move(other.m_Data[i]);
	}
}

template<typename T, size_t size>
Array<T, size>& Array<T, size>::operator=(Array&& other) noexcept
{
#ifdef __ARRAY_DEBUG
	std::cout << "[Array] Move Operator.\n";
#endif // __ARRAY_DEBUG

	for (size_t i = 0; i < size; ++i)
	{
		m_Data[i] = std::move(other.m_Data[i]);
	}

	return *this;
}

#pragma endregion


