#pragma once
#include <iostream>
//#define __VECTOR_DEBUG

template<typename T>
class Vector
{
private:
	T* m_Data = nullptr;
	size_t m_Capacity = 0;
	size_t m_Size = 0;

public:
	void Cout();
	void PushBack(const T& value);
	void PushBack(T&& value);
	template<typename... Args>
	T& EmplaceBack(Args&&... args);
	void PopBack();
	void Reserve(size_t capacity);
	void Swap(Vector& other);

private:
	void ReAlloc(size_t newCapacity);

public:
	const size_t Capacity() const;
	const size_t Size() const;
	const bool Empty() const;

	T& operator[](size_t index);
	const T& operator[](size_t index) const;

	T& Back();
	const T& Back() const;

	T* Data();
	const T* Data() const;

public:
	Vector();
	~Vector();

	Vector(const Vector& other);
	Vector& operator=(const Vector& other);

	Vector(Vector&& other) noexcept;
	Vector& operator=(Vector&& other) noexcept;
};

template<typename T>
inline void Vector<T>::Cout()
{
	for (size_t i = 0; i < m_Size; ++i)
		std::cout << m_Data[i] << '\n';
	std::cout << "-------\n";
}

template<typename T>
inline void Vector<T>::PushBack(const T& value)
{
	if (m_Size >= m_Capacity)
		ReAlloc(m_Capacity + m_Capacity * 1.5f);

	m_Data[m_Size++] = value;
}

template<typename T>
inline void Vector<T>::PushBack(T&& value)
{
	if (m_Size >= m_Capacity)
		ReAlloc(m_Capacity + static_cast<size_t>(m_Capacity * 1.5f));

	m_Data[m_Size++] = std::move(value);	
}

template<typename T>
inline void Vector<T>::PopBack()
{
#ifdef __VECTOR_DEBUG
	if (m_Size - 1 < 0)
		std::cout << "[ERROR] STATIC VECTOR NEGATIVE INDEX!\n";
#endif // __STATIC_VECTOR_DEBUG

	m_Data[--m_Size].~T();
}

template<typename T>
inline void Vector<T>::Reserve(size_t capacity)
{
	ReAlloc(capacity);
}

template<typename T>
inline void Vector<T>::Swap(Vector& other)
{
	T* temp = m_Data;
	m_Data = other.m_Data;
	other.m_Data = temp;
}

template<typename T>
template<typename ...Args>
inline T& Vector<T>::EmplaceBack(Args && ...args)
{
	if (m_Size >= m_Capacity)
		ReAlloc(m_Capacity + m_Capacity / 2);

	new(&m_Data[m_Size]) T(std::forward<Args>(args)...);
	return m_Data[m_Size++];
}

template<typename T>
inline void Vector<T>::ReAlloc(size_t newCapacity)
{	
#ifdef __VECTOR_DEBUG
	std::cout << "[Vector] Reallocate to " << newCapacity << " elements.\n";
#endif // __VECTOR_DEBUG

	m_Capacity = newCapacity;
	T* block = new T[m_Capacity];

	if (newCapacity < m_Size)
		m_Size = newCapacity;

	for (size_t i = 0; i < m_Size; ++i)
		block[i] = std::move(m_Data[i]);

	delete[] m_Data;
	m_Data = block;
}

template<typename T>
inline const size_t Vector<T>::Capacity() const
{
	return m_Capacity;
}

template<typename T>
inline const size_t Vector<T>::Size() const
{
	return m_Size;
}

template<typename T>
inline const bool Vector<T>::Empty() const
{
	return m_Size == 0;
}

template<typename T>
inline T& Vector<T>::operator[](size_t index)
{
#ifdef __VECTOR_DEBUG
	if (index >= m_Size)
		std::cout << "[ERROR] VECTOR OUT OF BOUNDS!\n";
#endif // __VECTOR_DEBUG
	
	return m_Data[index];
}

template<typename T>
inline const T& Vector<T>::operator[](size_t index) const
{
#ifdef __VECTOR_DEBUG
	if (index >= m_Size)
		std::cout << "[ERROR] VECTOR OUT OF BOUNDS!\n";
#endif // __VECTOR_DEBUG

	return m_Data[index];
}

template<typename T>
inline T& Vector<T>::Back()
{
	return m_Data[m_Size - 1];
}

template<typename T>
inline const T& Vector<T>::Back() const
{
	return m_Data[m_Size - 1];
}

template<typename T>
inline T* Vector<T>::Data()
{
	return m_Data;
}

template<typename T>
inline const T* Vector<T>::Data() const
{
	return m_Data;
}

template<typename T>
inline Vector<T>::Vector()
{
	ReAlloc(2);
}

template<typename T>
inline Vector<T>::~Vector()
{
	delete[] m_Data;
}

template<typename T>
inline Vector<T>::Vector(const Vector& other)
{
#ifdef __VECTOR_DEBUG
	std::cout << "[Vector] Copy Constructor.\n";
#endif // __VECTOR_DEBUG

	delete[] m_Data;
	m_Size = other.m_Size;
	m_Capacity = other.m_Capacity;

	m_Data = new T[m_Capacity];
	for (size_t i = 0; i < m_Size; ++i)
		m_Data[i] = other.m_Data[i];
}

template<typename T>
inline Vector<T>& Vector<T>::operator=(const Vector& other)
{
#ifdef __VECTOR_DEBUG
	std::cout << "[Vector] Copy Operator.\n";
#endif // __VECTOR_DEBUG

	delete[] m_Data;
	m_Size = other.m_Size;
	m_Capacity = other.m_Capacity;

	m_Data = new T[m_Capacity];
	for (size_t i = 0; i < m_Size; ++i)
		m_Data[i] = other.m_Data[i];
	return *this;
}

template<typename T>
inline Vector<T>::Vector(Vector&& other) noexcept
{
#ifdef __VECTOR_DEBUG
	std::cout << "[Vector] Move Constructor.\n";
#endif // __VECTOR_DEBUG

	m_Capacity = other.m_Capacity;
	other.m_Capacity = 0;

	m_Size = other.m_Size;
	other.m_Size = 0;

	delete[] m_Data;
	m_Data = other.m_Data;
	other.m_Data = nullptr;
}

template<typename T>
inline Vector<T>& Vector<T>::operator=(Vector&& other) noexcept
{
#ifdef __VECTOR_DEBUG
	std::cout << "[Vector] Move Operator.\n";
#endif // __VECTOR_DEBUG

	m_Capacity = other.m_Capacity;
	other.m_Capacity = 0;

	m_Size = other.m_Size;
	other.m_Size = 0;

	delete[] m_Data;
	m_Data = other.m_Data;
	other.m_Data = nullptr;
	return *this;
}
