#ifndef __WeAP_FileUtil_H__
#define __WeAP_FileUtil_H__

#include "Object.h"

namespace WeAP { namespace System {

class FileUtil: public Object
{
private:
    FileUtil();

public:

    static void ReadLines(const string& filePath, vector<string>& lines);

    static string GetFileName(const string& filePath);

    static string GetDirPath(const string& filePath);

    static bool Exists(const std::string& path);

};


}}


#endif //__WeAP_FileUtil_H__