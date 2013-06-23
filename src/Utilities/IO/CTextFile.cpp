/*
* Copyright (C) 2008, 2009, 2013 Damien Dusha
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

#include "CTextFile.h"

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/lexical_cast.hpp>

#include <fstream>

namespace Utilities
{
    namespace IO
    {
        bool CTextFileReader::LoadFile(const std::string &filename, unsigned int skipRows, bool skipBlankRows, bool trimWhitespace)
        {
            // Open the file
            std::ifstream input;
            input.open(filename.c_str(), std::ifstream::in);
            if(!input.is_open())
                return false;
            
            unsigned int skipRowCount = 0;
            
            // Read until EOF
            while (!input.eof())
            {
                std::string line;
                getline(input, line);
                
                if (skipRowCount >= skipRows)
                {
                    // Check if the row is blank
                    std::string trimmed_line = boost::algorithm::trim_copy(line);
                    if (skipBlankRows && (trimmed_line == ""))
                        continue;
                    
                    // Store the line
                    if (trimWhitespace)
                    {
                        m_data.push_back(trimmed_line);
                    }
                    else
                    {
                        m_data.push_back(line);
                    }
                }
                else
                {
                    skipRowCount++;
                }
            }
            
            input.close();
            return true;
        }
                
        int CTextFileReader::GetNumberOfLines() const
        {
            return m_data.size();
        }
        
        bool CTextFileReader::GetEntireData(std::vector<std::string> &data) const
        {
            data = m_data;
            return true;
        }
        
        bool CTextFileReader::GetLine(unsigned int line, std::string &data) const
        {
            if (line >= m_data.size())
                return false;
            
            data = m_data[line];
            return true;
        }    
    }
}
