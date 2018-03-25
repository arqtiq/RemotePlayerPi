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
	nCO, nDIS, nPING,
	dDIR, dPREV, dHOME,
	sPLAY, sPAUSE, sSTOP, sVOL, sREWIND
};

struct Command
{
	bool isValid, isConnection, isDisconnection;
	string command, func, param;
	char type;
};

class mCommand : mBase
{
    public:
        static mCommand* Instance();
		virtual bool Init();
        virtual void Update();
        virtual void Quit();
		std::map<std::string, FuncType> FuncToEnum;
		Command ProcessCommand(std::string command);
		bool ExecuteCommand(Command* command);
    protected:
    private:
        static mCommand* _instance;
        mCommand() {};
		bool ExData(std::string func, std::string param);
		bool ExSound(std::string func, std::string param);
		FuncType GetFuncTypeFromString(std::string& func);
		void SendFolderDescription();
};

#endif // MCOMMAND_H
