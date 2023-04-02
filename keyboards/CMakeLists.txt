include(ExternalProject)
include(AddKeyboard)

if(DEFINED QMK_KEYBOARD_FOLDER)
  add_keyboard(${CMAKE_SOURCE_DIR}/keyboards/${QMK_KEYBOARD_FOLDER}/CMakeFiles.txt)
endif()

file(GLOB_RECURSE KEYBOARDS **/CMakeLists.txt)

foreach(KEYBOARD_CMAKE ${KEYBOARDS})
  add_keyboard(${KEYBOARD_CMAKE})
endforeach()