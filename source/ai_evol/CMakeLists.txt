cmake_minimum_required (VERSION 2.6)
project (ai_evol)

set (${CMAKE_PROJECT_NAME}_VERSION_MAJOR 1)
set (${CMAKE_PROJECT_NAME}_VERSION_MINOR 0)


set (install_dir "$ENV{INSTALL_DIR}")
#CMAKE_BUILD_TYPE=Release
set (CMAKE_C_FLAGS_RELEASE "-Wall -Wextra -pedantic -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes -Wno-variadic-macros")
#CMAKE_BUILD_TYPE=Debug
set (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_RELEASE} -DDEBUG_UTIL_ACTIVATE -g")
#SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)

SET (MAIN_PROJ_PATH "") #importent / if it's not empty!

include_directories ("${PROJECT_SOURCE_DIR}/header")
include_directories ("${install_dir}/include")

configure_file (
		"${PROJECT_SOURCE_DIR}/config.h.in"
		"${PROJECT_SOURCE_DIR}/header/ai_evol_config.h")

file (GLOB sources "${PROJECT_SOURCE_DIR}/source/*.c")

add_library (ai_evol ${sources})
add_library (ai_evol_d ${sources})

file (GLOB headers "${PROJECT_SOURCE_DIR}/header/*.h")

install (FILES ${headers}
		 DESTINATION "${install_dir}/include/${MAIN_PROJ_PATH}${CMAKE_PROJECT_NAME}")

install (TARGETS ai_evol
		 DESTINATION "${install_dir}/lib" CONFIGURATIONS Release)
install (TARGETS ai_evol_d
		 DESTINATION "${install_dir}/lib" CONFIGURATIONS Debug)

#DOXYGEN extension
find_package(Doxygen)
if(DOXYGEN_FOUND)
configure_file(${PROJECT_SOURCE_DIR}/docs/Doxyfile.cmake ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
add_custom_target(doc
${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
COMMENT "Generating API documentation with Doxygen" VERBATIM
)
endif(DOXYGEN_FOUND)
