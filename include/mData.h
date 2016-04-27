#ifndef MDATA_H
#define MDATA_H

#include "dirent.h"

#include "Logger.h"

class mData
{
    public:
        static mData* Instance();
        void Update();
        void SetCurrentPath(std::string path);
		std::string GetCurrentPath();
    protected:
    private:
        static mData* _instance;
        mData() {};
		std::string path;
};

#endif // MDATA_H
