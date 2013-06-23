/*
* Copyright (C) 2008-2009, 2013 Damien Dusha
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

#ifndef __STRING_UTILITIES_H__
#define __STRING_UTILITIES_H__

// Boost headers
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

// C/C++ includes
#include <string>
#include <map>
#include <vector>
#include <ctype.h>
#include <iostream>

namespace Utilities
{
    // Converts a hex character to its numerical representation
    template <typename T> T HexCharToNumber(char hex);

    // Parses a hex string into a number
    template <typename T> bool ParseHexString(const std::string &value, T &hexValue);

    // Parses a bool value from a string
    bool ParseBool(const std::string &value, bool &boolValue);

    // Parses a string templated numeric value 
    template <typename T> bool ParseValue(const std::string &value, T &number);

    /// Map-String Utilities:
    template <typename T> bool GetEnumFromMap(const std::map<std::string, int> &stringMap, const std::string &param, T &enumValue);
    bool FindStringFromMapStringInt(const std::map<std::string, int> &map, const std::string &key, int &value);
    std::map<std::string, int> ReverseMapIntString(const std::map<int, std::string> &map);

    // Split a string based on a delimiter
    std::vector<std::string> SplitString(const std::string &haystack, const std::string &delimiter);

    // Recogition for strings consisting purely of numeric digits
    bool IsPositiveInteger(const std::string &data);
    bool IsDecimalFloatingPoint(const std::string &data);
};


// Implemenation of templated functions
namespace Utilities
{
    template <typename T>
    T HexCharToNumber(char hex)
    {
        if (hex >= '0' && hex <= '9')
            return hex - '0';

        hex = tolower(hex);
        return hex - 'a' + 10;
    }

    template <typename T>
    bool ParseHexString(const std::string &value, T &hexValue)
    {
        T number = 0;

        // The only valid characters are '0-9' and 'A-F' (or lowercase versiosn thereof)
        std::string clean = boost::to_lower_copy(boost::trim_copy(value));

        // Strip "0x", if found
        boost::erase_first(clean, "0x");

        // Check that all the characters are notable hex digits
        for(std::string::const_iterator it = clean.begin() ; it != clean.end() ; ++it)
        {
            if(!isxdigit(*it))
            {
                // std::cerr << "Non-hex digit in " << clean < std::endl;
                return false;
            }
        }

        // Accumulate the hex value
        T multiplier = 1;
        for (std::string::const_reverse_iterator it = clean.rbegin() ; it != clean.rend() ; it++)
        {
            number += multiplier * HexCharToNumber<T>(*it);
            multiplier *= 16;
        }

        hexValue = number;
        return true;
    }

    template <typename T>
    bool GetEnumFromMap(const std::map<std::string, int> &stringMap, const std::string &param, T &enumValue)
    {
        int value;
        bool ok = FindStringFromMapStringInt(stringMap, param, value);
        if (ok)
            enumValue = static_cast<T>(value);

        return ok;
    }

    template <typename T>
    bool ParseValue(const std::string &value, T &number)
    {
        try
        {
            number = boost::lexical_cast<T>(value);
        }
        catch(boost::bad_lexical_cast &)
        {
            return false;
        }

        return true;
    }
};



#endif // __STRING_UTILITIES_H__
