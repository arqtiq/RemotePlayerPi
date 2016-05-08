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

    if(!RemotePlayer::Instance()->Init())
    {
        cout << "Error Initializing RemotePlayer" << endl;
        return 0;
    }
    else
	{
        cout << "RemotePlayer Initialized !" << endl;
		RemotePlayer::Instance()->m_data->SetCurrentPath(string(argv[1]));
	}

    while(true)
    {
    	RemotePlayer::Instance()->Update();
    }

	RemotePlayer::Instance()->Quit();
    return 0;
}
