/*
 * CConfig.cpp
 *
 * Copyright © 2016 Sergey Cherepanov (sergey0311@gmail.com)
 *
 *  Created on: 20.01.2014
 *      Author: Sergey Cherepanov (https://github.com/CrazyLauren)
 *
 * Distributed under MPL 2.0 (See accompanying file LICENSE.txt or copy at
 * https://www.mozilla.org/en-US/MPL/2.0)
 */ 
#include <deftype>
#include <boost/config.hpp>
#include <algorithm>
#include <stack>

#include <rapidjson/reader.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/writer.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/transform_width.hpp>

typedef boost::property_tree::basic_ptree<std::string, std::string,
		std::less<std::string> > ptree_t;

namespace NSHARE
{
static size_t base64_encode(NSHARE::CText& _dest,const char* src, size_t aLen);
CConfig::CConfig(const CText& key, void const* aTo, size_t aMaxLen) :
		FKey(key)
{
	base64_encode(FValue,(char const*)aTo,aMaxLen);
}
CConfig::CConfig(const CText& key, CBuffer const & aTo) :
		FKey(key)
{
	base64_encode(FValue,(char const*)aTo.ptr_const(),aTo.size());
}

CConfig::CConfig(const CConfig& rhs) :
		FKey(rhs.FKey), FValue(rhs.FValue), FChildren(rhs.FChildren), FReferrer(
				rhs.FReferrer)
{
}
CConfig& CConfig::operator=(const CConfig& rhs)
{
	FKey=rhs.FKey;
	FValue=rhs.FValue;
	FChildren=rhs.FChildren;
	FReferrer=rhs.FReferrer;
	return *this;
}

const char UNIX_PATH_SEPARATOR = '/';
const char WINDOWS_PATH_SEPARATOR = '\\';

bool is_relative(const CText& fileName)
{
#if defined(_WIN32)  && !defined(__CYGWIN__)
	CText native(fileName);

	CText::size_type slash = 0;
	while ((slash = native.find_first_of(UNIX_PATH_SEPARATOR, slash))
			!= CText::npos)
	{
		native[slash] = WINDOWS_PATH_SEPARATOR;
	}
	//"C:\data"
	if (native.size() >= 3 && native[1] == ':' && native[2] == '\\')
		return false;
	//"\\server1\data"
	if (native.size() >= 2 && native[0] == '\\' && native[1] == '\\')
		return false;
	return true;
#else
	CText native(fileName);

	CText::size_type slash = 0;
	while ((slash = native.find_first_of(WINDOWS_PATH_SEPARATOR, slash))
			!= CText::npos)
	{
		native[slash] = UNIX_PATH_SEPARATOR;
	}
	return !(native.size() >= 1 && native[0] == '/');
#endif
}
CText concatPaths(const CText& left, const CText& right)
{
#if defined(WIN32) && !defined(__CYGWIN__)
	const char delimiterNative = WINDOWS_PATH_SEPARATOR;
	const char delimiterForeign = UNIX_PATH_SEPARATOR;
#else
	const char delimiterNative = UNIX_PATH_SEPARATOR;
	const char delimiterForeign = WINDOWS_PATH_SEPARATOR;
#endif

	if (left.empty())
	{
		return (right);
	}
	char lastChar = left[left.size() - 1];

	if (lastChar == delimiterNative)
	{
		return left + right;
	}
	else if (lastChar == delimiterForeign)
	{
		return left.substr(0, left.size() - 1) + delimiterNative + right;
	}
	else // lastChar != a delimiter
	{
		return left + delimiterNative + right;
	}
}
CText getFullPath(const CText& relativeTo, const CText &relativePath)
{
	if (!is_relative(relativePath) || relativeTo.empty())
		return relativePath;

	if (relativePath.empty())
		return relativeTo;

	//---Concatinate the paths together
	CText filename;
	CText::size_type slash = relativeTo.find_last_of("/\\");
	if (slash != std::string::npos)
		filename = CText(relativeTo, 0, slash);

	filename = concatPaths(filename, relativePath);

	std::list<CText> directories;
	size_t start = 0;
	for (size_t i = 0; i < filename.size(); ++i)
	{
		if (filename[i] == '\\' || filename[i] == '/')
		{
			//Get the current directory
			CText dir = filename.substr(start, i - start);

			if (dir != "..")
			{
				if (dir != ".")
				{
					directories.push_back(dir);
				}
			}
			else if (!directories.empty())
			{
				directories.pop_back();
			}
			start = i + 1;
		}
	}

	CText path;
	for (std::list<CText>::iterator itr = directories.begin();
			itr != directories.end(); ++itr)
	{
		path += *itr;
		path += "/";
	}

	path += filename.substr(start, CText::npos);
	return path;
}
void CConfig::MSetReferrer(const CText& referrer)
{
	FReferrer = referrer;
	for (ConfigSet::iterator _it = FChildren.begin(); _it != FChildren.end();
			++_it)
	{
		_it->MSetReferrer(getFullPath(FReferrer, _it->FReferrer));
	}
}

void CConfig::MInheritReferrer(const CText& referrer)
{
	if (FReferrer.empty() || !is_relative(referrer))
	{
		MSetReferrer(referrer);
	}
	else if (!referrer.empty())
	{
		MSetReferrer(concatPaths(FReferrer, referrer));
	}
}
CConfig const& CConfig::MChild(const CText& childName) const
{
	VLOG(6) << "Find child:" << childName << "  Number of children:"
						<< FChildren.size();
	for (ConfigSet::const_iterator i = FChildren.begin(); i != FChildren.end();
			++i)
	{
		VLOG(6) << "Child " << i->MKey();
		if (i->MKey() == childName)
		{
			VLOG(6) << "Found "<<childName<<" in "<<MKey();
			return *i;
		}
	}

	return sMGetEmpty();
}
CConfig const& CConfig::sMGetEmpty()
{
	static CConfig const emptyConf;
	return emptyConf;
}
const CConfig* CConfig::MChildPtr(const CText& childName) const
{
	for (ConfigSet::const_iterator i = FChildren.begin(); i != FChildren.end();
			++i)
	{
		if (i->MKey() == childName)
			return &(*i);
	}
	return NULL;
}

CConfig* CConfig::MMutableChild(const CText& childName)
{
	for (ConfigSet::iterator i = FChildren.begin(); i != FChildren.end(); ++i)
	{
		if (i->MKey() == childName)
			return &(*i);
	}

	return NULL;
}

void CConfig::MMerge(const CConfig& rhs)
{
	for (ConfigSet::const_iterator _it = rhs.FChildren.begin();
			_it != rhs.FChildren.end(); ++_it)
	{
		MRemove(_it->MKey());
		MAdd(*_it);
	}


}
void CConfig::MBlendWith(const CConfig& rhs)
{
	for (ConfigSet::const_iterator _it = rhs.FChildren.begin();
			_it != rhs.FChildren.end(); ++_it)
	{
		if(_it->MIsSimple())
		{

		}
		else
		{
			if (MIsChild(_it->MKey()))
			{
				MMutableChild(_it->MKey())->MBlendWith(*_it);
			}
			else
				MAdd(*_it);
		}
	}
}
const CConfig* CConfig::MFind(const CText& key, bool checkMe) const
{
	if (checkMe && key == this->MKey())
		return this;

	for (ConfigSet::const_iterator c = FChildren.begin(); c != FChildren.end();
			++c)
		if (key == c->MKey())
			return &(*c);

	for (ConfigSet::const_iterator c = FChildren.begin(); c != FChildren.end();
			++c)
	{
		const CConfig* r = c->MFind(key, false);
		if (r)
			return r;
	}

	return NULL;
}

CConfig*
CConfig::MFind(const CText& key, bool checkMe)
{
	if (checkMe && key == this->MKey())
		return this;

	for (ConfigSet::iterator c = FChildren.begin(); c != FChildren.end(); ++c)
		if (key == c->MKey())
			return &(*c);

	for (ConfigSet::iterator c = FChildren.begin(); c != FChildren.end(); ++c)
	{
		CConfig* r = c->MFind(key, false);
		if (r)
			return r;
	}

	return NULL;
}
CConfig CConfig::operator -(const CConfig& rhs) const
{
	CConfig result(*this);

	for (ConfigSet::const_iterator i = rhs.MChildren().begin();
			i != rhs.MChildren().end(); ++i)
	{
		result.MRemove(i->MKey());
	}

	return result;
}
std::ostream& CConfig::MPrint(std::ostream & aStream) const
{
	aStream << "Key:" << FKey;
	if (!FValue.empty())
		aStream << "; Value:" << FValue;
	if (!FReferrer.empty())
		aStream << "; Referer:" << FReferrer;
	if (!FChildren.empty())
	{
		aStream << "; Child of " << FKey;
		for (ConfigSet::const_iterator _it = FChildren.begin();
				_it != FChildren.end(); ++_it)
			aStream << std::endl << *_it;
		aStream << std::endl << "; End child of  " << FKey;
	}
	return aStream;
}

template<>
inline void CConfig::MReadFrom(ptree_t const& aTree, bool aFirst)
{
	if (aTree.empty() && aTree.data().empty())
	{
		VLOG(2) << "Node empty";
		return;
	}
	else
	{
		if (aFirst)
		{
			FKey = aTree.front().first;
			FValue = aTree.data();
			MReadFrom(aTree.front().second, false);
		}
		else
		{
			ptree_t::const_iterator _it = aTree.begin();
			for (; _it != aTree.end(); ++_it)
			{
				//VLOG(2) << "Property =" << _it->first << " :" << this;
				ptree_t::value_type const& _val = *_it;
				if (_val.second.empty()) //leaf
				{
					VLOG(3) << "Add leaf " << _val.first << " = "
										<< _val.second.data() << " :" << this;
					MAdd(_val.first, _val.second.data());
				}
				else if (_val.first == "<xmlattr>") //node
				{
					VLOG(2) << "Convert xmlattr";
					CConfig _child(_val.first, _val.second.data());
					_child.MReadFrom(_val.second, false);
					ConfigSet const& _set = _child.MChildren();
					ConfigSet::const_iterator _jt(_set.begin()), _jt_end(
							_set.end());
					for (; _jt != _jt_end; ++_jt)
					{
						VLOG(2) << "Push attr " << _jt->MKey() << " == "
											<< _jt->MValue();
						MAdd(*_jt);
					}
				}
				else //node
				{
					VLOG(2) << "Node =" << _val.first << " :" << this;
					CConfig _child(_val.first, _val.second.data());
					_child.MReadFrom(_val.second, false);
					if (!_child.MIsEmpty())
						MAdd(_child);
				}
			}
		}
		VLOG(2) << "End reading";
	}

}
template<>
inline void CConfig::MWriteTo(ptree_t& aTree, bool aFirst) const
{
	if (MIsEmpty())
	{
		VLOG(2) << "Node empty";
		return;
	}
	VLOG(2) << "Write " << MKey();
	if (MIsSimple())
	{
		VLOG(2) << "Put leaf " << MKey() << " = " << MValue();
		aTree.add(MKey(), MValue());
		return;
	}
	if (aFirst)
	{
		LOG_IF(DFATAL,MKey().empty()) << "Empty key not allowed";
		CText _path;
		if (MKey().empty())
			_path = "EmptyKeyNotAllowed";
		else
			_path = MKey();
		ptree_t & _node = aTree.add(_path.c_str(), "");
		MWriteTo(_node, false);
		VLOG(2) << "Write  ptree finished";
	}
	else
	{
		ConfigSet::const_iterator _it = FChildren.begin();
		for (; _it != FChildren.end(); ++_it)
		{
			if (_it->MIsEmpty())
			{
				VLOG(2) << "Node empty";
				continue;
			}
			CConfig const& _conf = *_it;

			LOG_IF(DFATAL,_conf.MKey().empty()) << "Empty key not allowed";

			CText const _path(
					!_conf.MKey().empty() ?
							_conf.MKey() : CText("EmptyKeyNotAllowed"));
			if (_it->MIsSimple())
			{
				VLOG(6) << "Put leaf " << _path << " = " << _conf.MValue();
				aTree.add(_path.c_str(), _conf.MValue());
			}
			else
			{

				VLOG(6) << "Property =" << _path << " :" << this;
				ptree_t & _node = aTree.add(_path.c_str(), "");
				_conf.MWriteTo(_node, false);
			}
		}
	}
}

namespace
{
using namespace rapidjson;
struct CJsonReader
{
	struct _stack_t
	{
		_stack_t()
		{
			FConf = NULL;
			FCurrentArrayLength = 0;
			FNumberOfArrayElements = 0;
		}
		NSHARE::CConfig* FConf;
		NSHARE::CText FArrayKey;
		unsigned FCurrentArrayLength;
		unsigned FNumberOfArrayElements;
	};

