#ifndef MDATA_H
#define MDATA_H

#include "dirent.h"
#include <vector>

#include "Logger.h"

class mData
{
    public:
        static mData* Instance();
        void Update();
        void SetCurrentPath(std::string path);
		std::string GetCurrentPath();
        std::vector<std::string> GetFiles();
        std::vector<std::string> GetFolders();
        void GoToSubFolder(std::string subFolder);
        void GoToPreviousFolder();
    protected:
    private:
        static mData* _instance;
        mData() {};
		std::string path;
		std::vector<std::string> GetData(int DT_TYPE);
};

#endif // MDATA_H
