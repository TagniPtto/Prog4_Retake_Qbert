#pragma once
#include <string>
#include <functional>
#include <filesystem>
#include "Application.h"

namespace dae
{
	class ISoundSystem;
	class ResourceManager;
	class SceneManager;
	class InputManager;
	class Renderer;


	class Minigin final
	{
		std::unique_ptr<ResourceManager>	m_pResourceManager;
		std::unique_ptr<SceneManager>		m_pSceneManager;
		std::unique_ptr<InputManager>		m_pInputManager;
		std::unique_ptr<ISoundSystem>		m_pSoundSystem;
		std::unique_ptr<Renderer>			m_pRenderer;

		std::unique_ptr<Application> m_pApplication;

		bool m_quit{};
	public:
		explicit Minigin(const std::filesystem::path& dataPath);
		~Minigin();
		void Run(std::unique_ptr<Application> application);
		void RunOneFrame();

		Minigin(const Minigin& other) = delete;
		Minigin(Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) = delete;
	};
}