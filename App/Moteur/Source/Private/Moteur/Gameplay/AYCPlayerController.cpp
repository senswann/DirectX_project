#include "Moteur/Gameplay/AYCPlayerController.h"

void AYCDX::AYCPlayerController::Update(float InDeltaTime)
{
	if (GetIsActiveAction(EAction::Forward)) {

	}
}

bool AYCDX::AYCPlayerController::GetIsActiveAction(EAction EInAction) const
{
	return this->m_currentlyHeldKeys.contains((WPARAM)EInAction);
}

bool AYCDX::AYCPlayerController::ReceiveKey(bool bIsDown, WPARAM InKey)
{
	bool bPassthrough = IAYCInputListener::ReceiveKey(bIsDown, InKey);

	switch (InKey)
	{
	case (WPARAM)EAction::Forward:
		OnForwardKey(bIsDown);
		break;
	case (WPARAM)EAction::Back:
		OnBackKey(bIsDown);
		break;
	case (WPARAM)EAction::Left:
		OLeftKey(bIsDown);
		break;
	case (WPARAM)EAction::Right:
		OnRightKey(bIsDown);
		break;
	case (WPARAM)EAction::Up:
		OnUpKey(bIsDown);
		break;
	case (WPARAM)EAction::Down:
		OnDownKey(bIsDown);
		break;
	default:
		break;
	}

	return bPassthrough;
}
