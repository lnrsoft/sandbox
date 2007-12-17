//
// HTML.h
//
// $Id: //poco/Main/WebWidgets/include/Poco/WebWidgets/HTML.h#2 $
//
// Library: WebWidgets
// Package: WebGUI
// Module:  HTML
//
// Definition of the HTML class.
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


#ifndef WebWidgets_HTML_INCLUDED
#define WebWidgets_HTML_INCLUDED


#include "Poco/WebWidgets/WebWidgets.h"
#include "Poco/WebWidgets/Label.h"


namespace Poco {
namespace WebWidgets {


class WebWidgets_API HTML: public Label
	/// HTML class contains raw HTML code
	///     <html>
	///          <![CDATA[
	///          <i>some text</i>
	///          ]]>
	///     </html>
{
public:
	static const std::string FACTORY_ID;

	HTML();
		/// Creates the HTML object without text

	HTML(const std::string& txt);
		/// Creates a HTML with the given html text

	HTML(const Poco::XML::Element* pElem);
		/// Creates a HTML from the given element

	virtual ~HTML();
		/// Destroys the HTML.

	void accept(Visitor& v);

	Poco::AutoPtr<Widget> find(const std::string& id) const;

	Poco::AutoPtr<Widget> clone() const;
};


inline Poco::AutoPtr<Widget> HTML::find(const std::string& id) const
{
	return Poco::AutoPtr<Widget>();
}


} } // namespace Poco::WebWidgets


#endif // WebWidgets_HTML_INCLUDED