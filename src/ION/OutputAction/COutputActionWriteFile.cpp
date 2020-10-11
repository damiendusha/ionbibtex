
#include "COutputActionWriteFile.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <string>
#include <boost/filesystem.hpp>

bool COutputActionWriteFile::PerformAction(const std::string& data, 
                                           const std::string& output_filename)
{
    FILE* fd = fopen(output_filename.c_str(), "wt");
    if (!fd) {
        return false;
    }

    fprintf(fd, "%s\n", data.c_str()); 
    fflush(fd);
    fclose(fd);
    return true;
}