	NSHARE::CConfig& FHead;
	NSHARE::CText FKey;
	std::stack<_stack_t> FStack;

	CJsonReader(NSHARE::CConfig& aTo) :
			FHead(aTo)
	{
	}
	~CJsonReader()
	{
	}
	bool Null()
	{
		return true;
	}
	bool Bool(bool b)
	{
		MAddLeaf(NSHARE::to_string(b));
		return true;
	}
	bool Int(int i)
	{
		MAddLeaf(NSHARE::to_string(i));
		return true;
	}
	bool Uint(unsigned u)
	{
		MAddLeaf(NSHARE::to_string(u));
		return true;
	}
	bool Int64(int64_t i)
	{
		MAddLeaf(NSHARE::to_string(i));
		return true;
	}
	bool Uint64(uint64_t u)
	{
		MAddLeaf(NSHARE::to_string(u));
		return true;
	}
	bool Double(double d)
	{
		MAddLeaf(NSHARE::to_string(d));
		return true;
	}
	bool RawNumber(const char* str, SizeType length, bool copy)
	{

		MAddLeaf(NSHARE::CText(str, length));
		return true;
	}
	bool String(const char* str, SizeType length, bool copy)
	{

		MAddLeaf(NSHARE::CText(str, length));
		return true;
	}

