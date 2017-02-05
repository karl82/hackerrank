set(SOURCE_FILES solution.cpp)
get_filename_component(CMAKE_CURRENT_LIST_DIR "${CMAKE_CURRENT_LIST_FILE}" DIRECTORY)
get_filename_component(SELF_DIR "${CMAKE_CURRENT_LIST_DIR}" NAME)
add_executable(${SELF_DIR} ${SOURCE_FILES})
