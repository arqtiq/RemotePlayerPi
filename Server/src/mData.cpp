#include "mData.h"

using namespace std;
using namespace boost::filesystem;

mData* mData::_instance = NULL;

mData* mData::Instance()
{
    if(!_instance)
        _instance = new mData;

    return _instance;
}

bool mData::Init()
{
    Logger::Log("Data module init OK");
	return true;
}

void mData::Update()
{ }

void mData::Quit()
{ }

bool mData::SetCurrentPath_str(string newPath)
{
    if(is_directory(newPath))
    {
        currentPath = path(newPath);
        return true;
    }

    return false;
}

bool mData::SetInitPath_str(string init)
{
	if (SetCurrentPath_str(init))
	{
		initPath = path(init);
		return true;
	}

	return false;
}

bool mData::SetCurrentPath(path newPath)
{
    if(is_directory(newPath))
    {
        currentPath = newPath;
        return true;
    }

    return false;
}

string mData::GetCurrentPath_str()
{
	return currentPath.filename().c_str();
}
path mData::GetCurrentPath()
{
    return currentPath;
}

vector<string> mData::GetFiles()
{
    vector<string> files;
    for(auto&& x : directory_iterator(currentPath))
    {
        if(is_regular_file(x.path()) && Prefs::IsMusicFileFormatSupported(x.path().extension().c_str()))
            files.push_back(x.path().filename().c_str());
    }
    return files;
}

vector<string> mData::GetFolders()
{
    vector<string> dirs;
    for(auto&& x : directory_iterator(currentPath))
    {
        if(is_directory(x.path()))
            dirs.push_back(x.path().filename().c_str());
    }
    return dirs;
}

void mData::GoToSubFolder(string subFolder)
{
    SetCurrentPath((currentPath / path(subFolder)));
}

void mData::GoToPreviousFolder()
{
	if(!equivalent(currentPath, initPath)) // avoid to go beyond home dir
		SetCurrentPath(currentPath.parent_path());
}

void mData::GoToHomeFolder()
{
	SetCurrentPath(initPath);
}
