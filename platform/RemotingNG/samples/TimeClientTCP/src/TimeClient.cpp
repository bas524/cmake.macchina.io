//
// TimeClient.cpp
//
// Copyright (c) 2006-2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "TimeServiceClientHelper.h"
#include "Poco/RemotingNG/TCP/TransportFactory.h"
#include "Poco/RemotingNG/TCP/Listener.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/Delegate.h"
#include "Poco/Thread.h"
#include <iostream>


void onWakeUp(const std::string& message)
{
	std::cout << "WakeUp: " << message << std::endl;
}


int main(int argc, char** argv)
{
	try
	{
		// register transport
		Poco::RemotingNG::TCP::TransportFactory::registerFactory();

		// create event listener
		Poco::RemotingNG::TCP::Listener::Ptr pListener = new Poco::RemotingNG::TCP::Listener;

		// get proxy for remote object
		Services::ITimeService::Ptr pClock = Services::TimeServiceClientHelper::find("remoting.tcp://127.0.0.1:7777/tcp/Services.TimeService/TheClock");

		// invoke method on remote object
		Poco::DateTime dt = pClock->currentTime();
		std::cout << Poco::DateTimeFormatter::format(dt, Poco::DateTimeFormat::SORTABLE_FORMAT) << std::endl;

		// enable events
		pClock->remoting__enableEvents(pListener);
		pClock->wakeUp += Poco::delegate(onWakeUp);

		// schedule wake up call
		Poco::DateTime wakeUpTime;
		wakeUpTime += Poco::Timespan(5000000); // 5 seconds
		pClock->wakeMeUp(wakeUpTime, "Good morning!");

		// wait for event
		Poco::Thread::sleep(10000);

		// disable events
		pClock->wakeUp -= Poco::delegate(onWakeUp);
		pClock->remoting__enableEvents(pListener, false);
	}
	catch (Poco::Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
		return 1;
	}
	return 0;
}
