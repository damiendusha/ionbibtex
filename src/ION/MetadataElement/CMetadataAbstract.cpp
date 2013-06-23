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

#include "CMetadataAbstract.h"
#include <stdio.h>
#include <iostream>

CMetadataAbstract::CMetadataAbstract() :
    CMetadataElement("abstract")
{

}

CMetadataAbstract::~CMetadataAbstract()
{

}

bool CMetadataAbstract::ParseData(const std::vector< std::string >& data)
{
    // Options:
    // "<tr><td class=\"title\" align=\"right\" valign=\"top\">Abstract:</td><td class=\"text\">");
    // "<tr><td align=\"right\" valign=\"top\" class=\"title\">Abstract:</td><td class=\"text\">");
    std::string prefix("\">Abstract:</td><td class=\"text\">");
    std::string suffix("</td></tr>");
    
    int start_line = FirstLineThatContainsString(data, prefix);
    int end_line   = FirstLineThatContainsString(data, suffix, start_line);
    
    if (start_line == -1 || end_line == -1)
        return false;
            
    if (start_line == end_line)
    {
        std::string abstract;
        bool ok = ParseSingleLine(data, prefix, suffix, abstract);
        if (!ok)
            return false;
        
        m_abstract.push_back(abstract);
        return true;
    }
    
    std::string abstract;
    bool ok = StripPrefix(data[start_line], prefix, abstract);
    if (!ok)
        return false;
    
    m_abstract.push_back(abstract);
    
    for (int i = start_line + 1; i < end_line ; ++i)
    {
        m_abstract.push_back(data[i]);
    }
    
    ok = StripSuffix(data[end_line], suffix, abstract);
    if (!ok)
        return false;
    
    m_abstract.push_back(abstract);
    
    return true;
}

std::string CMetadataAbstract::GetBibtexLine() const
{
    if (m_abstract.size() == 0)
        return "";
    
    // First line
    std::string output("abstract = {");
    output += std::string(m_abstract[0]);
    
    // Middle lines
    for (unsigned int i = 1 ; i < m_abstract.size() - 1; ++i)
    {
        output += std::string("  ") + m_abstract[i];
    }
    
    // Last line
    output += std::string("  ") + m_abstract[m_abstract.size() - 1] + std::string("}");
    return output;
}

