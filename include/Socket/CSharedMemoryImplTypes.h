/*
 * CSharedMemoryImplTypes.h
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 11.05.2016
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */
#ifndef CSHAREDMEMORYIMPLTYPES_H_
#define CSHAREDMEMORYIMPLTYPES_H_

namespace NSHARE
{
static const uint32_t INVALID_PID = 0;
//static const uint32_t DEF_FIFO_SIZE = 1128;
#define EVENT_RESERV 4
SHARED_PACKED(struct shared_port_t
{
	shared_port_t(uint32_t aPid) :
			FPid(aPid), FUserID(std::numeric_limits<uint16_t>::max()), FUniqueID(
					0)
	{

	}
	shared_port_t() :
			FPid(0), FUserID(std::numeric_limits<uint16_t>::max()), FUniqueID(0)
	{

	}
	inline shared_identify_t MGetId() const
	{
		shared_identify_t _id;
		_id.FPid = FPid;
		_id.FDescriptor = FUniqueID;
		_id.FUserId=FUserID;
		VLOG(2) << "Id of " << FPid << " = " << _id << " Unique Id="
				<< FUniqueID;
		return _id;
	}
	bool operator==(shared_port_t const& aRht) const
	{
		return  FPid == aRht.FPid && FUniqueID == aRht.FUniqueID;
	}
	bool operator!=(shared_port_t const& aRht) const
	{
		return !operator==(aRht);
	}
	bool operator<(shared_port_t const& aRht) const
	{
		return FPid < aRht.FPid && FUniqueID < aRht.FUniqueID;
	}
	bool operator>(shared_port_t const& aRht) const
	{
		return FPid > aRht.FPid && FUniqueID > aRht.FUniqueID;
	}
	bool operator<=(shared_port_t const& aRht) const
	{
		return FPid <= aRht.FPid && FUniqueID <= aRht.FUniqueID;
	}
	bool operator>=(shared_port_t const& aRht) const
	{
		return FPid >= aRht.FPid && FUniqueID >= aRht.FUniqueID;
	}
	uint32_t FPid; //Pid
	uint16_t FUserID; //It's used by user for identify client
	uint16_t FUniqueID; //it'is setuped by server
});
COMPILE_ASSERT(sizeof(shared_port_t) == 8,
		IVALID_SIZEOF_SHARED_PORT);
SHARED_PACKED(struct event_info_t
{
	event_info_t() :
			FEventType(0),FCounter(0)
	{

	}
	enum eEventType
	{
		E_NO, //
		E_DATA, //
		E_DATA_CONFIRAMTION, //
		E_CONNECT, //request
		E_CONNECTED, //answer
		E_DISCONECT, //request
		E_DISCONECTED, //answer
		E_KEEPALIVE_REQUEST, //
		E_KEEPALIVE_ANSWER, //
		MAX_EVENT_VALUE////for internal use only
	};
	enum
	{
		E_KEAP_RECV=1
	};
	struct connect_t
	{
		CSharedAllocator::offset_t FClientOffset;
	};
	struct keap_t
	{
		CSharedAllocator::offset_t FInfoOffset;
		uint8_t FAnswer;
	};
	struct recv_t
	{
		CSharedAllocator::offset_t FBufferOffset;
		CSharedAllocator::block_size_t FSize;
		uint32_t FBlockCode;//if is zero - Receiving of packet  has not to be  confirmed
		uint32_t FFlags;
	};
	struct data_confirmation_t
	{
		uint32_t FBlockCode;
	};
	uint32_t FEventType :8;
	uint32_t FCounter:24;
	shared_port_t FIdFrom;
	union
	{
		recv_t FRecive;
		data_confirmation_t FDataConfiramtion;
		connect_t FConnect;
		keap_t FKeapAlive;
	};
});
COMPILE_ASSERT(sizeof(event_info_t::recv_t) ==(sizeof(uint32_t)*3+sizeof(CSharedAllocator::offset_t)),
		IVALID_SIZEOF_EVENT_INFO_RECV);
COMPILE_ASSERT(sizeof(event_info_t) ==(sizeof(shared_port_t)+sizeof(event_info_t::recv_t)+sizeof(uint32_t)),
		IVALID_SIZEOF_EVENT_INFO);
SHARED_PACKED(struct event_fifo_t
{
	enum
	{
		E_NORMAl = 0x1 << 0, E_OVERLOAD = 0x1 << 1 //overload
	};
	typedef NSHARE::crc8_t<0x95> crc_t; //
	event_fifo_t(uint32_t aMemorySize) :
			FPIDOfLockedMutex(0x0),//
			FCrc(0x1), //
			FArraySize((aMemorySize - sizeof(event_fifo_t)) / sizeof(FInfo[0])), //
			FRead(0), //
			FWrite(0), //
			FMaxCountRecvEvent(FArraySize>EVENT_RESERV?(FArraySize-EVENT_RESERV):FArraySize), //
			FCountRecvEvent(0),//
			FReadTime(0),//
			FMaxValue((std::numeric_limits<uint16_t>::max()/FArraySize)*FArraySize)
	{
		FState=0;
		CHECK_GT(aMemorySize, sizeof(event_fifo_t));
		for (unsigned i = 0; i < FArraySize; ++i)
			FInfo[i].FEventType = event_info_t::E_NO;

		FSignalEvent[0] = '\0';
		FSignalMutex[0] = '\0';
		CHECK_GE(aMemorySize,
				sizeof(event_fifo_t) + FArraySize * sizeof(FInfo[0]));
	}
	int8_t FSignalEvent[32]; //is used to hold signal event name
	int8_t FSignalMutex[32]; //is used to hold signal event mutex name
	//
	uint32_t FPIDOfLockedMutex;
	//
	uint8_t FCrc;
	uint8_t FState :8;	//state
	uint16_t const FArraySize;//The Ring buffer is used to hold the data info  to avoid the memory fragmentation
	//
	uint16_t FRead;
	uint16_t FWrite;
	//
	uint16_t const FMaxCountRecvEvent;
	uint16_t FCountRecvEvent :16;
	//
	uint64_t FReadTime;
	//
	uint16_t const FMaxValue;//max valid value of FRead and FWrite
	uint16_t :16;
	//
	event_info_t FInfo[0];

	inline uint16_t MCount() const;
	inline bool MEmpty() const;
	inline bool MPut(event_info_t const& aData);
	bool MPop(event_info_t& aTo);
	bool MEraseFromFifo(event_info_t const& aData);
	bool MOverload() const
	{
		return (FState & E_OVERLOAD) != 0;
	}
	void MFillCRC()
	{
		FCrc = crc_t::sMCalcCRCofBuf(FSignalEvent,
				FSignalEvent + sizeof(FSignalEvent)+ sizeof(FSignalMutex));
	}
	bool MCheckCrc() const
	{
		uint8_t _crc = crc_t::sMCalcCRCofBuf(FSignalEvent,
				FSignalEvent + sizeof(FSignalEvent)+ sizeof(FSignalMutex));
		return _crc == FCrc;
	}
	inline uint16_t MInc(uint16_t aVal) const;
	inline uint16_t MDec(uint16_t aVal) const;
});
COMPILE_ASSERT(sizeof(event_fifo_t) ==(32+32+sizeof(uint32_t)*5+sizeof(uint64_t)),
		IVALID_SIZEOF_EVENT_FIFO);

inline uint16_t event_fifo_t::MCount() const
{
	int const _pos_w = FWrite;	//helps to avoid sigsev
	int const _pos_r = FRead;	//helps to avoid sigsev
	int _count =  _pos_w - _pos_r;
	if (_count < 0)
		_count += FMaxValue;
	LOG_IF(FATAL, _count < 0) << " Zero size " << _count << "; Write= " << FWrite
			<< "; Read=" << FRead<<"; ArraySize="<<FArraySize;
	CHECK_LE(_count, FArraySize);
	return _count;

}
inline bool event_fifo_t::MEmpty() const
{
	return FRead == FWrite;
}
inline uint16_t event_fifo_t::MDec(uint16_t aVal) const
{
	--aVal;
	aVal%=FMaxValue;
	return aVal;
}
inline uint16_t event_fifo_t::MInc(uint16_t aVal) const
{
	++aVal;
	aVal%=FMaxValue;
	return aVal;
}
inline bool event_fifo_t::MPut(event_info_t const& aData)
{
	VLOG(2) << "Put: " << FWrite << " Count=" << MCount() << " read=" << FRead;
	if (MCount() == FArraySize)
		return false;
	if (event_info_t::E_DATA == aData.FEventType)
	{
		if (FCountRecvEvent >= FMaxCountRecvEvent)
			return false;
		++FCountRecvEvent;
		VLOG(2) << "The number of recv event=" << FCountRecvEvent;
	};
	uint16_t const _pos = FWrite % FArraySize;	//helps to avoid sigsev
	VLOG(2) << "Put the offset to the array: " << FWrite << " array size= "
			<< FArraySize << " pos= " << _pos;
	FInfo[_pos] = aData;
	uint16_t const _count=MCount();
	FWrite=MInc(FWrite);
	CHECK_NE(_pos,FWrite%FArraySize);
	CHECK_EQ(MCount(),_count+1);
	return true;
}
inline bool event_fifo_t::MEraseFromFifo(event_info_t const& aData)
{
	VLOG(2) << "Erase: " << FRead << " write=" << FWrite;
	if (MEmpty())
			return false;
	uint16_t _read=FWrite;

	for (; _read != FRead; )
	{
		_read=MDec(_read);//it's reverse iterator
		uint16_t const _pos = _read % FArraySize;	//helps to avoid sigsev
		VLOG(2) << "Pos = " << _pos;
		if (memcmp(&FInfo[_pos], &aData, sizeof(aData)) == 0)
		{
			uint16_t _next_read = MInc(_read);

			for (; _next_read != FWrite; _read=MInc(_read), _next_read=MInc(_next_read))
			{
				uint16_t const _pos_insert = _read % FArraySize;
				uint16_t const _pos_read = _next_read % FArraySize;
				memcpy(&FInfo[_pos_insert], &FInfo[_pos_read],
						sizeof(FInfo[0]));
			}
			FWrite=MDec(FWrite);
			return true;
		}
	}
	return false;
}
inline bool event_fifo_t::MPop(event_info_t& aTo)
{
	VLOG(2) << "Pop: " << FRead << " write=" << FWrite;
	if (MEmpty())
		return false;
	uint16_t const _pos = FRead % FArraySize;	//helps to avoid sigsev
	VLOG(2) << "Pop the offset to the array: " << FRead << " pos=" << _pos;
	aTo = FInfo[_pos];
	if (event_info_t::E_DATA == aTo.FEventType)
	{
		CHECK_NE(FCountRecvEvent, 0);
		--FCountRecvEvent;
		VLOG(2) << "The number of recv event=" << FCountRecvEvent;
	};
	FRead=MInc(FRead);
	FReadTime=time(NULL);
	CHECK_NE(_pos,FRead% FArraySize);
	return true;
}
SHARED_PACKED
(struct shared_info_t	//must be last
{
	shared_info_t(uint32_t aPid, uint32_t aMemory) :
			FId(aPid),	//
			FFifo(aMemory)
	{

	}
	shared_port_t FId;
	event_fifo_t FFifo;
});
COMPILE_ASSERT(sizeof(shared_info_t) ==(sizeof(shared_port_t)+sizeof(event_fifo_t)),
		IVALID_SIZEOF_SHARED_POINT);

SHARED_PACKED(struct client_info_t
{
	client_info_t(uint32_t aPid, size_t aMemory);
	CSharedAllocator::offset_t FNext;

	shared_info_t FInfo;
	shared_identify_t MGetId() const;
	struct client_info_t * MNext(IAllocater const* aAllocater) const;
});
COMPILE_ASSERT(sizeof(client_info_t) ==(sizeof(shared_info_t)+sizeof(CSharedAllocator::offset_t)),
		IVALID_SIZEOF_CLIENT_INFO);

inline size_t get_client_fifo_size(unsigned aFifoSize)
{
	return sizeof(client_info_t) + sizeof(event_fifo_t)
			+ sizeof(event_info_t) * aFifoSize;
}
inline client_info_t::client_info_t(uint32_t aPid, size_t aMemory) :
		FNext(CSharedAllocator::NULL_OFFSET),	//
		FInfo(aPid, static_cast<uint32_t>(aMemory - sizeof(client_info_t)))	//
{
	CHECK_EQ(get_client_fifo_size(FInfo.FFifo.FArraySize),aMemory);
}

inline shared_identify_t client_info_t::MGetId() const
{
//	DCHECK_NE(FInfo.FId.FUniqueID, 0);
	return FInfo.FId.MGetId();
}
inline struct client_info_t * client_info_t::MNext(
		IAllocater const* aAllocater) const
{
	if (CSharedAllocator::sMIsNullOffset(FNext))
		return NULL;
	return (client_info_t *) aAllocater->MPointer(FNext);
}
SHARED_PACKED(
struct server_info_t //
{ //
	typedef NSHARE::crc8_t<0x91> crc_t; //

	server_info_t(uint32_t aPid, size_t aMemory);

	crc_t::type_t FCrc; //
	int8_t FMutex[32 - sizeof(crc_t::type_t)]; //
	//
	uint32_t FPIDOfLockedMutex;
	//
	//uint16_t FMaxClientFifoLen;	//def value
	uint16_t :16;
	uint16_t FNumberOfClients;

	//The list is used to hold the clients but it can fragment the memory
	CSharedAllocator::offset_t FOffsetToClient;
//	//The list is used to hold the clients but it can fragment the memory
//	CSharedAllocator::offset_pointer_t FOffsetToNewClient;
	//
	shared_info_t FInfo;

	void MFillCRC()
	{
		FCrc = crc_t::sMCalcCRCofBuf(FMutex, FMutex + sizeof(FMutex));
	}
	bool MCheckCrc() const
	{
		uint8_t _crc = crc_t::sMCalcCRCofBuf(FMutex, FMutex + sizeof(FMutex));
		return _crc == FCrc;
	}
	struct client_info_t * MFirstClientNode(IAllocater const* aAllocater) const
	{
		if (CSharedAllocator::sMIsNullOffset(FOffsetToClient))
			return NULL;
		return (client_info_t *) aAllocater->MPointer(FOffsetToClient);
	}
});
COMPILE_ASSERT(sizeof(server_info_t) ==(32+sizeof(uint32_t)*2+sizeof(CSharedAllocator::offset_t)+sizeof(shared_info_t)),
		IVALID_SIZEOF_SERVER_INFO);
inline size_t get_server_fifo_size(unsigned aFifoSize)
{
	return sizeof(server_info_t) + sizeof(event_fifo_t)
			+ sizeof(event_info_t) * aFifoSize;
}
inline server_info_t::server_info_t(uint32_t aPid, size_t aMemory) : //
		FCrc(0x1), //
		FPIDOfLockedMutex(0),//
		//FMaxClientFifoLen(0), //now it's set by client
		FNumberOfClients(0), //
		FOffsetToClient(CSharedAllocator::NULL_OFFSET), //
		FInfo(aPid, static_cast<uint32_t>(aMemory - sizeof(server_info_t)))
{
	FMutex[0]='\0';
	CHECK_GE(aMemory,
			sizeof(server_info_t)
					+ FInfo.FFifo.FArraySize * sizeof(FInfo.FFifo.FInfo[0]));

	CHECK_EQ(get_server_fifo_size(FInfo.FFifo.FArraySize),aMemory);
} //
}
namespace std
{
inline std::ostream& operator <<(std::ostream& aStream,
		NSHARE::shared_port_t const& aInfo)
{
	aStream << "PID:" << aInfo.FPid << ";UserId: " << aInfo.FUserID
			<< "; FUniqueID:  " << aInfo.FUniqueID;
	return aStream;
}
inline std::ostream& operator <<(std::ostream& aStream,
		NSHARE::event_info_t const& aInfo)
{
	aStream << "Type:" << (int) aInfo.FEventType << ";From: "
			<< aInfo.FIdFrom.MGetId();
	return aStream;
}
}
#endif /* CSHAREDMEMORYIMPLTYPES_H_ */
