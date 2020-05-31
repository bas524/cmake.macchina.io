//
// Properties.h
//
// Library: OSP
// Package: Util
// Module:  Properties
//
// Definition of the Properties class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef OSP_Properties_INCLUDED
#define OSP_Properties_INCLUDED


#include "Poco/OSP/OSP.h"
#include "Poco/String.h"
#include "Poco/Mutex.h"
#include <map>
#include <vector>


namespace Poco {
namespace OSP {


class OSP_API Properties
	/// The Properties class manages a collection of
	/// key-value pairs.
	///
	/// Property keys are not case sensitive.
{
public:
	Properties();
		/// Creates an empty Properties object.

	Properties(const Properties& props);
		/// Creates a Properties object by copying another one.

	~Properties();
		/// Destroys the Properties object.

	Properties& operator = (const Properties& props);
		/// Assigns another Properties object.

	void swap(Properties& props);
		/// Exchanges the contents of the Properties object
		/// with those from another one.

	std::string operator [] (const std::string& key) const;
		/// Returns the value for the given key.
		///
		/// Throws a Poco::NotFoundException if the given key
		/// does not exist.

	std::string get(const std::string& key) const;
		/// Returns the value for the given key.
		///
		/// Throws a Poco::NotFoundException if the given key
		/// does not exist.

	std::string get(const std::string& key, const std::string& deflt) const;
		/// Returns the value for the given key, or
		/// deflt if the key does not exist.

	bool getBool(const std::string& key) const;
		/// Returns the given value as a boolean.
		/// To be true, the string value must be something
		/// other than "false".
		///
		/// Throws a Poco::NotFoundException if the given key
		/// does not exist.

	bool getBool(const std::string& key, bool deflt) const;
		/// Returns the given value as a boolean.
		/// To be true, the string value must be something
		/// other than "false".
		///
		/// Returns deflt if key does not exist.

	int getInt(const std::string& key) const;
		/// Returns the given value as an integer.
		///
		/// Throws a Poco::NotFoundException if the given key
		/// does not exist and a Poco::SyntaxException if
		/// the property value is not a valid integer.

	int getInt(const std::string& key, int deflt) const;
		/// Returns the given value as an integer.
		///
		/// Returns deflt if key does not exist.

	Poco::Int64 getInt64(const std::string& key) const;
		/// Returns the given value as a 64-bit integer.
		///
		/// Throws a Poco::NotFoundException if the given key
		/// does not exist and a Poco::SyntaxException if
		/// the property value is not a valid integer.

	Poco::Int64 getInt64(const std::string& key, Poco::Int64 deflt) const;
		/// Returns the given value as a 64-bit integer.
		///
		/// Returns deflt if key does not exist.

	double getFloat(const std::string& key) const;
		/// Returns the given value as an integer.
		///
		/// Throws a Poco::NotFoundException if the given key
		/// does not exist and a Poco::SyntaxException if
		/// the property value is not a valid floating point number.

	double getFloat(const std::string& key, double deflt) const;
		/// Returns the given value as a double.
		///
		/// Returns deflt if key does not exist.

	void set(const std::string& key, const std::string& value);
		/// Adds a new or updates an existing property.

	void set(const std::string& key, const char* value);
		/// Adds a new or updates an existing property.

	void set(const std::string& key, bool value);
		/// Adds a new or updates an existing property.

	void set(const std::string& key, int value);
		/// Adds a new or updates an existing property.

	void set(const std::string& key, Poco::Int64 value);
		/// Adds a new or updates an existing property.

	void set(const std::string& key, double value);
		/// Adds a new or updates an existing property.

	bool has(const std::string& key) const;
		/// Returns true iff a property with the given key exists.

	void keys(std::vector<std::string>& keys) const;
		/// Fills the given vector with all keys.

	std::vector<std::string> keys() const;
		/// Returns a vector containing all keys.

protected:
	struct ILT
	{
		bool operator() (const std::string& s1, const std::string& s2) const
		{
			return Poco::icompare(s1, s2) < 0;
		}
	};

	using PropsMap = std::map<std::string, std::string, ILT>;

	static const std::string PROP_TRUE;
	static const std::string PROP_FALSE;

private:
	PropsMap _props;
	mutable Poco::FastMutex _mutex;
};


//
// inlines
//
inline std::string Properties::operator [] (const std::string& key) const
{
	return get(key);
}


inline void swap(Properties& p1, Properties& p2)
{
	p1.swap(p2);
}


inline std::vector<std::string> Properties::keys() const
{
	std::vector<std::string> result;
	keys(result);
	return result;
}


} } // namespace Poco::OSP


#endif // OSP_Properties_INCLUDED
