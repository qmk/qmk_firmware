# Finds (or builds) the ELF2UF2 executable
#
# This will define the following variables
#
#    ELF2UF2_FOUND
#
# and the following imported targets
#
#     ELF2UF2
#

if (NOT ELF2UF2_FOUND)
    # todo we would like to use pckgconfig to look for it first
    # see https://pabloariasal.github.io/2018/02/19/its-time-to-do-cmake-right/

    include(ExternalProject)

    set(ELF2UF2_SOURCE_DIR ${PICO_SDK_PATH}/tools/elf2uf2)
    set(ELF2UF2_BINARY_DIR ${CMAKE_BINARY_DIR}/elf2uf2)

    set(ELF2UF2_BUILD_TARGET ELF2UF2Build)
    set(ELF2UF2_TARGET ELF2UF2)

    if (NOT TARGET ${ELF2UF2_BUILD_TARGET})
        pico_message_debug("ELF2UF2 will need to be built")
        ExternalProject_Add(${ELF2UF2_BUILD_TARGET}
                PREFIX elf2uf2
                SOURCE_DIR ${ELF2UF2_SOURCE_DIR}
                BINARY_DIR ${ELF2UF2_BINARY_DIR}
                CMAKE_ARGS "-DCMAKE_MAKE_PROGRAM:FILEPATH=${CMAKE_MAKE_PROGRAM}"
                BUILD_ALWAYS 1 # force dependency checking
                INSTALL_COMMAND ""
                )
    endif()

    set(ELF2UF2_EXECUTABLE ${ELF2UF2_BINARY_DIR}/elf2uf2)
    if(NOT TARGET ${ELF2UF2_TARGET})
        add_executable(${ELF2UF2_TARGET} IMPORTED)
    endif()
    set_property(TARGET ${ELF2UF2_TARGET} PROPERTY IMPORTED_LOCATION
            ${ELF2UF2_EXECUTABLE})

    add_dependencies(${ELF2UF2_TARGET} ${ELF2UF2_BUILD_TARGET})
    set(ELF2UF2_FOUND 1)
endif()
