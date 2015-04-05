#include "user.h"

User::User(const uid_type id): _id(id), _friends()
{
}

User::User(QByteArray &arr) throw(SerializationException&): _id(0)
{
	bool ok;
	_id = arr.left(sizeof(uid_type)).toInt(&ok);
	if (!ok) {
		throw SerializationException("wrong user id");
	}
	arr = arr.remove(0,sizeof(uid_type));
	while(arr.size() > 0) {
		uid_type friend_id = arr.left(sizeof(uid_type)).toInt(&ok);
		if (!ok) {
			throw SerializationException("wrong friend id");
		}
		else {
			_friends.push_back(friend_id);
			arr = arr.remove(0,sizeof(uid_type));
		}
	}
}

User::~User()
{
}

User::operator const QByteArray()
{
	QByteArray r = QByteArray::number((qint32)_id);
	for (uid_type x : _friends) {
		r.append((qint32)x);
	}
	return r;
}

