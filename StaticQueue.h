#pragma once
#include <iostream>
//#define __STATIC_QUEUE_DEBUG

template<typename T, size_t maxCapacity>
class StaticQueue
{
private:
	T m_Data[maxCapacity];
	size_t m_First = 0;
	size_t m_Last = 0;

public:
	constexpr const size_t MaxCapacity() const;

	void Push(const T& value);
	void Push(T&& value);
	template<typename... Args>
	void Emplace(Args&&... args);

	T& Front();
	void Pop();
	bool Empty();
	void Cout() const;

	void Print()
	{
		std::cout << "First: " << m_First << "\nLast: " << m_Last << '\n';
		for (size_t i = 0; i < maxCapacity; ++i)
		{
			std::cout << m_Data[i] << '\n';
		}
		std::cout << "\n----------------\n\n";
	}

private:
	bool CheckLast();

public:
	StaticQueue() = default;
	~StaticQueue() = default;
};

template<typename T, size_t maxCapacity>
inline constexpr const size_t StaticQueue<T, maxCapacity>::MaxCapacity() const
{
	return maxCapacity;
}

template<typename T, size_t maxCapacity>
inline void StaticQueue<T, maxCapacity>::Push(const T& value)
{
#ifdef __STATIC_QUEUE_DEBUG
	if (m_Last + 1 >= maxCapacity)
	{
		std::cout << "[ERROR] STATIC QUEUE IS FULL!.\n";
		return;
	}
#endif // __STATIC_QUEUE_DEBUG

	if (!CheckLast()) return;

	m_Data[m_Last++] = value;
}

template<typename T, size_t maxCapacity>
inline void StaticQueue<T, maxCapacity>::Push(T&& value)
{
#ifdef __STATIC_QUEUE_DEBUG
	if (m_Last + 1 >= maxCapacity)
	{
		std::cout << "[ERROR] STATIC QUEUE IS FULL!.\n";
		return;
	}
#endif // __STATIC_QUEUE_DEBUG

	if (!CheckLast()) return;

	m_Data[m_Last++] = std::move(value);
}

template<typename T, size_t maxCapacity>
inline T& StaticQueue<T, maxCapacity>::Front()
{
	return m_Data[m_First];
}

template<typename T, size_t maxCapacity>
inline void StaticQueue<T, maxCapacity>::Pop()
{
	if (!Empty())
	{
		m_Data[m_First].~T();

		m_First++;

		if (m_First >= maxCapacity)
		{
			if (m_Last > 0 && m_Last < maxCapacity)
				m_First = 0;
			else
			{
				m_First = 0;
				m_Last = 0;
			}
		}
	}
	else
	{
		m_First = 0;
		m_Last = 0;
	}
}

template<typename T, size_t maxCapacity>
inline bool StaticQueue<T, maxCapacity>::Empty()
{
	return m_First == m_Last;
}

template<typename T, size_t maxCapacity>
inline void StaticQueue<T, maxCapacity>::Cout() const
{
	for (size_t i = m_First; i < m_Last; ++i)
	{
		std::cout << m_Data[i] << '\n';
	}
}

template<typename T, size_t maxCapacity>
inline bool StaticQueue<T, maxCapacity>::CheckLast()
{
	if (Empty())
	{
		m_First = 0;
		m_Last = 0;
		return true;
	}

	if (m_Last + 1 > maxCapacity)
	{
		if (m_First > 0)
		{
			m_Last = 0;
			return true;
		}
		else
		{
			std::cout << "[ERROR] STATIC QUEUE IS FULL!.\n";
			return false;
		}
	}
	return true;
}

template<typename T, size_t maxCapacity>
template<typename ...Args>
inline void StaticQueue<T, maxCapacity>::Emplace(Args && ...args)
{
#ifdef __STATIC_QUEUE_DEBUG
	if (m_Last + 1 >= maxCapacity)
	{
		std::cout << "[ERROR] STATIC QUEUE IS FULL!.\n";
		return;
	}
#endif // __STATIC_QUEUE_DEBUG

	if (!CheckLast()) return;

	new(&m_Data[m_Last]) T(std::forward<Args>(args)...);
	m_Last++;
}
