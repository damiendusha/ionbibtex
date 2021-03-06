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

#ifndef CPUBLICATION_H__
#define CPUBLICATION_H__

#include "MetadataElement/CMetadataElement.h"
#include "MetadataElement/CCitationMetadata.h"

class CPublication
{
    public:

        CPublication(const std::string& bibType);
        virtual ~CPublication();

        bool ParseData(const CCitationMetadata &citation_data);

        std::string WriteBibTeX();

    protected:

        std::string m_bibType;
        std::vector<CMetadataElement*> m_metadata;

        std::string WriteBibTeXRecordOpening();
        std::string WriteBibTeXRecordKey();
        std::string WriteBibTeXRecordData();
        std::string WriteBibTeXRecordClosing();
};



#endif  // CPUBLICATION_H__
