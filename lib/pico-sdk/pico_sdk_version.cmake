# PICO_BUILD_DEFINE: PICO_SDK_VERSION_MAJOR, SDK major version number, type=int, group=pico_base
# PICO_CMAKE_CONFIG: PICO_SDK_VERSION_MAJOR, SDK major version number, type=int, group=pico_base
set(PICO_SDK_VERSION_MAJOR 1)
# PICO_BUILD_DEFINE: PICO_SDK_VERSION_MINOR, SDK minor version number, type=int, group=pico_base
# PICO_CMAKE_CONFIG: PICO_SDK_VERSION_MINOR, SDK minor version number, type=int, group=pico_base
set(PICO_SDK_VERSION_MINOR 5)
# PICO_BUILD_DEFINE: PICO_SDK_VERSION_REVISION, SDK version revision, type=int, group=pico_base
# PICO_CMAKE_CONFIG: PICO_SDK_VERSION_REVISION, SDK version revision, type=int, group=pico_base
set(PICO_SDK_VERSION_REVISION 0)
# PICO_BUILD_DEFINE: PICO_SDK_VERSION_PRE_RELEASE_ID, optional SDK pre-release version identifier, type=string, group=pico_base
# PICO_CMAKE_CONFIG: PICO_SDK_VERSION_PRE_RELEASE_ID, optional SDK pre-release version identifier, type=string, group=pico_base
#set(PICO_SDK_VERSION_PRE_RELEASE_ID develop)

# PICO_BUILD_DEFINE: PICO_SDK_VERSION_STRING, SDK version, type=string, group=pico_base
# PICO_CMAKE_CONFIG: PICO_SDK_VERSION_STRING, SDK version, type=string, group=pico_base
set(PICO_SDK_VERSION_STRING "${PICO_SDK_VERSION_MAJOR}.${PICO_SDK_VERSION_MINOR}.${PICO_SDK_VERSION_REVISION}")

if (PICO_SDK_VERSION_PRE_RELEASE_ID)
    set(PICO_SDK_VERSION_STRING "${PICO_SDK_VERSION_STRING}-${PICO_SDK_VERSION_PRE_RELEASE_ID}")
endif()
