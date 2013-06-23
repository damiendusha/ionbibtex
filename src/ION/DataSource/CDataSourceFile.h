
#ifndef DATA_SOURCE_FILE_H__
#define DATA_SOURCE_FILE_H__

#include "CDataSource.h"

class CDataSourceFile : public CDataSource
{
    public:

        CDataSourceFile(const std::string& filename);
        virtual ~CDataSourceFile();

        virtual bool ParseDataSource(std::vector<std::string>& data);
};




#endif  // DATA_SOURCE_FILE_H__