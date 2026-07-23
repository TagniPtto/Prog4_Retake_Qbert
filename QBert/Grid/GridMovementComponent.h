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
		
		GridComponent* m_pGrid{}; 
		glm::ivec2 m_CurrentTile{};
	private:
		glm::ivec2 m_FromTile{};
		glm::ivec2 m_ToTile{};
		float m_Progress{ 0.f };
		float m_Speed{ 6.f };
		bool m_IsMoving{ false };

	public:
		virtual ~GridMovementComponent() = default;
		explicit GridMovementComponent(dae::GameObject& owner, GridComponent& grid);
	public:
		bool IsMoving()const;
		void Update() override;
		void SetToTile(glm::ivec2 pos);
	private:
		glm::vec2 InterpolatePosition(glm::vec2 p1, glm::vec2 p2 , float t);
	};
}