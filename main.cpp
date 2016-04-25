#include <iostream>

#include "RemotePlayer.h"

using namespace std;

int main()
{
    if(!RemotePlayer::Instance()->Init())
        std::cout << "Error Initializing RemotePlayer" << std::endl;
    else
        std::cout << "RemotePlayer Initialized !" << std::endl;

    return 0;
}
