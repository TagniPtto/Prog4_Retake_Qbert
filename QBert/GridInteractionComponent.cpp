#include "GridInteractionComponent.h"
#include "GridComponent.h"

#include <ServiceLocator.h>
#include <SceneSystem/SceneManager.h>
#include <SceneSystem/Scene.h>

qbert::GridInteractionComponent::GridInteractionComponent(dae::GameObject& owner):
	dae::ObjectComponent(owner)
{
    dae::Scene* scene = dae::ServiceLocator<dae::SceneManager>::Get().GetActiveScene();
    if (!m_pGridComp) {
        m_pGridComp = scene->FindComponent<qbert::GridComponent>();
    }
}

void qbert::GridInteractionComponent::Deserialize(const nlohmann::json &)
{}

void qbert::GridInteractionComponent::Serialize(nlohmann::json&) const
{}

void qbert::GridInteractionComponent::RequestPush(glm::ivec2)
{}
