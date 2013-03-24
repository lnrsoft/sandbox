//
// SerialConfig_POSIX.h
//
// $Id: //poco/Main/DeviceIO/include/Poco/DeviceIO/Serial/SerialConfig_POSIX.h#1 $
//
// Library: Serial
// Package: Serial
// Module:  SerialConfig
//
// Definition of the SerialConfigImpl class for POSIX.
//
// Copyright (c) 2008, Applied Informatics Software Engineering GmbH.
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


#ifndef Serial_SerialConfig_POSIX_INCLUDED
#define Serial_SerialConfig_POSIX_INCLUDED


#include "Poco/DeviceIO/Serial/Serial.h"
#include "Poco/RefCountedObject.h"
#include "Poco/Exception.h"
#include <termios.h>


namespace Poco {
namespace DeviceIO {
namespace Serial {


class Serial_API SerialConfigImpl: virtual public RefCountedObject
{
public:
	static const int NOT_SUPPORTED = -1;

	enum DataBitsImpl
	{
		DATA_BITS_FIVE_IMPL = CS5,
		DATA_BITS_SIX_IMPL = CS6,
		DATA_BITS_SEVEN_IMPL = CS7,
		DATA_BITS_EIGHT_IMPL = CS8
	};

	enum ParityImpl
	{
		PARITY_NONE_IMPL = 2,
		PARITY_ODD_IMPL = 1,
		PARITY_EVEN_IMPL = 0,
		PARITY_MARK_IMPL = NOT_SUPPORTED,
		PARITY_SPACE_IMPL = NOT_SUPPORTED
	};

	enum StartBitsImpl
	{
		START_ONE_IMPL = 0,
		START_ONE5_IMPL = NOT_SUPPORTED,
		START_TWO_IMPL = 1
	};

	enum StopBitsImpl
	{
		STOP_ONE_IMPL = 1,
		STOP_ONE5_IMPL = NOT_SUPPORTED,
		STOP_TWO_IMPL = 2
	};

	enum FlowControlImpl
	{
		FLOW_CTRL_HARDWARE_IMPL,
		FLOW_CTRL_SOFTWARE_IMPL
	};

	enum BPSRateImpl
	{
		BPS_110_IMPL = B110,
		BPS_300_IMPL = B300,
		BPS_600_IMPL = B600,
		BPS_1200_IMPL = B1200,
		BPS_2400_IMPL = B2400,
		BPS_4800_IMPL = B4800,
		BPS_9600_IMPL = B9600,
		BPS_14400_IMPL = NOT_SUPPORTED,
		BPS_19200_IMPL = B19200,
		BPS_38400_IMPL = B38400,
		BPS_57600_IMPL = B57600,
		BPS_115200_IMPL = B115200,
		BPS_128000_IMPL = NOT_SUPPORTED,
		BPS_230400_IMPL  = B230400,
		BPS_256000_IMPL = NOT_SUPPORTED,
		BPS_460800_IMPL  = B460800
	};

	virtual const std::string& name() const = 0;

protected:
	SerialConfigImpl(
		BPSRateImpl bpsRate,
		DataBitsImpl dataBits,
		char parity,
		StartBitsImpl startBits,
		StopBitsImpl stopBits,
		FlowControlImpl flowControl,
		unsigned char xOnChar,
		unsigned char xOffChar,
		bool useEOF,
		unsigned char eofChar,
		int bufferSize,
		int timeout);

	virtual ~SerialConfigImpl();

	void setBPSRateImpl(BPSRateImpl bpsRate);
	void setDataBitsImpl(DataBitsImpl dataBits);
	void setParityImpl(ParityImpl parity);
	void setParityCharImpl(char parityChar);
	void setStartBitsImpl(StartBitsImpl startBits);
	void setStopBitsImpl(StopBitsImpl stopBits);
	void setFlowControlImpl(FlowControlImpl flowControl,
		unsigned char xOnChar,
		unsigned char xOffChar);
	void setUseXonXoffImpl(unsigned char xOnChar,
		unsigned char xOffChar);
	void setXonCharImpl(unsigned char xOn);
	void setXoffCharImpl(unsigned char xOff);
	void setUseEOFImpl(bool) const;
	void setEOFCharImpl(unsigned char eof);
	void setBufferSizeImpl(int size);
	void setTimeoutImpl(int timeout);
	void setBlockingImpl();

