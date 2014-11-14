/*
* Copyright (C) 2014 Damien Dusha
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

#ifndef METADATA_URL_H
#define METADATA_URL_H

#include "CMetadataElement.h"

class CMetadataURL : public CMetadataElement 
{
    public:

        CMetadataURL();
        virtual ~CMetadataURL();

        virtual bool ParseData(const std::vector< std::string> &data);

        virtual std::string GetBibtexLine() const;

    protected:

        std::string m_url;


};

#endif  // METADATA_URL_H