/*
 * CRAII.h
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 05.04.2013
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */ 
#ifndef CRAII_H_
#define CRAII_H_

namespace NSHARE
{
class  CDenyCopying;
template<class T> class  CRAII: public CDenyCopying
{
public:
	CRAII()
	{
		T _error;
		_error.This_type_is_not_specialized=true;
		_error.Specialize_this_type=true;
	}
};
}//namespace USHARE

#endif /*CRAII_H_*/
