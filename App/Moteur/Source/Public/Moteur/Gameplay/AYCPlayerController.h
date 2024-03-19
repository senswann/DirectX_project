#pragma once
#include "Tools/RKeyCodes.h"
#include "Moteur/Interfaces/Listeners/IAYCInputListener.h"

namespace AYCDX {
	class AYCPlayerController : public IAYCInputListener {
		enum class EAction : WPARAM
		{
			Forward = YNOV_KEY_Z,
			Back = YNOV_KEY_S,
			Left = YNOV_KEY_Q,
			Right = YNOV_KEY_D,
			Up = YNOV_KEY_A,
			Down = YNOV_KEY_E
		};
	public:
		void Update(float InDeltaTime);
	protected:
		bool GetIsActiveAction(EAction EInAction) const;
		virtual bool ReceiveKey(bool bIsDown, WPARAM InKey) override;

		inline virtual void OnForwardKey(bool bInIsUp) {};
		inline virtual void OnBackKey(bool bInIsUp) {};
		inline virtual void OLeftKey(bool bInIsUp) {};
		inline virtual void OnRightKey(bool bInIsUp) {};
		inline virtual void OnUpKey(bool bInIsUp) {};
		inline virtual void OnDownKey(bool bInIsUp) {};
	};
}