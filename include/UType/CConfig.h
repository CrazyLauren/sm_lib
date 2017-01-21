/*
 * CConfig.h
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 20.01.2014
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */
#ifndef CCONFIG_H_
#define CCONFIG_H_

#ifndef SHARE_CONFIG_DEFINED
#	define SHARE_CONFIG_DEFINED
#endif
namespace NSHARE
{

class SHARE_EXPORT CConfig;
class CBuffer;

typedef std::list<class CConfig> ConfigSet;

class SHARE_EXPORT CConfig
{
public:
	static CConfig const& sMGetEmpty();


	CConfig()
	{
	}

	CConfig(const CText& key) :
			FKey(key)
	{
	}

	CConfig(const CText& key, const CText& value) :
			FKey(key), FValue(value)
	{
	}
	CConfig(const CText& key,void const* aTo, size_t aMaxLen);
	CConfig(const CText& key,CBuffer const & aTo);

	template<class T>
	CConfig(const CText& key, const T& value) :
			FKey(key)
	{
#ifdef		NUM_TO_STRING_EXIST
		FValue=to_string<T>(value);
#else
		std::stringstream out;
		out << value;
		FValue=out.str();
#endif
	}

	CConfig(const CConfig& rhs);



	CConfig& operator=(const CConfig& rhs);

	bool MFromXML(std::istream&);
	bool MToXML(std::ostream&,bool aPretty=false) const;


	bool MToJSON(std::ostream&,bool aPretty=false) const;
	bool MToJSON(NSHARE::CText&,bool aPretty=false) const;

	bool MFromJSON(NSHARE::CText const&);
	bool MFromJSON(std::istream&);
	NSHARE::CText MToJSON(bool aPretty=false) const;

	//relative
	void MSetReferrer(const CText& value);
	void MInheritReferrer(const CText& value);
	const CText& MReferrer() const
	{
		return FReferrer;
	}

	bool MIsEmpty() const
	{
		return FKey.empty() && FValue.empty() && FChildren.empty();
	}

	bool MIsSimple() const //leaf
	{
		return !FKey.empty() && !FValue.empty() && FChildren.empty();
	}

	CText& MKey()
	{
		return FKey;
	}
	const CText& MKey() const
	{
		return FKey;
	}

	const CText& MValue() const
	{
		return FValue;
	}
	CText& MValue()
	{
		return FValue;
	}
	size_t MValueBuf(size_t aMaxLen,void* aTo) const;
	void MValue(CBuffer & aTo) const;

	template<typename T>
	T MValue(T _val=T()) const
	{
		std::istringstream _stream(MValue());
		if (!_stream.eof())
			_stream >> _val;
		LOG_IF(ERROR, _stream.fail()) << "Cannot convert " << MValue();
		return _val;
	}
	// populates a primitive value.
	template<typename T>
	T MValue(const CText& key, T const& fallback) const
	{
		if (MChild(key).MValue().empty())
			return fallback;
		return MChild(key).MValue<T>(fallback);
	}

	const ConfigSet& MChildren() const
	{
		return FChildren;
	}
	ConfigSet& MChildren()//todo private
	{
		return FChildren;
	}
	const ConfigSet MChildren(const CText& key) const
	{
		ConfigSet r;
		for (ConfigSet::const_iterator i = FChildren.begin();
				i != FChildren.end(); ++i)
		{
			if (i->MKey() == key)
				r.push_back(*i);
		}
		return r;
	}

	bool MIsChild(const CText& key) const
	{
		for (ConfigSet::const_iterator i = FChildren.begin();
				i != FChildren.end(); ++i)
			if (i->MKey() == key)
				return true;
		return false;
	}

	void MRemove(const CText& key)
	{
		for (ConfigSet::iterator i = FChildren.begin(); i != FChildren.end();)
		{
			if (i->MKey() == key)
				i = FChildren.erase(i);
			else
				++i;
		}
	}

	CConfig const& MChild(const CText& key) const;

	const CConfig* MChildPtr(const CText& key) const;

	CConfig* MMutableChild(const CText& key);

	void MMerge(const CConfig& rhs);
	void MBlendWith(const CConfig& rhs);

	CConfig* MFind(const CText& key, bool checkThis = true);
	const CConfig* MFind(const CText& key, bool checkThis = true) const;

#ifdef SMART_FIELD_EXIST
	template<typename T>
	void MAddIfSet(const CText& key, const smart_field_t<T>& opt)
	{
		if (opt.MIs())
		{
			MAdd(key, to_string<T>(opt.MGetConst()));
		}
	}
#endif
	template<typename T>
	CConfig& MAdd(const CText& key, const T& value)
	{
#ifdef		NUM_TO_STRING_EXIST
		FChildren.push_back(CConfig(key, to_string<T>(value)));
#else
		std::stringstream out;
		out << value;
		FChildren.push_back(CConfig(key, out.str()));
#endif
		FChildren.back().MInheritReferrer(FReferrer);
		return FChildren.back();
	}

