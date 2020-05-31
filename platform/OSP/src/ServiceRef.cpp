//
// ServiceRef.cpp
//
// Library: OSP
// Package: Service
// Module:  ServiceRef
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/OSP/ServiceRef.h"
#include "Poco/OSP/ServiceFactory.h"


namespace Poco {
namespace OSP {


ServiceRef::ServiceRef(const std::string& name, const Properties& props, Service::Ptr pService):
	_name(name),
	_props(props),
	_pService(pService)
{
}


ServiceRef::~ServiceRef()
{
}


Service::Ptr ServiceRef::instance() const
{
	Poco::AutoPtr<ServiceFactory> pFactory = _pService.cast<ServiceFactory>();
	if (pFactory)
	{	
		return pFactory->createService();
	}
	else
	{
		return _pService;
	}
}


} } // namespace Poco::OSP
