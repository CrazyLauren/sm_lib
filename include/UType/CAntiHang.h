/*
 * CAntiHang.h
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 09.11.2015
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */ 
#ifndef CANTIHANG_H_
#define CANTIHANG_H_

#define HANG_INIT NSHARE::CAntiHang _hang(__FILE__,__LINE__)
#define HANG_CHECK _hang()
namespace NSHARE
{

class  CAntiHang
{
	double FTime;
	unsigned FCount;
	char const * FFile;
	unsigned const FLine;
public:
	CAntiHang(char const* aFile, const unsigned & aLine) : //
		FTime(0),//
		FCount(0),//
		FFile(aFile), //
			FLine(aLine) //
	{
	}
	CAntiHang() : //
			FTime(0),//
			FCount(0),//
			FFile(NULL), //
			FLine(0) //
	{
	}
	void operator()()
	{
		++FCount;
		if ((FCount ==10) || //after the first 10 reps is done,
			(FCount % 15 == 0)//Hang checking every 15 reps will be started 
			) 
		{
			double _delta = NSHARE::get_time() - FTime;
			if (_delta < 0.01) //10 ms
			{
				NSHARE::usleep(10000);
				LOG_IF(WARNING, !FFile) << "Hang occur in unknown place.";
				LOG_IF(WARNING, FFile) << "Hang occur in " << FFile << ":"
						<< FLine;
			}
			FTime = NSHARE::get_time();
		}
	}
	unsigned MCounter() const
	{
		return FCount;
	}
};
} /* namespace NSHARE */
#endif /* CANTIHANG_H_ */
