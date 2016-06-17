#include "mData.h"

using namespace std;

mData* mData::_instance = NULL;

mData* mData::Instance()
{
    if(!_instance)
        _instance = new mData;

    return _instance;
}

bool mData::SetCurrentPath_str(string newPath)
{
    if(is_directory(newPath))
    {
        this->currentPath = path(newPath);
        /*vector<string> f = mData::GetFolders();
        for(int i = 0; i < f.size(); i++)
            RemotePlayer::Instance()->logger.Log(f[i]);*/
        return true;
    }

    return false;
}
bool mData::SetCurrentPath(path newPath)
{
    if(is_directory(newPath))
    {
        this->currentPath = newPath;
        return true;
    }

    return false;
}

string mData::GetCurrentPath_str()
{
	return this->currentPath.filename().c_str();
}
path mData::GetCurrentPath()
{
    return this->currentPath;
}

vector<string> mData::GetFiles()
{
    vector<string> files;
    for(auto&& x : directory_iterator(this->currentPath))
    {
        if(is_regular_file(x.path()) && Prefs::IsMusicFileFormatSupported(x.path().extension().c_str()))
            files.push_back(x.path().filename().c_str());
    }
    return files;
}

vector<string> mData::GetFolders()
{
    vector<string> dirs;
    for(auto&& x : directory_iterator(this->currentPath))
    {
        if(is_directory(x.path()))
            dirs.push_back(x.path().filename().c_str());
      }
    return dirs;
}

void mData::GoToSubFolder(string subFolder)
{
    mData::SetCurrentPath((this->currentPath / path(subFolder)));
}

void mData::GoToPreviousFolder()
{
    mData::SetCurrentPath(this->currentPath.parent_path());
}

void mData::Update()
{

}
