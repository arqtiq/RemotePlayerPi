#ifndef MDATA_H
#define MDATA_H

#include <boost/filesystem.hpp>
#include <vector>
#include <cstring>

#include "Logger.h"
#include "prefs.h"

class mData
{
    public:
        static mData* Instance();
        void Update();
        bool SetCurrentPath_str(string newPath);
		bool SetInitPath_str(string initPath);
        bool SetCurrentPath(boost::filesystem::path newPath);
		string GetCurrentPath_str();
		boost::filesystem::path GetCurrentPath();
        vector<string> GetFiles();
        vector<string> GetFolders();
        void GoToSubFolder(string subFolder);
        void GoToPreviousFolder();
		void GoToHomeFolder();
    protected:
    private:
        static mData* _instance;
        mData() {};
		boost::filesystem::path initPath;
		boost::filesystem::path currentPath;
};

#endif // MDATA_H
