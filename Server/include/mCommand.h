#ifndef MCOMMAND_H
#define MCOMMAND_H

#include "Logger.h"
#include "prefs.h"
#include "mBase.h"

#include <string>
#include <map>

class RemotePlayer;

enum class FuncType
{
	dDIR, dPREV, dHOME, sPLAY, sPAUSE, sSTOP, sVOL, sREWIND
};

class mCommand : mBase
{
    public:
        static mCommand* Instance();
		virtual bool Init();
        virtual void Update();
        virtual void Quit();
		bool IsConnectionCommand(std::string command, std::string& name);
		std::map<std::string, FuncType> FuncToEnum;
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
