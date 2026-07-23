#pragma once
#include "Components/ObjectComponent.h"
#include "PlayerState.h"

#include <glm/glm.hpp>


namespace qbert {

	class GameObject;
	class GridMovementComponent;
	class GridInteractionComponent;
	
	class PlayerControllerComponent : public dae::ObjectComponent 
	{
	private:
		std::unique_ptr<IPlayerState> m_pCurrentState;
		GridMovementComponent* m_pMovementComponent;
		GridInteractionComponent* m_pInteractionComponent;

	public:
		explicit PlayerControllerComponent(dae::GameObject& pawn);
		virtual ~PlayerControllerComponent() = default;

		virtual void Move(glm::vec2 direction);
	private:
		void ChangeState(std::unique_ptr<IPlayerState> newState);
	public:
		void HandleRequest();
		void Update() override;
	};
}
