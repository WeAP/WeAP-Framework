#include "FileUtil.h"
#include "Error.h"
#include "Exception.h"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include <sys/types.h>
#include <sys/stat.h>
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

void FileUtil::WriteLines(const string& filePath, const vector<string>& lines)
{
    ofstream outFile(filePath.c_str());
    if (outFile.fail())
    {
        string errInfo = "file open failed, filePath:" + filePath;
        ERROR("%s", errInfo.c_str());
        throw Exception(Error::FileUtil_Open_Failed, errInfo);
    }
    for (size_t i = 0; i < lines.size(); i++)
    {
        outFile << lines[i];
    }
    
    outFile.close();
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
/*
void FileUtil::Dump(const string& data, const string& fileName)
{
    std::ofstream fs(fileName,std::ios::app);
    fs<<data;
    fs.close();
    
}
*/
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
/*
R_OK:只是检测当前用户是否具有可读权限；
W_OK:只是检测当前用户是否具有可读权限；;
X_OK:检查当前用户对该文件是否具有 可读 可写 可执行权限；
F_OK: 检查文件是否存在；
    if (access(path.c_str(), F_OK) == 0)
    {
        return true;
    }

    return false;
*/


    
}

bool FileUtil::ExistDir(const string& path)
{
    if (path.empty())
    {
        return false;
    }

    DIR* dir = opendir(path.c_str());
    if (dir == NULL)
    {
        return false;
    }

    closedir(dir);
    return true;
}

void FileUtil::MakeDir(const string& path)
{
    if (path.empty())
    {
        return;
    }
    if (FileUtil::ExistDir(path))
    {
        return;
    }

    //const char* dirPath = path.c_str();

    size_t pos = path.find('\\', 0);
    if (pos == string::npos)
    {
        return;
    }

    string currPath = path.substr(0, pos);

    do 
    {
        if (!FileUtil::ExistDir(currPath))
        {
            mkdir(currPath.c_str(), 0755);
        }

        currPath = path.substr(0, pos);

    }while (pos = path.find('\\', pos) != string::npos);

 
}



}}