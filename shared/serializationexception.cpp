#include "serializationexception.h"

SerializationException::SerializationException(const char* errMsg): _errMsg(errMsg)
{

}

const char *SerializationException::what() const
{
   return _errMsg;
}

