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
*/

#include "CMetadataConference.h"
#include <stdio.h>


CMetadataConference::CMetadataConference() :
    CMetadataElement("conference")
{
}


CMetadataConference::~CMetadataConference()
{
}


bool CMetadataConference::ParseData(const CCitationMetadata &metadata)
{
    constexpr auto kElement = ECitationElement::kConferenceTitle;
    if (metadata.citation_data.count(kElement) != 1)
        return false;

    m_conference = metadata.citation_data.find(kElement)->second;
    return true;
}


std::string CMetadataConference::GetBibtexLine() const
{
    char buffer[m_conference.size() + 1024];
    sprintf(buffer, "booktitle = {%s}", m_conference.c_str());
    
    return std::string(buffer);
}



