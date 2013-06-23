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

#ifndef __CCSV_READER_H__
#define __CCSV_READER_H__

#include "CDelimitedFileReader.h"

#include <string>
#include <vector>


namespace Utilities
{
    namespace IO
    {
        class CWhitespaceDelimitedFileReader : public CDelimitedFileReader
        {
            public:
                
                CWhitespaceDelimitedFileReader() {}
                ~CWhitespaceDelimitedFileReader() {}
                     
            protected:
                
                virtual void ParseLine(const std::string &line);
        };
    }
}



#endif // __CCSV_READER_H__

