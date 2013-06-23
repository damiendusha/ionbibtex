

link_directories(${BOOST_LIBRARY}) 

set(utilities_string_SRCS
    StringUtilities.cpp
)


add_library(utilities_string STATIC  ${utilities_string_SRCS} )
