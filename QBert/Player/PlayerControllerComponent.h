#pragma once
#include "Components/ObjectComponent.h"
#include "PlayerState.h"

#include <glm/glm.hpp>


namespace qbert {

	class GameObject;
	class GridEntityComponent;
	
	class PlayerControllerComponent : public dae::ObjectComponent 
	{
	private:

	private:
		std::unique_ptr<IPlayerState> m_pCurrentState;
		GridEntityComponent* m_pEntityComponent;

	public:
		explicit PlayerControllerComponent(dae::GameObject& pawn);
		virtual ~PlayerControllerComponent() = default;

		virtual void Move(glm::vec2 direction);
	private:
		void ChangeState(std::unique_ptr<IPlayerState> newState);
	public:
		void HandleRequest();
		void Update() override;
		void Start() override;
	};
}
