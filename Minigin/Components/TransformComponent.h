#pragma once
#include <glm/glm.hpp>
#include "ObjectComponent.h"

namespace dae
{
	class TransformComponent final : public ObjectComponent
	{
	public:
		explicit TransformComponent(dae::GameObject& owner);
		void SetLocalPosition(float x, float y, float z = 0);
		void SetLocalPosition(glm::vec3 position);
		glm::vec3 GetLocalPosition() const;
		glm::vec3 GetWorldPosition() const;

		void SetLocalRotation(float newRotation);
		float GetLocalRotation()const;
		float GetWorldRotation()const;

		void Rotate(float rotation);
		void Translate(glm::vec3 offset);

		void SetTransformDirty();
		void UpdateWorldTransform() const;
	private:
		mutable bool m_transformDirty{ false };

		glm::vec3 m_localPosition{};
		mutable glm::vec3 m_worldPosition{};
		float m_localRotation{};
		mutable float m_worldRotation{};
	};
}
