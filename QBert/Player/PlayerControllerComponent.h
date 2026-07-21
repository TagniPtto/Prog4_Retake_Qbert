#pragma once
#include "Components/ObjectComponent.h"

#include <glm/glm.hpp>


namespace qbert {

	class GameObject;
	
	class PlayerControllerComponent : public dae::ObjectComponent {

	public:
		explicit PlayerControllerComponent(dae::GameObject& pawn);
		virtual ~PlayerControllerComponent() = default;

		virtual void Move(glm::vec2 direction);
	};
}
