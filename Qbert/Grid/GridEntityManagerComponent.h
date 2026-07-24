#pragma once
#include <GameObject.h>
#include <vector>
#include <Components/ObjectComponent.h>
#include "GridEntityComponent.h"

namespace qbert {
	class GridComponent;

	class GridEntityManagerComponent : public dae::ObjectComponent
	{
	private:
		GridComponent* m_pGrid{};
	public:
		virtual ~GridEntityManagerComponent() = default;
		explicit GridEntityManagerComponent(dae::GameObject& owner,GridComponent& grid);

		bool RequestMove(GridEntityComponent* entity , glm::ivec2 direction);
	};
}
