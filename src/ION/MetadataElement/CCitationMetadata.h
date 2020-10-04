/*
* Copyright (C) 2020 Damien Dusha
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
* 
*/

#ifndef CITATION_METADATA_H
#define CITATION_METADATA_H

#include <string>
#include <map>
#include <utility>
#include <vector>

enum class ECitationElement {
    kAbstract,
    kAuthor,
    kFirstPage,
    kLastPage,
    kArticleTitle,
    kConferenceTitle,
    kJournalTitle,
    kVolume,
    kIssue,
    kDoi,
    kAbstractUrl,
    kPublicationDate,
    kIssn,
};


struct CCitationMetadata {
    using CitationPair = std::pair<ECitationElement, std::string>;

    // Stored citation data of interest.
    std::multimap<ECitationElement, std::string> citation_data;

    bool HasElement(ECitationElement element) const;

    std::string GetValue(ECitationElement element) const;

    std::vector<std::string> GetAllValues(ECitationElement element) const;
};

#endif  // CITATION_METADATA_H
