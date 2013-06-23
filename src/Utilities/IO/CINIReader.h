/*
* Copyright (C) 2008-2009 Damien Dusha
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

#ifndef __C_INI_READER_H__
#define __C_INI_READER_H__

#include <string>
#include <map>
#include <fstream>

namespace Utilities
{
    namespace IO
    {
        class CINIReader
        {
            public:
                
                CINIReader();
                ~CINIReader();
                
                bool LoadINIFile(const std::string &filename);
                bool GetAttribute(const std::string &section, const std::string &attribute, std::string &output) const;
                bool GetAttribute(const std::string &section, const std::string &attribute, int &output) const;
                bool GetAttribute(const std::string &section, const std::string &attribute, bool &output) const;
                bool GetAttribute(const std::string &section, const std::string &attribute, double &output) const;
                
                void Dump(std::ostream &stream);
                
            protected:
                
                typedef std::map<std::string, std::string> StringMap;
                typedef std::map<std::string, StringMap> MapStringMap;
                
                // Each section is a string map
                MapStringMap m_iniSections;
                bool m_fileLoaded;
        
                void ParseFile(std::ifstream &stream);
                
                bool IsComment(const std::string &line) const;
                bool IsSection(const std::string &line) const;
                std::string GetSection(const std::string &line) const;
                bool ExtractAttribute(const std::string &line, std::string &attribute, std::string &value) const;
                
                bool HasSection(const std::string &section) const;
                bool HasSection(const std::string &section, MapStringMap::const_iterator &it) const;
                
                bool HasAttribute(const std::string &section, const std::string &attribute) const;
                bool HasAttribute(const std::string &section, const std::string &attribute, StringMap::const_iterator &map_it) const;
                bool HasAttribute(const StringMap &map, const std::string &attribute, StringMap::const_iterator &it) const;
                bool HasAttribute(const MapStringMap::const_iterator &it, const std::string &attribute, StringMap::const_iterator &map_it) const;
        };
    };
};

#endif // __C_INI_READER_H__
