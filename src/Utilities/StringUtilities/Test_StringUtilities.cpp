

// This should be the entry function for the boost unit test framework
// The dynamic link is required since the boost library is a shared object
#define BOOST_TEST_DYN_LINK 
#define BOOST_TEST_MODULE   "String Utilities Test"

#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

using namespace boost::unit_test;

#include "StringUtilities.h"

#include <math.h>
#include <stdio.h>
#include <iostream>
#include <string>


BOOST_AUTO_TEST_CASE( NumericDigits )
{
    std::string data = "+123456";
    BOOST_REQUIRE( Utilities::IsPositiveInteger(data));
    BOOST_REQUIRE( Utilities::IsDecimalFloatingPoint(data));
    
    data = "-123456";
    BOOST_REQUIRE(!Utilities::IsPositiveInteger(data));
    BOOST_REQUIRE( Utilities::IsDecimalFloatingPoint(data));    
    
    data = "123456";
    BOOST_REQUIRE( Utilities::IsPositiveInteger(data));
    BOOST_REQUIRE( Utilities::IsDecimalFloatingPoint(data));
    
    data = "123hello";
    BOOST_REQUIRE(!Utilities::IsPositiveInteger(data));
    BOOST_REQUIRE(!Utilities::IsDecimalFloatingPoint(data));
    
    data = "123.456";
    BOOST_REQUIRE(!Utilities::IsPositiveInteger(data));
    BOOST_REQUIRE( Utilities::IsDecimalFloatingPoint(data));

    data = "-123.456";
    BOOST_REQUIRE(!Utilities::IsPositiveInteger(data));
    BOOST_REQUIRE( Utilities::IsDecimalFloatingPoint(data));
    
    data = "+123.456";
    BOOST_REQUIRE(!Utilities::IsPositiveInteger(data));
    BOOST_REQUIRE( Utilities::IsDecimalFloatingPoint(data));
}

