#pragma once
#include "Components/ObjectComponent.h"


namespace qbert {

	class GameObject;
	
	class PlayerControllerComponent : public dae::ObjectComponent {

	public:
		explicit PlayerControllerComponent(dae::GameObject& pawn);
		virtual ~PlayerControllerComponent() = default;
	};
}
