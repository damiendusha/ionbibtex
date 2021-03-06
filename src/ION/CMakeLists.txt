
# We depend on boost
find_package(Boost REQUIRED COMPONENTS
    thread
    filesystem
    system
)
find_package(gflags REQUIRED)

# Requires the utilities library
include_directories(
    ${CMAKE_SOURCE_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/
)

    
link_directories(
    ${CoreLibraries_BINARY_DIR}/Utilities 
    ${BOOST_LIBRARY}
    /usr/lib
    /usr/local/lib
    ) 

# Set the compiler flags
add_definitions("-Wall" -O3)


set(MetadataElements_SRCS
    MetadataElement/CCitationMetadata.cpp
    MetadataElement/CMetadataAbstract.cpp
    MetadataElement/CMetadataAuthor.cpp
    MetadataElement/CMetadataConference.cpp
    MetadataElement/CMetadataElement.cpp
    MetadataElement/CMetadataPages.cpp
    MetadataElement/CMetadataTitle.cpp
    MetadataElement/CMetadataYear.cpp
    MetadataElement/CMetadataJournal.cpp
    MetadataElement/CMetadataVolume.cpp
    MetadataElement/CMetadataIssue.cpp
    MetadataElement/CMetadataURL.cpp
    MetadataElement/CMetadataParser.cpp
    MetadataElement/CMetadataDoi.cpp
)

set(Publication_SRCS
    Publication/CPublication.cpp
    Publication/CPublicationJournal.cpp
    Publication/CPublicationConference.cpp
)

set(DataSource_SRCS
    DataSource/CDataSource.cpp
    DataSource/CDataSourceURL.cpp
)

set(OutputAction_SRCS
    OutputAction/COutputAction.cpp
    OutputAction/COutputActionConsole.cpp
    OutputAction/COutputActionWriteFile.cpp
)

set(ionbibtex_SRCS
    ion_parser.cpp
    ${MetadataElements_SRCS}
    ${Publication_SRCS}
    ${DataSource_SRCS}
    ${OutputAction_SRCS}
)

set(ionbibtex_LIBS
    m 
    ${Boost_LIBRARIES}
    curl
    utilities_io
    utilities_string
    gumbo
    ${gflags_LIBRARIES}
)

# Main Program
add_executable(ionbibtex ${ionbibtex_SRCS})
target_link_libraries(ionbibtex ${ionbibtex_LIBS})

INSTALL(TARGETS ionbibtex DESTINATION bin)


