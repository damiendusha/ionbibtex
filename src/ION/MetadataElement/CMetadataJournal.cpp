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
*/

#include "CMetadataJournal.h"
#include <stdio.h>


CMetadataJournal::CMetadataJournal() :
    CMetadataElement("journal")
{
}


CMetadataJournal::~CMetadataJournal()
{
}


std::string CMetadataJournal::GetBibtexLine() const
{
    char buffer[m_journal.size() + 1024];
    sprintf(buffer, "title = {%s}", m_journal.c_str());

    return std::string(buffer);
}


bool CMetadataJournal::ParseData(const std::vector< std::string> &data)
{
    const std::string prefix("<meta name=\"citation_journal_title\" content=\"");
    const std::string suffix("\">");
    
    return ParseSingleLine(data, prefix, suffix, m_journal);
}



