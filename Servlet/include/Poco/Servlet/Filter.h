//
// Filter.h
//
//
// Library: Servlet
// Package: Servlet
// Module:  Filter
//
// Definition of the Filter class.
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
//
// The code in this file is derived from Apache Tomcat project
// Copyright (c) 2004 The Apache Software Foundation.
// http://www.apache.org/licenses/LICENSE-2.0
// 


#ifndef Servlet_Filter_INCLUDED
#define Servlet_Filter_INCLUDED


#include "Poco/Servlet/ServletRequest.h"
#include "Poco/Servlet/ServletResponse.h"
#include "Poco/Servlet/ServletBase.h"


namespace Poco {
namespace Servlet {


class Servlet_API FilterChain 
	/// A FilterChain is an object provided by the servlet container to the developer
  /// giving a view into the invocation chain of a filtered request for a resource. Filters
  /// use the FilterChain to invoke the next filter in the chain, or if the calling filter
  /// is the last filter in the chain, to invoke the resource at the end of the chain.
{
 public:	

	virtual void doFilter(ServletRequest& request, ServletResponse& response) const = 0;
		/// Causes the next filter in the chain to be invoked, or if the calling filter is the last filter
		/// in the chain, causes the resource at the end of the chain to be invoked.
};


class Servlet_API FilterConfig 
	/// A filter configuration object used by a servlet container
	/// to pass information to a filter during initialization.
{
public:
	virtual const std::string& getFilterName() const = 0;
		/// Returns the filter-name of this filter as defined in the deployment descriptor. 

	virtual const ServletContext& getServletContext() const = 0;
		/// Returns a reference to the {ServletContext} in which the caller
		/// is executing.

	virtual const std::string& getInitParameter(const std::string& name) const = 0;
		/// Returns a string containing the value of the 
		/// named initialization parameter, or null if 
		/// the parameter does not exist.

	virtual std::vector<std::string> getInitParameterNames() const = 0;
		/// Returns the names of the filter's initialization parameters
		/// as an vector of string objects, or an empty vector if the filter 
		/// has no initialization parameters.
};


class Servlet_API Filter
	/// A filter is an object that performs filtering tasks on either the request to a resource 
	/// (a servlet or static content), or on the response from a resource, or both.
	/// Filters perform filtering in the doFilter method. Every Filter has access to 
	/// a FilterConfig object from which it can obtain its initialization parameters, a
	/// reference to the ServletContext which it can use, for example, to load resources
	/// needed for filtering tasks.
	/// Filters are configured in the deployment descriptor of a web application
	/// Examples that have been identified for this design are<br>
	/// 1) Authentication Filters
	/// 2) Logging and Auditing Filters
	/// 3) Image conversion Filters
	/// 4) Data compression Filters
	/// 5) Encryption Filters
	/// 6) Tokenizing Filters
	/// 7) Filters that trigger resource access events
	/// 8) XSL/T filters
	/// 9) Mime-type chain Filter
	///
{
public:
	Filter();
		/// Creates a Filter.

	virtual ~Filter();
		/// Destroys a filter.

	virtual void init(FilterConfig* pFilterConfig);
		/// Called by the web container to indicate to a filter that it is being placed into
		/// service. The servlet container calls the init method exactly once after instantiating the
		/// filter. The init method must complete successfully before the filter is asked to do any
		/// filtering work.
		///
		/// The web container cannot place the filter into service if the init method either
		///    1.Throws a ServletException
		///    2.Does not return within a time period defined by the web container 
	
	
	virtual void doFilter(ServletRequest& request, ServletResponse& response, const FilterChain* pchain=0) const = 0;
		/// The doFilter method of the Filter is called by the container
		/// each time a request/response pair is passed through the chain due
		/// to a client request for a resource at the end of the chain. The FilterChain passed in to this
		/// method allows the Filter to pass on the request and response to the next entity in the
		/// chain.
		/// A typical implementation of this method would follow the following pattern:
		/// 1. Examine the request
		/// 2. Optionally wrap the request object with a custom implementation to
		/// filter content or headers for input filtering
		/// 3. Optionally wrap the response object with a custom implementation to
		/// filter content or headers for output filtering
		/// 4. a)	Either invoke the next entity in the chain using the FilterChain object 
		///				(chain.doFilter()),
		///    b)	or not pass on the request/response pair to the next entity in the filter chain 
		///				to block the request processing
		/// 5. Directly set headers on the response after invocation of the next entity in the filter chain.

	virtual void destroy();
		/// Called by the web container to indicate to a filter that it is being taken out of service. This 
		/// method is only called once all threads within the filter's doFilter method have exited or after
		/// a timeout period has passed. After the web container calls this method, it will not call the
		/// doFilter method again on this instance of the filter.
		/// 
		/// This method gives the filter an opportunity to clean up any resources that are being held (for
		/// example, memory, file handles, threads) and make sure that any persistent state is synchronized
		/// with the filter's current state in memory.
	
private:
	FilterConfig* _pConfig;
};

///
/// inlines
///

inline void Filter::init(FilterConfig* pFilterConfig)
{
	_pConfig = pFilterConfig;
}


inline void Filter::destroy()
{
	delete _pConfig;
	_pConfig = 0;
}


} } // namespace Poco::Servlet


#endif //Servlet_Filter_Included
