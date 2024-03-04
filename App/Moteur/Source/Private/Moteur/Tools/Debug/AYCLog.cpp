#include "Moteur/Tools/Debug/AYCLog.h"
#include <system_error>
#include<iostream>

static const std::string ESERVITY_DISPLAY = TEXT("Display");
static const std::string ESERVITY_WARNING = TEXT("Warning");
static const std::string ESERVITY_ERROR = TEXT("Error");
static const std::string ESERVITY_EXCEPTION = TEXT("Exception");
static const std::string ESERVITY_UNKNOWN = TEXT("Unknown");

using std::cout, std::endl;

void AYCDX::AYCLog::Log(ESeverity EInSeverity,const std::string_view InDisplayError) {
	cout << "[ " << ToString(EInSeverity) << " ] : " << InDisplayError << endl;
}
void AYCDX::AYCLog::Log(ESeverity EInSeverity, const std::string_view InDisplayError, HRESULT result) {
	std::string hError = std::system_category().message(result);
	cout << "[ " << ToString(EInSeverity) << " ] : " << InDisplayError << "'with error code '" << hError << endl;
}
void AYCDX::AYCLog::Log(ESeverity EInSeverity, HRESULT result) {
	std::string hError = std::system_category().message(result);
	cout << "[ " << ToString(EInSeverity) << " ] : " << "'with error code '" << hError << endl;
}

const std::string& AYCDX::ToString(AYCLog::ESeverity EInSeverity) {
	switch (EInSeverity)
	{
		case AYCDX::AYCLog::ESeverity::Display:
			return ESERVITY_DISPLAY;
		case AYCDX::AYCLog::ESeverity::Warning:
			return ESERVITY_WARNING;
		case AYCDX::AYCLog::ESeverity::Error:
			return ESERVITY_ERROR;
		case AYCDX::AYCLog::ESeverity::Exception:
			return ESERVITY_EXCEPTION;
	default:
		cout << "[UnimpException] Case not handled in switch of type 'AYCLog::EServity' in AYCLog" << endl;
		return ESERVITY_UNKNOWN;
	}
}