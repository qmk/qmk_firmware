include(ExternalProject)
include(AddKeyboard)

if(NOT EXISTS "${CMAKE_SOURCE_DIR}/build/targets")
  file(WRITE "${CMAKE_SOURCE_DIR}/build/targets" "")
endif()

# if(DEFINED QMK_KEYBOARD_FOLDER)
#   if(NOT DEFINED QMK_KEYMAP_FOLDER)
#     set(QMK_KEYMAP_FOLDER "default")
#   endif()
#   add_keyboard(${QMK_KEYBOARD_FOLDER} ${QMK_KEYMAP_FOLDER})
# endif()

# file(GLOB_RECURSE KEYBOARDS **/CMakeLists.txt)

# foreach(KEYBOARD_CMAKE ${KEYBOARDS})
#   get_filename_component(KEYBOARD_FOLDER_ABS "${KEYBOARD_CMAKE}" DIRECTORY)
#   file(RELATIVE_PATH KEYBOARD_FOLDER "${CMAKE_SOURCE_DIR}/keyboards" "${KEYBOARD_FOLDER_ABS}")
#   add_keyboard(${KEYBOARD_FOLDER} "default")
# endforeach()

file(STRINGS "${CMAKE_SOURCE_DIR}/build/targets" TARGETS)

while(TARGETS)
    list(POP_FRONT TARGETS LINE)
    if (LINE MATCHES "(.+)\\|(.+)\\|(.+):(.+)\\|(.+)")
      set(KEYBOARD_FOLDER ${CMAKE_MATCH_3})
      set(KEYMAP_FOLDER ${CMAKE_MATCH_4})
      add_keyboard(${KEYBOARD_FOLDER} ${KEYMAP_FOLDER})
    endif()
endwhile()

# list all keyboards in build/all_keyboards

file(GLOB_RECURSE POSSIBLE_KEYBOARDS **/info.json)

file(WRITE "${CMAKE_SOURCE_DIR}/build/all_keyboards" "")
foreach(KEYBOARD_INFO ${POSSIBLE_KEYBOARDS})
  get_filename_component(KEYBOARD_FOLDER_ABS "${KEYBOARD_INFO}" DIRECTORY)
  file(RELATIVE_PATH KEYBOARD_FOLDER "${CMAKE_SOURCE_DIR}/keyboards" "${KEYBOARD_FOLDER_ABS}")
  file(APPEND "${CMAKE_SOURCE_DIR}/build/all_keyboards" "${KEYBOARD_FOLDER}\n")
endforeach()
