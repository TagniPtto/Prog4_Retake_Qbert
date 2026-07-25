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
		std::vector<GridEntityComponent*> m_pEntities;
	public:
		virtual ~GridEntityManagerComponent() = default;
		explicit GridEntityManagerComponent(dae::GameObject& owner,GridComponent& grid);

		std::vector<GridEntityComponent*> GetEntitiesAt(glm::ivec2 index) const;

		GridComponent* GetGridComponent() const;
		void RegisterEntity(GridEntityComponent* entity);
		bool RequestMove(GridEntityComponent* entity , glm::ivec2 direction);

	};
}
