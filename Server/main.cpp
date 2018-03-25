#include <iostream>

#include "RemotePlayer.h"

using namespace std;

int main(int argc, char* argv[])
{
	if(argc == 1)
	{
		cout << "No init dir arg set; Can't start !" << endl;
		return 0;
	}
	else if(argc == 2)
	{
		cout << "Using " << argv[1] << " init dir" << endl << endl;
	}

    if(!RemotePlayer::Instance()->Init(string(argv[1])))
    {
        cout << "Error Initializing RemotePlayer" << endl;
        return 0;
    }
    else
	{
        cout << "RemotePlayer Initialized..." << endl;
        RemotePlayer::Instance()->Start();
	}

    bool _update = true;
    do
    {
    	RemotePlayer::Instance()->Update();
    }
    while(_update);

	RemotePlayer::Instance()->Quit();
    return 0;
}
