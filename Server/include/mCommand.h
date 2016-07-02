#ifndef MCOMMAND_H
#define MCOMMAND_H

#include "Logger.h"
#include "prefs.h"

#include <string>
#include <map>

class RemotePlayer;

class mCommand
{
    public:
        static mCommand* Instance();
		std::map<std::string, FuncType> FuncToEnum;
        void Update();
        bool ProcessCommand(std::string command);
    protected:
    private:
        static mCommand* _instance;
        mCommand() {};
		char GetCommandType(std::string& command);
        bool ExtractCommandData(std::string command, std::string& function, std::string& parameter);
		bool ExData(std::string func, std::string param);
		bool ExSound(std::string func, std::string param);
		FuncType GetFuncTypeFromString(std::string& func);
};

#endif // MCOMMAND_H
