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

#include "CDelimitedFileReader.h"

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include <fstream>


namespace Utilities
{
    namespace IO
    {
        CDelimitedFileReader::CDelimitedFileReader()
        {
        }
        
        CDelimitedFileReader::~CDelimitedFileReader()
        {
        }
        
                
        bool CDelimitedFileReader::LoadFile(const std::string &filename, unsigned int skipRows)
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
                    ParseLine(line);
                else
                    skipRowCount++;
            }
            
            input.close();
            return true;
        }
                
        int CDelimitedFileReader::GetNumberOfLines() const
        {
            return m_data.size();
        }
        
                
        bool CDelimitedFileReader::GetEntireData(std::vector< std::vector<std::string> > &data) const
        {
            data = m_data;
            return true;
        }
        
        bool CDelimitedFileReader::GetLine(unsigned int line, std::vector<std::string> &data) const
        {
            if (line >= m_data.size())
                return false;
            
            data = m_data[line];
            return true;
        }
        
                
        bool CDelimitedFileReader::GetElement(unsigned int line, unsigned int element, std::string &data) const
        {
            std::vector<std::string> lineData;
            if( !GetLine(line, lineData))
            
            if (element >= lineData.size())
                return false;
            
            data = lineData[element];
            return true;
        }
        
        bool CDelimitedFileReader::GetElement(unsigned int line, unsigned int element, int &data) const
        {
            std::string rawElement;
            if ( !GetElement(line, element, rawElement))
                return false;
            
            try
            {
                data = boost::lexical_cast<int>(rawElement);
            }
            catch (...)
            {
                return false;
            }
            
            return true;
        }
        
        bool CDelimitedFileReader::GetElement(unsigned int line, unsigned int element, double &data) const
        {
            std::string rawElement;
            if ( !GetElement(line, element, rawElement))
                return false;
            
            try
            {
                data = boost::lexical_cast<double>(rawElement);
            }
            catch (...)
            {
                return false;
            }
            
            return true;
        }
        
        bool CDelimitedFileReader::GetColumn(unsigned int column, std::vector<std::string> &data) const
        {
            data.clear();
            data.resize(GetNumberOfLines());
            for (int i = 0 ; i < GetNumberOfLines() ; ++i)
            {
                std::string element;
                if (GetElement(i, column, element))
                {
                    data[i] = element;
                }
                else
                {
                    data.clear();
                    return false;
                }
            }
            
            return true; 
        }
        
    }
}

