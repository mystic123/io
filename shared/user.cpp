#include "user.h"

User::User()
{
}

User::User(const id_type id, const QList<id_type> &l): _id(id), _friends(l)
{
}

//User::User(QDataStream &stream) throw(SerializationException&): _id(0)
//{
//	bool ok;
//	_id = arr.left(sizeof(id_type)).toInt(&ok);
//	if (!ok) {
//		throw SerializationException("wrong user id");
//	}
//	arr = arr.remove(0,sizeof(id_type));
//	while(arr.size() > 0) {
//		id_type friend_id = arr.left(sizeof(id_type)).toInt(&ok);
//		if (!ok) {
//			throw SerializationException("wrong friend id");
//		}
//		else {
//			_friends.push_back(friend_id);
//			arr = arr.remove(0,sizeof(id_type));
//		}
//	}
//}

User::~User()
{
}

//User::operator const QByteArray()
//{
//	QByteArray r = QByteArray::number((qint32)_id);
//	for (id_type x : _friends) {
//		r.append((qint32)x);
//	}
//	return r;
//}

QDataStream& operator<<(QDataStream &out, const User &u)
{
	out << u._id << u._friends;
	return out;
}

QDataStream& operator>>(QDataStream &in, User &u)
{
	u = User();
	in >> u._id >> u._friends;
	return in;
}
