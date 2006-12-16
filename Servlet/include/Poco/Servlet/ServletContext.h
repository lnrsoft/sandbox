//
// ServletContext.h
//
//
// Library: Servlet
// Package: Servlet
// Module:  ServletContext
//
// Definition of the ServletContext class.
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


#ifndef Servlet_ServletContext_INCLUDED
#define Servlet_ServletContext_INCLUDED


#include "Poco/Servlet/ServletBase.h"
#include "Poco/Servlet/Object.h"
#include "Poco/Servlet/ServletException.h"
#include "Poco/Servlet/RequestDispatcher.h"
#include <string>
#include <vector>
#include <map>


namespace Poco {
namespace Servlet {


typedef std::map<std::string, std::string>        ContextInitParamMap;
typedef std::map<std::string, std::string>        MimeMap;
typedef std::map<std::string, RequestDispatcher*> RequestDispatcherMap;
typedef std::map<std::string, const Object*>      ObjectMap;


class Servlet;
class HttpSession;


class Servlet_API ServletContext 
	/// Defines a set of methods that a servlet uses to communicate with its servlet container,
	/// for example, to get the MIME type of a file, dispatch requests, or write to a
	/// log file.
	/// There is one context per web application(A �web application� is a collection of servlets 
	/// and content installed under a specific subset of the server�s URL namespace).
	/// The ServletContext object is contained within the ServletConfig object,
	/// which the Web server provides the servlet when the servlet is initialized.
{
public:
	ServletContext();
		/// Creates ServletContext.

	virtual ~ServletContext();
		/// Destroys ServletContext.

	virtual const Object* getAttribute(const std::string& name) const = 0;
		/// Returns the servlet container attribute with the given name, or null if there is
		/// no attribute by that name. An attribute allows a servlet container to give the
		/// servlet additional information not already provided by this interface. 
		/// A list of supported attributes can be retrieved using getAttributeNames.

	virtual std::vector<std::string> getAttributeNames() const = 0;
		/// Returns a vector containing the attribute names available within this
		/// servlet context. Use the getAttribute(std::string) method with an attribute
		/// name to get the value of an attribute.

	virtual const ServletContext* getContext(const std::string& uripath) const = 0;
		/// Returns a ServletContext object that corresponds to a specified URL on the
		/// server.
		/// This method allows servlets to gain access to the context for various parts of
		/// the server, and as needed obtain RequestDispatcher objects from the context.
		/// The given path must be begin with �/�, is interpreted relative to the
		/// server�s document root and is matched against the context roots of other web
		/// applications hosted on this container.
		/// In a security conscious environment, the servlet container may return empty object
		/// for a given URL.

	virtual std::string getInitParameter(const std::string& name) const = 0;
		/// Returns a String containing the value of the named context-wide initialization
		/// parameter, or empty string if the parameter does not exist.

	virtual std::vector<std::string> getInitParameterNames() const = 0;
		/// Returns the names of the context�s initialization parameters as a
		/// vector of string objects, or an empty vector if the context has
		/// no initialization parameters.

	int getMajorVersion();
		/// Returns the major version of the Servlet API that this servlet container
		/// supports. 

	virtual std::string getMimeType(const std::string& file) const = 0;
		/// Returns the MIME type of the specified file, or empty string if the MIME type is not
		/// known. The MIME type is determined by the configuration of the servlet
		/// container, and may be specified in a web application deployment descriptor.
		/// Common MIME types are �text/html� and �image/gif�.

	int getMinorVersion();
		/// Returns the minor version of the Servlet API that this servlet container
		/// supports. 

		//virtual const Servlet::RequestDispatcher* getNamedDispatcher(const std::string& name) const = 0;
		/// Returns a pointer to RequestDispatcher object that acts as a wrapper for the named
		/// servlet. Servlets may be given names via server administration
		/// or via a web application deployment descriptor. A servlet instance can determine
		/// its name using ServletConfig.getServletName() .
		/// This method returns 0 if the ServletContext cannot return a 
		/// RequestDispatcher for any reason.
		/// Important: Caller takes the ownership of the returned object and is
		/// responsible for cleaning up the resources after the object is not needed any more.

	virtual std::string getRealPath(const std::string& path) const = 0;
		/// Returns a String containing the real path for a given virtual path. For example,
		/// the path �/index.html� returns the absolute file path on the server�s filesystem
		/// that would be served by a request for �http://host/contextPath/index.html�,
		/// where contextPath is the context path of this ServletContext.
		/// The real path returned will be in a form appropriate to the computer and operating
		/// system on which the servlet container is running, including the proper
		/// path separators. This method returns empty string if the servlet container cannot
		/// translate the virtual path to a real path for any reason.

	//TODO
	//virtual const Servlet::RequestDispatcher* getRequestDispatcher(const std::string& path) const = 0;
		/// Returns a pointer to RequestDispatcher object that acts as a wrapper for the resource
		/// located at the given path. A RequestDispatcher object can be used to forward
		/// a request to the resource or to include the resource in a response. The
		/// resource can be dynamic or static.
		/// The pathname must begin with a �/� and is interpreted as relative to the current
		/// context root. Use getContext to obtain a RequestDispatcher for
		/// resources in foreign contexts. This method returns 0 if the 
		/// ServletContext cannot return a RequestDispatcher.
		/// Important: Caller takes the ownership of the returned object and is
		/// responsible for cleaning up the resources after the object is not needed any more.

	//TODO
	//virtual std::string getResource(const std::string& path) const = 0;
		/// Returns the resource mapped to the specified path. The path
		/// must begin with a �/� and is interpreted as relative to the current context root.
		/// This method allows the servlet container to make a resource available to servlets
		/// from any source.
		/// The servlet container must implement the URL handlers and URLConnection
		/// objects that are necessary to access the resource.
		/// This method throws NotFoundException if no resource is mapped to the pathname.
		
	//TODO
	//std::istream* getResourceAsStream(const std::string& path);
		/// Returns the resource located at the named path as an InputStream object.
		/// The data in the InputStream can be of any type or length. The path must be
		/// specified according to the rules given in getResource. This method returns
		/// null if no resource exists at the specified path.

	virtual std::vector<std::string> getResourcePaths(const std::string& path) const = 0;
		/// Returns a directory-like listing of all the paths to resources within the web
		/// application whose longest sub-path matches the supplied path argument.
		/// Paths indicating subdirectory paths end with a �/�. The returned paths are all
		/// relative to the root of the web application and have a leading �/�. For example,
		/// for a web application containing
		/// 	/welcome.html
		/// 	/catalog/index.html
		/// 	/catalog/products.html
		/// 	/catalog/offers/books.html
		/// 	/catalog/offers/music.html
		/// 	/customer/login.jsp
		/// 	/WEB-INF/web.xml
		/// 	/WEB-INF/classes/com.acme.OrderServlet.class,
		/// 	getResourcePaths(�/�) returns {�/welcome.html�, �/catalog/�, �/customer/�,
		/// 	�/WEB-INF/�}
		/// 	getResourcePaths(�/catalog/�) returns {�/catalog/index.html�, �/catalog/
		/// 	products.html�, �/catalog/offers/�}.

	virtual std::string getServerInfo() = 0;
		/// Returns the name and version of the servlet container on which the servlet is
		/// running. The form of the returned string is servername/versionnumber. 

	virtual std::string getServletContextName() const = 0;
		/// Returns the name of this web application corresponding to this 
		/// ServletContext as specified in the deployment descriptor 
		/// for this web application by the display-name element.

	//TODO 
	virtual void log(const std::string& msg) const = 0;
		/// Writes the specified message to the servlet log.
    
	//TODO 
	virtual void log(const std::string& message, const ServletException& servExcep) const = 0;
		/// Writes an explanatory message and info associated with the given 
		/// exception to the servlet log. The name and type of the servlet log is
		/// specific to the servlet container.

	virtual void fatalNS(const std::string& msg) const = 0;
	virtual void criticalNS(const std::string& msg) const = 0;
	virtual void errorNS(const std::string& msg) const = 0;
	virtual void warningNS(const std::string& msg) const = 0;
	virtual void noticeNS(const std::string& msg) const = 0;
	virtual void infoNS(const std::string& msg) const = 0;
	virtual void debugNS(const std::string& msg) const = 0;
	virtual void traceNS(const std::string& msg) const = 0;

	virtual void removeAttribute(const std::string& name) = 0;
		/// Removes the attribute with the given name from the servlet context. After
		/// removal, subsequent calls to getAttribute(String) to retrieve the
		/// attribute�s value will return null. If listeners are configured on the 
		/// ServletContext the container notifies them	accordingly.

	virtual void setAttribute(std::string name, const Object* pAttribute) = 0;
		/// Binds an object to a given attribute name in this servlet context. If the name
		/// specified is already used for an attribute, this method will replace the attribute
		/// with the new to the new attribute.
		/// If listeners are configured on the ServletContext the container notifies them
		/// accordingly.
		/// If null pointer is passed, the effect is the same as calling removeAttribute(name).

	const Servlet* getServlet(const std::string& name);
		///  Deprecated in standard API. Must return 0.

	const std::vector<Servlet*>* getServlets() const;
		///  Deprecated in standard API. Must return 0.
	
};


inline int ServletContext::getMajorVersion() 
{ 
	return POCO_SERVLET_VERSION_MAJOR;
}


inline int ServletContext::getMinorVersion()
{ 
	return POCO_SERVLET_VERSION_MINOR; 
}


inline const Servlet* ServletContext::getServlet(const std::string& name)
{
	return 0;
}


inline const std::vector<Servlet*>* ServletContext::getServlets() const
{
	return 0;
}


} } // namespace Poco::Servlet


#endif // Servlet_ServletContext_INCLUDED


