//
// HighRateAccelerometer.h
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_XDK_HighRateAccelerometer_INCLUDED
#define IoT_XDK_HighRateAccelerometer_INCLUDED


#include "IoT/Devices/Accelerometer.h"
#include "IoT/Devices/DeviceImpl.h"
#include "IoT/BtLE/Peripheral.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace XDK {


class HighRateAccelerometer: public IoT::Devices::DeviceImpl<IoT::Devices::Accelerometer, HighRateAccelerometer>
{
public:
	using Ptr = Poco::SharedPtr<HighRateAccelerometer>;

	HighRateAccelerometer(BtLE::Peripheral::Ptr pPeripheral);
		/// Creates a HighRateAccelerometer.

	~HighRateAccelerometer();
		/// Destroys the HighRateAccelerometer.

	bool isConnected() const;
		/// Returns true if the sensor's peripheral is connected.

	void update(const IoT::Devices::Acceleration& acceleration);
		/// Updates the acceleration.

	// Accelerometer
	IoT::Devices::Acceleration acceleration() const;

	static const std::string NAME;
	static const std::string TYPE;
	static const std::string SYMBOLIC_NAME;

protected:
	void init();
	void enable(bool enabled);
	Poco::Any getConnected(const std::string&) const;
	Poco::Any getEnabled(const std::string&) const;
	void setEnabled(const std::string&, const Poco::Any& value);
	Poco::Any getDisplayValue(const std::string&) const;
	Poco::Any getDeviceIdentifier(const std::string&) const;
	Poco::Any getName(const std::string&) const;
	Poco::Any getType(const std::string&) const;
	Poco::Any getSymbolicName(const std::string&) const;
	void onConnected();
	void onDisconnected();

protected:
	mutable BtLE::Peripheral::Ptr _pPeripheral;
	bool _enabled;
	bool _ready;
	IoT::Devices::Acceleration _acceleration;
	Poco::Any _deviceIdentifier;
};


} } // namespace IoT::XDK


#endif // IoT_XDK_HighRateAccelerometer_INCLUDED

