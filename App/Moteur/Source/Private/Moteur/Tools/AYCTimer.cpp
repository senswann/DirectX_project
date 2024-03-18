#include "Moteur/Tools/AYCTimer.h"

#if _DEBUG
#include <cassert>
#endif
#include<thread>
#include<chrono>

void AYCDX::AYCTimer::Init()
{
	static bool assertPerformance = false;
#if _DEBUG
	static bool assertedPerformance = false;
	assert(TRUE == QueryPerformanceFrequency(&pm_frequency));
#endif
	QueryPerformanceFrequency(&pm_frequency);

	QueryPerformanceCounter(&pm_startTime);

	//init time last 0 tick
	pm_previousTime = pm_startTime;
	pm_currentTime = pm_previousTime;
}

double AYCDX::AYCTimer::BeginNewFrame()
{
	//get old and new time
	pm_previousTime = pm_currentTime;
	QueryPerformanceCounter(&pm_currentTime);

	//Update DeltaTime and Elpased

	pm_LastElapsedTicks.QuadPart = pm_currentTime.QuadPart - pm_previousTime.QuadPart;
	pm_totalElapsedTicks.QuadPart = pm_currentTime.QuadPart - pm_startTime.QuadPart;

	m_lastCpuDeltaSecond = ComputeSecondTimeFromEapsedTicks(pm_LastElapsedTicks);
	m_fromStartCpuSecond = ComputeSecondTimeFromEapsedTicks(pm_totalElapsedTicks);

	return m_lastCpuDeltaSecond;
}

void AYCDX::AYCTimer::SleepMilliseconds(unsigned int nbMilliseconds)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(nbMilliseconds));
}
