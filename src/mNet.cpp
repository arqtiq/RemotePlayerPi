#include "mNet.h"

mNet* mNet::_instance = NULL;

mNet* mNet::Instance()
{
    if(!_instance)
        _instance = new mNet;

    return _instance;
}

void mNet::Update()
{
	
}