#
# SHAREMacros.cmake
#
# Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
#
#  Created on: 12.11.2016
#      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
#
# Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
# https://www.mozilla.org/en-US/MPL/2.0)
# 
 macro(configure_logging _DEP_PATH)
	
	SET(GLOG_ROOT_DIR ${_DEP_PATH}/glog)
	FIND_PACKAGE(glog)

	SET(LOG4CPLUS_ROOT_DIR ${_DEP_PATH}/log4cplus)
	FIND_PACKAGE(log4cplus)

	OPTION(LOGGING_TO_GLOG "Using glog for loging" OFF)
	OPTION(LOGGING_TO_LOG4CPLUS "Using log4cplus for loging" OFF)
	OPTION(LOGGING_TO_COUT "Logging to cout" OFF)
	OPTION(LOGGING_HAS_TO_BE_REMOVED "Removed logging" OFF)
	SET(LOGGING_COMMAND_FLAG "v" CACHE STRING  "")
	SET(LOGGING_COMMAND_LONG_NAME "verbose" CACHE STRING  "")

	SET(LOGGING_INCLUDES "" CACHE INTERNAL  "" FORCE)
	SET(LOGGING_LIBRARIES "" CACHE INTERNAL  "" FORCE)
	SET(LOGGING_DEFENITIONS "" CACHE INTERNAL  "" FORCE)
	
	if(NOT LOGGING_HAS_TO_BE_REMOVED)
	IF (LOGGING_TO_GLOG)
		if(NOT GLOG_FOUND)
			message(FATAL "Failed to find GLOG.")	
			return()
		endif()
		
		SET(LOGGING_DEFENITIONS "-DGLOG" CACHE INTERNAL  "" FORCE)
		
		SET(LOGGING_INCLUDES ${GLOG_INCLUDE_DIRS} CACHE INTERNAL  "LOGGING_INCLUDES" FORCE)
		SET(LOGGING_LIBRARIES ${GLOG_LIBRARIES} CACHE INTERNAL  "LOGGING_LIBRARIES" FORCE)
		
	ELSEIF (LOGGING_TO_LOG4CPLUS)
		if(NOT LOG4CPLUS_FOUND)
			message(FATAL "Failed to find log4cplus.")	
			return()
		endif()
		
		SET(LOGGING_DEFENITIONS "-DCPLUS_LOG" CACHE INTERNAL  "" FORCE)
		
		SET(LOGGING_INCLUDES ${LOG4CPLUS_INCLUDES} CACHE INTERNAL  "LOGGING_INCLUDES" FORCE)
		SET(LOGGING_LIBRARIES ${LOG4CPLUS_LIBRARIES} CACHE INTERNAL  "LOGGING_LIBRARIES" FORCE)
		
	ELSEIF (LOGGING_TO_COUT)
		SET(LOGGING_DEFENITIONS "-DCOUT_LOG" CACHE INTERNAL  "" FORCE)
	ELSE()
		SET(LOGGING_DEFENITIONS "-DNOLOG" CACHE INTERNAL  "" FORCE)
	ENDIF ()
	else(NOT LOGGING_HAS_TO_BE_REMOVED)
		SET(LOGGING_DEFENITIONS "-DREMOVE_LOG" CACHE INTERNAL  "" FORCE)	
	endif(NOT LOGGING_HAS_TO_BE_REMOVED)

	
	list(REMOVE_DUPLICATES LOGGING_LIBRARIES)
	list(REMOVE_DUPLICATES LOGGING_INCLUDES)
endmacro()

# Make a version
#	_TARGET - Name of the TARGET
#	_FILE_PATH - Path to revision.c
#	_MAJOR,_MINOR - Version of target
#	_SOVERSION - For library only, version in lib.so._SOVERSION - API Version

