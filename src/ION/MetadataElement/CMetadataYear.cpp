/*
* Copyright (C) 2013, 2014 Damien Dusha
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

#include "CMetadataYear.h"

#include "Utilities/StringUtilities/StringUtilities.h"

#include <boost/algorithm/string.hpp>
#include <stdio.h>

CMetadataYear::CMetadataYear() :
    CMetadataElement("year"),
    m_year(1900)
{
}


CMetadataYear::~CMetadataYear()
{
}


bool CMetadataYear::ParseData(const std::vector< std::string> &data)
{
    const std::string prefix("<meta xmlns=\"http://www.w3.org/1999/xhtml\" name=\"citation_publication_date\" content=\"");
    const std::string suffix("\" />");

    std::string date;
    bool ok = ParseSingleLine(data, prefix, suffix, date);
    if (!ok)
        return false;

    std::vector<std::string> split;
    boost::algorithm::split(split, date, boost::is_any_of("/"));

    if (split.size() != 3)
        return false;

    ok = Utilities::ParseValue<int>(split[0], m_year);
    if (!ok)
        return false;

    m_year = AdjustYear(m_year);
    return true;
}

std::string CMetadataYear::GetBibtexLine() const
{
    char buffer[1024];
    sprintf(buffer, "year = {%d}", m_year);

    return std::string(buffer);
}

std::string CMetadataYear::GetYear() const
{
    char buffer[1024];
    sprintf(buffer, "%d", m_year);

    return std::string(buffer);
}

int CMetadataYear::AdjustYear(const int year) const
{
    if (year >= 100)
        return year;

    if (year >= 90)
        return year + 1900;

    return year + 2000;
}

