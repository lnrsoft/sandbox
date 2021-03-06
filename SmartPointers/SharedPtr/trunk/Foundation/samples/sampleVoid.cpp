//
// sampleVoid.cpp
//
// Copyright (c) 2004-2008, Applied Informatics Software Engineering GmbH.
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

#include "Poco/SharedPtr.h"
#include "Poco/Debugger.h"
#include "Poco/Bugcheck.h"
#include <iostream>

using Poco::SharedPtr;

namespace
{
    class TestObject
    {
    public:
        TestObject(const int& data = 0) : _data(data)
        {
            ++_count;
            std::cout << "current counter : " << _count << "\n";
        }

        virtual ~TestObject()
        {
            --_count;
            std::cout << "current counter : " << _count << "\n";
        }

        void set(const int& data)
        {
            _data = data;
        }

        int& data()
        {
            return _data;
        }

        static int count()
        {
            return _count;
        }

		static void destory(TestObject* p){
			std::cout << "TestObject::destory delete" << std::endl;
			delete p;
		}

    private:
        int _data;
        static int _count;
    };

    int TestObject::_count = 0;

	class DerivedObject: public TestObject
	{
	public:
		DerivedObject(int i): _number(i)
		{
		}

		int number() const
		{
			return _number;
		}
	private:
		int _number;
	};
}

int main()
{

    {
        /// hold an arbitrary object
        SharedPtr<void> ptr (new TestObject);
        poco_assert(ptr.get() != 0);
        poco_assert(TestObject::count() == 1);
    }

    poco_assert(TestObject::count() == 0);

}