macro(configure_version _TARGET _FILE_PATH _MAJOR _MINOR )
	
	string(TOUPPER ${_TARGET} _PREFIX)
	
	if (("${ARGC}" GREATER 4) AND "${ARGV5}")
		set(_SOVERSION ${ARGV5})
	endif()
	# Make a version file containing the current version from git.
	SET(${_PREFIX}_MAJOR_VERSION ${_MAJOR} CACHE STRING "" FORCE)
	SET(${_PREFIX}_MINOR_VERSION ${_MINOR} CACHE STRING "" FORCE)
	SET(${_PREFIX}_REVISION_VERSION "0" CACHE STRING "" FORCE)
	SET(${_PREFIX}_PATH "no path" CACHE STRING "" FORCE)

	OPTION(${_PREFIX}_EMBED_GIT_SHA "Embeds the GIT SHA in the version code" ON)
	
	mark_as_advanced(${_PREFIX}_EMBED_GIT_SHA
					${_PREFIX}_REVISION_VERSION
					${_PREFIX}_PATH)
	
	IF (${_PREFIX}_EMBED_GIT_SHA)
		include(GetGitRevisionDescription)
		git_describe(VERSION --tags --dirty=-d)

	#parse the version information into pieces.
		IF(NOT VERSION  MATCHES  "-NOTFOUND")
			STRING(REGEX REPLACE "^v[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" ${_PREFIX}_PATH "${VERSION}")
			STRING(REGEX REPLACE "^v[0-9]+\\.[0-9]+\\.[0-9]+(.*)" "\\1" ${_PREFIX}_REVISION_VERSION "${VERSION}")
		ELSE(NOT VERSION  MATCHES  "-NOTFOUND")
			message("Cannot get revisiob from git:" "${VERSION}" ) 
		ENDIF (NOT VERSION  MATCHES  "-NOTFOUND")
	ENDIF (${_PREFIX}_EMBED_GIT_SHA)

	STRING(TIMESTAMP ${_PREFIX}_TIME "%H:%M:%S" )
	STRING(TIMESTAMP ${_PREFIX}_DATA "%Y-%m-%d" )

	SET(${_PREFIX}_VERSION 
	${${_PREFIX}_MAJOR_VERSION}.${${_PREFIX}_MINOR_VERSION}.${${_PREFIX}_REVISION_VERSION} CACHE INTERNAL "" FORCE)
	
	if(_SOVERSION)
		SET(${_PREFIX}_SOVERSION  ${_SOVERSION} CACHE INTERNAL "" FORCE)
	endif()
	
	message ("Version of " ${_PREFIX} " is " ${${_PREFIX}_VERSION} " from " ${${_PREFIX}_PATH})

	SET(CONF_VERSION_MAJOR ${${_PREFIX}_MAJOR_VERSION} CACHE INTERNAL "" FORCE)
	SET(CONF_VERSION_MINOR ${${_PREFIX}_MINOR_VERSION} CACHE INTERNAL "" FORCE)
	SET(CONF_VERSION_REVISION ${${_PREFIX}_REVISION_VERSION} CACHE INTERNAL "" FORCE)
	SET(CONF_VERSION_PATH ${${_PREFIX}_PATH} CACHE INTERNAL "" FORCE)
	SET(CONF_VERSION_TIME ${${_PREFIX}_TIME} CACHE INTERNAL "" FORCE)
	SET(CONF_VERSION_DATA ${${_PREFIX}_DATA} CACHE INTERNAL "" FORCE)
	
	configure_file(${PATH_TO_REVISION_IN}
                ${_FILE_PATH}/revision.c)
	
	UNSET(CONF_VERSION_MAJOR CACHE)
	UNSET(CONF_VERSION_MINOR  CACHE)
	UNSET(CONF_VERSION_REVISION CACHE)
	UNSET(CONF_VERSION_PATH CACHE)
	UNSET(CONF_VERSION_TIME  CACHE)
	UNSET(CONF_VERSION_DATA  CACHE)
endmacro()


# Define _LIB_NAME library to be built 
#       _LIB_NAME           - Name of the library to create.
#       _IS_MODULE          - to create a module or shared lib
#       _SOURCE_FILES_VAR2   - the source file names.
#       _HEADER_FILES_VAR   - the header file names.
#       _INSTALL_BIN        - TRUE if the lib should be installed
macro (share_add_library _LIB_NAME _IS_MODULE _SOURCE_FILES_VAR _HEADER_FILES_VAR _INSTALL_BIN)
    
	string(TOUPPER ${_LIB_NAME} _LIB_NAME_UP)
    string(TOUPPER ${_LIB_NAME}_EXPORTS _EXPORT_DEFINE)
	
    #STATIC LIBRARY SET UP
	set(${_LIB_NAME_UP}_BUILD_STATIC_TOO true CACHE BOOL "Build ${_LIB_NAME} as static library too")
	set(${_LIB_NAME_UP}_WITH_STATIC_DEPENDENCIES false CACHE BOOL "Link ${_LIB_NAME} with static dependecies")
	#OPTION(${_LIB_NAME_UP}_BUILD_STATIC_TOO "Build static library too" ON)


	
    if (${${_LIB_NAME_UP}_BUILD_STATIC_TOO})
        add_library(${_LIB_NAME}_Static STATIC ${${_SOURCE_FILES_VAR}} ${${_HEADER_FILES_VAR}})
