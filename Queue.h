#pragma once
#include "LinkedList.h"
#define __QUEUE_DEBUG

template<typename T>
class Queue
{
private:
	LinkedList<T> m_Data;

public:
	void Push(const T& value);
	void Push(T&& value);
	template<typename... Args>
	void Emplace(Args&&... args);

	T& Front();
	void Pop();
	bool Empty();
	void Cout();

public:
	Queue() = default;
	~Queue() = default;

	Queue(const Queue& other);
	Queue& operator=(const Queue& other);

	Queue(Queue&& other) noexcept;
	Queue& operator=(Queue&& other) noexcept;
};

template<typename T>
inline void Queue<T>::Push(const T& value)
{
	m_Data.PushBack(value);
}

template<typename T>
inline void Queue<T>::Push(T&& value)
{
	m_Data.PushBack(std::move(value));
}

template<typename T>
inline T& Queue<T>::Front()
{
	return *m_Data.Front();
}

template<typename T>
inline void Queue<T>::Pop()
{
	m_Data.PopFront();
}

template<typename T>
inline bool Queue<T>::Empty()
{
	return m_Data.Empty();
}

template<typename T>
inline void Queue<T>::Cout()
{
	m_Data.Cout();
}

template<typename T>
inline Queue<T>::Queue(const Queue& other)
{
#ifdef __QUEUE_DEBUG
	std::cout << "[Queue] Copy Constructor.\n";
#endif // __QUEUE_DEBUG

	this->m_Data = other.m_Data;
}

template<typename T>
inline Queue<T>& Queue<T>::operator=(const Queue& other)
{
#ifdef __QUEUE_DEBUG
	std::cout << "[Queue] Copy Operator.\n";
#endif // __QUEUE_DEBUG

	this->m_Data = other.m_Data;

	return *this;
}

template<typename T>
inline Queue<T>::Queue(Queue&& other) noexcept
{
#ifdef __QUEUE_DEBUG
	std::cout << "[Queue] Move Constructor.\n";
#endif // __QUEUE_DEBUG

	this->m_Data = std::move(other.m_Data);
}

template<typename T>
inline Queue<T>& Queue<T>::operator=(Queue&& other) noexcept
{
#ifdef __QUEUE_DEBUG
	std::cout << "[Queue] Move Operator.\n";
#endif // __QUEUE_DEBUG

	this->m_Data = std::move(other.m_Data);
	return *this;
}

template<typename T>
template<typename ...Args>
inline void Queue<T>::Emplace(Args && ...args)
{
	m_Data.EmplaceBack(std::forward<Args>(args)...);
}
