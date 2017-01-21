/*
 * revision.h
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 22.03.2013
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */
 
#ifndef CONTROL_VERSION_H_
#define CONTROL_VERSION_H_

#ifdef __cplusplus
#define SHARE_EXTERN_REVISION extern "C"
#else
#define SHARE_EXTERN_REVISION extern
#endif

#define DECLARATION_VERSION_FOR(aNAME) \
		SHARE_EXTERN_REVISION unsigned get_revision_number_##aNAME();\
		SHARE_EXTERN_REVISION unsigned get_major_version_##aNAME();\
		SHARE_EXTERN_REVISION unsigned get_minor_version_##aNAME();\
		SHARE_EXTERN_REVISION const char* get_revision_path_##aNAME();\
		SHARE_EXTERN_REVISION const char* get_compile_time_##aNAME();\
		SHARE_EXTERN_REVISION const char* get_compile_data_##aNAME();

#define REVISION_OF(aNAME) get_revision_number_##aNAME()
#define REVISION_PATH_OF(aNAME) get_revision_path_##aNAME()
#define MAJOR_VERSION_OF(aNAME) get_major_version_##aNAME()
#define MINOR_VERSION_OF(aNAME) get_minor_version_##aNAME()
#define COMPILE_TIME_OF(aNAME) get_compile_time_##aNAME()
#define COMPILE_DATA_OF(aNAME) get_compile_data_##aNAME()



#endif /*CONTROL_VERSION_H_*/
