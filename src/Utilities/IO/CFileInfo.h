/*
* Copyright (C) 2008, 2009, 2013 Damien Dusha
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

#ifndef __CFILENAME_H__
#define __CFILENAME_H__

#include <string>
#include <stdlib.h>

namespace Utilities
{
    namespace IO
    {
        class CFileInfo
        {
            public:
                
                CFileInfo(const std::string &fullPathName);
                
                void SetFilename(const std::string &fullPathName);
            
                std::string GetFullPathName() const;
                std::string GetFilename() const;
                std::string GetDirectory() const;
                std::string GetBasename() const;
                std::string GetExtension() const;
                
                bool GetFileSize(size_t &size) const;
                bool FileExists() const;
                
            private:
                
                std::string m_fullPathName;
                std::string m_filename;
                std::string m_directory;
                std::string m_basename;
                std::string m_extension;
                
        };
    };
};

#endif // __CFILENAME_H__

