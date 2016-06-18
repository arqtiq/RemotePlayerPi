#include "mCommand.h"

using namespace std;

enum class FuncType
{
	dDIR, dPREV, sPLAY, sPAUSE, sSTOP, sVOL, sREWIND
};

mCommand* mCommand::_instance = NULL;

mCommand* mCommand::Instance()
{
    if(!_instance)
        _instance = new mCommand;

	_instance-> FuncToEnum.insert(std::pair<string, FuncType>("dir", FuncType::dDIR));

    return _instance;
}

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

}

bool mCommand::ExSound(string func, string param)
{

}

void mCommand::Update()
{

}
