//
// FilterDispatcher.h
//
//
// Library: ServletEx
// Package: Servlet
// Module:  FilterDispatcher
//
// Definition of the FilterDispatcher class.
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


#ifndef ServletEx_FilterDispatcher_INCLUDED
#define ServletEx_FilterDispatcher_INCLUDED


#include "Poco/Servlet/ServletBase.h"
#include "Poco/Servlet/Ex/Dispatcher.h"
#include "Poco/Servlet/Servlet.h"
#include "Poco/Servlet/Ex/ServletProvider.h"
#include "Poco/Servlet/Ex/FilterProvider.h"
#include "Poco/Servlet/HttpServletRequest.h"
#include "Poco/Servlet/HttpServletResponse.h"
#include "Poco/Servlet/ServletContext.h"
#include <map>


namespace Poco {
namespace Servlet {
namespace Ex {


class Servlet_API FilterDispatcher : public Dispatcher
{
public:
	FilterDispatcher();
	virtual ~FilterDispatcher();

	void dispatch(Servlet& servlet,
		HttpServletRequest& request,
		HttpServletResponse& response);
		/// Filters and dispatches servlet request.

	FilterProvider* getFilterProvider(const std::string& name) const;
	void addFilterProvider(FilterProvider* pFilterProvider);

protected:

	ServletContext* getContext(const std::string& name);
		/// Returns the pointer to the named context or 0 if the
		/// context is not found.

	typedef std::map<std::string, FilterProvider*> FilterProviderMap;
	FilterProviderMap _filterProviderMap;
};


} } } // namespace Poco::Servlet::Ex


#endif //ServletEx_FilterDispatcher_INCLUDED
