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


#include "StringUtilities.h"

#include <string>
#include <iostream>
#include <iterator>
#include <boost/regex.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <vector>


namespace Utilities
{
    // boolValue = true if value is "true"
    bool ParseBool(const std::string &value, bool &boolValue)
    {
        std::string copy = boost::to_lower_copy(boost::trim_copy(value));

        if (copy == "true" || copy == "t")
        {
            boolValue = true;
            return true;
        }

        if (copy == "false" || copy == "f")
        {
            boolValue = false;
            return true;
        }

        return false;
    }

    bool FindStringFromMapStringInt(const std::map<std::string, int> &map, const std::string &key, int &value)
    {
        std::map<std::string, int>::const_iterator it = map.find(key);
        if (it != map.end())
        {
            value = it->second;
            return true;
        }

        return false;
    }

    std::map<std::string, int> ReverseMapIntString(const std::map<int, std::string> &map )
    {
        std::map<std::string, int> out;
        std::map<int, std::string>::const_iterator it;
        for(it = map.begin() ; it != map.end() ; ++it)
        {
            out[it->second] = it->first;
        }

        return out;
    }

    std::vector<std::string> SplitString(const std::string &haystack, const std::string &delimiter)
    {
        std::vector<std::string> result;
        boost::algorithm::split( result, haystack, boost::is_any_of(delimiter));
        return result;
    }

    // All digits must be numeric
    bool IsPositiveInteger(const std::string &data)
    {
        unsigned int i = 0;;
        if (data[0] == '+')
        {
            if (data.length() == 1)
                return false;
            else
                i++;
        }

        for ( ; i < data.length() ; ++i)
        {
            if (data[i] < '0' || data[i] > '9')
                return false;
        }

        return true;
    }

    // Can be of the form
    bool IsDecimalFloatingPoint(const std::string &data)
    {
        unsigned int i = 0;
        if ( !((data[i] >= '0' && data[i] <= '9') || data[i] == '+' || data[i] == '-'))
            return false;

        // The number can't only consist of a + or -
        if ((data[i] == '+' || data[i] == '-') && data.length() == 1)
            return false;

        // The next lot of digits may either be numbers or a decimal
        for (i = 1 ; i < data.length() ; ++i)
        {
            if ( !((data[i] >= '0' && data[i] <= '9') || data[i] == '.'))
                return false;

            if (data[i] == '.')
            {
                i++;
                break;
            }
        }

        // All remaining digits (if any) must be numeric
        for ( ; i < data.length() ; ++i)
        {
            if (data[i] < '0' || data[i] > '9')
                return false;
        }

        // If we've gotten this far, it must be a decimal floating point number
        return true;
    }
};


