#ifndef MNET_H
#define MNET_H

#include "Logger.h"

class mNet
{
    public:
        static mNet* Instance();
        void Update();
    protected:
    private:
        static mNet* _instance;
        mNet() {};
};

#endif // MNET_H
