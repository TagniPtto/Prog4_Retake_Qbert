#pragma once

#include <Components/ObjectComponent.h>
#include <glm/vec2.hpp>
#include "GridEvents.h"
#include "GridEntityComponent.h"

namespace qbert 
{
	class GridComponent;

	class GridInteractionComponent : public dae::ObjectComponent 
	{
	private:
		GridEntityComponent* m_pEntityComponent;
	public:
		virtual ~GridInteractionComponent() = default;
		explicit GridInteractionComponent(dae::GameObject& owner);
		void Start() override;
	private:
		void OnMoveEnter(const MoveEvent& event);
		void OnMoveExit(const MoveEvent& event);

		void OnOverlapEnter(const OverlapEvent& event);
		void OnOverlapExit(const OverlapEvent& event);
	};
}
