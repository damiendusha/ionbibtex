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


#include "Publication/CPublication.h"
#include "Publication/CPublicationConference.h"
#include "Publication/CPublicationJournal.h"

#include "DataSource/CDataSource.h"

#include "OutputAction/COutputAction.h"
#include "OutputAction/COutputActionConsole.h"
#include "OutputAction/COutputActionExecuteProgram.h"

#include "MetadataElement/CMetadataParser.h"

#include <iostream>
#include <memory>
#include <cstdlib>
#include <cctype>
#include <filesystem>


std::string GetJabrefImportPath(const std::string &this_binary)
{
    const auto path = std::filesystem::canonical(this_binary);
    return path.parent_path().append("jabref-import.sh");
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " file.txt" << std::endl;
        return -1;
    }

    std::unique_ptr<CDataSource> source = CDataSource::GetDataSource(argv[1]);
    if (!source)
    {
        std::cerr << "Unable to recognise source" << std::endl;
        return 1;
    }

    std::string data;
    if (!source->ParseDataSource(data))
    {
        std::cout << "Could not parse data" << std::endl;
        return 2;
    }
    
    CMetadataParser parser;
    CCitationMetadata metadata = parser.ParseFromHtml(data);

    std::vector<std::unique_ptr<CPublication>> publicationList;
    publicationList.push_back(std::make_unique<CPublicationConference>());
    publicationList.push_back(std::make_unique<CPublicationJournal>());

    bool found = false;
    std::string out;
    for (auto& publication: publicationList)
    {
        if (publication->ParseData(metadata))
        {
            found = true;
            out = publication->WriteBibTeX();
        }
    }

    if (!found)
    {
        std::cerr << "Unable to parse citation" << std::endl;
    }
    else
    {
        auto program_action = std::make_unique<COutputActionExecuteProgram>();
        const std::string jabref_path = GetJabrefImportPath(argv[0]);
        std::cout << "Exporting to " << jabref_path << std::endl;
        bool ok = program_action->PerformAction(out, jabref_path);

        if (!ok)
        {
            std::cerr << "Failed to import into JabRef" << std::endl;
        }

        /*
        auto action_console = std::make_unique<COutputActionConsole>();
        action_console->PerformAction(out, "");
        */
    }

    return 0;
}
