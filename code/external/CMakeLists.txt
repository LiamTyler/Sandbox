set(EXT_DIR ${CMAKE_SOURCE_DIR}/code/external)

#----------------------------ASSIMP--------------------------------------------
if(MSVC)
    if(NOT EXISTS ${CMAKE_BINARY_DIR}/lib/assimp-vc142-mt.lib)
        CONFIG_TIME_COMPILE(${EXT_DIR}/assimp ${CMAKE_BINARY_DIR}/ext/assimp Release)
        COPY_BUILD_FILES(${CMAKE_BINARY_DIR}/ext/assimp/bin/Release ${CMAKE_BINARY_DIR}/bin ${CMAKE_BINARY_DIR}/lib assimp)
        COPY_BUILD_FILES(${CMAKE_BINARY_DIR}/ext/assimp/lib/Release ${CMAKE_BINARY_DIR}/bin ${CMAKE_BINARY_DIR}/lib assimp)
    endif()
    set(ASSIMP_LIBS assimp-vc142-mt PARENT_SCOPE)
else()
    if(NOT EXISTS ${CMAKE_BINARY_DIR}/bin/libassimp.so)
        CONFIG_TIME_COMPILE(${EXT_DIR}/assimp ${CMAKE_BINARY_DIR}/ext/assimp Release)
        COPY_BUILD_FILES(${CMAKE_BINARY_DIR}/ext/assimp/bin/ ${CMAKE_BINARY_DIR}/bin ${CMAKE_BINARY_DIR}/lib assimp)
    endif()
    set(ASSIMP_LIBS assimp PARENT_SCOPE)
endif()
set(ASSIMP_INCLUDES
	${EXT_DIR}/assimp/include
	${CMAKE_BINARY_DIR}/ext/assimp/include
	PARENT_SCOPE
)

#------------------------------LZ4---------------------------------------------
if(MSVC)
    if(NOT EXISTS ${CMAKE_BINARY_DIR}/lib/lz4.lib)
        CONFIG_TIME_COMPILE(${EXT_DIR}/lz4 ${CMAKE_BINARY_DIR}/ext/lz4 Release)
        COPY_BUILD_FILES(${CMAKE_BINARY_DIR}/ext/lz4/Release ${CMAKE_BINARY_DIR}/bin ${CMAKE_BINARY_DIR}/lib lz4)
    endif()
else()
    if(NOT EXISTS ${CMAKE_BINARY_DIR}/lib/liblz4.a)
        CONFIG_TIME_COMPILE(${EXT_DIR}/lz4 ${CMAKE_BINARY_DIR}/ext/lz4 Release)
        COPY_BUILD_FILES(${CMAKE_BINARY_DIR}/ext/lz4/ ${CMAKE_BINARY_DIR}/bin ${CMAKE_BINARY_DIR}/lib lz4)
    endif()
endif()

#-------------------------------BC7ENC--------------------------------------------
if(MSVC)
    if(NOT EXISTS ${CMAKE_BINARY_DIR}/lib/bc7enc.lib)
        CONFIG_TIME_COMPILE(${EXT_DIR}/bc7enc_rdo ${CMAKE_BINARY_DIR}/ext/bc7enc Release)
        COPY_BUILD_FILES(${CMAKE_BINARY_DIR}/ext/bc7enc ${CMAKE_BINARY_DIR}/bin ${CMAKE_BINARY_DIR}/lib bc7enc)
    endif()
else()
    if(NOT EXISTS ${CMAKE_BINARY_DIR}/lib/libbc7enc.a)
        CONFIG_TIME_COMPILE(${EXT_DIR}/bc7enc_rdo ${CMAKE_BINARY_DIR}/ext/bc7enc Release)
        COPY_BUILD_FILES(${CMAKE_BINARY_DIR}/ext/bc7enc ${CMAKE_BINARY_DIR}/bin ${CMAKE_BINARY_DIR}/lib bc7enc)
    endif()
endif()