	void MAddLeaf(NSHARE::CText const& aVal)
	{
		CHECK(!FStack.empty());
		_stack_t& _stack = FStack.top();
		VLOG(6) << "Add leaf " << FKey << " = " << aVal << " to "
							<< _stack.FConf->MKey();
		if (!_stack.FArrayKey.empty())
		{
			_stack.FConf->MAdd(FStack.top().FArrayKey, aVal);
			++_stack.FCurrentArrayLength;
		}
		else
			_stack.FConf->MSet(FKey, aVal);
	}
	bool StartObject()
	{
		if (FStack.empty())
		{
			VLOG(6)<<"Heading ";
			_stack_t _stack;
			_stack.FConf = &FHead;
			FStack.push(_stack);
			return true;
		}
		_stack_t& _top = FStack.top();
		if (!_top.FArrayKey.empty())
		{
			VLOG(6) << "StartObject() For Array " << _top.FArrayKey;

			NSHARE::CConfig _conf(_top.FArrayKey);

			_top.FConf->MAdd(_conf);
			++_top.FCurrentArrayLength;

			_stack_t _stack;
			_stack.FConf = &_top.FConf->MChildren().back();
			FStack.push(_stack);
		}
		else
		{
			VLOG(6) << "StartObject() For Object";
			VLOG(6) << "Add new object " << FKey;
			NSHARE::CConfig _conf(FKey);
			_top.FConf->MAdd(_conf);
			_stack_t _stack;
			_stack.FConf = &_top.FConf->MChildren().back();
			FStack.push(_stack);
		}
		return true;
	}
	bool Key(const char* str, SizeType length, bool copy)
	{
		VLOG(6) << "Key(" << str << ", " << length << ", " << copy << ")";
		FKey = NSHARE::CText(str, length);
		//FStack.top()->M
		return true;
	}
	bool EndObject(SizeType memberCount)
	{
		if (!FStack.empty())
		{
			_stack_t& _top = FStack.top();
			VLOG(6) << "EndObject(" << memberCount << ") for "
								<< _top.FConf->MKey();
			CHECK_EQ(_top.FConf->MChildren().size(),
					memberCount + _top.FNumberOfArrayElements);
			FStack.pop();
		}
		return true;
	}

