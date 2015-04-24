#include "HTTPHeader.h"
#include <stdlib.h>    
using std::map;
using std::string;

HTTPHeader::HTTPHeader():
_status(HTTP_ERROR),
_fields()
{
}

std::string HTTPHeader::getField(const std::string& name)
{
    map<string,string>::iterator itor = _fields.find(name);
    if(itor == _fields.end())
        return string();
    return itor->second;
}

int HTTPHeader::getBodyLength()
{
    return atoi(getField("Content-Length").c_str());
}

