# can be passed a relative path (to CMAKE_SOURCE_DIR) to update/checkout that submodule
macro(update_submodule SUBMODULE)
    find_package(Git QUIET)
    if(GIT_FOUND AND EXISTS "${CMAKE_SOURCE_DIR}/.git")
        option(GIT_SUBMODULE "Check submodules during build" ON)
        if(GIT_SUBMODULE)
            message(STATUS "Updating submoudle ${SUBMODULE}")
            execute_process(COMMAND ${GIT_EXECUTABLE} submodule update ${SUBMODULE}
                            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                            RESULT_VARIABLE GIT_SUBMOD_RESULT)
            if(NOT GIT_SUBMOD_RESULT EQUAL "0")
                message(FATAL_ERROR "git submodule update ${SUBMODULE} failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
            endif()
        endif()
    else()
        message("Git not found - skipping submodule update")
    endif()

    if(NOT EXISTS "${CMAKE_SOURCE_DIR}/${SUBMODULE}/.git")
        message(FATAL_ERROR "The submodule was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
    endif()
endmacro()