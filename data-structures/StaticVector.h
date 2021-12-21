#pragma once
#define __STATIC_VECTOR_DEBUG
#include <iostream>

template<typename T, size_t maxCapacity>
class StaticVector
{
private:
	T m_Data[maxCapacity];
	size_t m_Size = 0;

public:
	constexpr const size_t Capacity() const;
	const size_t Size() const;
	const bool IsFull() const;

	T& operator[](size_t index);
	const T& operator[](size_t index) const;

	T* Data();
	const T* Data() const;

public:
	void Cout();
	void PushBack(const T& value);
	void PushBack(T&& value);
	void PopBack();
	template<typename... Args>
	T& EmplaceBack(Args&&... args);
	void Resize(size_t newSize);

public:
	StaticVector();

	StaticVector(const StaticVector& other);
	StaticVector& operator=(const StaticVector& other);

	StaticVector(StaticVector&& other) noexcept;
	StaticVector& operator=(StaticVector&& other) noexcept;
};

template<typename T, size_t maxCapacity>
inline void StaticVector<T, maxCapacity>::Cout()
{
	for (size_t i = 0; i < m_Size; ++i)
		std::cout << m_Data[i] << '\n';
	
	std::cout << "----------\n";
}

template<typename T, size_t maxCapacity>
inline constexpr const size_t StaticVector<T, maxCapacity>::Capacity() const
{
	return maxCapacity;
}

template<typename T, size_t maxCapacity>
inline const size_t StaticVector<T, maxCapacity>::Size() const
{
	return m_Size;
}

template<typename T, size_t maxCapacity>
inline const bool StaticVector<T, maxCapacity>::IsFull() const
{
	return maxCapacity == m_Size;
}

template<typename T, size_t maxCapacity>
inline T& StaticVector<T, maxCapacity>::operator[](size_t index)
{
#ifdef __STATIC_VECTOR_DEBUG
	if (index >= maxCapacity)
		std::cout << "[ERROR] STATIC VECTOR OUT OF BOUNDS!\n";
#endif // __STATIC_VECTOR_DEBUG

	return m_Data[index];
}

template<typename T, size_t maxCapacity>
inline const T& StaticVector<T, maxCapacity>::operator[](size_t index) const
{
#ifdef __STATIC_VECTOR_DEBUG
	if (index >= maxCapacity)
		std::cout << "[ERROR] STATIC VECTOR OUT OF BOUNDS!\n";
#endif // __STATIC_VECTOR_DEBUG

	return m_Data[index];
}

template<typename T, size_t maxCapacity>
inline T* StaticVector<T, maxCapacity>::Data()
{
	return m_Data;
}

template<typename T, size_t maxCapacity>
inline const T* StaticVector<T, maxCapacity>::Data() const
{
	return m_Data;
}

template<typename T, size_t maxCapacity>
inline void StaticVector<T, maxCapacity>::PushBack(const T& value)
{
#ifdef __STATIC_VECTOR_DEBUG
	if (m_Size + 1 >= maxCapacity)
		std::cout << "[ERROR] STATIC VECTOR OUT OF BOUNDS!\n";
#endif // __STATIC_VECTOR_DEBUG
	m_Data[m_Size++] = value;
}

template<typename T, size_t maxCapacity>
inline void StaticVector<T, maxCapacity>::PushBack(T&& value)
{
#ifdef __STATIC_VECTOR_DEBUG
	if (m_Size + 1 >= maxCapacity)
		std::cout << "[ERROR] STATIC VECTOR OUT OF BOUNDS!\n";
#endif // __STATIC_VECTOR_DEBUG
	m_Data[m_Size++] = std::move(value);
}

template<typename T, size_t maxCapacity>
inline void StaticVector<T, maxCapacity>::PopBack()
{
#ifdef __STATIC_VECTOR_DEBUG
	if (m_Size - 1 < 0)
		std::cout << "[ERROR] STATIC VECTOR NEGATIVE INDEX!\n";
#endif // __STATIC_VECTOR_DEBUG

	m_Data[--m_Size].~T();
}

template<typename T, size_t maxCapacity>
inline void StaticVector<T, maxCapacity>::Resize(size_t newSize)
{
#ifdef __STATIC_VECTOR_DEBUG
	if (newSize > maxCapacity)
		std::cout << "[ERROR] STATIC VECTOR OUT OF BOUNDS!\n";
#endif // __STATIC_VECTOR_DEBUG

	if (newSize < m_Size)
		while (m_Size > newSize)
			m_Data[--m_Size].~T();
	else
		m_Size = newSize;
}

template<typename T, size_t maxCapacity>
inline StaticVector<T, maxCapacity>::StaticVector()
{
	m_Size = 0;
}

template<typename T, size_t maxCapacity>
inline StaticVector<T, maxCapacity>::StaticVector(const StaticVector& other)
{
#ifdef __STATIC_VECTOR_DEBUG
	std::cout << "[StaticVector] Copy Constructor.\n";
#endif // __STATIC_VECTOR_DEBUG

	this->m_Size = other.m_Size;
	for (size_t i = 0; i < m_Size; ++i)
	{
		m_Data[i] = other.m_Data[i];
	}
}

template<typename T, size_t maxCapacity>
inline StaticVector<T, maxCapacity>& StaticVector<T, maxCapacity>::operator=(const StaticVector& other)
{
#ifdef __STATIC_VECTOR_DEBUG
	std::cout << "[StaticVector] Copy Operator.\n";
#endif // __STAITC_VECTOR_DEBUG

	this->m_Size = other.m_Size;
	for (size_t i = 0; i < m_Size; ++i)
	{
		m_Data[i] = other.m_Data[i];
	}
	return *this;
}

template<typename T, size_t maxCapacity>
inline StaticVector<T, maxCapacity>::StaticVector(StaticVector&& other) noexcept
{
#ifdef __STATIC_VECTOR_DEBUG
	std::cout << "[StaticVector] Move Constructor.\n";
#endif // __STATIC_VECTOR_DEBUG

	this->m_Size = other.m_Size;
	other.m_Size = 0;
	for (size_t i = 0; i < m_Size; ++i)
	{
		m_Data[i] = std::move(other.m_Data[i]);
	}
}

template<typename T, size_t maxCapacity>
inline StaticVector<T, maxCapacity>& StaticVector<T, maxCapacity>::operator=(StaticVector&& other) noexcept
{
#ifdef __STATIC_VECTOR_DEBUG
	std::cout << "[StaticVector] Move Operator.\n";
#endif // _STATIC_VECTOR_DEBUG

	this->m_Size = other.m_Size;
	for (size_t i = 0; i < m_Size; ++i)
	{
		m_Data[i] = std::move(other.m_Data[i]);
	}
	return *this;
}

template<typename T, size_t maxCapacity>
template<typename ...Args>
inline T& StaticVector<T, maxCapacity>::EmplaceBack(Args && ...args)
{
#ifdef __STATIC_VECTOR_DEBUG
	if (m_Size + 1 >= maxCapacity)
		std::cout << "[ERROR] STATIC VECTOR OUT OF BOUNDS!\n";
#endif // __STATIC_VECTOR_DEBUG

	new(&m_Data[m_Size]) T(std::forward<Args>(args)...);
	return m_Data[m_Size++];
}
