#include "global.h"

QDataStream& operator<<(QDataStream &out, const MessCodes &m)
{
	out << (qint32)m;
	return out;
}


QDataStream& operator>>(QDataStream &in, MessCodes &m)
{
	qint32 x;
	in >> x;
	m = (MessCodes)x;
	return in;
}

MessCodes toMessCode(const QByteArray &a)
{
   bool ok;
	qDebug() << "toMC:" << a;
   MessCodes r = (MessCodes)a.toInt(&ok);
	qDebug() << "ok:" << ok;
   if (ok)
		return r;
   return MessCodes::error_occured;
}