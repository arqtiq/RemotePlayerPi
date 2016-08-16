#ifndef MNET_H
#define MNET_H

#include "Logger.h"
#include "prefs.h"
#include "SDL/SDL_net.h"
#include <string.h>

class mNet
{
    public:
        static mNet* Instance();
		bool ClientConnected;
		std::string Resolve();
        void Update();
		void DisconnectClient();
    protected:
    private:
        static mNet* _instance;
		char buffer[Prefs::NET_BUFFER_SIZE];
		IPaddress serverIP;
		TCPsocket serverSocket;
		TCPsocket clientSocket;
		SDLNet_SocketSet socketSet;
		mNet();
		void SendToClient(std::string msg, bool tempSocket);
};

#endif // MNET_H
