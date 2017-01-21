/*
 * ISocket.h
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 12.04.2013
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */  
#ifndef ISOCKET_H_
#define ISOCKET_H_

namespace NSHARE
{

class SHARE_EXPORT ISocket
{
public:
	enum eSendState
	{
		E_SENDED = 0, //
		E_ERROR = -1,//
		E_AGAIN = -2,//The client buffer is full
		E_TOO_LARGE = -3,
		E_NOT_OPENED = -4,
		E_INVALID_VALUE = -5
	};
	struct sent_state_t
	{
		sent_state_t(eSendState eError,size_t aBytes):
		FError(eError), //
		FBytes(aBytes)//
		{

		}
		sent_state_t()
		{
			FError=E_ERROR;
			FBytes=0;
		}
		bool MIs() const
		{
			return FError ==E_SENDED;
		}
		eSendState FError;
		size_t FBytes;
	};

	enum eFlush
	{
		FLUSH_IN = 0x1 << 0, FLUSH_OUT = 0x1 << 1,
	};

	typedef NSHARE::CBuffer data_t;

	struct receive_from_t
	{
		NSHARE::CConfig FAddr; //json info
		data_t::iterator FBufBegin;
		data_t::difference_type FSize;
	};
	typedef std::vector<receive_from_t> recvs_from_t;

	struct status_t
	{
		size_t FReadBytes;
		size_t FReadError;

		size_t FWriteBytes;
		size_t FWriteError;
	};

	virtual ~ISocket()
	{
		;
	}

	virtual size_t MAvailable() const=0;
	virtual bool MIsOpen() const =0;
	virtual void MClose()=0;
	virtual bool MReOpen()=0;

	virtual sent_state_t MSend(void const* aData, std::size_t aSize,
			NSHARE::CConfig const& aTo)
	{
		VLOG(0)<<"MSend to is not implemented";
		return MSend(aData, aSize);
	}
	virtual sent_state_t MSend(void const* aData, std::size_t aSize)=0;

	sent_state_t MSend(data_t const& aVal)
	{
		if(aVal.empty())
		return MSend(NULL, 0);
		else
		return MSend(aVal.ptr_const(), aVal.size());
	}
	sent_state_t MSend(data_t const& aVal, NSHARE::CConfig const& aTo)
	{
		if(aVal.empty())
		return MSend(NULL, 0);
		else
		return MSend(aVal.ptr_const(), aVal.size(),
				aTo);
	}
	//one of the method must be oveloaded, otherwise the recursion will be.
	virtual ssize_t MReceiveData(data_t * aData, float const aTime,
			recvs_from_t *aFrom)
	{
		VLOG(0)<<"MReceiveData from is not implemented";
		return MReceiveData(aData, aTime);
	}
	virtual ssize_t MReceiveData(data_t *aData, float const aTime)
	{
		VLOG(0)<<"MReceiveData is not implemented";
		return MReceiveData(aData, aTime, NULL);
	}
	virtual std::ostream & MPrint(std::ostream & aStream) const =0;
	virtual NSHARE::CConfig MSerialize() const=0;
	virtual NSHARE::CConfig MSettings(void) const=0;
	virtual void MFlush(eFlush const&)
	{
		;
	}
	virtual size_t MMaxPacketSize()
	{
		return ((size_t)-1);
	}

protected:
	ISocket()
	{
	}
private:
	ISocket(ISocket const&)
	{
	}
	ISocket & operator=(ISocket const&)
	{	return *this;
	}
};
}
 //namespace USHARE
namespace std
{
inline std::ostream& operator <<(std::ostream& aStream,
	const NSHARE::ISocket& aSock)
{
return aSock.MPrint(aStream);
}
inline std::ostream& operator <<(std::ostream& aStream,
	const NSHARE::ISocket::recvs_from_t& aAddress)
{
if (aAddress.empty())
	return aStream << "No addresses";
NSHARE::ISocket::recvs_from_t::const_iterator _it = aAddress.begin();
for (;;)
{
	aStream << _it->FAddr;
	if (++_it == aAddress.end())
		break;
	else
		aStream << ",";
}
return aStream;
}
inline std::ostream& operator <<(std::ostream& aStream,
	const NSHARE::ISocket::sent_state_t& aVal)
{
return aStream << " Error = " << aVal.FError << " sent=" << aVal.FBytes;
}
}
#endif /* ISOCKET_H_ */
