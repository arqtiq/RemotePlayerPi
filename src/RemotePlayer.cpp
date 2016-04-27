#include "RemotePlayer.h"

RemotePlayer* RemotePlayer::_instance = NULL;

RemotePlayer* RemotePlayer::Instance()
{
    if(!_instance)
        _instance = new RemotePlayer;

    return _instance;
}

bool RemotePlayer::Init()
{
    logger = Logger();
    m_audio = mAudio::Instance();
    m_net = mNet::Instance();
    m_command = mCommand::Instance();
    m_data = mData::Instance();

    return InitSDL() && InitMixer() && InitNet();
}

bool RemotePlayer::InitSDL()
{
    int r = SDL_Init(SDL_INIT_AUDIO);
    if(r == -1)
        RemotePlayer::Instance()->logger.Log("Error initializing SDL; " + static_cast<std::string>(SDL_GetError()));
    return r == -1 ? false : true;
}

bool RemotePlayer::InitMixer()
{
    int r = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
    if(r == -1)
        RemotePlayer::Instance()->logger.Log("Error initializing SDL_Mixer; " + static_cast<std::string>(Mix_GetError()));
    return r == -1 ? false : true;
}

bool RemotePlayer::InitNet()
{
    int r = SDLNet_Init();
    if(r == -1)
        RemotePlayer::Instance()->logger.Log("Error initializing SDL_Net; " + static_cast<std::string>(SDLNet_GetError()));
    return r == -1 ? false : true;
}

void RemotePlayer::Quit()
{
	SDLNet_Quit();
	Mix_Quit();
	SDL_Quit();
}

void RemotePlayer::Update()
{
    m_audio->Update();
    m_net->Update();
    m_command->Update();
    m_data->Update();
}
