message("Downloading avr-gcc")
if(WIN32)
file(DOWNLOAD
    https://github.com/ZakKemble/avr-gcc-build/releases/download/v12.1.0-1/avr-gcc-12.1.0-x64-windows.zip
    ${CMAKE_SOURCE_DIR}/toolchains/downloads/avr-gcc-x64-windows.zip
    EXPECTED_HASH SHA256=e921a964fdeaedbe963352d0f26c6520a0a3eb8effc6ff232f3824b06c4ea0e2
    SHOW_PROGRESS
)
file(ARCHIVE_EXTRACT
    INPUT ${CMAKE_SOURCE_DIR}/toolchains/downloads/avr-gcc-x64-windows.zip
    DESTINATION ${CMAKE_SOURCE_DIR}/toolchains/
)
elseif(UNIX)
file(DOWNLOAD
    https://github.com/ZakKemble/avr-gcc-build/releases/download/v12.1.0-1/avr-gcc-12.1.0-x64-linux.tar.bz2
    ${CMAKE_SOURCE_DIR}/toolchains/downloads/avr-gcc-x64-linux.tar.bz2
    EXPECTED_HASH SHA256=feb034f4b85237032da8bac1f03765af5ebc4a8939b69bed57ff31bc482ca1a6
    SHOW_PROGRESS
)
file(ARCHIVE_EXTRACT
    INPUT ${CMAKE_SOURCE_DIR}/toolchains/downloads/avr-gcc-x64-linux.tar.bz2
    DESTINATION ${CMAKE_SOURCE_DIR}/toolchains/
)
endif()