#        string(TOUPPER ${_LIB_NAME_UP}_STATIC _EXPORT_STATIC)
#		set_property(TARGET ${_LIB_NAME}_Static APPEND PROPERTY COMPILE_DEFINITIONS ${_EXPORT_STATIC})
		set_property(TARGET ${_LIB_NAME}_Static APPEND PROPERTY COMPILE_DEFINITIONS ${_EXPORT_DEFINE})
    endif()


    #SHARED LIBRARY SET UP
	add_library(${_LIB_NAME} SHARED ${${_SOURCE_FILES_VAR}} ${${_HEADER_FILES_VAR}})
	
    set_target_properties(${_LIB_NAME} PROPERTIES DEFINE_SYMBOL ${_EXPORT_DEFINE})
	

    if (NOT ${_IS_MODULE})
		if(NOT ${_LIB_NAME_UP}_VERSION)
			message(FATAL_ERROR "${_LIB_NAME} error: Version:${_LIB_NAME_UP}_VERSION is not set") 
		endif()
		if(${_LIB_NAME_UP}_SOVERSION)
            set_target_properties(${_LIB_NAME} PROPERTIES
                VERSION ${${_LIB_NAME_UP}_VERSION}
                SOVERSION ${${_LIB_NAME_UP}_SOVERSION}
            )
		else()
            set_target_properties(${_LIB_NAME} PROPERTIES
                VERSION ${${_LIB_NAME_UP}_VERSION}
                SOVERSION ${${_LIB_NAME_UP}_MAJOR_VERSION}
            )		
		endif()
    endif()

    #INSTALLATION
    if (${_INSTALL_BIN})
		install(TARGETS ${_LIB_NAME} 
						LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
						ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
                        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)


        if (${${_LIB_NAME_UP}_BUILD_STATIC_TOO})
            install(TARGETS ${_LIB_NAME}_Static
   						LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
						ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
                        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
        endif()
    endif()
	
	mark_as_advanced (
    ${_LIB_NAME}_INCLUDES
	${_LIB_NAME}_DEPENDENCIES_PATH
    )
	
endmacro()

# Add libs to a target
macro (share_target_link_libraries _LIB_NAME)
    target_link_libraries(${_LIB_NAME} ${ARGN})

    #get_target_property(_LIB_EXISTS ${_LIB_NAME}_Static TYPE)
    if (TARGET ${_LIB_NAME}_Static)
        foreach(_LIB ${ARGN})
            if (${_LIB} STREQUAL optimized OR ${_LIB} STREQUAL debug OR ${_LIB} STREQUAL general)
                set (_BUILD ${_LIB})
            else()
                #get_target_property(_LIB_IS_IN_PROJECT ${_LIB}_Static TYPE)

                if (TARGET ${_LIB}_Static)
                    target_link_libraries(${_LIB_NAME}_Static ${_BUILD} ${_LIB}_Static)
                else()
                    target_link_libraries(${_LIB_NAME}_Static ${_BUILD} ${_LIB})
                endif()
            endif()
        endforeach()
    endif()
endmacro()

macro (share_add_dependency _TARGET_NAME )
    
	#get_target_property(_STATIC_EXISTS ${_TARGET_NAME}_Static TYPE)	
	#dynamic
	string(TOUPPER ${_TARGET_NAME} _TARGET_NAME_UP)

	#OPTION(${_TARGET_NAME_UP}_WITH_STATIC_DEPENDENCIES "Link with static dependecies" OFF)
	
    foreach(_DEP_NAME ${ARGN})		
	
		if (${${_TARGET_NAME_UP}_WITH_STATIC_DEPENDENCIES} AND TARGET ${_DEP_NAME}_Static)
			
			string(TOUPPER ${_DEP_NAME}_STATIC _EXPORT_STATIC)
			set_property(TARGET ${_TARGET_NAME} APPEND PROPERTY COMPILE_DEFINITIONS ${_EXPORT_STATIC})
			
			target_link_libraries(${_TARGET_NAME} PRIVATE ${_DEP_NAME}_Static)
		else()
			target_link_libraries(${_TARGET_NAME} ${_DEP_NAME})
		endif()

	#static
		if (TARGET ${_TARGET_NAME}_Static)
			if (TARGET ${_DEP_NAME}_Static)
				string(TOUPPER ${_DEP_NAME}_STATIC _EXPORT_STATIC)
				set_property(TARGET ${_TARGET_NAME}_Static APPEND PROPERTY COMPILE_DEFINITIONS ${_EXPORT_STATIC})
				target_link_libraries(${_TARGET_NAME}_Static ${_DEP_NAME}_Static)
			else()
				target_link_libraries(${_TARGET_NAME}_Static ${_DEP_NAME})
			endif()
		endif()
    endforeach(_DEP_NAME ${ARGN})	
endmacro()

# Define _NAME library to be built 
#       _NAME           - Name of the library to create.
#       _IS_MODULE          - to create a module or shared lib
#       _SOURCE_FILES_VAR   - the source file names.
#       _HEADER_FILES_VAR   - the header file names.
#       _INSTALL_BIN        - TRUE if the lib should be installed

macro (share_add_executable TARGET_NAME _SOURCE_FILES_VAR _HEADER_FILES_VAR _INSTALL_BIN)


	string(TOUPPER ${TARGET_NAME} _NAME_UP)
    #Statically Linked
	set(${_NAME_UP}_WITH_STATIC_DEPENDENCIES false CACHE BOOL "Link with static dependecies")
	#OPTION(${_NAME_UP}_BUILD_STATIC_TOO "Build as static too" ON)

    if (${${_NAME_UP}_WITH_STATIC_DEPENDENCIES})
		add_executable (${TARGET_NAME}_Static ${${_SOURCE_FILES_VAR}} ${${_HEADER_FILES_VAR}})
        string(TOUPPER ${_NAME_UP}_STATIC _EXPORT_STATIC)
		set_property(TARGET ${TARGET_NAME}_Static APPEND PROPERTY COMPILE_DEFINITIONS ${_EXPORT_STATIC})
    endif()

    #Dynamically Linked

    add_executable(${TARGET_NAME} ${${_SOURCE_FILES_VAR}} ${${_HEADER_FILES_VAR}})

    #Install
	if (${_INSTALL_BIN})
		install(TARGETS ${TARGET_NAME} 
						LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
                        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
                        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)


		if (${${_NAME_UP}_WITH_STATIC_DEPENDENCIES})
			install(TARGETS ${TARGET_NAME}_Static
						LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
                        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
                        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
		endif()
	endif(${_INSTALL_BIN})
endmacro()
#Define loadable module - this is loaded dynamically at runtime
macro (add_loadable_module _TARGET_NAME _MAJOR _MINOR)
	
	set(TARGET_NAME ${_TARGET_NAME})
	SET(${CUSTOMER_TARGET_NAME_UP}_AVAILABLE_MODULES ${${CUSTOMER_TARGET_NAME_UP}_AVAILABLE_MODULES} ${TARGET_NAME} CACHE STRING "list of available modules" FORCE)


	string(TOUPPER ${TARGET_NAME} _TARGET_NAME_UP)

	set(${_TARGET_NAME_UP}_BUILD_STATIC_TOO false CACHE INTERNAL "Build static library too" FORCE)
	set(${_TARGET_NAME_UP}_WITH_STATIC_DEPENDENCIES false CACHE INTERNAL "Link ${_TARGET_NAME_UP} with static dependecies" FORCE)

	
#	if(NOT ${${CUSTOMER_TARGET_NAME_UP}_WITH_STATIC_MODULES})
#	else()
#		set(${_TARGET_NAME_UP}_BUILD_STATIC_TOO true CACHE BOOL "Build static library too" FORCE)
#	endif()
	
	add_definitions(${LOGGING_DEFENITIONS})

	configure_version(${TARGET_NAME} ${CMAKE_CURRENT_SOURCE_DIR} ${_MAJOR} ${_MINOR})

	file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)			
	list (APPEND SOURCE_FILES    ${CMAKE_CURRENT_SOURCE_DIR}/revision.c)

	file (GLOB HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

	include_directories (${CMAKE_CURRENT_SOURCE_DIR} ${SHARE_INCLUDES} ${Boost_INCLUDE_DIRS} ${CUSTOMER_INCLUDES} ${UDT_SHARE_INCLUDES} ${LOGGING_INCLUDES})

	#create objects files for for customer
	if(${${CUSTOMER_TARGET_NAME_UP}_WITH_STATIC_MODULES})
		list (FIND ${CUSTOMER_TARGET_NAME_UP}_LIST_STATIC_MODULES ${TARGET_NAME} _index)
		if (${_index} GREATER -1)
			add_library(${TARGET_NAME}_Object OBJECT ${SOURCE_FILES} ${HEADER_FILES})
			
			get_property(CUSTOMER_COMPILE_DEF TARGET ${CUSTOMER_TARGET_NAME} PROPERTY COMPILE_DEFINITIONS)
			
			set_property(TARGET ${TARGET_NAME}_Object APPEND PROPERTY COMPILE_DEFINITIONS 
					${_TARGET_NAME_UP}_STATIC
					${CUSTOMER_TARGET_NAME_UP}_STATIC ${CUSTOMER_COMPILE_DEF})
		endif()
	endif(${${CUSTOMER_TARGET_NAME_UP}_WITH_STATIC_MODULES})
	
	share_add_library(${TARGET_NAME} TRUE SOURCE_FILES HEADER_FILES TRUE)

	share_target_link_libraries(${TARGET_NAME} ${PLATFORM_LIBS} )

	share_add_dependency(${TARGET_NAME} ${CUSTOMER_LIBRARIES})
endmacro()