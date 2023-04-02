message("Downloading gcc-arm-none-eabi")
if(WIN32)
file(DOWNLOAD
    https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-win32.zip?rev=8f4a92e2ec2040f89912f372a55d8cf3&hash=8A9EAF77EF1957B779C59EADDBF2DAC118170BBF
    ${CMAKE_SOURCE_DIR}/toolchains/downloads/gcc-arm-none-eabi-win32.zip
    EXPECTED_HASH MD5=2bc8f0c4c4659f8259c8176223eeafc1
    SHOW_PROGRESS
)
file(ARCHIVE_EXTRACT
    INPUT ${CMAKE_SOURCE_DIR}/toolchains/downloads/gcc-arm-none-eabi-win32.zip
    DESTINATION ${CMAKE_SOURCE_DIR}/toolchains/
)
elseif(UNIX)
file(DOWNLOAD
    https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2?rev=78196d3461ba4c9089a67b5f33edf82a&hash=D484B37FF37D6FC3597EBE2877FB666A41D5253B
    ${CMAKE_SOURCE_DIR}/toolchains/downloads/gcc-arm-none-eabi-x86_64-linux.tar.bz2
    EXPECTED_HASH MD5=3fe3d8bb693bd0a6e4615b6569443d0d
    SHOW_PROGRESS
)
file(ARCHIVE_EXTRACT
    INPUT ${CMAKE_SOURCE_DIR}/toolchains/downloads/gcc-arm-none-eabi-x86_64-linux.tar.bz2
    DESTINATION ${CMAKE_SOURCE_DIR}/toolchains/
)
endif()