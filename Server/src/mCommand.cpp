#include "mCommand.h"

#include "mAudio.h"
#include "mData.h"

using namespace std;

mCommand* mCommand::_instance = NULL;

mCommand* mCommand::Instance()
{
    if(!_instance)
        _instance = new mCommand;

    return _instance;
}

bool mCommand::Init()
{
	FuncToEnum.insert(std::pair<string, FuncType>("dir", FuncType::dDIR));
	FuncToEnum.insert(std::pair<string, FuncType>("prev", FuncType::dPREV));
	FuncToEnum.insert(std::pair<string, FuncType>("home", FuncType::dHOME));
	FuncToEnum.insert(std::pair<string, FuncType>("play", FuncType::sPLAY));
	FuncToEnum.insert(std::pair<string, FuncType>("pause", FuncType::sPAUSE));
	FuncToEnum.insert(std::pair<string, FuncType>("stop", FuncType::sSTOP));
	FuncToEnum.insert(std::pair<string, FuncType>("vol", FuncType::sVOL));
	FuncToEnum.insert(std::pair<string, FuncType>("rew", FuncType::sREWIND));

	Logger::Log("Command module init OK");
	return true;
}

void mCommand::Update()
{ }

void mCommand::Quit()
{ }

bool mCommand::ProcessCommand(string command)
{
	if(!Prefs::IsCommandFormatValid(command))
		return false;

	string func, param;
	if(!ExtractCommandData(command, func, param))
		return false;

	switch (GetCommandType(command))
	{
		case 'd':
			return ExData(func, param);
		case 's':
			return ExSound(func, param);
		default:
			return false;
	}
}

char mCommand::GetCommandType(string& command)
{
	return command.at(1);
}

bool mCommand::ExtractCommandData(string command, string& function, string& parameter)
{
	string str = command.substr(3);
	size_t split_pos = str.find(';');
	if(split_pos == string::npos)
		return false;

	function = command.substr(0, split_pos);
	parameter = command.substr(split_pos + 1, command.size() - split_pos - 1);
	return true;
}

bool mCommand::ExData(string func, string param)
{
	switch (GetFuncTypeFromString(func))
	{
		case FuncType::dHOME:
			mData::Instance()->GoToHomeFolder();
			return true;
		case FuncType::dDIR:
			if (param.size() == 0)
				return false;
			mData::Instance()->GoToSubFolder(param);
			return true;
		case FuncType::dPREV:
		{
			if (param.size() == 0)
			{
				mData::Instance()->GoToPreviousFolder();
				return true;
			}
			int iter = atoi(param.data());
			while(iter--)
				mData::Instance()->GoToPreviousFolder();
			return true;
        }
		default:
			return false;
	}
}

bool mCommand::ExSound(string func, string param)
{
	switch (GetFuncTypeFromString(func))
	{
		default:
			return false;
	}
}

FuncType mCommand::GetFuncTypeFromString(std::string& func)
{
	return FuncToEnum[func];
}
