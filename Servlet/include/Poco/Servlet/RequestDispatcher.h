//
// RequestDispatcher.h
//
//
// Library: Servlet
// Package: Servlet
// Module:  RequestDispatcher
//
// Definition of the RequestDispatcher class.
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


#ifndef Servlet_RequestDispatcher_INCLUDED
#define Servlet_RequestDispatcher_INCLUDED


#include "Poco/Servlet/ServletBase.h"
#include "Poco/Servlet/ServletException.h"


namespace Poco {
namespace Servlet {


class ServletRequest;
class ServletResponse;


class Servlet_API RequestDispatcher
	/// Defines an object that receives requests from the client and sends them to any
	/// resource (such as a servlet, HTML file, or JSP file) on the server. The servlet container
	/// creates the RequestDispatcher object, which is used as a wrapper around a
	/// server resource located at a particular path or given by a particular name.
	/// This interface is intended to wrap servlets, but a servlet container can create
	/// RequestDispatcher objects to wrap any type of resource.
{
public:

	RequestDispatcher();
		/// Creates RequestDispatcher.

	virtual ~RequestDispatcher();
		/// Destroys RequestDispatcher.

	virtual void forward(ServletRequest& request, ServletResponse& response) = 0;
		/// Forwards a request from a servlet to another resource (servlet, JSP file, or
		/// HTML file) on the server. This method allows one servlet to do preliminary
		/// processing of a request and another resource to generate the response.
		/// For a RequestDispatcher obtained via getRequestDispatcher(), the
		/// ServletRequest object has its path elements and parameters adjusted to
		/// match the path of the target resource.
		/// forward should be called before the response has been committed to the client
		/// (before response body output has been flushed). If the response already
		/// has been committed, this method throws an IllegalStateException.
		/// Uncommitted output in the response buffer is automatically cleared before
		/// the forward.
		/// The request and response parameters must be either the same objects as were
		/// passed to the calling servletís service method or be subclasses of the
		/// ServletRequestWrapper or ServletResponseWrapper classes that wrap them.

  virtual void include(ServletRequest& request, ServletResponse& response) = 0;
		/// Includes the content of a resource (servlet, JSP page, HTML file) in the
		/// response. In essence, this method enables programmatic server-side includes.
		/// The ServletResponse object has its path elements and parameters remain
		/// unchanged from the callerís. The included servlet cannot change the response
		/// status code or set headers; any attempt to make a change is ignored.
		/// The request and response parameters must be either the same objects as were
		/// passed to the calling servletís service method or be subclasses of the
		/// ServletRequestWrapper or ServletResponseWrapper classes that wrap them.

};


} } // namespace Poco::Servlet


#endif // Servlet_RequestDispatcher_INCLUDED
