#
# toolchain-QNX-6.4.0.cmake
#
# Copyright © 2016 https://github.com/CrazyLauren 
#
#  Created on: 12.11.2016
#      Author: https://github.com/CrazyLauren 
#
# Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
# https://www.mozilla.org/en-US/MPL/2.0)

set (QNX_VERSION        640)
set (QNX_VERSION_STRING 6.4.0 CACHE STRING "QNX version")
set (QNX_PLATFORM x86 CACHE STRING "")
set (QNX_COMPILER_VERSION "4.2.4" CACHE STRING "QCC version")

set (CISST_TOOLCHAIN_DIR ${CMAKE_CURRENT_LIST_DIR})

include ("${CISST_TOOLCHAIN_DIR}/toolchain-QNX-common.cmake")
