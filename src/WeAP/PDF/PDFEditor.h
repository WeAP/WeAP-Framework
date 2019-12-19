#ifndef __WeAP_PDFEditor_H__
#define __WeAP_PDFEditor_H__

//#include <sys/shm.h>
//#include <pthread.h>

/*
g++ main.cpp PDFEditor.cpp -lpodofo -o main.bin -L/home/xzwang/WeAP-Framework/dependency/podofo-0.9.6/src -rdynamic -lpodofo /usr/local/lib/libfontconfig.so /usr/local/lib/libz.so -lcrypto -lcrypto -lssl -lpthread /usr/local/lib/libfreetype.so /usr/local/lib/libpng.so /usr/local/lib/libz.so /usr/local/lib/libtiff.so -lcrypto -lcrypto -lssl -lpthread /usr/local/lib/libfreetype.so /usr/local/lib/libpng.so /usr/local/lib/libtiff.so -Wl,-rpath,/home/xzwang/WeAP-Framework/dependency/podofo-0.9.6/src:/usr/local/lib
*/

namespace WeAP { namespace PDF {

class PDFEditor
{
public:
    PDFEditor();
    virtual ~PDFEditor();

    void GenerateFile();
    
};


}}

#endif