	BPSRateImpl getBPSRateImpl() const;
	DataBitsImpl getDataBitsImpl() const;
	ParityImpl getParityImpl() const;
	char getParityCharImpl() const;
	StartBitsImpl getStartBitsImpl() const;
	StopBitsImpl getStopBitsImpl() const;
	FlowControlImpl getFlowControlImpl() const;
	bool getUseXonXoffImpl() const;
	unsigned char getXonCharImpl() const;
	unsigned char getXoffCharImpl() const;
	bool getUseEOFImpl() const;
	unsigned char getEOFCharImpl() const;
	int getBufferSizeImpl() const;
	int getTimeoutImpl() const;

private:
	SerialConfigImpl();

	termios& getTermios();

	termios		 _termios;
	int			 _bufferSize;
	FlowControlImpl _flowControl;

	friend class SerialChannelImpl;
};


//
// inlines
//


inline termios& SerialConfigImpl::getTermios()
{
	return _termios;
}


inline void SerialConfigImpl::setStartBitsImpl(SerialConfigImpl::StartBitsImpl startBits)
{
	throw Poco::InvalidAccessException("Operation not supported.");
}


inline void SerialConfigImpl::setEOFCharImpl(unsigned char eof)
{
	_termios.c_cc[VEOF] = eof;
}


inline void SerialConfigImpl::setBufferSizeImpl(int size)
{
	_termios.c_cc[VMIN] = size;
}


inline void SerialConfigImpl::setTimeoutImpl(int timeoutMS)
{
	_termios.c_cc[VTIME] = timeoutMS * 100; // convert from ms to 1/10 s
}


inline void SerialConfigImpl::setUseXonXoffImpl(unsigned char,
		unsigned char)
{
	setFlowControlImpl(FLOW_CTRL_SOFTWARE_IMPL, 0, 0);
}


inline void SerialConfigImpl::setUseEOFImpl(bool) const
{
	throw NotImplementedException();
}


inline SerialConfigImpl::BPSRateImpl SerialConfigImpl::getBPSRateImpl() const
{
	return (BPSRateImpl) cfgetospeed(&_termios);
}


inline SerialConfigImpl::StartBitsImpl SerialConfigImpl::getStartBitsImpl() const
{
	throw Poco::InvalidAccessException("Operation not supported.");
}


inline SerialConfigImpl::FlowControlImpl SerialConfigImpl::getFlowControlImpl() const
{
	return _flowControl;
}


inline bool SerialConfigImpl::getUseXonXoffImpl() const
{
	return FLOW_CTRL_SOFTWARE_IMPL == _flowControl;
}


inline unsigned char SerialConfigImpl::getXonCharImpl() const
{
	return _termios.c_cc[VSTART];
}


inline unsigned char SerialConfigImpl::getXoffCharImpl() const
{
	return _termios.c_cc[VSTOP];
}


inline bool SerialConfigImpl::getUseEOFImpl() const
{
	return 0 != _termios.c_cc[VEOF];
}


inline unsigned char SerialConfigImpl::getEOFCharImpl() const
{
	return _termios.c_cc[VEOF];
}


inline int SerialConfigImpl::getBufferSizeImpl() const
{
	return _termios.c_cc[VMIN];
}


inline int SerialConfigImpl::getTimeoutImpl() const
{
	return _termios.c_cc[VTIME] * 100; // convert from 1/10 s to ms
}


inline void SerialConfigImpl::setBlockingImpl()
{
	_termios.c_cc[VTIME] = 0;
}


} } } // namespace Poco::DeviceIO::Serial


#endif // Serial_SerialConfig_POSIX_INCLUDED
