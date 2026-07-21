#pragma once
#include <Components/ObjectComponent.h>
#include <glm/vec2.hpp>


namespace dae {
	class GameObject;
	class TransformComponent;
}

namespace qbert {
	class GridComponent;

	class GridMovementComponent : public dae::ObjectComponent {
	private:
		
		GridComponent* m_pGridComp{}; 
		dae::TransformComponent* m_pTransformComp{};

		glm::ivec2 m_CurrentTile{};
		
		glm::ivec2 m_FromTile{};
		glm::ivec2 m_ToTile{};

		float m_Progress{ 0.f };
		float m_Speed{ 6.f };

		bool m_IsMoving{ false };

	public:
		~GridMovementComponent() = default;
		explicit GridMovementComponent(
			dae::GameObject& owner, 
			dae::TransformComponent* trans = nullptr, 
			GridComponent* grid = nullptr);
	public:
		bool IsMoving();
		void Update() override;

	};
}