#include "UrlPackage.h"

namespace WeAP { namespace Framework {

UrlPackage::UrlPackage()
{
}


UrlPackage::~UrlPackage()
{
    
}

void UrlPackage::Parse(const string& str, char sep1, char sep2)
{
    this->params.Parse(str, sep1, sep2);
}

void UrlPackage::ToString()
{
    this->params.ToUrlString();
}


}}
