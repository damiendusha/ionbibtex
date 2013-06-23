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

#include "Utilities/IO/CTextFile.h"
#include <iostream>
#include <stdlib.h>
#include <ctype.h>

#include "Publication/CPublication.h"
#include "Publication/CPublicationConference.h"
#include "Publication/CPublicationJournal.h"

std::string GetDataFile(const std::string &location)
{
    if (location.empty())
        return "";

    std::string file = location;

    // Assume a paper number if a digit is given
    if ( isdigit(file[0]))
    {
        file = std::string("http://www.ion.org/search/view_abstract.cfm?jp=p&idno=") + location;
    }

    // Check for a URL
    if (file.find("http://") != std::string::npos || file.find("https://") != std::string::npos)
    {
        std::string command("wget -O site.txt '");
        command += file;
        command += std::string("' > /dev/null");

        int ok = system(command.c_str());
        if (ok != 0)
        {
            std::cerr << "Error getting URL " << file << std::endl;
            return "";
        }

        return "site.txt";
    }

    return file;
}


int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " file.txt" << std::endl;
        return -1;
    }

    std::string file = GetDataFile(argv[1]);

    Utilities::IO::CTextFileReader reader;
    if (!reader.LoadFile(file))
    {
        std::cerr << "Cannot read file \"" << argv[1] << "\"" << std::endl;
        return -1;
    }

    // Get everything from the file
    std::vector<std::string> data;
    reader.GetEntireData(data);

    std::vector<CPublication*> publicationList;
    publicationList.push_back(new CPublicationConference());
    publicationList.push_back(new CPublicationJournal());

    bool found = false;
    for (std::vector<CPublication*>::iterator it = publicationList.begin(); it < publicationList.end(); ++it)
    {
        if ((*it)->ParseData(data))
        {
            found = true;
            std::cout << (*it)->WriteBibTeX();
        }
    }

    if (!found)
    {
        std::cerr << "Unable to parse citation" << std::endl;
    }

    for (unsigned i = 0 ; i < publicationList.size(); ++i)
    {
        delete publicationList[i];
    }

    return 0;
}
