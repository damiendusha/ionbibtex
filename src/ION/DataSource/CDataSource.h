/*
* Copyright (C) 2013, 2020 Damien Dusha
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software Foundation,
* Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
* 
*/

#ifndef DATA_SOURCE_H__
#define DATA_SOURCE_H__

#include <vector>
#include <string>
#include <memory>

class CDataSource
{
    public:

        struct Options
        {
            std::string url;
            std::string article_id;
            
            Options() {}

            static Options GetFromFlags();
        };

        static std::unique_ptr<CDataSource> GetDataSource(const Options &options);

        CDataSource(const std::string& resourceName);
        virtual ~CDataSource() {}

        bool ParseDataSource(std::string& data);


    protected:
        std::string m_resourceName;

        virtual bool InternalParseDataSource(std::string& data) = 0;
};

#endif  // DATA_SOURCE_H__
