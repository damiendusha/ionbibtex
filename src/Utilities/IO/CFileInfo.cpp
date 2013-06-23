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

#include "CFileInfo.h"

#include <sys/stat.h>

namespace Utilities
{
    namespace IO
    {
        CFileInfo::CFileInfo(const std::string &filename)
        {
            SetFilename(filename);
        }
                
        void CFileInfo::SetFilename(const std::string &filename)
        {
            m_fullPathName = filename;
            m_filename = filename;
            
            size_t lastSlash = m_filename.find_last_of("/");
            if(lastSlash == m_filename.npos)
            {
                // No slash found
                m_directory = "";
                m_basename = m_fullPathName; 
            }
            else
            {
                m_directory = m_fullPathName.substr(0, lastSlash);
                m_filename  = m_fullPathName.substr(lastSlash + 1);
                m_basename  = m_fullPathName.substr(lastSlash + 1);
            }
            
            // Find the last dot (if any) in basename
            size_t lastDot = m_basename.find_last_of(std::string("."));
            if (lastDot == m_basename.npos || lastDot == 0 || m_basename == "..")
            {
                // Dot not found, or file is a hidden file, or filename is ".."
                return;
            }
            
            // Otherwise, assign the extension
            m_extension = m_basename.substr(lastDot);
            m_basename = m_basename.substr(0, lastDot);
            
        }
        
        std::string CFileInfo::GetFullPathName() const
        {
            return m_fullPathName;
        }
        
        std::string CFileInfo::GetFilename() const
        {
            return m_filename;
        }
        
        std::string CFileInfo::GetDirectory() const
        {
            return m_directory;
        }
        
        std::string CFileInfo::GetBasename() const
        {
            return m_basename;
        }
        
        std::string CFileInfo::GetExtension() const
        {
            return m_extension;
        }
        
        bool CFileInfo::GetFileSize(size_t &size) const
        {
            struct stat fileStat; 
            int err = stat( m_fullPathName.c_str(), &fileStat );
            if (0 != err)
                return false;
            
            size = fileStat.st_size; 
            return true;
        }
        
        bool CFileInfo::FileExists() const
        {
            struct stat fileStat; 
            int err = stat( m_fullPathName.c_str(), &fileStat );
            if (0 != err)
                return false;
            
            return true;
        }
    }
};


