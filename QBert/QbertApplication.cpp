#include "QbertApplication.h"

#include <ServiceLocator.h>
#include <SceneSystem/SceneManager.h>
#include "Scenes/Scene01.h"


void qbert::QbertApplication::Initialize()
{

	auto& sceneManager = dae::ServiceLocator<dae::SceneManager>::Get();
	sceneManager.AddScene(std::make_unique<qbert::Scene01>());
	sceneManager.LoadScene(0);

}

void qbert::QbertApplication::ShutDown()
{}

dae::ApplicationContext& qbert::QbertApplication::GetContext()
{
	return m_context;
}
