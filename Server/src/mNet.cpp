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
	clientIP = 0;
}

bool mNet::Init()
{
    int r = SDLNet_Init();
    if(r == -1)
	{
        Logger::Log("Error initializing SDL_Net; " + std::string(SDLNet_GetError()));
		return false;
	}
	socket = SDLNet_UDP_Open(Prefs::NET_PORT);
	if (!socket)
	{
		Logger::Log("Error creating server socket; " + std::string(SDLNet_GetError()));
		return false;
	}

	packet = SDLNet_AllocPacket(Prefs::NET_BUFFER_SIZE);
	if (!packet)
	{
		Logger::Log("Error alocation packet size; " + std::string(SDLNet_GetError()));
		return false;
	}

    Logger::Log("Net module init OK");
	return true;
}

void mNet::SendMessage(string msg)
{

}

void mNet::Update()
{
	if (SDLNet_UDP_Recv(socket, packet))
	{
		int ip = (int)packet->address.port;
		string data = string((char *)packet->data);
		Logger::Log("Command received :" + data);
		CommandData c = mCommand::Instance()->ProcessCommand(data);
		if (!c.isValid)
		{
			Logger::Log("Command invalid.");
			return;
		}

		if (c.isDisconnection && ClientConnected)
			DisconnectClient(ip);
		else if (c.isConnection)
		{
			if (ClientConnected)
				Logger::Log("Connection refused.");
			else
				ConnectClient(ip);
		}
		else
		{
			mCommand::Instance()->ExecuteCommand(&c);
			Logger::Log("Command executed.");
		}
	}
}

void mNet::ConnectClient(int ip)
{
	clientIP = ip;
	ClientConnected = true;
	Logger::Log("Client connected : " + to_string(ip));
}

void mNet::DisconnectClient(int ip)
{
	if (ip == clientIP)
	{
		clientIP = 0;
		ClientConnected = false;
		Logger::Log("Client disconnected : " + to_string(ip));
	}
}

void mNet::Quit()
{
    SDLNet_Quit();
}
