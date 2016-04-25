#ifndef APPSYSTEM_H
#define APPSYSTEM_H

#include "RemotePlayer.h"

class AppSystem
{
    public:
        AppSystem(RemotePlayer *player);
    protected:
        RemotePlayer player;
    private:
};

#endif // APPSYSTEM_H
