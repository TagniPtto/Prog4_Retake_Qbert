#include "SDLLoggingSoundSystem.h"

#include "../Utils.h"
void dae::SDLLoggingSoundSystem::LoadAudio(const std::string& path, const std::string& name)
{
	LOGLN( "Loading audio : " << path <<"| with name : " << name);
	SDLSoundSystem::LoadAudio(path, name);
}

void dae::SDLLoggingSoundSystem::UnloadAudio(const std::string& name)
{
	LOGLN( "UnLoading audio : " << name);
	SDLSoundSystem::UnloadAudio(name);
}

void dae::SDLLoggingSoundSystem::PlayAudio(const std::string & name, const float volume)
{
	LOGLN( "Playing audio : " << name << " | Volume : " << volume);
	SDLSoundSystem::PlayAudio(name , volume);
}

void dae::SDLLoggingSoundSystem::PlayMusic(const std::string& name, const float volume)
{
	LOGLN( "Playing music : " << name << " | Volume : " << volume);
	SDLSoundSystem::PlayMusic(name, volume);
}
