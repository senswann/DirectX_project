#pragma once
#include "Moteur/pch.h"
#include "Tools/Singelton.h"


namespace AYCDX {
	class AYCTimer : public  Tools::Singelton<AYCTimer> {
	private:
		double m_lastCpuDeltaSecond;
		double m_fromStartCpuSecond;

		LARGE_INTEGER pm_frequency;

		LARGE_INTEGER pm_startTime;
		LARGE_INTEGER pm_previousTime;
		LARGE_INTEGER pm_currentTime;

		LARGE_INTEGER pm_LastElapsedTicks;
		LARGE_INTEGER pm_totalElapsedTicks;

		inline double ComputeSecondTimeFromEapsedTicks(const LARGE_INTEGER& InNbElapsedTick) {
			return (static_cast<double>(InNbElapsedTick.QuadPart) / pm_frequency.QuadPart);
		}

	public:
		//Init timer
		
		void Init();

		//Update
		double BeginNewFrame();

		static void SleepMilliseconds(unsigned int nbMilliseconds);

		inline double GetLastTick() const { return m_lastCpuDeltaSecond; };
		inline double GetFormStartSeconds() const { return m_fromStartCpuSecond; };
	};
}