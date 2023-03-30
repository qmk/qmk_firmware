
get_property(IS_IN_TRY_COMPILE GLOBAL PROPERTY IN_TRY_COMPILE)
foreach(LANG IN ITEMS C CXX ASM)
    set(CMAKE_${LANG}_FLAGS_INIT "${ARM_TOOLCHAIN_COMMON_FLAGS}")
    if (PICO_DEOPTIMIZED_DEBUG)
        set(CMAKE_${LANG}_FLAGS_DEBUG_INIT "-O0")
    else()
        set(CMAKE_${LANG}_FLAGS_DEBUG_INIT "-Og")
    endif()
    set(CMAKE_${LANG}_LINK_FLAGS "-Wl,--build-id=none")

    # try_compile is where the feature testing is done, and at that point,
    # pico_standard_link is not ready to be linked in to provide essential
    # functions like _exit. So pass -nostdlib so it doesn't link in an exit()
    # function at all.
    if(IS_IN_TRY_COMPILE)
        set(CMAKE_${LANG}_LINK_FLAGS "${CMAKE_${LANG}_LINK_FLAGS} -nostdlib")
    endif()
endforeach()
