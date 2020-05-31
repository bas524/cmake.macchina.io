//
// PizzaPickupService.h
//
// Definition of the PizzaPickupService class.
//
// Copyright (c) 2006-2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef PizzaPickupService_INCLUDED
#define PizzaPickupService_INCLUDED


#include "Pizzeria/PizzaDeliveryService.h"
#include "Poco/Random.h"
#include "Poco/DateTime.h"
#include "Poco/Timespan.h"


namespace Pizzeria {


//@ namespace="http://www.appinf.com/webservices/PizzaDeliveryService/", cacheExpire="5min"
class PizzaPickupService: public PizzaDeliveryService
	/// Pizzeria that allows self pickup.
{
public:
	PizzaPickupService();
		/// Creates the PizzaPickupService.

	virtual ~PizzaPickupService();
		/// Destroys the PizzaPickupService.

	//@ remote
	//@ synchronized = "true"
	//@ $pizza = {order = 2}
	//@ $phoneNumber = {order = 1}
	Poco::DateTime orderForSelfPickup(const Pizza& pizza, const std::string& phoneNumber);
		/// Order a pizza, send it to the given deliveryAddress.
		/// Returns the expected time when the Pizza will arrive.

	//@ remote
	//@ synchronized = "true"
	//@ $pizza = {order = 2}
	//@ $deliverTo = {order = 1}
	Poco::DateTime order(const Pizza& pizza, const DeliveryAddress& deliverTo);
		/// Order a pizza, send it to the given deliveryAddress.
		/// Returns the expected time when the Pizza will arrive.
		/// Note that when we override a method it must be equal even for all annotations
};


inline Poco::DateTime PizzaPickupService::order(const Pizza& pizza, const DeliveryAddress& deliverTo)
{
	return PizzaDeliveryService::order(pizza, deliverTo);
}


} // namespace Pizzeria


#endif // PizzaPickupService_INCLUDED
