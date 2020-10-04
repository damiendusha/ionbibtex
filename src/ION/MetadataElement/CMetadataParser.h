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

#ifndef METADATA_PARSER_H
#define METADATA_PARSER_H

#include "CCitationMetadata.h"

#include "gumbo.h"

#include <string>
#include <map>
#include <utility>
#include <optional>

class CMetadataParser
{
  public:
    CMetadataParser() {}

    CCitationMetadata ParseFromHtml(const std::string &raw_data);

  private:
    // Mapping of metadata tags to fields of interest.
    const std::map<std::string, ECitationElement> allowed_tags_ = {
        {"citation_abstract", ECitationElement::kAbstract},
        {"citation_author", ECitationElement::kAuthor},
        {"citation_firstpage", ECitationElement::kFirstPage},
        {"citation_lastpage", ECitationElement::kLastPage},
        {"citation_title",  ECitationElement::kArticleTitle},
        {"citation_conference_title",  ECitationElement::kConferenceTitle},
        {"citation_journal_title",  ECitationElement::kJournalTitle},
        {"citation_doi",  ECitationElement::kDoi},
        {"citation_volume", ECitationElement::kVolume},
        {"citation_issue", ECitationElement::kIssue},
        {"citation_issn", ECitationElement::kIssn},
        {"citation_abstract_html_url", ECitationElement::kAbstractUrl},
        {"citation_publication_date", ECitationElement::kPublicationDate},
    };

    CCitationMetadata metadata_;

    void SearchForMetadata(GumboNode* node);

    std::optional<CCitationMetadata::CitationPair> MaybeGetAttributeData(
        GumboNode* node) const;
};

#endif  // METADATA_PARSER_H
