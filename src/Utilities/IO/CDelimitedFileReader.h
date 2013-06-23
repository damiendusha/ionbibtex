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

#ifndef __DELIMITED_FILE_READER_H__
#define __DELIMITED_FILE_READER_H__

#include <string>
#include <vector>


namespace Utilities
{
    namespace IO
    {
        class CDelimitedFileReader
        {
            public:
                
                CDelimitedFileReader();
                virtual ~CDelimitedFileReader();
                
                bool LoadFile(const std::string &filename, unsigned int skipRows = 0);
                
                int GetNumberOfLines() const;
                
                bool GetEntireData(std::vector< std::vector<std::string> > &data) const;

                bool GetLine(unsigned int line, std::vector<std::string> &data) const;
                
                bool GetElement(unsigned int line, unsigned int element, std::string &data) const;
                bool GetElement(unsigned int line, unsigned int element, int &data) const;
                bool GetElement(unsigned int line, unsigned int element, double &data) const;
                
                bool GetColumn(unsigned int line, std::vector<std::string> &data) const;
                
            protected:
                
                std::vector< std::vector<std::string> > m_data;
                
                virtual void ParseLine(const std::string &line) = 0;
        };
    }
}



#endif // __CCSV_READER_H__

