#ifndef SERIALIZATIONEXCEPTION_H
#define SERIALIZATIONEXCEPTION_H

#include <QException>

class SerializationException : public QException
{
public:
	SerializationException(const char*);
	const char* what() const throw ();

private:
	const char* _errMsg;
};

#endif // SERIALIZATIONEXCEPTION_H
