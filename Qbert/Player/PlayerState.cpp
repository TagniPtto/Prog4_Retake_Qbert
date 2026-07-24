#include "PlayerState.h"

#include "ServiceLocator.h"
#include "PlayerControllerComponent.h"
#include <SoundSystem/ISoundSystem.h>
#include <Components/AnimationComponent.h>
#include "../Events/QbertEvents.h"


namespace qbert 
{
	void IPlayerState::OnEnter(PlayerControllerComponent&)
	{}
	void IPlayerState::OnExit(PlayerControllerComponent&)
	{}
	std::unique_ptr<IPlayerState> IPlayerState::Update(PlayerControllerComponent&)
	{
		return nullptr;
	}


	void IdleState::OnEnter(PlayerControllerComponent&)
	{
	}


	std::unique_ptr<IPlayerState> IdleState::HandleRequest(PlayerControllerComponent&)
	{

	}


	void MoveState::OnEnter(PlayerControllerComponent&)
	{

	}
	
	std::unique_ptr<IPlayerState> MoveState::Update(PlayerControllerComponent&)
	{
		return nullptr;
	}

	std::unique_ptr<IPlayerState> MoveState::HandleRequest(PlayerControllerComponent&)
	{
		return nullptr;
	}


	void DeadState::OnEnter(PlayerControllerComponent&)
	{
	}

	std::unique_ptr<IPlayerState> DeadState::HandleRequest(PlayerControllerComponent& controller)
	{
		//controller.NotifyObservers();
		return nullptr;
	}
}