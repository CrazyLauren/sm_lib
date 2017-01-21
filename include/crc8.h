/*
 * crc8.h
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 03.09.2012
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */
#ifndef _CRC8_H_
#define _CRC8_H_

#define INITIAL_CRC8  0x00
namespace NSHARE
{
extern const uint8_t CrcTable[256];

uint8_t SHARE_EXPORT SHARED_DEPRECATED_F(CalcCRC8(uint8_t const *pBuffer, int nSize, uint8_t bOldCRC8 =
		INITIAL_CRC8));

template<class T>
uint8_t SHARED_DEPRECATED_F(CalcCRC8(T  pBegin, T const& pEnd, uint8_t aCRC8 = INITIAL_CRC8))
{
	for (; pBegin!= pEnd;++pBegin)
		aCRC8 = CrcTable[aCRC8 ^ *pBegin];

	return aCRC8;
}

///@brief structure that helps to work with crc8
/// @tparam FPolynom crc8 polynomial
/// @tparam TOffset Initial value
/// @tparam TLsb Byte order
template<unsigned FPolynom, uint8_t TInitValue = INITIAL_CRC8, bool TLsb = false>
struct crc8_t
{

	typedef uint8_t type_t;

	enum
	{
		Polynom = FPolynom
	};
	enum
	{
		Initial = TInitValue
	};
	enum
	{
		SizeTable = 256
	};
	enum
	{
		isLSB = TLsb
	};
	struct table_t
	{
		table_t();
		type_t FCrc[SizeTable];
	};
	///@brief CRC Table
	///@return  CRC Table
	static type_t const* sMCRCTable();

	///@brief Print CRC Table
	inline static void sMPrintTable(std::ostream & aStream);

	///@brief Calculate buffer CRC
	///@tparam  T type of buffer pointer
	///@param  pBegin Buffer begin
	///@param  pEnd Buffer end
	///@param  aOffset Initial value
	template<class T>
	inline static type_t sMCalcCRCofBuf(T const* __restrict  pBegin, T const* __restrict   pEnd,
			 type_t aOffset = Initial)
	{
		static const table_t _table;
		size_t const _size=pEnd-pBegin;
		for (size_t i=0; i<_size; ++i)
			aOffset = _table.FCrc[aOffset ^ pBegin[i]]; /*sMCalcNextCRC(aOffset, *pBegin)*/

		return aOffset;
	}
	template<class U>
	inline static type_t sMCalcCRCofBuf2(U pBegin, U const& pEnd,
			type_t aOffset = Initial)
	{
		for (; pBegin != pEnd; ++pBegin)
			aOffset = sMCalcNextCRC(aOffset, *pBegin);

		return aOffset;
	}
	///@brief Adds the following byte to the CRC
	///@param aCRC8 Current  CRC
	///@param  aNextVal  The following byte
	///@return  new CRC
	inline static type_t sMCalcNextCRC(type_t aCRC8, type_t aNextVal)
	{
		return sMCRCTable()[aCRC8 ^ aNextVal];
	}

	///@brief Return checking const
	///@param aCRC8 Current  CRC
	///@param  aNextVal  The following byte
	///@return  new CRC
	inline static type_t sMCheckingConstant()
	{
		return sMCalcNextCRC(Initial,Initial);
	}

private:

