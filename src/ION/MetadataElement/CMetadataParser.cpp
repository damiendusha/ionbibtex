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

#include "CMetadataParser.h"
#include "gumbo.h"

#include <iostream>

CCitationMetadata CMetadataParser::ParseFromHtml(const std::string &raw_data)
{
    GumboOutput* output = gumbo_parse(raw_data.c_str());
    SearchForMetadata(output->root);
    gumbo_destroy_output(&kGumboDefaultOptions, output);

    return metadata_;
}

void CMetadataParser::SearchForMetadata(GumboNode* node)
{
    if (node->type != GUMBO_NODE_ELEMENT)
        return;

    if (node->v.element.tag == GUMBO_TAG_META) {
        const auto optional_attribute = MaybeGetAttributeData(node);
        if (optional_attribute) {
            metadata_.citation_data.insert(optional_attribute.value());
        }
    }

    GumboVector* children = &node->v.element.children;
    for (unsigned int i = 0; i < children->length; ++i)
    {
        SearchForMetadata(static_cast<GumboNode*>(children->data[i]));
    }
}

std::optional<CCitationMetadata::CitationPair> CMetadataParser::MaybeGetAttributeData(GumboNode* node) const
{
    GumboAttribute* citation_name = gumbo_get_attribute(
            &node->v.element.attributes, "name");
    GumboAttribute* citation_content = gumbo_get_attribute(
            &node->v.element.attributes, "content");
    if (citation_name == nullptr || citation_content == nullptr)
        return std::nullopt;

    const auto it = allowed_tags_.find(citation_name->value);
    if (it == allowed_tags_.end())
        return std::nullopt;

    return std::make_pair(it->second, std::string(citation_content->value));
}