#-------------------------------LIBTIFF--------------------------------------------
if(MSVC)
    if(NOT EXISTS ${CMAKE_BINARY_DIR}/lib/tiff.lib)
        CONFIG_TIME_COMPILE(${EXT_DIR}/libtiff ${CMAKE_BINARY_DIR}/ext/libtiff Release)
        COPY_BUILD_FILES(${CMAKE_BINARY_DIR}/ext/libtiff/libtiff/Release ${CMAKE_BINARY_DIR}/bin ${CMAKE_BINARY_DIR}/lib tiff)
    endif()
else()
    if(NOT EXISTS ${CMAKE_BINARY_DIR}/bin/libtiff.so)
        CONFIG_TIME_COMPILE(${EXT_DIR}/libtiff ${CMAKE_BINARY_DIR}/ext/libtiff Release)
        COPY_BUILD_FILES(${CMAKE_BINARY_DIR}/ext/libtiff/libtiff ${CMAKE_BINARY_DIR}/bin ${CMAKE_BINARY_DIR}/lib tiff)
    endif()
endif()

#-------------------------------IMAGELIB--------------------------------------------
# much more likely to be edited than the other projects, so always recompile
CONFIG_TIME_COMPILE_DEBUG_AND_RELEASE(${EXT_DIR}/ImageLib ${CMAKE_BINARY_DIR}/ext/ImageLib)
if(MSVC)
    COPY_BUILD_FILES(${CMAKE_BINARY_DIR}/ext/ImageLib/lib ${CMAKE_BINARY_DIR}/bin ${CMAKE_BINARY_DIR}/lib *)
    COPY_BUILD_FILES(${CMAKE_BINARY_DIR}/ext/ImageLib/bin ${CMAKE_BINARY_DIR}/bin ${CMAKE_BINARY_DIR}/lib *)
else()
    COPY_BUILD_FILES(${CMAKE_BINARY_DIR}/ext/ImageLib/Debug/lib ${CMAKE_BINARY_DIR}/bin ${CMAKE_BINARY_DIR}/lib *)
    COPY_BUILD_FILES(${CMAKE_BINARY_DIR}/ext/ImageLib/Release/lib ${CMAKE_BINARY_DIR}/bin ${CMAKE_BINARY_DIR}/lib *)
endif()
set(IMAGELIB_INCLUDES
    ${EXT_DIR}/ImageLib/
	${EXT_DIR}/libtiff/libtiff/
    ${CMAKE_BINARY_DIR}/ext/libtiff/libtiff/
    ${EXT_DIR}/compressonator/
    ${EXT_DIR}/compressonator/cmp_core/source/
	PARENT_SCOPE
)
# NOTE: need to do this for all libraries libtiff ends up using (so far only zlib on linux?)
set(ZLIB_LIBS "")
if(NOT MSVC)
    find_package(ZLIB)
    if(ZLIB_FOUND)
        set(ZLIB_LIBS ${ZLIB_LIBRARIES})
    endif()
endif()
set(IMAGELIB_LIBS ImageLib tiff bc7enc ${ZLIB_LIBS} PARENT_SCOPE)
set(IMAGELIB_LIBS_DEBUG ImageLib_d tiff bc7enc ${ZLIB_LIBS} PARENT_SCOPE)

set(IMAGELIB_EXT_FILES
	${EXT_DIR}/ImageLib/bc_compression.cpp
    ${EXT_DIR}/ImageLib/bc_compression.hpp
	${EXT_DIR}/ImageLib/bc_decompression.cpp
    ${EXT_DIR}/ImageLib/bc7_reference_tables.hpp
	${EXT_DIR}/ImageLib/image.cpp
    ${EXT_DIR}/ImageLib/image.hpp
	${EXT_DIR}/ImageLib/image_load.cpp
    ${EXT_DIR}/ImageLib/image_load.hpp
	${EXT_DIR}/ImageLib/image_save.cpp
    ${EXT_DIR}/ImageLib/image_save.hpp
	PARENT_SCOPE
)
