# Simple CMake utility to read variables from MK files
# - Gets contents from given file (name or path)
# - Parses the assignment statements
# - Makes the same assignments in the PARENT_SCOPE

if(POLICY CMP0007)
    cmake_policy(SET CMP0007 NEW)
endif()

function(ParseMakefile MKFile)
    _ParseMakefile(${MKFile} ${ARGN})
endfunction()

macro(_ParseMakefile MKFile)
    message(CHECK_START "Parsing Makefile")
    list(APPEND CMAKE_MESSAGE_INDENT "  ")
    message(STATUS "Reading \"${MKFile}\"")

    file(READ "${MKFile}" FileContents)
    # replace the \ newlines with spaces
    string(REGEX REPLACE "\\\\\r?\n *" " " FileContents ${FileContents})
    # turn each line into an item in a list
    string(REGEX REPLACE "\r?\n" ";" FileLines ${FileContents})
    list(REMOVE_ITEM FileLines "")

    foreach(line ${FileLines})
        # remove comments from the ends of each line
        string(REGEX REPLACE "#.*" "" line ${line})

        # remove now-empty lines
        if("${line}" STREQUAL "")
            continue()
        endif()

        # try to process includes, if the file exists
        if(line MATCHES "^-?include (.+)$")
            set(MAKE_CHILD ${CMAKE_MATCH_1})
            if(EXISTS ${MAKE_CHILD})
                _ParseMakefile("${MAKE_CHILD}" ${ARGN})
            else()
                message(STATUS "Could not read ${MAKE_CHILD}")
            endif()
            continue()
        endif()

        # turn the assignment into a list with the first item being the variable name
        string(REPLACE "=" ";" line_split ${line})
        list(LENGTH line_split count)

        if(count LESS 2)
            message(STATUS "Skipping ${line}")
            continue()
        endif()

        list(GET line_split -1 value)
        string(STRIP ${value} value)
        # separate_arguments(value)
        # string(REPLACE " " ";" value ${value})
        list(REMOVE_AT line_split -1)

        foreach(var_name ${line_split})
            string(STRIP ${var_name} var_name)
            # replace $(?) with the variable ? from cmake
            if(value MATCHES "\\$\\(([^\\(\\)]+)\\)")
                set(MAKE_VARIABLE "${CMAKE_MATCH_1}")
                string(REPLACE "$(${MAKE_VARIABLE})" "${${MAKE_VARIABLE}}" value ${value})
            endif()

            # look for +, assuming it used to be +=
            if(${var_name} MATCHES "([^ \\+]+) *\\+")
                message(STATUS "Appending \"${CMAKE_MATCH_1}\" with \"${value}\"")
                # read parent variable in local & append
                set(LOCAL_${CMAKE_MATCH_1} ${CMAKE_MATCH_1})
                # APPEND accepts spaces between values
                list(APPEND LOCAL_${CMAKE_MATCH_1} ${value})
                set(${CMAKE_MATCH_1} ${LOCAL_${CMAKE_MATCH_1}})
                set(${CMAKE_MATCH_1} ${LOCAL_${CMAKE_MATCH_1}} PARENT_SCOPE)
            else()
                # set needs ; between elements to be considered a list
                string(REGEX REPLACE " +" ";" value ${value})
                # try to find variable in cache and FORCE wtih INTERNAL if it exists
                if(DEFINED CACHE${${var_name}})
                    message(STATUS "Caching \"${var_name}\" to \"${value}\"")
                    # set locally so replacement still work
                    set(${var_name} ${value})
                    set(${var_name} ${value} CACHE INTERNAL "")
                else()
                    message(STATUS "Setting \"${var_name}\" to \"${value}\"")
                    set(${var_name} ${value})
                    set(${var_name} ${value} PARENT_SCOPE)
                endif()
            endif()
        endforeach()
    endforeach()

    list(POP_BACK CMAKE_MESSAGE_INDENT)
    message(CHECK_PASS "Complete")
endmacro()