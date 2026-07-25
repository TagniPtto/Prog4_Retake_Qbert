#pragma once
#include <Components/ObjectComponent.h>
#include <Components/TransformComponent.h>
#include <glm/vec2.hpp>

#include <EventSystem/EventDispatcher.h>
#include "GridEvents.h"


namespace dae {
	class GameObject;
	class TransformComponent;
}

namespace qbert {
	class GridComponent;

	class GridMovementComponent : public dae::ObjectComponent {
	
	public:
		dae::EventDispatcher<MoveEvent> OnMoveEntered;
		dae::EventDispatcher<MoveEvent> OnMoveExited;
	public:
		virtual ~GridMovementComponent() = default;
		explicit GridMovementComponent(dae::GameObject& owner, GridComponent& grid);
	public:
		bool IsMoving()const;

		void Start() override;
		void Update() override;

		void SetCurrentTileIndex(glm::ivec2 pos);
		glm::ivec2 GetCurrentTileIndex() const;
		void MoveBetweenTiles(glm::ivec2 t1, glm::ivec2 t2);

	private:
		void SetPositionWithVisualOffset(glm::vec3 tilePosition);
		glm::vec3 InterpolatePosition(glm::vec3 p1, glm::vec3 p2, float t);

	private:
		GridComponent* m_pGrid{};
		dae::TransformComponent* m_pTransform;
		glm::ivec2 m_CurrentTile{};
	private:
		glm::ivec2 m_FromTile{};
		glm::ivec2 m_ToTile{};
		float m_Progress{ 0.f };
		float m_Speed{ 3.f };
		bool m_IsMoving{ false };

	};
}