/*
* Copyright (C) 2013, 2014 Damien Dusha
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

#include "CPublicationConference.h"

#include "MetadataElement/CMetadataAbstract.h"
#include "MetadataElement/CMetadataAuthor.h"
#include "MetadataElement/CMetadataConference.h"
#include "MetadataElement/CMetadataPages.h"
#include "MetadataElement/CMetadataYear.h"
#include "MetadataElement/CMetadataTitle.h"
#include "MetadataElement/CMetadataURL.h"


CPublicationConference::CPublicationConference()
    : CPublication("inproceedings")
{
    m_metadata.push_back(new CMetadataTitle());
    m_metadata.push_back(new CMetadataAuthor());
    m_metadata.push_back(new CMetadataConference());
    m_metadata.push_back(new CMetadataPages());
    m_metadata.push_back(new CMetadataYear());
    m_metadata.push_back(new CMetadataAbstract());
    m_metadata.push_back(new CMetadataURL());
}

CPublicationConference::~CPublicationConference()
{
}
