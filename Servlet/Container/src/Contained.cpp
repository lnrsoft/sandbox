//
// Contained.cpp
//
// Library: Container
// Package: ContainerCore
// Module:  Contained
//
// Copyright (c) 2006, Aleksandar Fabijanic and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#include "Poco/Servlet/Container/Contained.h"
#include "Poco/Servlet/Ex/SystemFiles.h"
#include "Poco/Util/LayeredConfiguration.h"
#include "Poco/Util/PropertyFileConfiguration.h"
#include "Poco/Util/SystemConfiguration.h"
#include "Poco/Util/XMLConfiguration.h"
#include "Poco/Mutex.h"
#include "Poco/Path.h"
#include "Poco/SharedLibrary.h"
#include "Poco/Exception.h"
#include <iostream>


using Poco::Util::LoggingConfigurator;
using Poco::Util::XMLConfiguration;
using Poco::Util::LayeredConfiguration;
using Poco::Util::PropertyFileConfiguration;
using Poco::Util::SystemConfiguration;
using Poco::Servlet::Ex::SystemFiles;


namespace Poco {
namespace Servlet {
namespace Container {


Contained::Contained(const std::string& path):
_pConf(0), _pLogger(0)
{
	poco_assert(path.size());
	std::string s = path;
	if(s[s.size()-1] != Path::separator())
		s += Path::separator();

	Path p(s);
	_name = p[p.depth()-1];
	_rootPath = path;
	loadConfiguration();
}


Contained::~Contained()
{
	if(_pLogger)
	{
		SplitterChannel* pFC = dynamic_cast<Poco::SplitterChannel*>(_pLogger->getChannel());
		if(pFC) pFC->close();
		Poco::Logger::destroy(_name);
	}
}


void Contained::loadConfiguration()
{
	std::ostringstream conf;
	conf << _rootPath.toString() << SystemFiles::WEB_INF_DIR << Path::separator() << SystemFiles::WEB_XML_FILE;
	std::ifstream fstr(conf.str().c_str());	
	
	if(!fstr) 
		throw InvalidArgumentException("Could not open file: " + conf.str());
	
	try
	{
		_pConf = new LayeredConfiguration;

		_pConf->add(new SystemConfiguration);
		_pConf->add(new XMLConfiguration(fstr));
	}
	catch(std::exception& ex)
	{
		if(_pLogger) _pLogger->error(ex.what());
		fstr.close();
		throw;
	}

	fstr.close();
}


Poco::Logger* Contained::getLogger()
{
	return _pLogger;
}


const std::string& Contained::name() const
{
	return _name;
}


void Contained::initLogging()
{
	std::ostringstream os;
	os << _rootPath.toString() << SystemFiles::WEB_INF_DIR 
		 << Path::separator() << getInitParameter("log.properties");

	AutoPtr<LayeredConfiguration> pLC = new LayeredConfiguration;
	AutoPtr<PropertyFileConfiguration> pPFC = new PropertyFileConfiguration(os.str());
	AutoPtr<SystemConfiguration> pSC = new SystemConfiguration;

	pLC->add(pPFC);
	pLC->add(pSC);

	LoggingConfigurator configurator;
	configurator.configure(pLC);
	

	std::string loggerName = pPFC->getString("logging.loggers.l1.name");
	Logger& logger1 = Logger::get(loggerName);
	SplitterChannel* pFC = dynamic_cast<SplitterChannel*>(logger1.getChannel());

	if(pFC)	_pLogger = &(Logger::create(_name, pFC));
	if(_pLogger && pFC)	_pLogger->setChannel(pFC);
}


Poco::Path Contained::getSharedLibPath(const std::string& fileName)
{
	std::stringstream dllFile("");

	dllFile << _rootPath.toString()
		<< SystemFiles::WEB_INF_DIR
		<< Path::separator()
		<< SystemFiles::CLASS_DIR
		<< Path::separator()
		<< fileName << SharedLibrary::suffix();

	return Poco::Path(dllFile.str());
}


} } } // namespace Poco::Servlet::Container'