	inline static void sMPrintHex(std::ostream & aStream, unsigned aVal)
	{

		aStream.setf(std::ios::hex, std::ios::basefield);
		aStream << "0x" << static_cast<unsigned const&>(aVal);
		aStream.unsetf(std::ios::hex);
	}
	template<typename TPolyType,bool _TLsb=true>
	struct make_t;
};
/*
struct head_t
{
	//1-st word
	uint16_t FHeadSize;
	uint16_t FTimeMs;

	uint8_t FTime;
	uint8_t FCrcHead;
};
int main(int argc, char *argv[])
{
	typedef NSHARE::crc8_t<0x87, 0x01> crc_head_t;
	{
		head_t _head;
		_head.FCrcHead = crc_head_t::sMCalcCRCofBuf((uint8_t*) &_head+1,
				(uint8_t*) &_head + sizeof(head_t) - 1); //-1 - calculate without FCrcHead

		//search of head
		if (crc_head_t::sMCalcCRCofBuf((uint8_t*) &_head,
				(uint8_t*) &_head + sizeof(head_t))
				== crc_head_t::sMCheckingConstant())
			std::cout << "Crc is valid" << std::endl;
		else
			std::cerr << "Crc is not valid" << std::endl;
	}
	return EXIT_SUCCESS;
}
*/

template<unsigned FPolynom, uint8_t TOffset, bool FTLSb>
template<typename TPolyType,bool _TLsb>
struct crc8_t<FPolynom, TOffset, FTLSb>::make_t
{
	///@brief Calculate CRCR table
	/// @param _crctab CRC Table
	inline static void sMakeCRCTable(type_t _crctab[SizeTable])
	{
		TPolyType _remaind = 1;

		_crctab[0] = 0;

		for (int i = (SizeTable >> 1); i; i >>= 1)
		{
			_remaind = (_remaind >> 1) ^ (_remaind & 1 ? Polynom : 0);
			for (int j = 0; j < SizeTable; j += 2 * i)
				_crctab[i + j] = _crctab[j] ^ _remaind;
		}

	}
};
template<unsigned FPolynom, uint8_t TOffset, bool FTLSb>
template<typename TPolyType>
struct crc8_t<FPolynom, TOffset, FTLSb>::make_t<TPolyType,false>
{
	typedef NSHARE::crc8_t<FPolynom, TOffset, FTLSb> base_t;
	inline static void sMakeCRCTable(typename base_t::type_t _crctab[base_t::SizeTable])
	{
		const TPolyType msbit = 0x80;
		TPolyType _remaind = msbit;

		_crctab[0] = 0;

		for (int i = 1; i < base_t::SizeTable; i *= 2)
		{
			_remaind = (_remaind << 1) ^ (_remaind & msbit ? base_t::Polynom : 0);
			for (int j = 0; j < i; j++)
				_crctab[i + j] = _crctab[j] ^ _remaind;
		}

	}
};
template<unsigned FPolynom, uint8_t TOffset, bool FTLSb>
inline crc8_t<FPolynom, TOffset, FTLSb>::table_t::table_t()
{
	make_t<unsigned, isLSB>::sMakeCRCTable(FCrc);
}

template<unsigned FPolynom, uint8_t TOffset, bool FTLSb>
inline
typename crc8_t<FPolynom, TOffset, FTLSb>::type_t const* crc8_t<FPolynom, TOffset,
		FTLSb>::sMCRCTable()
{
	static const table_t _crc;
	return _crc.FCrc;
}
template<unsigned FPolynom, uint8_t TOffset, bool FTLSb>
inline void crc8_t<FPolynom, TOffset, FTLSb>::sMPrintTable(std::ostream & aStream)
{
	aStream << "CRC8 Polynomial ";
	sMPrintHex(aStream, FPolynom);
	aStream << std::endl;

	for (int i = 0; i < SizeTable; i++)
	{
		sMPrintHex(aStream, sMCRCTable()[i]);
		if (!((i + 1) % 4))
			aStream << std::endl;
		else
			aStream << "\t";
	}
	aStream << std::endl;
}
} //namespace USHARE
namespace std
{
template<unsigned FPolynom, uint8_t TOffset, bool FTLSb>
inline std::ostream& operator<<(std::ostream & aStream,
		struct NSHARE::crc8_t<FPolynom, TOffset, FTLSb> const& aCrc)
{
	aCrc.sMPrintTable(aStream);
	return aStream;
}
}
#endif                                      // #ifndef _CRC8_H_
