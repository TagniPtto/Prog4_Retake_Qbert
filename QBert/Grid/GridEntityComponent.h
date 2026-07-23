#pragma once
#include <Components/ObjectComponent.h>
#include <glm/vec2.hpp>

namespace qbert 
{
	class GridEntityManagerComponent;
	class GridMovementComponent;
	class GridInteractionComponent;

	class GridEntityComponent : public dae::ObjectComponent 
	{
	private:
		GridEntityManagerComponent* m_pManager;
		GridMovementComponent* m_pMovement;
		GridInteractionComponent* m_pInteration;
	private:
		int m_index;
	public:
		virtual ~GridEntityComponent() = default;
		explicit GridEntityComponent(dae::GameObject& owner, GridEntityManagerComponent& manager,int index);
		int GetIndex();

		bool RequestMove(glm::ivec2 direction);
	};
}