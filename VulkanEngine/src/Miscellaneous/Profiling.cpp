#include "Profiling.h"

namespace Profiling {

	Timer::Timer()
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}
	Timer::~Timer()
	{
		Stop();
	}

	void Timer::Stop()
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();
		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		auto durationMicroseconds = end - start;
		auto durationMilliseconds = durationMicroseconds * 0.001;
		auto durationSeconds = durationMilliseconds * 0.001;
		float fps = 1 / durationSeconds;

		std::cout << fps << " FPS " << "(" << durationMicroseconds << "us)" <<  " (" << durationMilliseconds << "ms)" << std::endl;
	}
}
