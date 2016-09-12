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
		std::string Resolve();
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
		void OnMessageReceived(std::string msg);
};

#endif // MNET_H
