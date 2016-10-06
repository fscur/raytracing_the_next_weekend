#ifndef _FILE_INFO_H_
#define _FILE_INFO_H_

#include <string>

struct fileInfo
{
public:
    std::string name;
    std::string path;
};

#endif

#ifndef _DIRECTORY_INFO_H_
#define _DIRECTORY_INFO_H_

struct directoryInfo
{
public:
    std::string name;
    std::string path;
};

#endif

#ifndef _PATH_H_
#define _PATH_H_

#include <vector>
#include "io.h"

class path
{
public:
    static bool exists(std::string path);
    static std::string getDirectoryFullName(std::string path);
    static std::string getFileName(std::string path);
    static std::string getFileNameWithoutExtension(std::string path);
    static std::string getExtension(std::string path);
    static std::vector<fileInfo> getFiles(const std::string directory);
    static std::vector<directoryInfo> getDirectories(const std::string directory);
    static std::string combine(const std::string path0, const std::string path1);
};

#endif