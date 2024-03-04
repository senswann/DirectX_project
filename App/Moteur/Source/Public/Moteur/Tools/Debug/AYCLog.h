#pragma once
#include "Moteur/pch.h"

#include <string_view>

namespace AYCDX {
	class AYCLog {
	public:
		enum class ESeverity : UINT8
		{
			Display = 0,
			Warning = 1,
			Error = 2,
			Exception = 3
		};
	public:
		static void Log(ESeverity EInSeverity, const std::string_view InDisplayError);
		static void Log(ESeverity EInSeverity, const std::string_view InDisplayError, HRESULT result);
		static void Log(ESeverity EInSeverity, HRESULT result);
	};

	constexpr AYCLog::ESeverity LOG_DISPLAY = AYCLog::ESeverity::Display;
	constexpr AYCLog::ESeverity LOG_WARNING = AYCLog::ESeverity::Warning;
	constexpr AYCLog::ESeverity LOG_ERROR = AYCLog::ESeverity::Error;
	constexpr AYCLog::ESeverity LOG_EXCEPTION = AYCLog::ESeverity::Exception;

	const std::string& ToString(AYCLog::ESeverity EInSeverity);
}