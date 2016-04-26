#ifndef MAUDIO_H
#define MAUDIO_H

#include "Logger.h"

class mAudio
{
    public:
        static mAudio* Instance();
        void Update();
    protected:
    private:
        static mAudio* _instance;
        mAudio() {};
};

#endif // MAUDIO_H
