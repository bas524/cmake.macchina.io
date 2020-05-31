//
// HighRateAccelerometer.cpp
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "HighRateAccelerometer.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Delegate.h"
#include "Poco/Format.h"


namespace IoT {
namespace XDK {


const std::string HighRateAccelerometer::NAME("XDK Accelerometer");
const std::string HighRateAccelerometer::TYPE("io.macchina.accelerometer");
const std::string HighRateAccelerometer::SYMBOLIC_NAME("io.macchina.xdk.accelerometer");


HighRateAccelerometer::HighRateAccelerometer(BtLE::Peripheral::Ptr pPeripheral):
	_pPeripheral(pPeripheral),
	_enabled(false),
	_ready(false),
	_deviceIdentifier(pPeripheral->address())
{
	addProperty("displayValue", &HighRateAccelerometer::getDisplayValue);
	addProperty("enabled", &HighRateAccelerometer::getEnabled, &HighRateAccelerometer::setEnabled);
	addProperty("connected", &HighRateAccelerometer::getConnected);
	addProperty("deviceIdentifier", &HighRateAccelerometer::getDeviceIdentifier);
	addProperty("symbolicName", &HighRateAccelerometer::getSymbolicName);
	addProperty("name", &HighRateAccelerometer::getName);
	addProperty("type", &HighRateAccelerometer::getType);

	_pPeripheral->connected += Poco::delegate(this, &HighRateAccelerometer::onConnected);
	_pPeripheral->disconnected += Poco::delegate(this, &HighRateAccelerometer::onDisconnected);

	init();
}


HighRateAccelerometer::~HighRateAccelerometer()
{
	_pPeripheral->connected -= Poco::delegate(this, &HighRateAccelerometer::onConnected);
	_pPeripheral->disconnected -= Poco::delegate(this, &HighRateAccelerometer::onDisconnected);

	_pPeripheral = 0;
}


bool HighRateAccelerometer::isConnected() const
{
	return _pPeripheral->isConnected();
}


IoT::Devices::Acceleration HighRateAccelerometer::acceleration() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _acceleration;
}


void HighRateAccelerometer::enable(bool enabled)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	_enabled = enabled;
}


Poco::Any HighRateAccelerometer::getEnabled(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _enabled;
}


void HighRateAccelerometer::setEnabled(const std::string&, const Poco::Any& value)
{
	enable(Poco::AnyCast<bool>(value));
}


Poco::Any HighRateAccelerometer::getConnected(const std::string&) const
{
	return isConnected();
}


Poco::Any HighRateAccelerometer::getDisplayValue(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_ready && _enabled)
		return Poco::format("x=%.2f y=%.2f z=%.2f", _acceleration.x, _acceleration.y, _acceleration.z);
	else
		return std::string("n/a");
}


Poco::Any HighRateAccelerometer::getDeviceIdentifier(const std::string&) const
{
	return _deviceIdentifier;
}


Poco::Any HighRateAccelerometer::getName(const std::string&) const
{
	return NAME;
}


Poco::Any HighRateAccelerometer::getType(const std::string&) const
{
	return TYPE;
}


Poco::Any HighRateAccelerometer::getSymbolicName(const std::string&) const
{
	return SYMBOLIC_NAME;
}


void HighRateAccelerometer::update(const IoT::Devices::Acceleration& acceleration)
{
	Poco::ScopedLockWithUnlock<Poco::Mutex> lock(_mutex);

	if (_enabled)
	{
		if (!_ready || acceleration.x != _acceleration.x || acceleration.y != _acceleration.y || acceleration.z != _acceleration.z)
		{
			_ready = true;
			_acceleration = acceleration;
			lock.unlock();

			accelerationChanged(this, acceleration);
		}
	}
}


void HighRateAccelerometer::init()
{
	enable(true);
}


void HighRateAccelerometer::onConnected()
{
}


void HighRateAccelerometer::onDisconnected()
{
	Poco::Mutex::ScopedLock lock(_mutex);

	_ready = false;
}


} } // namespace IoT::XDK
