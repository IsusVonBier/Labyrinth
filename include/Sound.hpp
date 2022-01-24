#pragma once
#include <SDL2/SDL_mixer.h>

class Sound
{
	Mix_Chunk *m_sound;

public:
	Sound(std::string soundfilepath)
	{
		MIX_INIT_MP3;
		if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
		{
			std::cout << "Audio library not working: " << Mix_GetError() << "\n";
		}
		m_sound = Mix_LoadWAV(soundfilepath.c_str());
		Mix_VolumeChunk(m_sound, 40);
	}

	~Sound()
	{
		Mix_FreeChunk(m_sound);
	}

	// number of times to play the music; 0=0, -1=loop
	void PlaySound()
	{
		if (m_sound != nullptr)
		{
			Mix_PlayChannel(-1, m_sound, 0);
		}
	}

	// // range 0 - 128
	void SetVolume(int32_t volume)
	{
		Mix_VolumeChunk(m_sound, volume);
	}
};