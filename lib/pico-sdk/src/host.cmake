# For targeting the host for testing purposes

function(pico_add_extra_outputs TARGET)
endfunction()

set(PICO_NO_HARDWARE "1" CACHE INTERNAL "")
set(PICO_ON_DEVICE "0" CACHE INTERNAL "")

add_subdirectory(common)
add_subdirectory(host)