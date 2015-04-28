#ifndef GLOBAL_H
#define GLOBAL_H

#include <QtGlobal>
#include <QDateTime>
#include <QDebug>
#include <QDataStream>
#include <QTcpSocket>

typedef qint32 id_type;

enum class MessCodes : qint32 {
    ok,
    error_occured,
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
};


QDataStream& operator<<(QDataStream &out, const MessCodes &m);

QDataStream& operator>>(QDataStream &in, MessCodes &m);

MessCodes toMessCode(const QByteArray &a);

void accept(QTcpSocket *_socket, QDataStream &st);

#endif // GLOBAL_H

