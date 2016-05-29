#include "mAudio.h"

mAudio* mAudio::_instance = NULL;

mAudio* mAudio::Instance()
{
    if(!_instance)
        _instance = new mAudio;

    return _instance;
}

void mAudio::Update()
{
    //RemotePlayer::Instance()->logger.Log(IsPlaying());
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
		Mix_PlayMusic(song, -1);
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

void mAudio::LoadSong(std::string path)
{
	Pause();
	song = Mix_LoadMUS(path.c_str());
	Play();
}

void mAudio::SetVolume(int percentage)
{
	Mix_VolumeMusic((percentage * MIX_MAX_VOLUME) / 100);
}
