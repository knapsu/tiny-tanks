#ifndef _AUDIO_HPP_
#include "Audio.hpp"
#endif



CMusic::CMusic(void)
{
    music = 0;
}


/*CMusic::~CMusic(void)
{
}*/



int CMusic::Load(std::string file_name)
{
	Mix_FreeMusic(music);
    music = Mix_LoadMUS(file_name.c_str());
    if (music == 0)
    {
		std::cerr << "Error: " << Mix_GetError() << std::endl;
		return -1;
	}
	
	return 0;
}


void CMusic::Play(void)
{
    Mix_PlayMusic(music, -1);
}


void CMusic::Pause(void)
{
    Mix_PauseMusic();
}


void CMusic::Resume(void)
{
    Mix_ResumeMusic();
}


void CMusic::Toggle(void)
{
	if (Mix_PlayingMusic() == 0)
	{
		Play();
	}
	else
	{
		Stop();
	}
}


void CMusic::Stop(void)
{
    Mix_HaltMusic();
}


