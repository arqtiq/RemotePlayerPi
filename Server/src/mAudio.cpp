#include "mAudio.h"

mAudio* mAudio::_instance = NULL;

mAudio* mAudio::Instance()
{
    if(!_instance)
        _instance = new mAudio;

    return _instance;
}

bool mAudio::Init()
{
	int r = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
    if(r == -1)
        Logger::Log("Error initializing SDL_Mixer; " + std::string(Mix_GetError()));
    return r == -1 ? false : true;
}

void mAudio::Update()
{ }

void mAudio::Quit()
{
	Mix_Quit();
}

bool mAudio::IsPlaying()
{
	return Mix_PlayingMusic() == 1;
}

bool mAudio::IsPaused()
{
	return Mix_PausedMusic() == 1;
}

void mAudio::Play()
{
	if(IsPaused())
		Mix_ResumeMusic();
	else
		Mix_PlayMusic(song, 1);
}

void mAudio::Pause()
{
    if(IsPlaying())
        Mix_PauseMusic();
}

void mAudio::TogglePlay()
{
	if(IsPlaying())
		Pause();
	else
		Play();
}

void mAudio::Stop()
{
	Mix_HaltMusic();
}

void mAudio::Rewind()
{
	Mix_RewindMusic();
}

void mAudio::LoadSong(std::string path, bool play)
{
	Stop();
	song = Mix_LoadMUS(path.data());
	if (play)
		Play();
}

void mAudio::SetVolume(int percentage)
{
	Mix_VolumeMusic((percentage * MIX_MAX_VOLUME) / 100);
}
