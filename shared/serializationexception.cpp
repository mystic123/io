#include "serializationexception.h"

SerializationException::SerializationException() noexcept: exception(), _errMsg("empty")
{
}

SerializationException::SerializationException(const char* errMsg): exception(), _errMsg(errMsg)
{
}

SerializationException::SerializationException(const SerializationException &e) noexcept: _errMsg(e.what())
{

}

SerializationException::~SerializationException()
{
}

SerializationException& SerializationException::operator=(const SerializationException &e) noexcept
{
	_errMsg = e.what();
	return *this;
}

const char * SerializationException::what() const noexcept
{
	return _errMsg;
}

