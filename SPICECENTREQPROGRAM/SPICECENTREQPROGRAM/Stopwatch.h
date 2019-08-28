#pragma once
class Stopwatch
{
public:
	// Initialize the stopwatch to a safe initial state
	Stopwatch() noexcept;

	// Clear the stopwatch state
	void Reset() noexcept;

	// Start measuring time.
	// When finished, call Stop().
	// Can call ElapsedTime() also before calling Stop(): in this case,
	// the elapsed time is measured since the Start() call.
	void Start() noexcept;

	// Stop measuring time.
	// Call ElapsedMilliseconds() to get the elapsed time from the Start() call.
	void Stop() noexcept;

	// Return elapsed time interval duration, in milliseconds.
	// Can be called both after Stop() and before it. 
	// (Start() must have been called to initiate time interval measurements).
	double ElapsedMilliseconds() const noexcept;


	//
	// Ban copy
	//
private:
	Stopwatch(const Stopwatch&) = delete;
	Stopwatch& operator=(const Stopwatch&) = delete;


	//
	// *** IMPLEMENTATION ***
	//
private:
	bool m_running;                 // is the timer running?
	long long m_start;              // start tick count
	long long m_finish;             // end tick count
	const long long m_frequency;    // cached frequency value

									// Wrapper to Win32 API QueryPerformanceCounter()
	static long long Counter() noexcept;

	// Wrapper to Win32 API QueryPerformanceFrequency()
	static long long Frequency() noexcept;

	// Calculate elapsed time in milliseconds,
	// given a start tick and end tick counts.
	double ElapsedMilliseconds(long long start, long long finish) const noexcept;
};