cmake_minimum_required (VERSION 3.7.2) # For FindVulkan module

Project(Sandbox)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(helpful_functions)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMakePredefinedTargets")
set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY true)
SET_PLATFORM_DEFINES()
find_package(OpenMP REQUIRED)

configure_file(${CMAKE_SOURCE_DIR}/cmake/platform_defines.hpp.in ${CMAKE_SOURCE_DIR}/code/shared/platform_defines.hpp)

SET_BIN_AND_LIB_DIRS(${CMAKE_BINARY_DIR}/bin ${CMAKE_BINARY_DIR}/lib)

set_property(DIRECTORY PROPERTY COMPILE_DEFINITIONS
    $<$<CONFIG:Debug>:CMAKE_DEFINE_DEBUG_BUILD>
    $<$<CONFIG:Release>:CMAKE_DEFINE_RELEASE_BUILD>
)

set(COMMON_INCLUDE_DIRS
	${CMAKE_SOURCE_DIR}/code/
    ${CMAKE_SOURCE_DIR}/code/external/
)

add_subdirectory(code/external)

set(CODE_DIR ${CMAKE_SOURCE_DIR}/code)
set(SRC
    ${CODE_DIR}/main.cpp
    
    ${CODE_DIR}/core/bounding_box.cpp
    ${CODE_DIR}/core/bounding_box.hpp
	${CODE_DIR}/core/time.cpp
    ${CODE_DIR}/core/time.hpp
    
    ${CODE_DIR}/shared/assert.hpp
    ${CODE_DIR}/shared/bitops.hpp
    ${CODE_DIR}/shared/color_spaces.hpp
    ${CODE_DIR}/shared/core_defines.hpp
    ${CODE_DIR}/shared/filesystem.cpp
    ${CODE_DIR}/shared/filesystem.hpp
    ${CODE_DIR}/shared/float_conversions.hpp
    ${CODE_DIR}/shared/hash.hpp
    ${CODE_DIR}/shared/logger.cpp
    ${CODE_DIR}/shared/logger.hpp
    ${CODE_DIR}/shared/lz4_compressor.cpp
    ${CODE_DIR}/shared/lz4_compressor.hpp
    ${CODE_DIR}/shared/math.cpp
    ${CODE_DIR}/shared/math.hpp
    ${CODE_DIR}/shared/random.cpp
    ${CODE_DIR}/shared/random.hpp
    ${CODE_DIR}/shared/serializer.cpp
    ${CODE_DIR}/shared/serializer.hpp
    ${CODE_DIR}/shared/string.cpp
    ${CODE_DIR}/shared/string.hpp
)

set(
	EXTERNALS
    ${CODE_DIR}/external/memory_map/MemoryMapped.h
    ${CODE_DIR}/external/memory_map/MemoryMapped.cpp
    ${CODE_DIR}/external/getopt/getopt.c
    ${CODE_DIR}/external/getopt/getopt.h
)

set(ALL_FILES ${SRC} ${EXTERNALS} ${IMAGELIB_EXT_FILES})
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${ALL_FILES})
set_source_files_properties(${IMAGELIB_EXT_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)
add_executable(${PROJECT_NAME} ${ALL_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/
    ${COMMON_INCLUDE_DIRS} ${IMAGELIB_INCLUDES}
)

SET_TARGET_POSTFIX(${PROJECT_NAME})
SET_TARGET_COMPILE_OPTIONS_DEFAULT(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} PUBLIC debug
    OpenMP::OpenMP_CXX ${IMAGELIB_LIBS_DEBUG} lz4
)
target_link_libraries(${PROJECT_NAME} PUBLIC optimized
    OpenMP::OpenMP_CXX ${IMAGELIB_LIBS} lz4 ${PUGIXML_LIBS}
)
target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_BINARY_DIR}/lib ${CMAKE_BINARY_DIR}/bin)