	bool StartArray()
	{
		CHECK(!FStack.empty());
		_stack_t& _top = FStack.top();
		VLOG(6) << "StartArray() for " << _top.FConf->MKey()
							<< " Key " << FKey << " Count = "
							<< _top.FCurrentArrayLength;
		_top.FArrayKey = FKey;
		_top.FCurrentArrayLength = 0;
		CHECK(!FKey.empty());
		return true;
	}
	bool EndArray(SizeType elementCount)
	{
		CHECK(!FStack.empty());
		_stack_t& _top = FStack.top();
		VLOG(6) << "EndArray(" << elementCount << ") for "
							<< _top.FConf->MKey() << " Key " << FKey;

		_top.FArrayKey.clear();
		CHECK_EQ(_top.FCurrentArrayLength, elementCount);

		_top.FNumberOfArrayElements +=
			_top.FCurrentArrayLength > 0 ?
			_top.FCurrentArrayLength - 1 : 0;
		_top.FCurrentArrayLength = 0;
		return true;
	}
};

template<class T>
void write_json_impl(T & writer, NSHARE::CConfig const& aFrom, bool aIsArray);

void write_json_to_pretty(NSHARE::CConfig const& aFrom, NSHARE::CText* aTo)
{
	StringBuffer s;
	PrettyWriter<StringBuffer> writer(s);
	writer.StartObject();
	write_json_impl(writer, aFrom, false);
	writer.EndObject();
	aTo->assign(s.GetString());
}
void write_json_to_pretty(NSHARE::CConfig const& aFrom, std::ostream& aStream)
{
	OStreamWrapper s(aStream);
	PrettyWriter<OStreamWrapper> writer(s);
	writer.StartObject();
	write_json_impl(writer, aFrom, false);
	writer.EndObject();
}

void write_json_to(NSHARE::CConfig const& aFrom, NSHARE::CText* aTo)
{
	StringBuffer s;
	Writer<StringBuffer> writer(s);
	writer.StartObject();
	write_json_impl(writer, aFrom, false);
	writer.EndObject();
	aTo->assign(s.GetString());
}
void write_json_to(NSHARE::CConfig const& aFrom, std::ostream& aStream)
{
	OStreamWrapper s(aStream);
	Writer<OStreamWrapper> writer(s);
	writer.StartObject();
	write_json_impl(writer, aFrom, false);
	writer.EndObject();
}
template<class T>
void write_json_impl(T & writer, NSHARE::CConfig const& aFrom, bool aIsArray)
{

	if (aFrom.MIsEmpty())
	{
		VLOG(2) << "Node empty";
		return;
	}
	VLOG(6) << "Write " << aFrom.MKey();
	if (aFrom.MIsSimple())
	{
		VLOG(6) << "Put leaf " << aFrom.MKey() << " = " << aFrom.MValue();
		if (!aIsArray)
			writer.Key(aFrom.MKey().c_str());
		writer.String(aFrom.MValue().c_str());
		return;
	}
	else
	{
		bool _is = !aFrom.MKey().empty();
		if (_is)
		{
			if (!aIsArray)
				writer.Key(aFrom.MKey().c_str());
			writer.StartObject();
		}
		typedef std::map<NSHARE::CText, std::list<NSHARE::CConfig const*> > _arrays_t;
		typedef std::map<NSHARE::CText, unsigned> _counter_t;

		NSHARE::ConfigSet const& _childs = aFrom.MChildren();

		std::list<NSHARE::CConfig const*> _objects;
		_arrays_t _arrays;
		_counter_t _counter;
		{
			NSHARE::ConfigSet::const_iterator _it = _childs.begin();
			for (; _it != _childs.end(); ++_it)
			{
				_counter[_it->MKey()]++;
			}
			_it = _childs.begin();
			for (; _it != _childs.end(); ++_it)
			{
				if (_counter[_it->MKey()] > 1)
					_arrays[_it->MKey()].push_back(&(*_it));
				else
					_objects.push_back(&(*_it));
			}
		}
		{
			std::list<NSHARE::CConfig const*>::const_iterator _it;
			_it = _objects.begin();
			for (; _it != _objects.end(); ++_it)
			{
				NSHARE::CConfig const& _conf = *(*_it);
				if (_conf.MIsEmpty())
				{
					VLOG(2) << "Node empty";
					continue;
				}

				LOG_IF(DFATAL,_conf.MKey().empty()) << "Empty key not allowed";
				VLOG(6) << "put object " << _conf.MKey();
				write_json_impl(writer, _conf, false);
			}
		}
		_arrays_t::const_iterator _jt = _arrays.begin();

		for (; _jt != _arrays.end(); ++_jt)
		{
			std::list<NSHARE::CConfig const*>::const_iterator _it(
					_jt->second.begin()), _it_end(_jt->second.end());
			VLOG(2) << "put array " << _jt->first;
			writer.Key(_jt->first.c_str());
			writer.StartArray();
			for (; _it != _it_end; ++_it)
			{
				NSHARE::CConfig const& _conf = *(*_it);
				if (_conf.MIsEmpty())
				{
					VLOG(2) << "Node empty";
					continue;
				}

				LOG_IF(DFATAL,_conf.MKey().empty()) << "Empty key not allowed";

				write_json_impl(writer, _conf, true);
			}
			writer.EndArray();
		}

		if (_is)
			writer.EndObject();

	}
}
}
bool CConfig::MFromJSON(std::istream& aStream)
{
	Reader _reader;
	IStreamWrapper _buf(aStream);

	CJsonReader handler(*this);

	return _reader.Parse(_buf, handler);
}
bool CConfig::MFromJSON(NSHARE::CText const& aText)
{
	if (aText.empty())
	{
		LOG(ERROR)<<"Empty string.";
		return false;
	}
	Reader _reader;
	StringStream _buf(aText.c_str());

	CJsonReader handler(*this);

	return _reader.Parse(_buf, handler);
}
NSHARE::CText CConfig::MToJSON(bool aPretty) const
{
	NSHARE::CText _rval;
	MToJSON(_rval,aPretty);
	return _rval;
}
bool CConfig::MToJSON(NSHARE::CText& aText,bool aPretty) const
{
	if (aPretty)
		write_json_to_pretty(*this, &aText);
	else
		write_json_to(*this, &aText);
	return true;
}
bool CConfig::MToJSON(std::ostream& aStream, bool aPretty) const
{
	if (aPretty)
		write_json_to_pretty(*this, aStream);
	else
		write_json_to(*this, aStream);
	return true;
}
bool CConfig::MToXML(std::ostream& aStream, bool aPretty) const
{
	ptree_t _tree;
	MWriteTo(_tree);

#if (BOOST_VERSION / 100000 >=1) &&(BOOST_VERSION / 100 % 1000<56)
	boost::property_tree::xml_writer_settings<char> settings('\t', 1);
#else
	boost::property_tree::xml_writer_settings<std::string> settings('\t', 1);
#endif
	
	try
	{
		if (aPretty)
			boost::property_tree::xml_parser::write_xml(aStream, _tree,
					settings);
		else
			boost::property_tree::xml_parser::write_xml(aStream, _tree);
	} catch (boost::property_tree::xml_parser_error &e)
	{
		LOG(ERROR)<<"Cannot write xml "<<e.message()<<" "<<e.filename()<<":"<<e.line();
		return false;
	}
	return true;
}
bool CConfig::MFromXML(std::istream& aStream)
{
	VLOG(2) << "Read from xml";
	ptree_t _tree;
	try
	{
		boost::property_tree::xml_parser::read_xml(aStream, _tree);
		MReadFrom(_tree);

	} catch (boost::property_tree::xml_parser_error &e)
	{
		LOG(ERROR)<<"Cannot read xml "<<e.message()<<" "<<e.filename()<<":"<<e.line();
		(void) e;
		return false;
	}
	return true;
}
//from StackOverflow
size_t base64_encode(NSHARE::CText& _dest,const char* src, size_t aLen)
{
	using namespace boost::archive::iterators;
	char tail[3] =
	{ 0, 0, 0 };
	typedef base64_from_binary<transform_width<const char *, 6, 8> > base64_enc;

	size_t one_third_len = aLen / 3;
	size_t len_rounded_down = one_third_len * 3;
	size_t j = len_rounded_down + one_third_len;

	_dest.reserve(len_rounded_down);

	std::back_insert_iterator<CText> _back(_dest);

	std::copy(base64_enc(src), base64_enc(src + len_rounded_down), _back);

	if (len_rounded_down != aLen)
	{
		size_t i = 0;
		for (; i < aLen - len_rounded_down; ++i)
		{
			tail[i] = src[len_rounded_down + i];
		}

		std::copy(base64_enc(tail), base64_enc(tail + 3), _back);

		for (i = aLen + one_third_len + 1; i < j + 4; ++i)
		{
			_dest[i] = '=';
		}

		return i;
	}

    return j;
}
const char* base64_decode(char* dest, const char* src, size_t* len)
{
	using namespace boost::archive::iterators;
	size_t output_len = *len;

    typedef transform_width<binary_from_base64<const char*>, 8, 6> base64_dec;

    size_t i=0;
    try
    {
        base64_dec src_it(src);
        for(; i < output_len; ++i)
        {
            *dest++ = *src_it;
            ++src_it;
        }
    }
    catch(dataflow_exception const& e)
    {
    	VLOG(1)<<"Overflow error:"<<e.what();
    }

    *len = i;
    return src + (i+2)/3*4; // bytes in = bytes out / 3 rounded up * 4
}
void base64_decode(CBuffer & aTo, NSHARE::CText const& aFrom)
{
	using namespace boost::archive::iterators;
    typedef transform_width<binary_from_base64<const uint8_t*>, 8, 6> base64_dec;

    aTo.reserve(aFrom.length()/2);
    CText::size_type const _len=aFrom.find_last_not_of('=');
    CHECK_NE(_len,CText::npos);
    try
    {
        base64_dec src_it(aFrom.c_str()),_it_end(aFrom.c_str()+_len);
        for(; src_it!=_it_end; ++src_it)
        {
        	uint8_t _val=*src_it;
        	aTo.push_back(_val);
        }
    }
    catch(dataflow_exception const& e)
    {
    	LOG(ERROR)<<"Overflow error:"<<e.what();
    }

}
void CConfig::MValue(CBuffer & aTo) const
{
	base64_decode(aTo,MValue());
}

size_t CConfig::MValueBuf(size_t aMaxLen,void* aTo) const
{
	base64_decode((char*)aTo,MValue().c_str(),&aMaxLen);
	VLOG(2)<<"Buf length="<<aMaxLen;
	return aMaxLen;
}
CConfig&  CConfig::MAdd(const CText& key, void const* aTo, size_t aMaxLen)
{
	FChildren.push_back(CConfig(key));
	FChildren.back().MInheritReferrer(FReferrer);
	base64_encode(FChildren.back().FValue,(char const*)aTo,aMaxLen);
	VLOG(6)<<"Data string for "<<key<<" is "<<FChildren.back().MValue();
	return FChildren.back();
}
CConfig& CConfig::MAddTo(const CText& key, CBuffer const & aTo)
{
	return MAdd(key,aTo.ptr_const(),aTo.size());
}

} /* namespace NSHARE */
