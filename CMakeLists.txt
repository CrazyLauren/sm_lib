CMAKE_MINIMUM_REQUIRED(VERSION 2.8.11)



if(COMMAND cmake_policy)#i don't know what is it
    cmake_policy(SET CMP0003 NEW)
    cmake_policy(SET CMP0005 OLD)
endif(COMMAND cmake_policy)

# default to Release build (it's what most people will use, except cegui devs)
if (NOT CMAKE_BUILD_TYPE)
    set( CMAKE_BUILD_TYPE Release CACHE STRING "Sets the configuration to build (Release, Debug, etc...)")
endif()


################################################################################
# Start of main Project definitions
################################################################################
if(DEFINED PROJECT_NAME)
	PROJECT(${PROJECT_NAME}_SM_LIB C CXX)
else()
	PROJECT(SM_LIB C CXX)
endif()

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules")
INCLUDE(FindPackageHandleStandardArgs)
INCLUDE(SHAREMacros)

SET(SHARE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
SET(SHARE_INCLUDES ${SHARE_ROOT_PATH}/include CACHE PATH  "Include path for the header files of SHARE" )
SET(SHARE_DEPENDENCIES_PATH ${SHARE_ROOT_PATH}/dependencies CACHE PATH  "share dependencies")
list( APPEND CMAKE_FIND_ROOT_PATH ${SHARE_DEPENDENCIES_PATH} )

SET(CMAKE_MODULE_PATH "${SHARE_ROOT_PATH}/CMakeModules;${CMAKE_MODULE_PATH}")

SET(CMAKE_DEBUG_POSTFIX  "" CACHE STRING "add a postfix, usually d on windows")
SET(CMAKE_RELEASE_POSTFIX "" CACHE STRING "add a postfix, usually empty on windows")

SET(SHARE_LIBRARIES "" CACHE STRING "Link these to use SHARE")
SET(PLATFORM_LIBS ""  CACHE STRING "Platform library")


mark_as_advanced (
	SHARE_LIBRARIES
	PLATFORM_LIBS
    SHARE_INCLUDES
	SHARE_DEPENDENCIES_PATH
	CMAKE_DEBUG_POSTFIX
	CMAKE_RELEASE_POSTFIX
    )
################################################################################
# Create bin and lib directories if required
################################################################################
IF("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
   FILE(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin ${CMAKE_BINARY_DIR}/lib)
ENDIF("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")

SET(OUTPUT_BINDIR ${PROJECT_BINARY_DIR}/bin)
MAKE_DIRECTORY(${OUTPUT_BINDIR})
SET(EXECUTABLE_OUTPUT_PATH ${OUTPUT_BINDIR})

SET(OUTPUT_LIBDIR ${PROJECT_BINARY_DIR}/lib)
MAKE_DIRECTORY(${OUTPUT_LIBDIR})
SET(LIBRARY_OUTPUT_PATH ${OUTPUT_LIBDIR})

LINK_DIRECTORIES( ${LINK_DIRECTORIES} ${OUTPUT_LIBDIR} )


SET(CMAKE_SHARE_INCLUDE_PATH ${CMAKE_SHARE_INCLUDE_PATH} CACHE STRING "You may add additional search paths here. Use ; to separate multiple paths.")
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} CACHE STRING "You may add additional search paths here. Use ; to separate multiple paths.")

################################################################################
#Look for packages
################################################################################
add_definitions(-DBOOST_ALL_NO_LIB)
if(NOT DEFINED BOOST_ROOT)
	SET(BOOST_ROOT ${SHARE_DEPENDENCIES_PATH}  CACHE PATH "boost path")
endif(NOT DEFINED BOOST_ROOT)
	
FIND_PACKAGE(Boost REQUIRED)

if(NOT Boost_FOUND)
	message(FATAL "Failed to find boost.")	
	return()
endif()

FIND_PACKAGE(rapidjson REQUIRED)
if(NOT RAPIDJSON_FOUND)
	message(FATAL "Failed to find rapidjson.")	
	return()
endif()


# Windows specific config
IF (WIN32)
   if (MSVC)
		add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_DEPRECATE -DNOMINMAX )
        # This option is to enable the /MP switch for Visual Studio 2005 and above compilers
        OPTION(BUILD_BY_MP "Set to ON to build SHARE with the /MP option (Visual Studio 2005 and above)." OFF)
        MARK_AS_ADVANCED(BUILD_BY_MP)
        IF(BUILD_BY_MP)
            SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
        ENDIF(BUILD_BY_MP)

    endif(MSVC)
ENDIF()


################################################################################
# descend into subdirs
################################################################################
add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(tools)
