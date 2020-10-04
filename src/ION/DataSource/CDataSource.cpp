/*
* Copyright (C) 2013, 2014, 2020 Damien Dusha
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

#include "CDataSource.h"
#include "CDataSourceURL.h"

#include <boost/algorithm/string.hpp>

#include <iostream>

CDataSource::CDataSource(const std::string& resourceName)
    : m_resourceName(resourceName)
{
}

CDataSource::~CDataSource()
{
}

std::unique_ptr<CDataSource> CDataSource::GetDataSource(const std::string& location)
{
    if (location.empty())
        return NULL;

    std::string file = location;

    // Assume a paper number if a digit is given
    if (isdigit(file[0]))
    {
        return std::make_unique<CDataSourceURL>(std::string("https://www.ion.org/publications/abstract.cfm?articleID=") + location);
    }

    // Check for a URL
    if (file.find("http://") != std::string::npos || file.find("https://") != std::string::npos)
    {
        return std::make_unique<CDataSourceURL>(file);
    }

    return nullptr;
}

bool CDataSource::ParseDataSource(std::string& data)
{
    return InternalParseDataSource(data);
}
