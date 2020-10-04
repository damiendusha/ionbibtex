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

#ifndef METADATA_VOLUME_H
#define METADATA_VOLUME_H

#include "CMetadataElement.h"

class CMetadataVolume : public CMetadataElement 
{
    public:

        CMetadataVolume();
        virtual ~CMetadataVolume();

        virtual bool ParseData(const CCitationMetadata &metadata);

        virtual std::string GetBibtexLine() const;

    protected:

        std::string m_volume;


};

#endif  // METADATA_VOLUME_H
