#pragma once
#include <wtypes.h>
#include <unordered_set>

namespace AYCDX{
	class IAYCInputListener {
	protected:
		std::unordered_set<WPARAM> m_currentlyHeldKeys;
	public:
		virtual bool ReceiveKey(bool bIsDown, WPARAM InKey);
	};
}