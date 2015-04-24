#ifndef HTTPHEADER_H
#define HTTPHEADER_H

#include <string>
#include <map>

enum HTTPStatus { HTTP_OK, HTTP_ERROR };

class HTTPSClient;

class HTTPHeader
{
    friend class HTTPSClient;

    public :
    
        HTTPHeader();
        
        std::string getField(const std::string& name);  
        int getBodyLength();
        
    private :
    
        HTTPStatus _status;
        std::map<std::string, std::string> _fields;
};


#endif
