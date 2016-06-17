#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <sstream>

using namespace std;

class Logger
{
    public:
        Logger();

        static void Log(std::string message)
        {
            std::cout << message << std::endl;
        }

        template<typename T>
        static void LogStream(T message)
        {
            std::stringstream ss;
            ss << message;
            std::cout << ss.str() << std::endl;
        }

    protected:
    private:
};

#endif // LOGGER_H
