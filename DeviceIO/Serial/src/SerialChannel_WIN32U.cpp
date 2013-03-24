//
// SerialChannel_WIN32.cpp
//
// $Id: //poco/Main/DeviceIO/Serial/src/SerialChannel_POSIX.cpp#1 $
//
// Library: Serial
// Package: Serial
// Module:  SerialChannel
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


#include "Poco/DeviceIO/Serial/SerialChannel_WIN32U.h"
#include "Poco/UnicodeConverter.h"
#include "Poco/Exception.h"
#include <windows.h>


namespace Poco {
namespace DeviceIO {
namespace Serial {


SerialChannelImpl::SerialChannelImpl(SerialConfigImpl* pConfig): 
	_pConfig(pConfig, true)
{
}


SerialChannelImpl::~SerialChannelImpl()
{
}


void SerialChannelImpl::initImpl()
{
	if (!SetCommState(_handle, &(_pConfig->dcb()))) handleError(_pConfig->name());

	if (!SetCommTimeouts(_handle, &(_pConfig->commTimeouts()))) handleError(_pConfig->name());

	DWORD bufSize = (DWORD) _pConfig->getBufferSizeImpl();
	SetupComm(_handle, bufSize, bufSize);
}


void SerialChannelImpl::openImpl()
{
	std::wstring uname;
	Poco::UnicodeConverter::toUTF16(_pConfig->name(), uname);
	_handle = CreateFileW(uname.c_str(), GENERIC_READ|GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
	if (INVALID_HANDLE_VALUE == _handle) handleError(_pConfig->name());

	initImpl();
}


void SerialChannelImpl::closeImpl()
{
	if (!CloseHandle(_handle)) handleError(_pConfig->name());
}


int SerialChannelImpl::readImpl(char* pBuffer, int length)
{
	DWORD read = 0;
	DWORD readCount = 0;
	ZeroMemory(pBuffer, length);
	do
	{
		if (!ReadFile(_handle, pBuffer + readCount, length - readCount, &read, NULL)) 
			handleError(_pConfig->name());
		else if (0 == read) break;

		poco_assert (read <= length - readCount);
		readCount += read;
	}while(readCount < length);

	return readCount;
}


int SerialChannelImpl::readImpl(char*& pBuffer)
{
	if (!_pConfig->getUseEOFImpl())
		throw InvalidAccessException();

	const char eofChar = _pConfig->getEOFCharImpl();
	int bufSize = _pConfig->getBufferSizeImpl();
	int it = 1;

	if ((0 == bufSize) || (0 != pBuffer))
		throw InvalidArgumentException();

	std::string buffer;
	DWORD read = 0;
	DWORD readCount = 0;

	pBuffer = static_cast<char*>(std::calloc(bufSize, sizeof(char)));//! freed in parent call

	do
	{
		if (_leftOver.size())
		{
			read = _leftOver.size() > bufSize - readCount ? bufSize - readCount : _leftOver.size();
			std::memcpy(pBuffer + readCount, _leftOver.data(), read);
			if (read == _leftOver.size())
				_leftOver.clear();
			else
				_leftOver.assign(_leftOver, read, _leftOver.size() - read);
		}
		else
		{
			if (!ReadFile(_handle, pBuffer + readCount, bufSize - readCount, &read, NULL)) 
				handleError(_pConfig->name());
			else if (0 == read) break;
		}

		poco_assert (read <= bufSize - readCount);
		
		buffer.assign(static_cast<char*>(pBuffer + readCount), read);
		size_t pos = buffer.find(_pConfig->getEOFCharImpl());
		if (pos != buffer.npos)
		{
			readCount += static_cast<DWORD>(pos);
			PurgeComm(_handle, PURGE_RXCLEAR);
			_leftOver.assign(buffer, pos + 1, buffer.size() - pos - 1);
			break;
		}

		readCount += read;
		if (readCount >= bufSize)
		{
			bufSize *= ++it;
			pBuffer = static_cast<char*>(std::realloc(pBuffer, bufSize * sizeof(char)));
		}
	}while(true);

	return readCount;
}


int SerialChannelImpl::writeImpl(const char* buffer, int length)
{
	DWORD written = 0;

	if (!WriteFile(_handle, buffer, length, &written, NULL) || 
		((written != length) && (0 != written)))
		handleError(_pConfig->name());
	else if (0 == written)
		throw IOException("Error writing to " + _pConfig->name());

	return written;
}


const std::string& SerialChannelImpl::getNameImpl() const
{
	return _pConfig->name();
}


std::string& SerialChannelImpl::getErrorText(DWORD errCode, std::string& buf)
{
	DWORD dwRet;
	LPWSTR pTemp = NULL;

	dwRet = FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ARGUMENT_ARRAY,
		NULL,
		errCode,
		LANG_USER_DEFAULT,
		(LPWSTR) &pTemp,
		0,
		NULL);

	if (dwRet && pTemp)
	{
		if ((std::wstring(pTemp).length()-2) >= 0)
		{
			pTemp[std::wstring(pTemp).length()-2] = TEXT('\0');  //remove cr and newline character
			Poco::UnicodeConverter::toUTF8(pTemp, buf);
		}

		LocalFree((HLOCAL) pTemp);
	}

	return buf;
}


void SerialChannelImpl::handleError(const std::string& name)
{
	std::string errorText;
	DWORD error = GetLastError();

	switch (error)
	{
	case ERROR_FILE_NOT_FOUND:
		throw FileNotFoundException(name, getErrorText(error, errorText));
	case ERROR_ACCESS_DENIED:
		throw FileAccessDeniedException(name, getErrorText(error, errorText));
	case ERROR_ALREADY_EXISTS:
	case ERROR_FILE_EXISTS:
		throw FileExistsException(name, getErrorText(error, errorText));
	case ERROR_FILE_READ_ONLY:
		throw FileReadOnlyException(name, getErrorText(error, errorText));
	case ERROR_CANNOT_MAKE:
	case ERROR_INVALID_NAME:
	case ERROR_FILENAME_EXCED_RANGE:
		throw CreateFileException(name, getErrorText(error, errorText));
	case ERROR_BROKEN_PIPE:
	case ERROR_INVALID_USER_BUFFER:
	case ERROR_INSUFFICIENT_BUFFER:
		throw IOException(name, getErrorText(error, errorText));
	case ERROR_NOT_ENOUGH_MEMORY:
		throw OutOfMemoryException(name, getErrorText(error, errorText));
	case ERROR_HANDLE_EOF: break;
	default:
		throw FileException(name, getErrorText(error, errorText));
	}
}


} } } // namespace Poco::DeviceIO::Serial
