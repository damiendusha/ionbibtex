
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(Utilities)
add_subdirectory(ION)

install(FILES "scripts/jabref-import.sh" 
        PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
        DESTINATION bin)

