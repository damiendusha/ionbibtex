
link_directories(${BOOST_LIBRARY}) 

set(utilities_io_SRCS
    CDelimitedFileReader.cpp
    CFileInfo.cpp
    CINIReader.cpp
    CCSVReader.cpp
    CListFileReader.cpp
    CWhitespaceDelimitedFileReader.cpp
    CTextFile.cpp
)


add_library(utilities_io STATIC  ${utilities_io_SRCS} )
