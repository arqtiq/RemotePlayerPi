#ifndef REMOTEPLAYER_H
#define REMOTEPLAYER_H

#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_net.h"

#include "Logger.h"

class RemotePlayer
{
    public:
        static RemotePlayer* Instance();
        Logger logger;
        mAudio m_audio;
        mData m_data;
        mnet m_net;
        mCommand m_command;

        bool Init();
        void Update();
    protected:
    private:
        static RemotePlayer* _instance;
        RemotePlayer() {};
        bool InitSDL();
        bool InitMixer();
        bool InitNet();
};

#endif // REMOTEPLAYER_H
