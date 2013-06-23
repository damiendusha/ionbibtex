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

#ifndef METADATA_ELEMENT_H
#define METADATA_ELEMENT_H

#include <string>
#include <vector>

class CMetadataElement
{
    public:

        CMetadataElement(const std::string &elementName);
        virtual ~CMetadataElement() {}

        virtual bool ParseData(const std::vector<std::string> &data) = 0;

        virtual std::string GetBibtexLine() const = 0;

        std::string GetElementName() const;

    protected:

        std::string m_elementName;

        size_t FirstLineThatContainsString(const std::vector< std::string> &data, const std::string &needle, int start_line = 0) const;
        std::vector<size_t> LinesThatContainsString(const std::vector< std::string> &data, const std::string &needle, int start_line = 0) const;
 
        bool StripPrefix(const std::string &in, const std::string &prefix, std::string &out) const;
        bool StripSuffix(const std::string &in, const std::string &suffix, std::string &out) const;
 
        bool ParseSingleLine(const std::vector<std::string> &data, const std::string &prefix, const std::string &suffix, std::string &out) const;
        bool ParseSingleLine(const std::string &line, const std::string &prefix, const std::string &suffix, std::string &out) const;
};




#endif  // METADATA_ELEMENT_H
