#ifndef GLOBAL_H
#define GLOBAL_H

#include <QtGlobal>
#include <QtCore>
#include <QDateTime>
#include <QDebug>
#include <QDataStream>

typedef qint64 id_type;

enum class MessCodes : qint32 {
	ok,
	error,
	login,
	signup,
   user_data,
   friends_list,
   events_list,
   event_data,
	create_event,
	update_event,
	join_event,
	add_friend,
	del_friend,
	fb_friends_list,
	comment_data,
	add_comment,
	update_comment,
	del_comment,
	create_userDEBUG,
	del_user
};

/* refreshing time when waiting for data */
const qint32 REFRESH_TIME = 30;

QDataStream& operator<<(QDataStream &out, const MessCodes &m);

QDataStream& operator>>(QDataStream &in, MessCodes &m);

#endif // GLOBAL_H

