/*
 * client.cpp
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 24.06.2016
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren/UDT)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */
#include <deftype>
#include <iostream>
#include <sm_socket.h>

using namespace NSHARE;

#define SEND_BUF_SIZE 1000

int main(int argc, char *argv[])
{
	for (;;)
	{
		CSharedMemoryClient _client;

		for (;!_client.MOpen("test"); NSHARE::usleep(100000))
		{
			std::cerr << "Cannot opened test SM" << std::endl;
		}
		std::cout << "Opened" << std::endl;
		for(;!_client.MConnect();)
			std::cerr << "Cannot connect to server 'test'" << std::endl;
		std::cout << "Connected" << std::endl;
		std::cout << "Buf suze="<<SEND_BUF_SIZE <<" bytes"<< std::endl;
		
		unsigned _flags=1;
		for (;;)
		{
			NSHARE::CBuffer _buf=_client.MAllocate(SEND_BUF_SIZE);
			if(!_buf.empty() && _client.MSend(_buf,false,_flags)==CSharedMemoryClient::E_SENDED)
				++_flags;
		}
		NSHARE::usleep(10000);
		std::cerr << "closing" << std::endl;
		_client.MClose();
		std::cerr << "closed" << std::endl;

	}

}

