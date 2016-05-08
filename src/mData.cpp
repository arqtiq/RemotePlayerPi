#include "mData.h"
#include "RemotePlayer.h"

#include <cstring>

using namespace std;

mData* mData::_instance = NULL;

mData* mData::Instance()
{
    if(!_instance)
        _instance = new mData;

    return _instance;
}

void mData::SetCurrentPath(string path)
{
	this->path = path;
}

string mData::GetCurrentPath()
{
	return this->path;
}

vector<string> mData::GetFiles()
{
    return mData::GetData(DT_REG);
}

vector<string> mData::GetFolders()
{
    return mData::GetData(DT_DIR);
}

vector<string> mData::GetData(int DT_TYPE)
{
    vector<string> output;
    DIR *dir = opendir(this->path.c_str());
    struct dirent* entry = readdir(dir);
    while(entry != NULL)
    {
        if(entry->d_type == DT_TYPE)
        {
            if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
                output.push_back(entry->d_name);
        }
        entry = readdir(dir);
    }
    return output;
}

void mData::GoToSubFolder(string subFolder)
{
    mData::SetCurrentPath(mData::GetCurrentPath() + "/" + subFolder);
}

void mData::GoToPreviousFolder()
{

}

void mData::Update()
{

}
