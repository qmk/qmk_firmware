if (NOT (DEFINED PICO_COMPILER OR DEFINED CMAKE_TOOLCHAIN_FILE))
    pico_message("Defaulting PICO platform compiler to pico_arm_gcc since not specified.")
    set(PICO_COMPILER "pico_arm_gcc")
endif ()



