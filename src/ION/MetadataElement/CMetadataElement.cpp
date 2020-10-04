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
*/

#include "CMetadataElement.h"

CMetadataElement::CMetadataElement(const std::string& elementName) : 
        m_elementName(elementName)
{
}

bool CMetadataElement::ParseSingleLine(const CCitationMetadata &metadata,
            ECitationElement element, std::string &out)
{
    if (!metadata.HasElement(element))
        return false;

    out = metadata.GetValue(element);
    return true;
}

std::string CMetadataElement::FormatSingleField(
    const std::string &tag, 
    const std::string &value)
{
    return tag + std::string(" = {") + value + std::string("}");
}

std::string CMetadataElement::FormatSingleField(
    const std::string &tag, 
    const int value)
{
    return tag + std::string(" = {") + std::to_string(value) + std::string("}");
}
