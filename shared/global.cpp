#include "global.h"

QDataStream& operator<<(QDataStream &out, const MessCodes &m)
{
	out << (qint32)m;
	return out;
}


QDataStream& operator>>(QDataStream &in, MessCodes &m)
{
	in >> m;
	return in;
}

static MessCodes toMessCode(const QByteArray &a)
{
   bool ok;
   MessCodes r = (MessCodes)a.toInt(&ok);
   if (ok)
		return r;
   return MessCodes::error_occured;
}