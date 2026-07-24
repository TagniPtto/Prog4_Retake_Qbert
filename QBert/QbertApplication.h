#pragma once

#include <Application.h>
#include <EventSystem/EventDispatcher.h>

namespace qbert
{
	class QbertApplicationContext : public dae::ApplicationContext
	{
	public:
		//TODO Make actual event
		dae::EventDispatcher<int> OnPlayerDeath{};
		dae::EventDispatcher<int> OnEnemyDeath{};

	};
	class QbertApplication : public dae::Application
	{
	private:
		QbertApplicationContext m_context;
	public:

		void Initialize() override;

		void ShutDown() override;

		dae::ApplicationContext & GetContext() override;

	};
}