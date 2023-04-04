message("Downloading dfu-programmer")
if(WIN32)
file(DOWNLOAD
    https://github.com/dfu-programmer/dfu-programmer/releases/download/v1.0.0/dfu-programmer-x64-1.0.0.7z
    ${CMAKE_SOURCE_DIR}/toolchains/downloads/dfu-programmer-x64-1.0.0.7z
    SHOW_PROGRESS
)
file(ARCHIVE_EXTRACT
    INPUT ${CMAKE_SOURCE_DIR}/toolchains/downloads/dfu-programmer-x64-1.0.0.7z
    DESTINATION ${CMAKE_SOURCE_DIR}/toolchains/dfu-programmer/
)
elseif(UNIX)
file(DOWNLOAD
    https://github.com/dfu-programmer/dfu-programmer/releases/download/v1.0.0/dfu-programmer-linux-1.0.0.7z
    ${CMAKE_SOURCE_DIR}/toolchains/downloads/dfu-programmer-linux-1.0.0.7z
    SHOW_PROGRESS
)
file(ARCHIVE_EXTRACT
    INPUT ${CMAKE_SOURCE_DIR}/toolchains/downloads/dfu-programmer-linux-1.0.0.7z
    DESTINATION ${CMAKE_SOURCE_DIR}/toolchains/dfu-programmer/
)
endif()