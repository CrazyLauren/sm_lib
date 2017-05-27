/*
 * revision.c
 *
 * Copyright © 2016 https://github.com/CrazyLauren 
 *
 *  Created on: 15.10.2015
 *      Author: https://github.com/CrazyLauren 
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 * revision file for GIT
 */ 
#include <stdlib.h>
#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN extern
#endif

#define MAJOR 0
#define MINOR 4
#define REVISION "0"
#define REVISION_PATH "no path"
#define TIME	"13:14:00"
#define DATA	"2017-02-19"
static char gPath[]=REVISION_PATH;
static char gTime[]=TIME;
static char gData[]=DATA;

EXTERN unsigned get_revision_number_SM_SOCKET()
{
	return atoi(REVISION);
}

EXTERN const char* get_revision_path_SM_SOCKET()
{
	return gPath;
}
EXTERN const char* get_compile_time_SM_SOCKET()
{
	return gTime;
}
EXTERN const char* get_compile_data_SM_SOCKET()
{
	return gData;
}
EXTERN unsigned get_major_version_SM_SOCKET()
{
	return MAJOR;
}
EXTERN unsigned get_minor_version_SM_SOCKET()
{
	return MINOR;
}
