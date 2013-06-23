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

#ifndef TEXT_FILE_READER_H
#define TEXT_FILE_READER_H

#include <vector>
#include <string>


namespace Utilities
{
    namespace IO
    {
        class CTextFileReader
        {
            public:
                
                CTextFileReader() {}
                virtual ~CTextFileReader() {}
                
                bool LoadFile(const std::string &filename, unsigned int skipRows = 0, bool skipBlankRows = false, bool trimWhitespace = true);
                
                int GetNumberOfLines() const;
                
                bool GetEntireData(std::vector<std::string> &data) const;

                bool GetLine(unsigned int line, std::string &data) const;
                
                
            protected:
                
                std::vector<std::string> m_data;
        };
    };
};

#endif  // TEXT_FILE_READER_H
