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
		getFiles();
		getFolders();
        return true;
    }

    return false;
}

path mData::GetCurrentPath()
{
    return currentPath;
}

void mData::getFiles()
{
	files.clear();
    for(auto&& x : directory_iterator(currentPath))
    {
        if(is_regular_file(x.path()) && Prefs::IsMusicFileFormatSupported(x.path().extension().string()))
            files.push_back(x.path().filename().string());
    }
}

void mData::getFolders()
{
	folders.clear();
    for(auto&& x : directory_iterator(currentPath))
    {
        if(is_directory(x.path()))
            folders.push_back(x.path().filename().string());
    }
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

string mData::GetFolderDescription()
{
	string desc = currentPath.string().substr(initPath.parent_path().string().length(),
		currentPath.string().length());
	desc += "|";
	for (size_t i = 0; i < folders.size(); i++)
		desc += (!i ? "" : "*") + folders[i];
    desc += "|";
	for (size_t j = 0; j < files.size(); j++)
		desc += (!j ? "" : "*") + files[j];

	return desc;
}
