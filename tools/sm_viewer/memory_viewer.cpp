// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * memory_viewer.cpp
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 11.12.2016
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren/UDT)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */
#include <shm_ipc.h>
#include <iostream>
#include <fstream>
#include <UType/CCommonAllocater.h>
#include <UType/CSharedMemory.h>

using namespace NSHARE;

int main(int argc, char *argv[])
{
	CSharedMemory _memory;
	if(argc==1)
	{
		std::cerr<<"Unable to load SM. It's not specified as second argument."<<std::endl;
		return -1;
	}
	std::cout << "View SM:" << argv[1] << std::endl;
	bool _is = _memory.MOpen(argv[1],false);

	CConfig _conf(argv[1]);
	std::cout<<"serializing"<<std::endl;
	_memory.MSerialize(_conf);
	
	std::cout<<"data output"<<std::endl;
	std::stringstream output_stream;
	_conf.MToJSON(output_stream,true);
	std::cout<<output_stream.str()<<std::endl;
	std::fstream _stream;
	std::cout<<"saving to ./mem.json"<<std::endl;
	_stream.open("./mem.json",std::ios_base::in | std::ios_base::out|std::ios_base::trunc);
	_stream<<output_stream.str();
	_stream.close();
	std::cout<<"finish"<<std::endl;
	return 0;
}

