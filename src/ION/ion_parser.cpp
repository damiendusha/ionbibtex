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
#include "OutputAction/COutputActionWriteFile.h"

#include "MetadataElement/CMetadataParser.h"

#include <gflags/gflags.h>

#include <iostream>
#include <memory>
#include <cstdlib>
#include <cctype>
#include <filesystem>

DEFINE_bool(output_console, false, "Output bibtex to console");
DEFINE_string(output_filename, "", "Output bibtex to the given filename");


int main(int argc, char **argv)
{
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    std::unique_ptr<CDataSource> source = CDataSource::GetDataSource(
        CDataSource::Options::GetFromFlags());
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
    std::string output_bibtex;
    for (auto& publication: publicationList)
    {
        if (publication->ParseData(metadata))
        {
            found = true;
            output_bibtex = publication->WriteBibTeX();
        }
    }

    if (!found)
    {
        std::cerr << "Unable to parse citation" << std::endl;
    }
    else
    {
        if (FLAGS_output_console)
        {
            COutputActionConsole console;
            console.PerformAction(output_bibtex, std::string());
        }

        std::string output_filename = FLAGS_output_filename;
        if (!output_filename.empty())
        {
            COutputActionWriteFile write_file;
            write_file.PerformAction(output_bibtex, output_filename);
        }
    }

    return 0;
}
