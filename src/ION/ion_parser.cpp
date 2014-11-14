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


#include <iostream>
#include <stdlib.h>
#include <ctype.h>

#include "Publication/CPublication.h"
#include "Publication/CPublicationConference.h"
#include "Publication/CPublicationJournal.h"

#include "DataSource/CDataSource.h"

#include "OutputAction/COutputAction.h"
#include "OutputAction/COutputActionConsole.h"
#include "OutputAction/COutputActionExecuteProgram.h"


int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " file.txt" << std::endl;
        return -1;
    }

    CDataSource* source = CDataSource::GetDataSource(argv[1]);
    if (!source)
    {
        std::cerr << "Unable to recognise source" << std::endl;
        return 1;
    }

    std::vector<std::string> data;
    if (!source->ParseDataSource(data))
    {
        delete source;
        return 2;
    }

    delete source;

    std::vector<CPublication*> publicationList;
    publicationList.push_back(new CPublicationConference());
    publicationList.push_back(new CPublicationJournal());

    bool found = false;
    std::string out;
    for (std::vector<CPublication*>::iterator it = publicationList.begin(); it < publicationList.end(); ++it)
    {
        if ((*it)->ParseData(data))
        {
            found = true;
            out = (*it)->WriteBibTeX();
        }
    }

    if (!found)
    {
        std::cerr << "Unable to parse citation" << std::endl;
    }
    else
    {
        COutputAction* action = new COutputActionExecuteProgram();
        bool ok = action->PerformAction(out, "./jabref-import.sh");
        delete action;

        if (!ok)
        {
            std::cerr << "Failed to import into JabRef" << std::endl;
        }

        /*
        COutputAction* action = new COutputActionConsole();
        action->PerformAction(out, "");
        delete action;
        */
    }

    for (unsigned int i = 0 ; i < publicationList.size(); ++i)
    {
        delete publicationList[i];
    }

    return 0;
}
