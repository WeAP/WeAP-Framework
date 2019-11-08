#include "FileUtil.h"
#include "Error.h"
#include "Exception.h"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include <sys/types.h>
#include <dirent.h>


namespace WeAP { namespace System {


void FileUtil::ReadLines(const string& filePath, vector<string>& lines)
{
    std::ifstream infile;
    infile.open(filePath.c_str(), std::ios::in);
    if(!infile.is_open())
    {
        string errInfo = "file open failed, filePath:" + filePath;
        ERROR("%s", errInfo.c_str());
        throw Exception(Error::FileUtil_Open_Failed, errInfo);
    }

    string line;
    while(getline(infile,line)) //读取一行，直到所有行读完
    {
        if (line.empty())
        {
            continue;
        }
        if (line[0] == '#')
        {
            continue;
        }

        lines.push_back(line);
    }
    
}

string FileUtil::GetFileName(const string& filePath)
{
   if( filePath == "" )
   {
     return "";
   }

   size_t pos = filePath.rfind("/");
   if( pos + 1 == filePath.length() )
   {
       return "";
   }
   
   return filePath.substr( pos + 1 );
}

string FileUtil::GetDirPath(const string& filePath)
{
    if( filePath.size() == 0 )
    {
        return "";
    }
    
    size_t pos = filePath.rfind("/");
    if (pos == filePath.size() - 1 || pos == std::string::npos)
    {
        return "";
    }

    return filePath.substr( 0, pos + 1 );
}

bool FileUtil::Exists(const std::string& path)
{
    fstream fs;
    fs.open(path.c_str(),ios::in);

    if(fs.is_open())
    {
        fs.close();
        return true;
    }

    return false;
}



}}