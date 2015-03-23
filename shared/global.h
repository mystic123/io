#ifndef GLOBAL_H
#define GLOBAL_H

#include <QtGlobal>
#include <QDateTime>
#include <QDebug>

typedef qint32 uid_type;
typedef qint32 eid_type;

enum class MessCodes : qint32 {
   user_data,
   friends_list,
   events_list,
   event_data,
   create_event
};

#endif // GLOBAL_H

