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

#include "CMetadataElement.h"

CMetadataElement::CMetadataElement(const std::string& elementName) : 
    m_elementName(elementName)
{
}


size_t CMetadataElement::FirstLineThatContainsString(const std::vector< std::string> &data, const std::string &needle, int start_line) const
{
    for (size_t i = start_line; i < data.size() ; ++i)
    {
        if (data[i].find(needle) != std::string::npos)
            return i;
    }

    return -1;
}

std::vector<size_t> CMetadataElement::LinesThatContainsString(const std::vector< std::string> &data, const std::string &needle, int start_line) const
{
    std::vector<size_t> lines;
    for (size_t i = start_line; i < data.size() ; ++i)
    {
        if (data[i].find(needle) != std::string::npos)
            lines.push_back(i);
    }
    
    return lines;
}

bool CMetadataElement::StripPrefix(const std::string& in, const std::string& prefix, std::string& out) const
{
    // Strip the prefix and suffix
    size_t first_index = in.find(prefix);

    if (first_index == std::string::npos)
        return false;

    // Store the string
    out = in.substr(first_index + prefix.length());
    return true;
}

bool CMetadataElement::StripSuffix(const std::string& in, const std::string& suffix, std::string& out) const
{
    size_t last_index = in.rfind(suffix);
    
    if (last_index == std::string::npos)
        return false;

    out = in.substr(0, last_index);
    return true;
}

bool CMetadataElement::ParseSingleLine(const std::vector<std::string> &data, const std::string& prefix, const std::string& suffix, std::string& out) const
{
    // Find the key
    int element = FirstLineThatContainsString(data, prefix);
    if (element < 0)
        return false;
    
    // Get the line
    std::string line = data[element];
    
    return ParseSingleLine(line, prefix, suffix, out);
}
    
    
bool CMetadataElement::ParseSingleLine(const std::string &line, const std::string &prefix, const std::string &suffix, std::string &out) const
{
    std::string stripped_prefix;
    
    // Remove the parts of non-interest
    bool ok = true;
    ok = ok && StripPrefix(line, prefix, stripped_prefix);
    ok = ok && StripSuffix(stripped_prefix, suffix, out);
    
    return ok;
}

std::string CMetadataElement::GetElementName() const
{
    return m_elementName;
}

