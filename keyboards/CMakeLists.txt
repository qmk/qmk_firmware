include(ExternalProject)
include(AddKeyboard)

if(DEFINED QMK_KEYBOARD_FOLDER)
  if(NOT DEFINED QMK_KEYMAP_FOLDER)
    set(QMK_KEYMAP_FOLDER "default")
  endif()
  add_keyboard(${QMK_KEYBOARD_FOLDER} ${QMK_KEYMAP_FOLDER})
endif()

file(GLOB_RECURSE KEYBOARDS **/CMakeLists.txt)

foreach(KEYBOARD_CMAKE ${KEYBOARDS})
  get_filename_component(KEYBOARD_FOLDER_ABS "${KEYBOARD_CMAKE}" DIRECTORY)
  file(RELATIVE_PATH KEYBOARD_FOLDER "${CMAKE_SOURCE_DIR}/keyboards" "${KEYBOARD_FOLDER_ABS}")
  add_keyboard(${KEYBOARD_FOLDER} "default")
endforeach()