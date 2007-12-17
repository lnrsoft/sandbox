//
// Form.h
//
// $Id: //poco/Main/WebWidgets/include/Poco/WebWidgets/Form.h#2 $
//
// Library: WebWidgets
// Package: WebGUI
// Module:  Form
//
// Definition of the Form class.
//
// Copyright (c) 2007, Applied Informatics Software Engineering GmbH.
// and Contributors.
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


#ifndef WebWidgets_Form_INCLUDED
#define WebWidgets_Form_INCLUDED


#include "Poco/WebWidgets/WebWidgets.h"
#include "Poco/WebWidgets/IndexedPanel.h"
#include "Poco/URI.h"


namespace Poco {
namespace WebWidgets {


class WebWidgets_API Form: public IndexedPanel
	/// A HTML form object containing multiple other widgets.
	/// A Form contains two urls: one allows to specify the action that should be executed
	/// e.g. the url of a CGI script, and the 2nd optional is a redirect URL to a page that
	/// should be shown after processing has finished.
{
public:
	static const std::string FACTORY_ID;
	static const std::string XML_ACTION;
	static const std::string XML_REDIRECT;
	static const std::string XML_METHOD;
	static const std::string VAL_GET;
	static const std::string VAL_POST;

	enum Method
	{
		M_GET,
		M_POST
	};

	Form(const Poco::URI& action, const Poco::URI& redirect, Method m = M_GET, const std::vector<Poco::AutoPtr<Widget> >& children = std::vector<Poco::AutoPtr<Widget> >());
		/// Creates the Form. If redirect is an empty URL, we assume to redirect to action.

	Form(const Poco::XML::Element* pElem);
		/// Creates the Form from the XML.

	virtual ~Form();
		/// Destroys the Form.

	void accept(Visitor& v);

	const Poco::URI& getAction() const;
		/// Get the url to which the form will direct to.

	const Poco::URI& getRedirect() const;
		/// Get the url to which we will redirect after we have prcoessed the form elements 

	Form::Method getMethod() const;
		/// Returns if we use a GET or POST HTML command

	const std::string& getMethodStr() const;
		/// Returns if we use a GET or POST HTML command as string

	void setAction(const Poco::URI& action);
		/// Sets the action

	void setMethod(Form::Method method);
		/// Sets the type of command method

	Poco::AutoPtr<Widget> clone() const;

private:
	Poco::URI _action;
	Poco::URI _redirect;
	Method    _method;
};


inline const Poco::URI& Form::getAction() const
{
	return _action;
}


inline const Poco::URI& Form::getRedirect() const
{
	return _redirect;
}


inline Form::Method Form::getMethod() const
{
	return _method;
}


inline void Form::setAction(const Poco::URI& action)
{
	_action = action;
}


inline void Form::setMethod(Form::Method method)
{
	_method = method;
}


} } // namespace Poco::WebWidgets


#endif // WebWidgets_Form_INCLUDED