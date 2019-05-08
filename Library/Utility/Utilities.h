//
// This script is partly courtesy of John Horton from the Book "Beginning C++ Game Programming" released by Packt>
// Created by Martin on 08.04.2019.
//

#ifndef STARBORN_01_UTILITIES_H
#define STARBORN_01_UTILITIES_H

#define RUNNING_WINDOWS

#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>

namespace Utility {
#ifdef RUNNING_WINDOWS
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <shlwapi.h>
#include <pathcch.h>
    
    inline std::string GetWorkingDirectory()
    {
        char result[MAX_PATH];
        std::string path = std::string(result, GetModuleFileName(nullptr, result, MAX_PATH));
        size_t lastIndex = path.find_last_of("\\");
        return path.substr(0, lastIndex);
    }
    
    template<class T>
    inline T Interpolate(float tBegin, float tEnd, const T &begin_val, const T &end_val, float tX)
    {
        return static_cast<T>((((end_val - begin_val) / (tEnd - tBegin)) * (tX - tBegin)) + begin_val);
    }
    
    inline float Remap(
            float value,
            float from1,
            float to1,
            float from2,
            float to2
                      )
    {
        return (value - from1) / (to1 - from1) * (to2 - from2) +
               from2;
    }

/* Old SFML Book Stuff. Mastering SFMl or Beginning SFML
inline std::vector<std::pair<std::string, bool>> GetFileList(const std::string &l_directory,
                                                             const std::string &l_search = "*.*",
                                                             bool l_directories = false)
{
    std::vector<std::pair<std::string, bool>> files;
    if (l_search.empty()) { return files; }
    std::string path = l_directory + l_search;
    WIN32_FIND_DATA data;
    HANDLE found = FindFirstFile(path.c_str(), &data);
    if (found == INVALID_HANDLE_VALUE) { return files; }
    do
    {
        if (!(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) || l_directories)
        {
            files.emplace_back(std::make_pair(
                    std::string(data.cFileName),
                    ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
                                             ));
        }
    }
    while (FindNextFile(found, &data));
    FindClose(found);
    return files;
}

inline void ReadQuotedString(std::stringstream &l_stream, std::string &l_string)
{
    l_stream >> l_string;
    if (l_string.at(0) == '"')
    {
        while (l_string.at(l_string.length() - 1) != '"' || !l_stream.eof())
        {
            std::string str;
            l_stream >> str;
            l_string.append(" " + str);
        }
    }
    l_string.erase(std::remove(l_string.begin(), l_string.end(), '"'), l_string.end());
}
*/

#endif

}

#endif //STARBORN_01_UTILITIES_H
