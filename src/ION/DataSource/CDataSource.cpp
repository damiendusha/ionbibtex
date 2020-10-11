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
#include <gflags/gflags.h>

#include <iostream>

DEFINE_string(url, "", "URL of ION website to parse");
DEFINE_string(article_id, "", "Document ID of the ION paper to parse");

CDataSource::Options CDataSource::Options::GetFromFlags()
{
    Options options;
    options.url = FLAGS_url;
    options.article_id = FLAGS_article_id;
    return options;
}

CDataSource::CDataSource(const std::string& resourceName)
    : m_resourceName(resourceName)
{
}

std::unique_ptr<CDataSource> CDataSource::GetDataSource(const Options &options)
{
    // Assume a paper number if a digit is given
    if (!options.article_id.empty())
    {
        return std::make_unique<CDataSourceURL>(
            std::string("https://www.ion.org/publications/abstract.cfm?articleID=") 
            + options.article_id);
    }

    // Check for a URL
    if (!options.url.empty())
    {
        return std::make_unique<CDataSourceURL>(options.url);
    }

    return nullptr;
}

bool CDataSource::ParseDataSource(std::string& data)
{
    return InternalParseDataSource(data);
}
