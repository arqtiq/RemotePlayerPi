#ifndef MNET_H
#define MNET_H

#include "Logger.h"
#include "prefs.h"
#include "mBase.h"
#include "SDL/SDL_net.h"

#include <string.h>

class mNet : mBase
{
    public:
        static mNet* Instance();
		virtual bool Init();
        virtual void Update();
        virtual void Quit();
		bool ClientConnected;
		void DisconnectClient(int ip);
    protected:
    private:
        static mNet* _instance;
		UDPSocket socket;
		UDPpacket *packet;
		int clientIP;
		mNet();
		void SendToClient(string msg, bool tempSocket);
		void OnMessageReceived(string msg);
		void ConnectClient(int ip);
};

#endif // MNET_H
