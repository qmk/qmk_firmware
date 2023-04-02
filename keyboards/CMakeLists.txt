include(ExternalProject)
include(AddKeyboard)

if(DEFINED QMK_KEYBOARD_FOLDER)
  add_keyboard(${QMK_KEYBOARD_FOLDER})
endif()

file(GLOB_RECURSE KEYBOARDS **/CMakeLists.txt)

foreach(KEYBOARD_CMAKE ${KEYBOARDS})
  get_filename_component(KEYBOARD_FOLDER_ABS "${KEYBOARD_CMAKE}" DIRECTORY)
  file(RELATIVE_PATH KEYBOARD_FOLDER "${CMAKE_SOURCE_DIR}/keyboards" "${KEYBOARD_FOLDER_ABS}")
  add_keyboard(${KEYBOARD_FOLDER})
endforeach()