#include <iostream>

#include "RemotePlayer.h"

using namespace std;

int main()
{
    if(!RemotePlayer::Instance()->Init())
    {
        std::cout << "Error Initializing RemotePlayer" << std::endl;
        return 0;
    }
    else
        std::cout << "RemotePlayer Initialized !" << std::endl;

    while(true)
    {
    	RemotePlayer::Instance()->Update();
    }

    return 0;
}
