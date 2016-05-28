#ifndef MAUDIO_H
#define MAUDIO_H

#include "Logger.h"
#include "SDL/SDL_mixer.h"

class mAudio
{
    public:
        static mAudio* Instance();
        void Update();
		bool IsPlaying();
		bool IsPaused();
		void Play();
		void Pause();
		void TogglePlay();
		void Stop();
		void Rewind();
		//void SetPosition //https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_65.html#SEC65
		void LoadSong(std::string path);
		void SetVolume(int percentage);
    protected:
    private:
        static mAudio* _instance;
		Mix_Music *song;
        mAudio() {};
};

#endif // MAUDIO_H
