#ifndef SERIALIZATIONEXCEPTION_H
#define SERIALIZATIONEXCEPTION_H

#include "global.h"
#include <exception>

class SerializationException : public std::exception
{
public:
	SerializationException() noexcept;
	SerializationException(const char*);
	SerializationException(const SerializationException&) noexcept;
	virtual ~SerializationException();
	SerializationException& operator= (const SerializationException&) noexcept;

	virtual const char* what() const noexcept;

private:
	const char *_errMsg;
};

#endif // SERIALIZATIONEXCEPTION_H
