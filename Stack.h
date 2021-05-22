#pragma once
#include "LinkedList.h"
#define __STACK_DEBUG

template<typename T>
class Stack
{
private:
	LinkedList<T> m_Data;

public:
	void Push(const T& value);
	void Push(T&& value);
	template<typename... Args>
	void Emplace(Args&&... args);

	T& Top();
	void Pop();
	bool Empty();
	void Cout();

public:
	Stack() = default;
	~Stack() = default;

	Stack(const Stack& other);
	Stack& operator=(const Stack& other);

	Stack(Stack&& other) noexcept;
	Stack& operator=(Stack&& other) noexcept;
};

template<typename T>
inline void Stack<T>::Push(const T& value)
{
	m_Data.PushFront(value);
}

template<typename T>
inline void Stack<T>::Push(T&& value)
{
	m_Data.PushFront(std::move(value));
}

template<typename T>
inline T& Stack<T>::Top()
{
	return *m_Data.Front();
}

template<typename T>
inline void Stack<T>::Pop()
{
	m_Data.PopFront();
}

template<typename T>
inline bool Stack<T>::Empty()
{
	return m_Data.Empty();
}

template<typename T>
inline void Stack<T>::Cout()
{
	m_Data.Cout();
}

template<typename T>
inline Stack<T>::Stack(const Stack& other)
{
#ifdef __STACK_DEBUG
	std::cout << "[Stack] Copy constructor.\n";
#endif // __STACK_DEBUG

	this->m_Data = other.m_Data;
}

template<typename T>
inline Stack<T>& Stack<T>::operator=(const Stack& other)
{
#ifdef __STACK_DEBUG
	std::cout << "[Stack] Copy Operator.\n";
#endif // __STACK_DEBUG

	this->m_Data = other.m_Data;

	return *this;
}

template<typename T>
inline Stack<T>::Stack(Stack&& other) noexcept
{
#ifdef __STACK_DEBUG
	std::cout << "[Stack] Move Constructor.\n";
#endif // __STACK_DEBUG

	this->m_Data = std::move(other.m_Data);
}

template<typename T>
inline Stack<T>& Stack<T>::operator=(Stack&& other) noexcept
{
#ifdef __STACK_DEBUG
	std::cout << "[Stack] Move Operator.\n";
#endif // __STACK_DEBUG

	this->m_Data = std::move(other.m_Data);

	return *this;
}

template<typename T>
template<typename ...Args>
inline void Stack<T>::Emplace(Args && ...args)
{
	m_Data.EmplaceFront(std::forward<Args>(args)...);
}
