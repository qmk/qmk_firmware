# Simple CMake utility to read variables from MK files
# - Gets contents from given file (name or path)
# - Parses the assignment statements
# - Makes the same assignments in the PARENT_SCOPE

if(POLICY CMP0007)
    cmake_policy(SET CMP0007 NEW)
endif()

function(ParseHeader HeaderFile Prefix)
    _ParseHeader(${HeaderFile} ${Prefix})
endfunction()

macro(_ParseHeader HeaderFile Prefix)
    message(CHECK_START "Parsing Header")
    list(APPEND CMAKE_MESSAGE_INDENT "  ")
    message(STATUS "Reading \"${HeaderFile}\"")

    file(READ "${HeaderFile}" FileContents)
    string(REGEX REPLACE "/\\*.*\\*/" "" FileContents ${FileContents})
    # replace the \ newlines with spaces
    string(REGEX REPLACE "\\\\\r?\n *" " " FileContents ${FileContents})
    # turn each line into an item in a list
    string(REGEX REPLACE "\r?\n" ";" FileLines ${FileContents})
    list(REMOVE_ITEM FileLines "")

    foreach(line ${FileLines})
        # remove comments from the ends of each line
        string(REGEX REPLACE "//.*" "" line ${line})

        # remove now-empty lines
        if("${line}" STREQUAL "")
            continue()
        endif()

        # try to process includes, if the file exists
        if(line MATCHES "^#include \"(.+)\"")
            set(INCLUDED_HEADER ${CMAKE_MATCH_1})
            if(EXISTS ${INCLUDED_HEADER})
                _ParseHeader("${INCLUDED_HEADER}" ${Prefix})
            else()
                message(STATUS "Could not read ${INCLUDED_HEADER}")
            endif()
            continue()
        endif()
        
        # array
        if(line MATCHES "#define ([A-Za-z0-9_]+) {(.*)}")
            set(VARIABLE_NAME ${CMAKE_MATCH_1})
            set(VARIABLE_VALUE ${CMAKE_MATCH_2})
            set(${Prefix}${VARIABLE_NAME} ${VARIABLE_VALUE})
        endif()

        # regular variable
        if(line MATCHES "#define ([A-Za-z0-9_]+) (.*)")
            set(VARIABLE_NAME ${CMAKE_MATCH_1})
            set(VARIABLE_VALUE ${CMAKE_MATCH_2})
            set(${Prefix}${VARIABLE_NAME} ${VARIABLE_VALUE})
        endif()
    endforeach()

    list(POP_BACK CMAKE_MESSAGE_INDENT)
    message(CHECK_PASS "Complete")
endmacro()