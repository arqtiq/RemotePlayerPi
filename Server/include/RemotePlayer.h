#ifndef REMOTEPLAYER_H
#define REMOTEPLAYER_H

#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_net.h"

#include "Logger.h"

#include "mData.h"
#include "mAudio.h"
#include "mCommand.h"
#include "mNet.h"

#include <vector>
#include <sstream>

class RemotePlayer
{
    public:
        static RemotePlayer* Instance();

        bool Init();
        void Start();
		void Quit();
        bool Update();
    protected:
    private:
        static RemotePlayer* _instance;
        SDL_Event event;
        RemotePlayer() {};
        bool InitSDL();
        bool InitMixer();
        bool InitNet();
};

#endif // REMOTEPLAYER_H
