#pragma once

namespace dae 
{
	class ApplicationContext
	{
	public:
		virtual ~ApplicationContext() = default;
	};
	class Application
	{
	public:
		virtual ~Application() = default;

		virtual void Initialize() = 0;
		virtual void ShutDown() = 0;
		virtual ApplicationContext& GetContext() = 0;
	};
}
