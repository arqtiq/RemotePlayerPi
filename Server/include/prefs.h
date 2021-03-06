#ifndef PREFS_H
#define PREFS_H

#include <algorithm>
#include <array>

class Prefs
{
    public:
        Prefs() {}

		static unsigned const short NET_PORT = 1234;
		static unsigned const short NET_BUFFER_SIZE = 512;

        static bool IsMusicFileFormatSupported(std::string format)
        {
            std::string supp[3] = {".flac", ".mp3", ".ogg"};
            string *f = std::find(std::begin(supp), std::end(supp), format);
            return !(f == std::end(supp));
        }

        static bool IsCommandFormatValid(std::string command)
        {
            if(command.size() < 4)
                return false;
            if(command.at(0) != '@' || command.at(2) != ':')
                return false;
            array<char, 3> pre = {'s','d','n'};
            for(size_t i = 0; i < pre.size(); i++)
                if(pre[i] == command.at(1))
                    return true;

            return false;
        }
};

#endif // PREFS_H
