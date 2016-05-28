#ifndef MDATA_H
#define MDATA_H

#include <boost/filesystem.hpp>
#include <vector>
#include <cstring>

#include "Logger.h"

using namespace boost::filesystem;

class mData
{
    public:
        static mData* Instance();
        void Update();
        bool SetCurrentPath_str(std::string newPath);
        bool SetCurrentPath(path newPath);
		std::string GetCurrentPath_str();
		path GetCurrentPath();
        std::vector<std::string> GetFiles();
        std::vector<std::string> GetFolders();
        void GoToSubFolder(std::string subFolder);
        void GoToPreviousFolder();
    protected:
    private:
        static mData* _instance;
        mData() {};
		path currentPath;
};

#endif // MDATA_H
