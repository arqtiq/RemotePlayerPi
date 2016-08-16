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
	modules.push_back((mBase*)mAudio::Instance());
	modules.push_back((mBase*)mData::Instance());
	modules.push_back((mBase*)mCommand::Instance());
	modules.push_back((mBase*)mNet::Instance());

	bool res = InitSDL();
	for (size_t i = 0; i < modules.size(); i++)
		res &= modules[i]->Init();

    return res;
}

bool RemotePlayer::InitSDL()
{
    int r = SDL_Init(SDL_INIT_AUDIO);
    if(r == -1)
        Logger::Log("Error initializing SDL; " + static_cast<std::string>(SDL_GetError()));
    return r == -1 ? false : true;
}

void RemotePlayer::Start()
{
    /*m_audio->LoadSong("/home/raspi/Music/song.mp3", true);
    m_audio->SetVolume(75);*/
}

void RemotePlayer::Quit()
{
	for (size_t i = 0; i < modules.size(); i++)
		modules[i]->Quit();

	SDL_Quit();
}

void RemotePlayer::Update()
{
    SDL_WaitEvent(&event);

    for (size_t i = 0; i < modules.size(); i++)
		modules[i]->Update();
}
