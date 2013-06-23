
#include "COutputActionExecuteProgram.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

COutputActionExecuteProgram::COutputActionExecuteProgram()
{
}

COutputActionExecuteProgram::~COutputActionExecuteProgram()
{
}

bool COutputActionExecuteProgram::PerformAction(const std::string& data, const std::string& actionArgument)
{
    int return_code = -1;

    char prefix[128];
    strcpy(prefix, "");

    char* filename = tempnam(NULL, prefix);

    FILE* fd = fopen(filename, "wt");
    if (fd)
    {
        fprintf(fd, "%s\n", data.c_str()); 
        fflush(fd);
        fclose(fd);

        std::string command = actionArgument + std::string(" ") + std::string(filename);
        return_code = system(command.c_str());
    }

    free(filename);
    return return_code == 0;
}


