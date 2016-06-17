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
        Logger::Log("Error initializing SDL; " + static_cast<std::string>(SDL_GetError()));
    return r == -1 ? false : true;
}

bool RemotePlayer::InitMixer()
{
    int r = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
    if(r == -1)
        Logger::Log("Error initializing SDL_Mixer; " + std::string(Mix_GetError()));
    return r == -1 ? false : true;
}

bool RemotePlayer::InitNet()
{
    int r = SDLNet_Init();
    if(r == -1)
        Logger::Log("Error initializing SDL_Net; " + std::string(SDLNet_GetError()));
    return r == -1 ? false : true;
}

void RemotePlayer::Start()
{
    /*m_audio->LoadSong("/home/raspi/Music/song.mp3", true);
    m_audio->SetVolume(75);*/
}

void RemotePlayer::Quit()
{
	SDLNet_Quit();
	Mix_Quit();
	SDL_Quit();
}

bool RemotePlayer::Update()
{
    SDL_WaitEvent(&event);

    m_audio->Update();
    m_net->Update();
    m_command->Update();
    m_data->Update();

    return true;
}
