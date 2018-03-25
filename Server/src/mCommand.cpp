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

Command mCommand::ProcessCommand(string command)
{
	Command _command;
	_command.command = command;

	if (!Prefs::IsCommandFormatValid(command))
	{
		_command.isValid = false;
		return _command;
	}

	string str = command.substr(3);
	size_t split_pos = str.find(';');
	if (split_pos == string::npos)
	{
		_command.isValid = false;
		return _command;
	}

	_command.isValid = true;
	_command.type = command.at(1);
	_command.func = str.substr(0, split_pos);
	_command.param = str.substr(split_pos + 1, str.size() - split_pos - 1);

	_command.isConnection = _command.type == 'n' && _command.func == "connect";
	_command.isDisconnection = _command.type == 'n' && _command.func == "disconnect";

	return _command;
}

bool mCommand::ExecuteCommand(Command* command)
{
	switch (command->type)
	{
		case 'd':
			return ExData(command->func, command->param);
		case 's':
			return ExSound(command->func, command->param);
		default:
			return false;
	}
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
