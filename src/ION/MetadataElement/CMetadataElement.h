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

#ifndef METADATA_ELEMENT_H
#define METADATA_ELEMENT_H

#include "CCitationMetadata.h"

#include <string>
#include <vector>

class CMetadataElement
{
    public:

        CMetadataElement(const std::string &elementName);
        virtual ~CMetadataElement() {}
        
        virtual bool ParseData(const CCitationMetadata &metadata) = 0;

        virtual std::string GetBibtexLine() const = 0;

        const std::string& GetElementName() const
        {
            return m_elementName;
        }

    protected:

        std::string m_elementName;

        static bool ParseSingleLine(const CCitationMetadata &metadata,
            ECitationElement element, std::string &out);
        
        static std::string FormatSingleField(const std::string &tag, 
                                             const std::string &value);
        
        static std::string FormatSingleField(const std::string &tag, 
                                             int value);
};




#endif  // METADATA_ELEMENT_H
