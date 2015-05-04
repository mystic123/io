#ifndef GLOBAL_H
#define GLOBAL_H

#include <QtGlobal>
#include <QDateTime>
#include <QDebug>
#include <QDataStream>

typedef qint64 id_type;

enum class MessCodes : qint32 {
	ok,
	error_occured,
	login,
   user_data,
   friends_list,
   events_list,
   event_data,
	create_event,
	update_event,
	invite_event,
	join_event,
	add_friend,
	del_friend,
	fetchFacebook
};

/* refreshing time when waiting for data */
const qint32 REFRESH_TIME = 30;

QDataStream& operator<<(QDataStream &out, const MessCodes &m);

QDataStream& operator>>(QDataStream &in, MessCodes &m);

#endif // GLOBAL_H

