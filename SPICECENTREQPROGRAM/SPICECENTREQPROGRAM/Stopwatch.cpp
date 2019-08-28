#include "Stopwatch.h"



Stopwatch::Stopwatch() noexcept
	: m_running{ false }
	, m_start{ 0 }
	, m_finish{ 0 }
	, m_frequency{ Frequency() }
{}


void Stopwatch::Reset() noexcept
{
	m_finish = m_start = 0;
	m_running = false;
}


void Stopwatch::Start() noexcept
{
	m_running = true;
	m_finish = 0;

	m_start = Counter();
}


void Stopwatch::Stop() noexcept
{
	m_finish = Counter();
	m_running = false;
}

#include <crtdbg.h>     // For _ASSERTE
#include <Windows.h>   

double Stopwatch::ElapsedMilliseconds() const noexcept
{
	if (m_running)
	{
		const long long current{ Counter() };
		return ElapsedMilliseconds(m_start, current);
	}

	return ElapsedMilliseconds(m_start, m_finish);
}


long long Stopwatch::Counter() noexcept
{
	LARGE_INTEGER li;
	::QueryPerformanceCounter(&li);
	return li.QuadPart;
}


long long Stopwatch::Frequency() noexcept
{
	LARGE_INTEGER li;
	::QueryPerformanceFrequency(&li);
	return li.QuadPart;
}


double Stopwatch::ElapsedMilliseconds(long long start, long long finish) const noexcept
{
	_ASSERTE(start >= 0);
	_ASSERTE(finish >= 0);
	_ASSERTE(start <= finish);

	return ((finish - start) * 1000.0) / m_frequency;
}