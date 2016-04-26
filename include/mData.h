#ifndef MDATA_H
#define MDATA_H

#include "dirent.h"

#include "Logger.h"

class mData
{
    public:
        static mData* Instance();
        void Update();
        void SetCurrentPath();
    protected:
    private:
        static mData* _instance;
        mData() {};
};

#endif // MDATA_H
