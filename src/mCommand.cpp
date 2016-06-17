#include "mCommand.h"

mCommand* mCommand::_instance = NULL;

mCommand* mCommand::Instance()
{
    if(!_instance)
        _instance = new mCommand;

    return _instance;
}

void mCommand::ProcessCommand(std::string command)
{

}

void mCommand::Update()
{

}
