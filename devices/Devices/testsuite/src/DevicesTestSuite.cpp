//
// DevicesTestSuite.cpp
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "DevicesTestSuite.h"
#include "EventModerationPolicyTest.h"


CppUnit::Test* DevicesTestSuite::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("DevicesTestSuite");

	pSuite->addTest(EventModerationPolicyTest::suite());

	return pSuite;
}
