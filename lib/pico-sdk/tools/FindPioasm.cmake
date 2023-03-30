# Finds (or builds) the Pioasm executable
#
# This will define the following variables
#
#    Pioasm_FOUND
#
# and the following imported targets
#
#     Pioasm
#

if (NOT Pioasm_FOUND)
    # todo we would like to use pckgconfig to look for it first
    # see https://pabloariasal.github.io/2018/02/19/its-time-to-do-cmake-right/

    include(ExternalProject)

    set(PIOASM_SOURCE_DIR ${PICO_SDK_PATH}/tools/pioasm)
    set(PIOASM_BINARY_DIR ${CMAKE_BINARY_DIR}/pioasm)

    set(PioasmBuild_TARGET PioasmBuild)
    set(Pioasm_TARGET Pioasm)

    if (NOT TARGET ${PioasmBuild_TARGET})
        pico_message_debug("PIOASM will need to be built")
#        message("Adding external project ${PioasmBuild_Target} in ${CMAKE_CURRENT_LIST_DIR}}")
        ExternalProject_Add(${PioasmBuild_TARGET}
                PREFIX pioasm
                SOURCE_DIR ${PIOASM_SOURCE_DIR}
                BINARY_DIR ${PIOASM_BINARY_DIR}
                CMAKE_ARGS "-DCMAKE_MAKE_PROGRAM:FILEPATH=${CMAKE_MAKE_PROGRAM}"
                CMAKE_CACHE_ARGS "-DPIOASM_EXTRA_SOURCE_FILES:STRING=${PIOASM_EXTRA_SOURCE_FILES}"
                BUILD_ALWAYS 1 # force dependency checking
                INSTALL_COMMAND ""
                )
    endif()

    if (CMAKE_HOST_WIN32)
        set(Pioasm_EXECUTABLE ${PIOASM_BINARY_DIR}/pioasm.exe)
    else()
        set(Pioasm_EXECUTABLE ${PIOASM_BINARY_DIR}/pioasm)
    endif()
    if(NOT TARGET ${Pioasm_TARGET})
#        message("Adding executable ${Pioasm_Target} in ${CMAKE_CURRENT_LIST_DIR}")
        add_executable(${Pioasm_TARGET} IMPORTED)
    endif()
    set_property(TARGET ${Pioasm_TARGET} PROPERTY IMPORTED_LOCATION
            ${Pioasm_EXECUTABLE})

#    message("EXE is ${Pioasm_EXECUTABLE}")
    add_dependencies(${Pioasm_TARGET} ${PioasmBuild_TARGET})
    set(Pioasm_FOUND 1)
endif()
