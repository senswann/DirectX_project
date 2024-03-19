#include "Moteur/Interfaces/Listeners/IAYCInputListener.h"

bool AYCDX::IAYCInputListener::ReceiveKey(bool bIsDown, WPARAM InKey)
{
	if (bIsDown) {
		if (!m_currentlyHeldKeys.contains(InKey)) {
			m_currentlyHeldKeys.emplace(InKey);
		}
	}
	else {
		if (m_currentlyHeldKeys.contains(InKey)) {
			m_currentlyHeldKeys.erase(InKey);
		}
	}
	return true;
}
