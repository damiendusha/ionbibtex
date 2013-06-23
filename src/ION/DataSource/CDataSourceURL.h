/*
* Copyright (C) 2013 Damien Dusha
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



#ifndef DATA_SOURCE_URL_H__
#define DATA_SOURCE_URL_H__

#include "CDataSource.h"
#include <stdlib.h>

class CDataSourceURL : public CDataSource
{
    public:

        CDataSourceURL(const std::string& filename);
        virtual ~CDataSourceURL();

        virtual bool ParseDataSource(std::vector<std::string>& data);

    protected:

        bool GetURL(const std::string& url, std::string& output_data);

        static size_t CurlWriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);
};




#endif  // DATA_SOURCE_URL_H__