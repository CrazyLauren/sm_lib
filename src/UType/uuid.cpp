/*
 * uuid.cpp
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 30.11.2015
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */
#include <deftype>
#include <boost/uuid/uuid_generators.hpp>

namespace NSHARE
{
static uint64_t uuid_generate_time(CText const& aText = CText())
{
	uint8_t out[8];
	srand(NSHARE::get_unix_time()%std::numeric_limits<unsigned>::max());
	uint64_t time = NSHARE::get_unix_time();
	out[0] = (uint8_t) (time >> 56) | (uint8_t) (time);
	out[1] = (uint8_t) (time >> 48) ^ (uint8_t) (time >> 8);
	out[2] = rand() & 0xFF;
	out[3] = rand() & 0xFF;

	unsigned _pid = NSHARE::CThread::sMPid(); //getpid();
	out[4] = rand() & 0xFF;
	out[5] = rand() & 0xFF;
	out[6] = ((_pid >> 8) & 0xFF) ^ 0x0A;
	out[7] = (_pid & 0xFF) | 0x10;

	for (CText::const_iterator _it = aText.begin(); _it != aText.end(); ++_it)
	{
		const unsigned _pos = rand() % 4 + 2;
		out[_pos] = out[_pos] ^ (*_it & 0xFF);
	}
	boost::uuids::uuid _b_uuid = boost::uuids::random_generator()();
	for (boost::uuids::uuid::iterator _it = _b_uuid.begin();
			_it != _b_uuid.end(); ++_it)
	{
		const unsigned _pos=rand()%6;
		out[_pos] = out[_pos] ^ (*_it& 0xFF);
	}

	memcpy(&time, out, sizeof(time));
	return time;
}
static uuid_t g_uuid;
uuid_t get_uuid(CText const& aVal)
{
	uuid_t _rval;
	for(HANG_INIT;(_rval.FVal = uuid_generate_time(aVal))==0;HANG_CHECK)
		;
	return _rval;
}

const CText uuid_t::NAME="uuid";
uuid_t::uuid_t(NSHARE::CConfig const& aConf) :
		FVal(0)
{
	if(!aConf.MValue().empty())
		FVal = aConf.MValue<uint64_t>(0);
	VLOG(4)<<"Value = "<<FVal;
}
CConfig uuid_t::MSerialize() const
{
	return CConfig(NAME,FVal);
}
CText uuid_t::MToString() const
{
	char _buf[64];
	uint8_t const *_this = reinterpret_cast<uint8_t const *>(&FVal);
	sprintf(_buf, "%02x-%02x-"
		"%02x-%02x-"
		"%02x-%02x-"
		"%02x-%02x", _this[0], _this[1], _this[2], _this[3], _this[4],
		_this[5], _this[6], _this[7]);
	return _buf;
}
bool uuid_t::MIsValid() const
{
	return FVal != 0;
}
bool uuid_t::MFromString(CText const& aText)
{
	uint8_t *_this = reinterpret_cast<uint8_t *>(&FVal);
	uint32_t _data[8];
	memset(_data, 0, sizeof(_data));
	int count = sscanf(aText.c_str(),
			"%*c%*c%02x%*c" //
					"%*c%*c%02x%*c"//
					"%*c%*c%02x%*c"//
					"%*c%*c%02x%*c"//
					"%*c%*c%02x%*c"//
					"%*c%*c%02x%*c"//
					"%*c%*c%02x%*c"//
					"%*c%*c%02x"//
			, &_data[0], &_data[1], &_data[2], &_data[3], &_data[4], &_data[5],
			&_data[6], &_data[7]);
	if (count == 8)
	{
		for (int i = 0; i < 8; ++i)
			_this[i] = _data[i];
	}
	return count == 8;
}
uuid_t get_programm_uuid(CText const& aVal)
{
	static bool g_is_uuid = false;
	if (!g_is_uuid)
	{
		CText _text = aVal;
		if (aVal.empty())
			_text= get_random_str(8);
		g_is_uuid = true;
		volatile uuid_t _uuid = get_uuid(_text);
		g_uuid.FVal = _uuid.FVal;
	}
	return g_uuid;
}
uint32_t uuid_t::MGetHash() const
{
	uint64_t _val = FVal;
	_val = (~_val) + (_val << 18);
	_val = _val ^ (_val >> 31);
	_val *= 21;
	_val = _val ^ (_val >> 11);
	_val = _val + (_val << 6);
	_val = _val ^ (_val >> 22);
	return (uint32_t)_val;
}
CText get_random_str(size_t aLen)
{
	static char const _alphanum[] = "0123456789"
		"QWERTYUIOPASDFGHJKLZXCVBNM"
		"qwertyuiopasdfghjklzxcvbnm";
	static size_t const _alphanum_size = sizeof(_alphanum) - 1;
	if (!aLen)
	{
		VLOG(1) << "The Random string size is null.";
		return CText();
	}

	CText _rstr; 
	_rstr.resize(aLen);

	uint64_t _val = get_uuid().FVal;
	for (unsigned i = 0; aLen != 0;)	//aLen всегда >0
	{
		uint8_t _pos = (_val >> (i * 8)) & 0xff;
		_rstr[--aLen] = _alphanum[_pos % _alphanum_size];
		if (++i == sizeof(_val))
		{
			_val = get_uuid().FVal;
			i = 0;
		}
	}

	return _rstr;
}
}
;

