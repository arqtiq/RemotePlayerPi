#ifndef PREFS_H
#define PREFS_H

#include <algorithm>
#include <array>

using namespace std;

class Prefs
{
    public:
        Prefs() {}

        static bool IsMusicFileFormatSupported(string format)
        {
            string supp[3] = {".flac", ".mp3", ".ogg"};
            string *f = find(begin(supp), end(supp), format);
            return !(f == end(supp));
        }

        static bool IsCommandFormatValid(string command)
        {
            if(command.size() < 4)
                return false;
            array<char, 2> pre = {'s','d'};
            if(command.at(0) != '@' || command.at(2) != ':')
                return false;
            for(size_t i = 0; i < pre.size(); i++)
                if(pre[i] == command.at(1))
                    return true;

            return false;
        }

    protected:
    private:
};

#endif // PREFS_H
