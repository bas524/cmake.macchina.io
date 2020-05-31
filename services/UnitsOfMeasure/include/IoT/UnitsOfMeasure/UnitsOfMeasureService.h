//
// UnitsOfMeasureService.h
//
// Library: IoT/UnitsOfMeasure
// Package: UnitsOfMeasure
// Module:  UnitsOfMeasureService
//
// Definition of the UnitsOfMeasureService interface.
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_UnitsOfMeasure_UnitsOfMeasureService_INCLUDED
#define IoT_UnitsOfMeasure_UnitsOfMeasureService_INCLUDED


#include "IoT/UnitsOfMeasure/UnitsOfMeasure.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace UnitsOfMeasure {


//@ serialize
struct IoTUnitsOfMeasure_API Prefix
	/// A multiplier prefix, e.g. Y (yotta) or k (kilo).
{
	using Ptr = Poco::SharedPtr<Prefix>;

	Prefix(): value(0) { }

	std::string code;
		/// case-sensitive code (e.g. "k")

	std::string icode;
		/// case-insensitive code (e.g. "K")

	std::string name;
		/// name (e.g. "kilo")

	std::string print;
		/// printable prefix

	double value;
		/// multiplier value (e.g. 1000 for kilo)
};


//@ serialize
struct IoTUnitsOfMeasure_API Unit
	/// A base or derived unit, e.g. m (meter).
{
	using Ptr = Poco::SharedPtr<Unit>;

	Unit(): metric(false), value(0) { }

	std::string code;
		/// case-sensitive code (e.g. "m")

	std::string icode;
		/// case-insensitive code (e.g. "M")

	std::string name;
		/// unit name (e.g. "meter")

	std::string print;
		/// printable unit (UTF-8); may contain the following tags:
		///    - <sub>: subscript
		///    - <sup>: superscript
		///    - <r>: roman literal
		///    - <i>: italic

	std::string property;
		/// physical quantity (e.g., "length", "temperature")

	std::string group;
		/// group (class) this unit belongs to, e.g.
		/// "dimless", "si", "iso1000", "const", etc.

	std::string dim;
		/// dimension for base units, empty for derived units.
		///   - L: Length
		///   - T: Time
		///   - M: Mass
		///   - A: Angle
		///   - C: Temperature (theta)
		///   - Q: Electric Charge
		///   - F: Luminous Intensity (J)

	bool metric;
		/// true if unit is metric, otherwise false

	std::string unit;
		/// definition unit (e.g., "J/C" for Volt)

	std::string iunit;
		/// case-insensitive definition unit

	double value;
		/// definition value
};


//@ serialize
struct PrefixedUnit
	/// A structure combining prefix and unit.
{
	Prefix::Ptr prefix; /// optional, may be null
	Unit::Ptr unit;     /// mandatory, not null
};


//@ serialize
struct CanonicalValue
	/// A canonical value, obtained by removing the prefix from a unit
	/// and scaling the value accordingly.
{
	CanonicalValue(): value(0) { }

	double value;
	std::string code;
};


//@ remote
class IoTUnitsOfMeasure_API UnitsOfMeasureService
	/// The UnitsOfMeasureService service is mainly used to map
	/// [[http://unitsofmeasure.org/ucum.html Unified Code for Units of Measure]] (UCUM),
	/// codes, such as used with the IoT::Devices::Sensor interface, to display/print units.
	///
	/// It provides a programmatic interface to the
	/// [[http://unitsofmeasure.org/ucum-essence.xml UCUM-Essence XML file]]
	/// containing unit definitions.
{
public:
	using Ptr = Poco::SharedPtr<UnitsOfMeasureService>;

	UnitsOfMeasureService();
		/// Creates the UnitsOfMeasureService.

	virtual ~UnitsOfMeasureService();
		/// Destroys the UnitsOfMeasureService.

	virtual Prefix::Ptr findPrefix(const std::string& code) const = 0;
		/// Looks up the prefix with the given code.
		///
		/// Returns the Prefix, or a null pointer if not found.

	virtual Unit::Ptr findUnit(const std::string& code) const = 0;
		/// Looks up the unit with the given (non-prefixed) code.
		///
		/// Returns the Unit, or a null pointer if not found.

	virtual PrefixedUnit resolve(const std::string& prefixedCode) const = 0;
		/// Looks up the given unit code with optional prefix (e.g., "cm")
		/// and returns a PrefixUnit structure containing the (optional) prefix
		/// and unit information.
		///
		/// Throws a Poco::NotFoundException if no matching unit is found.

	virtual std::string format(const std::string& prefixedCode) const = 0;
		/// Looks up the given unit code with optional prefix (e.g., "cm")
		/// and returns the "printable" string.
		///
		/// If not found, simply returns prefixedCode.

	virtual CanonicalValue canonicalize(double value, const std::string& prefixedCode) const = 0;
		/// Removes the prefix from the code and scales the value accordingly.

	virtual double convert(double value, const std::string& fromPrefixedCode, const std::string& toPrefixedCode) const = 0;
		/// Attempts to convert the value from one unit (given in fromPrefixedCode) to a different one
		/// (given in toPrefixedCode). Conversion only works if both units share the same base unit,
		/// which must be atomic. Unfortunately, this means that conversion only works for
		/// a small set of unit pairs, e.g. from km to nautical miles [nmi_i].
		///
		/// Temperature conversions between degrees Celsius ("Cel"), degrees Fahrenheit ("[degF]") and Kelvin ("K") are supported.
		///
		/// Throws a Poco::InvalidArgumentException if the conversion cannot be performed.
};


} } // namespace IoT::UnitsOfMeasure


#endif // IoT_UnitsOfMeasure_UnitsOfMeasureService_INCLUDED
