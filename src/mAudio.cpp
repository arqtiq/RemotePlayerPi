#include "mAudio.h"

mAudio* mAudio::_instance = NULL;

mAudio* mAudio::Instance()
{
    if(!_instance)
        _instance = new mAudio;

    return _instance;
}

void mAudio::Update()
{
	
}