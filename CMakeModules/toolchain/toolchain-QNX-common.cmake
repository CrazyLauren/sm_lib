#
# toolchain-QNX-common.cmake
#
# Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
#
#  Created on: 12.11.2016
#      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
#
# Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
# https://www.mozilla.org/en-US/MPL/2.0)

set (CMAKE_SYSTEM_NAME      QNX CACHE INTERNAL "")
set (QNX TRUE CACHE INTERNAL "")
set (QNXNTO TRUE CACHE INTERNAL "")
set (TOOLCHAIN              QNX  CACHE INTERNAL "")

set (CMAKE_SYSTEM_VERSION   ${QNX_VERSION_STRING} CACHE STRING "" FORCE)
set (CMAKE_SYSTEM_PROCESSOR ${QNX_PLATFORM} CACHE STRING "" FORCE)



set (CMAKE_SHARED_LIBRARY_PREFIX "lib")
set (CMAKE_SHARED_LIBRARY_SUFFIX ".so")
set (CMAKE_STATIC_LIBRARY_PREFIX "lib")
set (CMAKE_STATIC_LIBRARY_SUFFIX ".a")

# set executable extension on Windows
if (CMAKE_HOST_WIN32)
    set (HOST_EXECUTABLE_SUFFIX ".exe")
endif ()

# set QNX_HOST
if (DEFINED ENV{QNX_HOST})
    set (QNX_HOST $ENV{QNX_HOST} CACHE PATH "")
else ()
    FIND_PATH (QNX_HOST
               NAME usr/bin/qcc${HOST_EXECUTABLE_SUFFIX}
               PATHS "/opt/qnx${QNX_VERSION}/host/linux/x86"
                     "C:/QNX${QNX_VERSION}/host/win32/x86"
               NO_CMAKE_PATH
               NO_CMAKE_ENVIRONMENT_PATH)
endif ()

if(NOT DEFINED QNX_HOST)
	message (FATAL_ERROR "QNX_HOST is not defined")
endif()
# set QNX_TARGET
if (DEFINED ENV{QNX_TARGET})
    set (QNX_TARGET $ENV{QNX_TARGET} CACHE PATH "")
else ()
    find_path (QNX_TARGET
               NAME usr/include/qnx_errno.h
               PATHS "/opt/qnx${QNX_VERSION}/target/qnx6"
                     "C:/QNX${QNX_VERSION}/target/qnx6"
               NO_CMAKE_PATH
               NO_CMAKE_ENVIRONMENT_PATH)
endif ()

if(NOT DEFINED QNX_TARGET)
	message (FATAL_ERROR "QNX_HOST is not defined")
endif()

# set QNX_CONFIGURATIOn (only on Windows)
if (DEFINED ENV{QNX_CONFIGURATION})
    set (QNX_CONFIGURATION $ENV{QNX_CONFIGURATION} CACHE PATH "")
else ()
    if (CMAKE_HOST_WIN32)
        find_path (QNX_CONFIGURATION
                   NAME "bin/qnxactivate.exe"
                   PATHS "C:/Program Files/QNX Software Systems/qconfig"
                   NO_CMAKE_PATH
                   NO_CMAKE_ENVIRONMENT_PATH)
    endif ()
endif ()

if(NOT DEFINED QNX_CONFIGURATION AND CMAKE_HOST_WIN32)
	message (FATAL_ERROR "QNX_CONFIGURATION is not defined")
endif()

file(GLOB _FILES "${QNX_HOST}/usr/bin/nto*")
foreach(_FILE ${_FILES})
	string(REGEX MATCH  "^.*bin[/\\]nto(.*)\\.*-gcc.*-([0-9 .]+)\\.exe" "\\1,\\2" _C ${_FILE})
	if(CMAKE_MATCH_1 AND CMAKE_MATCH_2)
		set(_COMPILERS ${_COMPILERS} ${CMAKE_MATCH_2})
		set(_PATFORMS ${_PATFORMS} ${CMAKE_MATCH_1})
	endif()
endforeach()

if(_COMPILERS)
	list(REMOVE_DUPLICATES _COMPILERS)
	list(REMOVE_DUPLICATES _PATFORMS)
	set(QNX_AVAILABLE_PLATFORMS ${_PATFORMS} CACHE STRING "Available platforms" FORCE)
	set(QNX_AVAILABLE_COMPILERS ${_COMPILERS} CACHE STRING "Available compilers" FORCE)
