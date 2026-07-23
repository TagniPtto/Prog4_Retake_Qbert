#pragma once

#include <Components/ObjectComponent.h>
#include <glm/vec2.hpp>

namespace qbert {
	class GridComponent;

	class GridInteractionComponent : public dae::ObjectComponent {
	private:
		GridComponent* m_pGridComp{};
	public:
		virtual ~GridInteractionComponent() = default;
		explicit GridInteractionComponent(dae::GameObject& owner);

		void RequestPush(glm::ivec2 direction);

	};
}
