#include "PlayerState.h"
#include "PlayerStateComponent.h"

#include "PlayerCommands.h"


#include "ServiceLocator.h"
#include <SoundSystem/ISoundSystem.h>
#include <Components/AnimationComponent.h>
#include "../GridMovementComponent.h"
#include "../GridInteractionComponent.h"


namespace qbert 
{
	void PlayerState::OnEnter(PlayerStateComponent& )
	{}
	void PlayerState::OnExit(PlayerStateComponent& )
	{}
	std::unique_ptr<PlayerState> PlayerState::Update(PlayerStateComponent&)
	{
		return nullptr;
	}


	void IdleState::OnEnter(PlayerStateComponent& stateComponent)
	{
		stateComponent.GetAnimationComponent()->PauseCurrentAnimation();
	}


	std::unique_ptr<PlayerState> IdleState::HandleRequest(
		PlayerStateComponent&,
		PlayerStateChange change)
	{

		if (change == PlayerStateChange::MoveUp||
			change == PlayerStateChange::MoveDown || 
			change == PlayerStateChange::MoveLeft || 
			change == PlayerStateChange::MoveRight ) {
			return std::make_unique<MoveState>(change);
		}
		if (change == PlayerStateChange::Death) {
			return std::make_unique<DeadState>();
		}
		return nullptr;
	}



	MoveState::MoveState(PlayerStateChange)
	{}

	void MoveState::OnEnter(PlayerStateComponent&)
	{

	}
	
	std::unique_ptr<PlayerState> MoveState::Update(PlayerStateComponent& stateComp)
	{
		if (!stateComp.GetGridMovementComponent()->IsMoving()) {
			return std::make_unique<IdleState>();
		}
		return nullptr;
	}

	std::unique_ptr<PlayerState> MoveState::HandleRequest(
		PlayerStateComponent&,
		PlayerStateChange change)
	{
		if (change == PlayerStateChange::Death) {
			return std::make_unique<DeadState>();
		}
		return nullptr;
	}



	void PushState::OnEnter(PlayerStateComponent& stateComponent)
	{
		dae::ServiceLocator<dae::ISoundSystem>::Get().LoadAudio("Data/SFX/Push_Ice_Block.mp3", "PushIce");
		stateComponent.GetGridInterationComponent()->RequestPush(glm::ivec2{});
	}

	std::unique_ptr<PlayerState> PushState::HandleRequest(PlayerStateComponent&, PlayerStateChange change)
	{
		if (change == PlayerStateChange::Death) {
			return std::unique_ptr<DeadState>();
		}
		return nullptr;
	}

	void DeadState::OnEnter(PlayerStateComponent& stateComponent)
	{
		stateComponent.GetAnimationComponent()->PlayAnimation("Death");
	}

	std::unique_ptr<PlayerState> DeadState::HandleRequest(
		PlayerStateComponent& , 
		PlayerStateChange)
	{
		return nullptr;
	}
}