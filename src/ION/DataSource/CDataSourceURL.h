
#ifndef DATA_SOURCE_URL_H__
#define DATA_SOURCE_URL_H__

#include "CDataSource.h"

class CDataSourceURL : public CDataSource
{
    public:

        CDataSourceURL(const std::string& filename);
        virtual ~CDataSourceURL();

        virtual bool ParseDataSource(std::vector<std::string>& data);
};




#endif  // DATA_SOURCE_URL_H__