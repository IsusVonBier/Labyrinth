#pragma once
#include <SDL2/SDL_mixer.h>

class Music
{
	Mix_Music *m_music;

public:
	Music(std::string musicfilepath)
	{
		MIX_INIT_MP3;
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
		{
			std::cout << "Audio library not working: " << Mix_GetError() << "\n";
		}

		m_music = Mix_LoadMUS(musicfilepath.c_str());
	}

	~Music()
	{
		Mix_FreeMusic(m_music);
	}

	// number of times to play the music; 0=0, -1=loop
	void PlayMusic(int32_t loops)
	{
		if (m_music != nullptr)
		{
			Mix_PlayMusic(m_music, loops);
		}
	}

	void PauseMusic()
	{
		Mix_PauseMusic();
	}

	// range 0 - 128
	void SetVolume(int32_t volume)
	{
		Mix_VolumeMusic(volume);
	}
};