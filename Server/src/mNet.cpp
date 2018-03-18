#include "mNet.h"
#include "mCommand.h"

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

bool mNet::Init()
{
    int r = SDLNet_Init();
    if(r == -1)
	{
        Logger::Log("Error initializing SDL_Net; " + std::string(SDLNet_GetError()));
		return false;
	}

	std::string error;
	if(!Resolve(error))
	{
		Logger::Log("Error creating server; " + error);
		return false;
	}

    Logger::Log("Net module init OK");
	return true;
}

bool mNet::Resolve(string &error)
{
    socketSet = SDLNet_AllocSocketSet(2);
	if(socketSet == NULL)
	{
		error = "Could not allocate socket set : " + string(SDLNet_GetError());
		return false;
    }

	if(SDLNet_ResolveHost(&serverIP, NULL, Prefs::NET_PORT) == -1)
	{
		error = "Could not resolve server host : " + string(SDLNet_GetError());
		return false;
    }

	serverSocket = SDLNet_TCP_Open(&serverIP);
	if(!serverSocket)
	{
		error = "Could not create server socket : " + string(SDLNet_GetError());
		return false;
    }

	SDLNet_TCP_AddSocket(socketSet, serverSocket);
	return true;
}

void mNet::SendToClient(string msg, bool tempSocket = false)
{
	strcpy(buffer, msg.c_str());
	int lgth = strlen(buffer) + 1;

	TCPsocket sendSocket = tempSocket ? SDLNet_TCP_Accept(serverSocket) : clientSocket;
	SDLNet_TCP_Send(sendSocket, (void*)buffer, lgth);

	if(tempSocket)
		SDLNet_TCP_Close(sendSocket);
}

void mNet::OnMessageReceived(std::string msg)
{
	mCommand::Instance()->ProcessCommand(msg);
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

void mNet::Quit()
{
    SDLNet_Quit();
}
