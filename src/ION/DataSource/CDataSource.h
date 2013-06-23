
#ifndef DATA_SOURCE_H__
#define DATA_SOURCE_H__

#include <vector>
#include <string>

class CDataSource
{
    public:

        static CDataSource* GetDataSource(const std::string& source);

        CDataSource(const std::string& resourceName);
        virtual ~CDataSource();

        virtual bool ParseDataSource(std::vector<std::string>& data) = 0;


    protected:

        std::string m_resourceName;
};




#endif  // DATA_SOURCE_H__