	CConfig&  MAdd(const CText& key,void const* aTo,size_t aMaxLen);
	CConfig&  MAddTo(const CText& key,CBuffer const & aTo);
	CConfig& MAdd(const CConfig& conf)
	{
		FChildren.push_back(conf);

		FChildren.back().MInheritReferrer(FReferrer);
		return FChildren.back();
	}

	CConfig& MAdd(const CText& key, const CConfig& conf)
	{
		CConfig temp = conf;
		temp.MKey() = key;
		return MAdd(temp);
	}

	void MAdd(const ConfigSet& set)
	{
		for (ConfigSet::const_iterator _it = set.begin(); _it != set.end();
				++_it)
			MAdd(*_it);
	}
#ifdef SMART_FIELD_EXIST
	template<typename T>
	void MUpdateIfSet(const CText& key, const smart_field_t<T>& opt)
	{
		if (opt.MIs())
		{
			MRemove(key);
			MAdd(key, to_string<T>(opt.MGetConst()));
		}
	}
#endif
	template<typename T>
	CConfig& MUpdate(const CText& key, const T& value)
	{
#ifdef		NUM_TO_STRING_EXIST
		return MUpdate(CConfig(key, to_string<T>(value)));
#else
		std::stringstream out;
		out << value;
		return MUpdate(CConfig(key, out.str()));
#endif

	}

	CConfig& MUpdate(const CConfig& conf)
	{
		MRemove(conf.MKey());
		return MAdd(conf);
	}

	template<typename T>
	CConfig& MSet(const CText& key, const T& value)
	{
		return MUpdate(key, value);
	}

	bool MHasValue(const CText& key) const
	{
		return !MValue(key).empty();
	}

	const CText& MValue(const CText& key) const
	{
		return MChild(key).MValue();
	}


	const CText MReferrer(const CText& key) const
	{
		return MChild(key).MReferrer();
	}

#ifdef SMART_FIELD_EXIST
	// populates the output value iff the Config exists.
	template<typename T>
	bool MGetIfSet(const CText& key, smart_field_t<T>& output) const
	{
		if (MIsChild(key))
		{
			output = MValue<T>(key, T());
			return true;
		}
		else
			return false;
	}
#endif
	template<typename T>
	bool MGetIfSet(const CText& key, T& output) const
	{
		if (MHasValue(key))
		{
			output = MValue<T>(key, output);
			return true;
		}
		return false;
	}

	// remove everything from (this) that also appears in rhs
	CConfig operator -(const CConfig& rhs) const;
	std::ostream& MPrint(std::ostream & aStream) const;

private:
	template<class T>
	inline void MReadFrom(T const&, bool aFirst = true); //ptree - boost

	template<class T>
	inline void MWriteTo(T&, bool aFirst = true) const; //ptree - boost

	CText FKey;
	CText FValue;
	ConfigSet FChildren;
	CText FReferrer;//todo
};

#ifdef SMART_FIELD_EXIST
// specialization for Config
template<> inline
void CConfig::MAddIfSet<CConfig>(const CText& key,
		const smart_field_t<CConfig>& opt)
{
	if (opt.MIs())
	{
		CConfig conf = opt.MGetConst();
		conf.MKey() = key;
		MAdd(conf);
	}
}

template<> inline
void CConfig::MUpdateIfSet<CConfig>(const CText& key,
		const smart_field_t<CConfig>& opt)
{
	if (opt.MIs())
	{
		MRemove(key);
		CConfig conf = opt.MGetConst();
		conf.MKey() = key;
		MAdd(conf);
	}
}

template<> inline
bool CConfig::MGetIfSet<CConfig>(const CText& key,
		smart_field_t<CConfig>& output) const
{
	if (MIsChild(key))
	{
		output = MChild(key);
		return true;
	}
	else
	return false;
}
#endif
template<> inline
CConfig& CConfig::MAdd<CText>(const CText& key, const CText& value)
{
	FChildren.push_back(CConfig(key, value));
	//_children.back().setReferrer( _referrer );
	FChildren.back().MInheritReferrer(FReferrer);
	return FChildren.back();
}
template<> inline
CText CConfig::MValue<CText>(CText _val) const
{
	return MValue();
}
//fixme
//template<> inline
// CBuffer CConfig::MValue<CBuffer>() const
//{
//	CBuffer _to;
//	MValue(_to);
//	return _to;
//}
template<> inline
CConfig& CConfig::MAdd<CBuffer>(const CText& key,CBuffer const & aTo)
{
	return MAddTo(key,aTo);
}
template<> inline
CConfig& CConfig::MUpdate<CText>(const CText& key, const CText& value)
{
	MRemove(key);
	return MAdd(CConfig(key, value));
}

template<> inline
CConfig& CConfig::MUpdate<CConfig>(const CText& key, const CConfig& conf)
{
	MRemove(key);
	CConfig temp = conf;
	temp.MKey() = key;
	return MAdd(temp);
}
} /* namespace NSHARE */
namespace std
{
inline std::ostream& operator <<(std::ostream& aStream,
		NSHARE::CConfig const& aInfo)
{
	aInfo.MPrint(aStream);
	return aStream;
}
}
#endif /* CCONFIG_H_ */
