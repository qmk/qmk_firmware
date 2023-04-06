# Simple CMake utility to read variables from MK files
# - Gets contents from given file (name or path)
# - Parses the assignment statements
# - Makes the same assignments in the PARENT_SCOPE

if(POLICY CMP0007)
    cmake_policy(SET CMP0007 NEW)
endif()

function(ParseMakefile MKFile)
    _ParseMakefile(${MKFile})
endfunction()

macro(_ParseMakefile MKFile)
    message(VERBOSE "Parsing ${MKFile}")
    file(READ "${MKFile}" FileContents)
    string(REGEX REPLACE "\\\\\r?\n *" " " FileContents ${FileContents})
    string(REGEX REPLACE "(\r?\n)+" ";" FileLines ${FileContents})
    list(REMOVE_ITEM FileLines "")

    foreach(line ${FileLines})
        # if(line MATCHES "\\$\\((.+)\\)")
        # set(MAKE_VARIABLE "${CMAKE_MATCH_1}")
        # string(REPLACE "$(${MAKE_VARIABLE})" "${${MAKE_VARIABLE}}" line ${line})
        # endif()
        # message(STATUS "From: ${line}")
        string(REGEX REPLACE "#.*" "" line ${line})

        if("${line}" STREQUAL "")
            continue()
        endif()

        string(REGEX REPLACE "\\$\\(([^\\(\\)]+)\\)" "${CHIBIOS}" line ${line})

        # message(STATUS "To  : ${line}")
        # if(line MATCHES "^include (.+)$")
        # set(MAKE_CHILD ${CMAKE_MATCH_1})
        # message(STATUS "Reading ${MAKE_CHILD}")
        # _ParseMakefile("${MAKE_CHILD}")
        # else()
        string(REPLACE "=" ";" line_split ${line})
        list(LENGTH line_split count)

        if(count LESS 2)
            message(VERBOSE "Skipping ${line}")
            continue()
        endif()

        list(GET line_split -1 value)
        string(STRIP ${value} value)
        separate_arguments(value)
        list(REMOVE_AT line_split -1)

        foreach(var_name ${line_split})
            string(STRIP ${var_name} var_name)
            if(${var_name} MATCHES "([^ \\+]+) *\\+")
                message(VERBOSE "Appending '${CMAKE_MATCH_1}' with '${value}'")
                set(${CMAKE_MATCH_1} ${${CMAKE_MATCH_1}} ${value} PARENT_SCOPE)
            else()
                if(DEFINED CACHE${${var_name}})
                    message(VERBOSE "Caching '${var_name}' to '${value}'")
                    set(${var_name} ${value} CACHE INTERNAL "")
                else()
                    message(VERBOSE "Setting '${var_name}' to '${value}'")
                    set(${var_name} ${value} PARENT_SCOPE)
                endif()
            endif()
        endforeach()

        # endif()
    endforeach()
endmacro()