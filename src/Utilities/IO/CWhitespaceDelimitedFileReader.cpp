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

#include "CWhitespaceDelimitedFileReader.h"

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

namespace Utilities
{
    namespace IO
    {
        void CWhitespaceDelimitedFileReader::ParseLine(const std::string &line)
        {
            // Split the line based on commas
            std::vector<std::string> split;
            boost::algorithm::split(split, line, boost::is_any_of("\t "));
            
            m_data.push_back(split);
        }
    }
}
