#ifndef EVENT_H
#define EVENT_H

#include "global.h"

class Event
{
public:
   explicit Event(eid_type id);
   virtual ~Event();
   eid_type id() const;
   QDateTime date() const;
   QList<uid_type> invited() const;
   QList<uid_type> attending() const;
   void setDescription(QString);
   void setTime(QDateTime);
   void invite(uid_type);
   void invite(QList<uid_type>);


private:
   const eid_type _id;
   QString _desc;
   QDateTime _date;
   QList<uid_type> *_invited;
   QList<uid_type> *_attending;
   /* Location */
   /* Comments */

};
/*
 *
 * -id:int
-description: string
-time: (time_type)
-place: Location
-invited: List<User>
-attending: List<User>
-comments: List<Comments>
 * /
#endif // EVENT_H
