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

#include "CINIReader.h"

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include <iostream>
#include "./../StringUtilities/StringUtilities.h"

namespace Utilities
{
    namespace IO
    {
                
        CINIReader::CINIReader() :
                m_fileLoaded(false)
        {
        }
        
        CINIReader::~CINIReader()
        {
        }
        
        bool CINIReader::LoadINIFile(const std::string &filename)
        {
            std::ifstream stream(filename.c_str(), std::ifstream::in);
            if (!stream.is_open())
                return false;
            
            ParseFile(stream);
            
            stream.close();
            m_fileLoaded = true;
            return true;
        }
        
        bool CINIReader::GetAttribute(const std::string &section, const std::string &attribute, std::string &output) const
        {
            if (!m_fileLoaded)
                return false;
            
            StringMap::const_iterator it;
            if (!HasAttribute(section, attribute, it))
                return false;
            
            output = it->second;
        
            return true;
        }
        
        bool CINIReader::GetAttribute(const std::string &section, const std::string &attribute, int &output) const
        {
            std::string rawData;
            if (!GetAttribute(section, attribute, rawData))
                return false;
            
            // Parse the string as an integer
            try
            {
                output = boost::lexical_cast<int>(rawData);
            }
            catch (boost::bad_lexical_cast)
            {
                return false;
            }
            
            // Parse was successful
            return true;
        }
        
        bool CINIReader::GetAttribute(const std::string &section, const std::string &attribute, double &output) const
        {
            std::string rawData;
            if (!GetAttribute(section, attribute, rawData))
                return false;
            
            // Parse the string as a double
            try
            {
                output = boost::lexical_cast<double>(rawData);
            }
            catch (boost::bad_lexical_cast)
            {
                return false;
            }
            
            // Parse was successful
            return true;
        }
         
        
        bool CINIReader::GetAttribute(const std::string &section, const std::string &attribute, bool &output) const
        {
            std::string rawData;
            if (!GetAttribute(section, attribute, rawData))
                return false;
            
            return Utilities::ParseBool(rawData, output);
        }
        
        
        void CINIReader::ParseFile(std::ifstream &stream)
        {
            if (m_fileLoaded)
                m_iniSections.clear();
            
            std::string section = "";
            bool sectionAssigned = false;
            
            while( !stream.eof() )
            {
                std::string line;
                std::getline(stream, line);
                
                boost::trim(line);
                
                if (line.empty())
                    continue;
                
                if (IsComment(line))
                    continue;
                
                if (IsSection(line))
                {
                    section = GetSection(line);
                    sectionAssigned = true;
                    continue;
                }
                
                // Attributes must be assigned to a section - ignore any not in a section
                if (!sectionAssigned)
                    continue;
                
                std::string attribute;
                std::string value;
                if( !ExtractAttribute(line, attribute, value) )
                    continue;
                
                // Get the section
                StringMap sectionMap;
                MapStringMap::const_iterator it;
                if (HasSection(section, it))
                    sectionMap = it->second;
                
                // Set the attribute, assign to the section
                sectionMap[attribute] = value;
                m_iniSections[section] = sectionMap;
            }
        }
        
        bool CINIReader::IsComment(const std::string &line) const
        {
            if (line[0] == '#' || line[0] == ';')
                return true;
            
            return false;
        }
        
        bool CINIReader::IsSection(const std::string &line) const
        {
            if (line.length() < 2)
                return false;
            
            if (line[0] == '[' && line[line.length()-1] == ']')
                return true;
            
            return false;
        }
        
        std::string CINIReader::GetSection(const std::string &line) const
        {
            return std::string(line, 1, line.length() - 2);
        }
        
        bool CINIReader::ExtractAttribute(const std::string &line, std::string &attribute, std::string &value) const
        {
            size_t position = line.find_first_of("=");
            
            // Equals not found
            if (position == std::string::npos)
                return false;
            
            // Equals at the start of the line
            if (position == 0)
                return false;
            
            // Special Case: Allow an empty value string
            if (position == line.length() - 1)
            {
                attribute.assign(line, 0, position);
                value = "";
                return true;
            }
            
            attribute.assign(line, 0, position);
            boost::trim(attribute);
            
            value.assign(line, position + 1, line.length() - position - 1);
            boost::trim(value);
            
            return true;
        }
        
        bool CINIReader::HasSection(const std::string &section) const
        {
            MapStringMap::const_iterator it;
            return HasSection(section, it);
        }
        
        bool CINIReader::HasSection(const std::string &section, MapStringMap::const_iterator &it) const
        {
            it = m_iniSections.find(section);
            if (it == m_iniSections.end())
                return false;
            
            return true;
        }
        
        bool CINIReader::HasAttribute(const std::string &section, const std::string &attribute) const
        {
            StringMap::const_iterator it;
            return HasAttribute(section, attribute, it);
        }
        
        bool CINIReader::HasAttribute(const std::string &section, const std::string &attribute, StringMap::const_iterator &map_it) const
        {
            MapStringMap::const_iterator it;
            if (!HasSection(section, it))
                return false;
            
            return HasAttribute(it, attribute, map_it);
        }
        
        bool CINIReader::HasAttribute(const MapStringMap::const_iterator &it, 
                                    const std::string &attribute, StringMap::const_iterator &map_it) const
        {
            map_it = it->second.find(attribute);
            if (map_it == it->second.end())
                return false;
            
            return true;
        }
        
        bool CINIReader::HasAttribute(const StringMap &map, const std::string &attribute, StringMap::const_iterator &it) const
        {
            it = map.find(attribute);
            if (it == map.end())
                return false;
            
            return true;
        }
        
        void CINIReader::Dump(std::ostream &stream)
        {
            if (!m_fileLoaded)
                return;
            
            // Iterate through each section
            for( MapStringMap::const_iterator it = m_iniSections.begin() ; it != m_iniSections.end() ; ++it)
            {
                // Print the section header
                stream << "[" << it->first << "]" << std::endl;
                
                // Print all the attributes
                for (StringMap::const_iterator attribute = it->second.begin() ; attribute != it->second.end() ; ++attribute)
                {
                    stream << attribute->first << "=" << attribute->second << std::endl;
                }
                
                stream << std::endl;
            }
        }
    };
};


