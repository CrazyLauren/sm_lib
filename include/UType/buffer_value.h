/*
 * buffer_value.h
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 29.06.2016
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */ 
#ifndef BUFFER_VALUE_H_
#define BUFFER_VALUE_H_

namespace NSHARE
{
template<class T>
struct buf_val_t
{
	buf_val_t()
	{
	}
	;
	buf_val_t(T const & aVal) :
			FVal(aVal)
	{
	}
	;
	template<typename U>
	explicit buf_val_t(U const & aVal) :
			FVal(aVal)
	{
	}
	;

	operator T()
	{
		return FVal;
	}
	operator T const() const
	{
		return FVal;
	}
private:
	T FVal;
};
#ifdef COMPILE_ASSERT
COMPILE_ASSERT(sizeof(buf_val_t<uint8_t>)==sizeof(uint8_t),InvalidSizeofBufVal8);
COMPILE_ASSERT(sizeof(buf_val_t<uint16_t>)==sizeof(uint16_t),InvalidSizeofBufVal16);
COMPILE_ASSERT(sizeof(buf_val_t<uint32_t>)==sizeof(uint32_t),InvalidSizeofBufVal32);
#endif
//typedef struct TagBuffer: std::vector<buf_val_t<uint8_t> >
//{
//	typedef std::vector<buf_val_t<uint8_t> > base_t;
//	typedef buf_val_t<uint8_t> val_type;
//	TagBuffer()
//	{
//	}
//	TagBuffer(size_type aSize, const uint8_t &aVal = 0) :
//			base_t(aSize, aVal)
//	{
//	}
//	TagBuffer(TagBuffer const& aBuf) :
//			base_t(aBuf)
//	{
//	}
//	template<class TIt>
//	TagBuffer(TIt aFirst, TIt aLast) :
//			base_t(aFirst, aLast)
//	{
//	}
//} buffer_t;
namespace detail
{
template<class T>
inline std::ostream& print_b_value(std::ostream& aStream, T const& aVal)
{
	aStream.setf(std::ios::hex, std::ios::basefield);
	aStream << "0x" << static_cast<unsigned const&>(aVal);
	aStream.unsetf(std::ios::hex);
	return aStream;
}
};
template<class T>
inline std::ostream& print_buffer(std::ostream& aStream, T aBegin, T aEnd)
{
	int _i = 0;
	for (; aBegin != aEnd; ++aBegin)
	{
		detail::print_b_value(aStream,*aBegin);
		aStream << " ";
		if (!(++_i % 8))
			aStream << "\n";
	}
	return aStream;
}
template<class T>
struct print_buffer_t
{
	const T& FBegin;
	const T& FEnd;
	print_buffer_t(const T& aBegin, const T& aEnd) :
			FBegin(aBegin), FEnd(aEnd)
	{
	}
};
}
namespace std
{
template<typename T>
inline std::ostream& operator<<(std::ostream & aStream,
		NSHARE::print_buffer_t<T> const& aVal)
{
	NSHARE::print_buffer(aStream,aVal.FBegin,aVal.FEnd);
	return aStream;
}
template<typename T>
inline std::ostream& operator<<(std::ostream & aStream,
		NSHARE::buf_val_t<T> const& aVal)
{
	aStream.setf(ios::hex, ios::basefield);
	aStream << "0x" << static_cast<unsigned const&>(aVal);
	aStream.unsetf(ios::hex);
	return aStream;
}
//inline std::ostream& operator<<(std::ostream& aStream,
//		NSHARE::buffer_t const& aVal)
//{
//	aStream << "Buffer size =" << aVal.size() << ",\n";
//	NSHARE::print_buffer(aStream, aVal.begin(), aVal.end());
//	return aStream;
//}

//inline std::ostream& operator<<(std::ostream & aStream,
//		NSHARE::buffer_t::const_iterator const& aIt)
//{
//	aStream.setf(ios::hex, ios::basefield);
//	aStream << "PData=0x" << reinterpret_cast<intptr_t>(&(*aIt)) << ", PIt=0x"
//			<< &aIt;
//	aStream.unsetf(ios::hex);
//	return aStream;
//}
template<class T>
struct numeric_limits<NSHARE::buf_val_t<T> >:numeric_limits<T>
{

};
}
#endif /* BUFFER_VALUE_H_ */
