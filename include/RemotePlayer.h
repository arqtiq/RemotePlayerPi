#ifndef REMOTEPLAYER_H
#define REMOTEPLAYER_H

#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"

#include "Logger.h"

class RemotePlayer
{
    public:
        static RemotePlayer* Instance();
        bool Init();

        Logger logger;
    protected:
    private:
        static RemotePlayer* _instance;
        RemotePlayer() {};
        bool InitSDL();
        bool InitMixer();
};

#endif // REMOTEPLAYER_H
