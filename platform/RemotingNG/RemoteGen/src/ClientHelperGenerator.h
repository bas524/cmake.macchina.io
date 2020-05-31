//
// ClientHelperGenerator.h
//
// Definition of the ClientHelperGenerator class.
//
// Copyright (c) 2006-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef RemoteGen_ClientHelperGenerator_INCLUDED
#define RemoteGen_ClientHelperGenerator_INCLUDED


#include "AbstractGenerator.h"
#include "Poco/CodeGeneration/CppGenerator.h"


class ClientHelperGenerator: public AbstractGenerator
	/// ClientHelperGenerator generates a proxy for a given class definition. C++ specific. 
{
public:

	ClientHelperGenerator(Poco::CodeGeneration::CppGenerator& cppGen);
		/// Creates the ClientHelperGenerator.

	~ClientHelperGenerator();
		/// Destroys the ClientHelperGenerator.

	static std::string generateClassName(const Poco::CppParser::Struct* pStruct);
		/// Generates for a given class, its interface class name.

	static std::string generateQualifiedClassName(const std::string& ns, const Poco::CppParser::Struct* pStruct);
		/// Generates for a given class, its interface class name.

	void structStart(const Poco::CppParser::Struct* pStruct, const CodeGenerator::Properties& properties);
		/// Must not write the namespace

	void methodStart(const Poco::CppParser::Function* pFunc, const CodeGenerator::Properties& properties);
		/// Writes the method header. Properties contains the properties found in the functions docuementation and in the class documentation.

	void registerCallbacks(Poco::CodeGeneration::GeneratorEngine& e);

	std::string newClassName(const Poco::CppParser::Struct* pStruct);
		/// generates the new class name based on the old one

	std::vector<std::string> newBaseClasses(const Poco::CppParser::Struct* pStruct);

private:
	static void constructorCodeGen(const Poco::CppParser::Function* pFunc, const Poco::CppParser::Struct* pStruct, CodeGenerator& gen, void* addParam);
	static void instanceCodeGen(const Poco::CppParser::Function* pFunc, const Poco::CppParser::Struct* pStruct, CodeGenerator& gen, void* addParam);
	static void findCodeGen(const Poco::CppParser::Function* pFunc, const Poco::CppParser::Struct* pStruct, CodeGenerator& gen, void* addParam);
	static void findImplCodeGen(const Poco::CppParser::Function* pFunc, const Poco::CppParser::Struct* pStruct, CodeGenerator& gen, void* addParam);
	static void singletonHolder(const Poco::CppParser::Function* pFunc, const Poco::CppParser::Struct* pStruct, CodeGenerator& gen, void* addParam);
};


//
// inlines
//
inline std::string ClientHelperGenerator::newClassName(const Poco::CppParser::Struct* pStruct)
{
	return ClientHelperGenerator::generateClassName(pStruct);
}


#endif // RemoteGen_ClientHelperGenerator_INCLUDED
