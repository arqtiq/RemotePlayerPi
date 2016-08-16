#include "mNet.h"

using namespace std;

mNet* mNet::_instance = NULL;

mNet* mNet::Instance()
{
    if(!_instance)
        _instance = new mNet;

    return _instance;
}

mNet::mNet()
{
	ClientConnected = false;
}

string mNet::Resolve()
{
	if(socketSet = SDLNet_AllocSocketSet(2) == NULL)
		return "Could not allocate socket set : " + SDLNet_GetError();

	if(SDLNet_ResolveHost(&serverIP, NULL, Prefs::NET_PORT) == -1)
		return "Could not resolve server host : " + SDLNet_GetError();

	serverSocket = SDLNet_TCP_Open(&serverIP);
	if(!serverSocket)
		return "Could not create server socket : " + SDLNet_GetError();

	SDLNet_TCP_AddSocket(socketSet, serverSocket);
	return "OK";
}

void mNet::SendToClient(string msg, bool tempSocket = false)
{
	strcpy(buffer, msg.c_str());
	int lgth = strlen(buffer) + 1;
	if(tempSocket)
	{
		TCPsocket tempSock = SDLNet_TCP_Accept(serverSocket);
		SDLNET_TCP_Send(tempSocket, (void*)buffer, lgth);
		SDLNet_TCP_Close(tempSocket);
	}
	else
		SDLNET_TCP_Send(clientSocket, (void*)buffer, lgth);
}

void mNet::Update()
{
	int serverSocketActivity = SDLNet_SocketReady(serverSocket);
    if (serverSocketActivity != 0)
    {
		if(!ClientConnected) // new connection
		{
			clientSocket = SDLNet_TCP_Accept(serverSocket);
			SDLNet_TCP_AddSocket(socketSet, clientSocket);
			ClientConnected = true;
			SendToClient("1");
			Logger::Log("Client connected !");
		}
		else // server busy
		{
			SendToClient("0", true);
			Logger::Log("Client refused !");
		}
	}
}