#pragma once
#include <filesystem>
#include <string>
#include <memory>
#include <map>
#include "Singleton.h"
#include <nlohmann/json.hpp>

namespace dae
{
	class Texture2D;
	class Font;
	class ResourceManager final
	{
	public:
		void Init(const std::filesystem::path& data);
		std::shared_ptr<Texture2D> LoadTexture(const std::string& file);
		std::shared_ptr<Font> LoadFont(const std::string& file, uint8_t size);
		nlohmann::json LoadMap(const std::string& file);
	private:
		friend class Minigin;
		ResourceManager() = default;
		std::filesystem::path m_dataPath;

		void UnloadUnusedResources();

		std::map<std::string, nlohmann::json>m_loadedJson;
		std::map<std::string, std::shared_ptr<Texture2D>> m_loadedTextures;
		std::map<std::pair<std::string, uint8_t>, std::shared_ptr<Font>> m_loadedFonts;

	};
}
