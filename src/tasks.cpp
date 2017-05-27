// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * tasks.cpp
 *
 * Copyright © 2016 https://github.com/CrazyLauren 
 *
 *  Created on: 12.04.2016
 *      Author: https://github.com/CrazyLauren 
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */ 
#include <deftype>
#include <tasks.h>
#include <signal.h>
namespace NSHARE
{
bool is_process_exist(int pID)
{
	VLOG(2) << "Checking  process " << pID << " exist.";
#if defined(_WIN32)
	HANDLE handle = OpenProcess(PROCESS_QUERY_INFORMATION, false, pID);
	if (!handle)
	{
		VLOG(2)<<"The process "<<pID<<" is not exist.";
		return false;
	}
	else
	{
		DWORD _status=0;
		bool _result=GetExitCodeProcess(handle,&_status)!=FALSE;
		CloseHandle(handle);
		VLOG_IF(2,_result)<<"The process "<<pID<<" is   exist.";
		VLOG_IF(2,!_result)<<"The process "<<pID<<" is not   exist.";
		return _status==STILL_ACTIVE;
	}
#else
	if (kill(pID, 0) != 0 && errno != EPERM)
	{
		VLOG(2) << "The process " << pID << " is not  exist.";
		return false;
	}
	else
	{
		VLOG(2) << "The process " << pID << " is  exist.";
		return true;
	}
#endif
}
}