endif()

list (FIND QNX_AVAILABLE_PLATFORMS ${CMAKE_SYSTEM_PROCESSOR} _index)

if(NOT "${QNX_AVAILABLE_PLATFORMS}" MATCHES ".*(${CMAKE_SYSTEM_PROCESSOR}).*")
	message (FATAL_ERROR "Paltform ${CMAKE_SYSTEM_PROCESSOR} is not available. Available platforms: ${QNX_AVAILABLE_PLATFORMS}")
endif()

if(NOT "${QNX_AVAILABLE_COMPILERS}" MATCHES ".*(${QNX_COMPILER_VERSION}).*")
	message (FATAL_ERROR "Compiler ${QNX_COMPILER_VERSION}, is not available. Available compilers: ${QNX_AVAILABLE_COMPILERS}")
endif()


set (CMAKE_MAKE_PROGRAM "${QNX_HOST}/usr/bin/make${HOST_EXECUTABLE_SUFFIX}" CACHE FILE "QNX Make Program")
set (CMAKE_SH           "${QNX_HOST}/usr/bin/sh${HOST_EXECUTABLE_SUFFIX}"   CACHE FILE "QNX shell Program")
set (CMAKE_AR           "${QNX_HOST}/usr/bin/nto${CMAKE_SYSTEM_PROCESSOR}-ar${HOST_EXECUTABLE_SUFFIX}"      CACHE FILE "QNX ar Program")
set (CMAKE_RANLIB       "${QNX_HOST}/usr/bin/nto${CMAKE_SYSTEM_PROCESSOR}-ranlib${HOST_EXECUTABLE_SUFFIX}"  CACHE FILE "QNX ranlib Program")
set (CMAKE_NM           "${QNX_HOST}/usr/bin/nto${CMAKE_SYSTEM_PROCESSOR}-nm${HOST_EXECUTABLE_SUFFIX}"      CACHE FILE "QNX nm Program")
set (CMAKE_OBJCOPY      "${QNX_HOST}/usr/bin/nto${CMAKE_SYSTEM_PROCESSOR}-objcopy${HOST_EXECUTABLE_SUFFIX}" CACHE FILE "QNX objcopy Program")
set (CMAKE_OBJDUMP      "${QNX_HOST}/usr/bin/nto${CMAKE_SYSTEM_PROCESSOR}-objdump${HOST_EXECUTABLE_SUFFIX}" CACHE FILE "QNX objdump Program")
set (CMAKE_LINKER       "${QNX_HOST}/usr/bin/nto${CMAKE_SYSTEM_PROCESSOR}-ld" CACHE FILE "QNX Linker Program")
set (CMAKE_STRIP        "${QNX_HOST}/usr/bin/nto${CMAKE_SYSTEM_PROCESSOR}-strip${HOST_EXECUTABLE_SUFFIX}"   CACHE FILE "QNX Strip Program")


set (CMAKE_C_COMPILER ${QNX_HOST}/usr/bin/qcc${HOST_EXECUTABLE_SUFFIX} CACHE FILE "" FORCE)

set (CMAKE_C_FLAGS_INIT "-V${QNX_COMPILER_VERSION},gcc_nto${CMAKE_SYSTEM_PROCESSOR}" CACHE INTERNAL "" FORCE)
set (CMAKE_C_FLAGS_DEBUG "-g" CACHE STRING "")
set (CMAKE_C_FLAGS_MINSIZEREL "-Os -DNDEBUG" CACHE STRING "")
set (CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG" CACHE STRING "")
set (CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g" CACHE STRING "")

set (CMAKE_CXX_COMPILER ${QNX_HOST}/usr/bin/qcc${HOST_EXECUTABLE_SUFFIX} CACHE FILE "" FORCE)

set (CMAKE_CXX_FLAGS_INIT "${CMAKE_C_FLAGS_INIT}" CACHE INTERNAL "" FORCE)
set (CMAKE_CXX_FLAGS_DEBUG "-g" CACHE STRING "")
set (CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG" CACHE STRING "")
set (CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG" CACHE STRING "")
set (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g" CACHE STRING "")


set (CMAKE_FIND_ROOT_PATH ${QNX_TARGET} CACHE STRING "") 
set (CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set (CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set (CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)



