#include "mData.h"

mData* mData::_instance = NULL;

mData* mData::Instance()
{
    if(!_instance)
        _instance = new mData;

    return _instance;
}

void mData::SetCurrentPath(std::string path)
{
	this->path = path;
}

std::string mData::GetCurrentPath()
{
	return this->path;
}

void mData::Update()
{
	
}