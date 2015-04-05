#ifndef GLOBAL_H
#define GLOBAL_H

#include <QtGlobal>
#include <QDateTime>
#include <QDebug>

typedef qint32 uid_type;
typedef qint32 eid_type;

enum class MessCodes : qint32 {
   error_occured,
   user_data,
   friends_list,
   events_list,
   event_data,
   create_event
};

static MessCodes toMessCode(const QByteArray &a)
{
   bool ok;
   MessCodes r = (MessCodes)a.toInt(&ok);
   if (ok)
	return r;
   return MessCodes::error_occured;
}

#endif // GLOBAL_H

