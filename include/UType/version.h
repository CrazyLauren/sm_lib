/*
 * version.h
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 22.03.2013
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */
#ifndef VERSION_H_
#define VERSION_H_

namespace NSHARE
{
#ifdef SHARE_CONFIG_DEFINED
#define	SHARED_CONFIG_MSVC_FIX NSHARE::CConfig
#else
#define	SHARED_CONFIG_MSVC_FIX int
#endif
SHARED_PACKED(struct SHARE_EXPORT version_t
{
	static const NSHARE::CText NAME;

	uint8_t FMajor;
	uint8_t FMinor;
	mutable uint16_t FRelease;


	version_t(uint8_t aMajor=0,uint8_t aMinor=0,uint16_t aRelease=0);

	inline bool MIsExist() const;
	version_t( SHARED_CONFIG_MSVC_FIX const& aConf);
	SHARED_CONFIG_MSVC_FIX MSerialize() const;
});

inline bool  version_t::MIsExist() const
{
	return FMajor!=0 || FMinor!=0 || FRelease!=0;
}
inline version_t::version_t(uint8_t aMajor,uint8_t aMinor,uint16_t aRelease):
	FMajor(aMajor),
	FMinor(aMinor),
	FRelease(aRelease)
{
}
#ifdef SHARE_CONFIG_DEFINED
inline version_t::version_t(NSHARE::CConfig const& aConf):
			FMajor(0),
			FMinor(0),
			FRelease(0)
{
	FMajor=aConf.MValue<unsigned>("mj", 0);
	FMinor=aConf.MValue<unsigned>("mn", 0);
	FRelease=aConf.MValue<unsigned>("rs",0);
}
inline NSHARE::CConfig version_t::MSerialize() const
{
	NSHARE::CConfig _conf(NAME);
	if(MIsExist())
	{
		_conf.MSet("mj", FMajor);
		_conf.MSet("mn", FMinor);
		_conf.MSet("rs", FRelease);
	}
	return _conf;
}
#endif
template<class T, unsigned Major, unsigned Minor>
struct  impl_version_t
{
	typedef T class_t;

	template<class U>
	struct check
	{
		typedef char False[1];
		typedef char True[2];

		static True& f(U*);
		static False& f(...);

		static T* MakeT();
		enum
		{
			result = sizeof(f(MakeT())) == sizeof(True),
		};
	};
	enum
	{
		minor = Minor, major = Major
	};
};

template<class T>
struct  ver_impl_t
{
	typedef T class_t;
	struct IsThereVersion
	{
		struct FallBack
		{
			struct version //Attention!!! должен совпадать с именем типа "версия" в CBaseObject
			{
				;
			};
		};
		struct Derived: class_t, FallBack
		{
		};

		typedef char False[1];
		typedef char True[2];

		template<typename U>
		static False& f(typename U::version *);

		template<typename U>
		static True& f(U*);
		enum
		{
			result = sizeof(f<Derived>(0)) == sizeof(True),
		};
	};

	template<class U, bool val = IsThereVersion::result>
	struct IsVersion
	{
		template<class X>
		struct _ver
		{
			static NSHARE::version_t& sV()
			{
				static NSHARE::version_t _version =
				{ 0, 0, 0 };
				return _version;

			}
		};
	};
	template<class U>
	struct IsVersion<U, true>
	{
		template<class X, bool val = X::version::template check<X>::result>
		struct _ver
		{
			static NSHARE::version_t& sV()
			{
				static NSHARE::version_t _version =
				{ 0, 0, 0 };
				return _version;

			}
		};
		template<class X>
		struct _ver<X, true>
		{
			static NSHARE::version_t& sV()
			{
				static NSHARE::version_t _version (
				 X::version::major, X::version::minor, 0 );
				return _version;
			}
		};
	};
	typedef typename ver_impl_t<T>::template IsVersion<T>::template _ver<T> _v;
};
} //namespace USHARE
namespace std
{
inline std::ostream& operator<<(std::ostream & aStream,
		const NSHARE::version_t& aVersion)
{
	aStream << (int) aVersion.FMajor << '.'<< (int) aVersion.FMinor << '.'
			<< (int) aVersion.FRelease;
	return aStream;
}
inline std::istream& operator>>(std::istream& aStream,
		NSHARE::version_t& aVersion) //TODO
{
	char _c;
	 aStream>>aVersion.FMajor;
	if (aStream.fail() || aStream.eof())
	{
		aStream.setstate(std::istream::failbit);
		return aStream;
	}
	 aStream>>_c;
	if (_c != '.')
	{
		aStream.setstate(std::istream::failbit);
		return aStream;
	}
	aStream>>aVersion.FMinor;
	if (aStream.fail() || aStream.eof())
	{
		aStream.setstate(std::istream::failbit);
		return aStream;
	}
	_c = 0;
	aStream>>_c;
	if (_c != '.')
	{
		aStream.setstate(std::istream::failbit);
		return aStream;
	}
	unsigned _val=0;
	aStream>>_val;
	if (aStream.fail())
	{
		aStream.setstate(std::istream::failbit);
		return aStream;
	}
	aVersion.FRelease=_val;
	return aStream;
}
}
#endif /* VERSION_H_ */
