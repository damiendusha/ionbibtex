/*
* Copyright (C) 2014 Damien Dusha
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
*/

#include "CMetadataURL.h"
#include <stdio.h>


CMetadataURL::CMetadataURL() :
    CMetadataElement("url")
{
}

CMetadataURL::~CMetadataURL()
{
}


bool CMetadataURL::ParseData(const std::vector< std::string >& data)
{
    std::string prefix("<meta xmlns=\"http://www.w3.org/1999/xhtml\" name=\"citation_abstract_html_url\" content=\"");
    std::string suffix("\" />");

    return ParseSingleLine(data, prefix, suffix, m_url);
}


std::string CMetadataURL::GetBibtexLine() const
{
    char buffer[m_url.size() + 1024];
    sprintf(buffer, "Url = {%s}", m_url.c_str());

    return std::string(buffer);
}



