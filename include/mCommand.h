#ifndef MCOMMAND_H
#define MCOMMAND_H

#include "Logger.h"

class mCommand
{
    public:
        static mCommand* Instance();
        void Update();
        void ProcessCommand(std::string command);
    protected:
    private:
        static mCommand* _instance;
        mCommand() {};
};

#endif // MCOMMAND_H
