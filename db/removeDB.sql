ALTER TABLE Invited DROP CONSTRAINT FKInvited634451;
ALTER TABLE Invited DROP CONSTRAINT FKInvited563501;
ALTER TABLE Event DROP CONSTRAINT FKEvent342052;
ALTER TABLE Friends DROP CONSTRAINT FKFriends869808;
ALTER TABLE Friends DROP CONSTRAINT FKFriends354266;
ALTER TABLE Comment DROP CONSTRAINT FKComment63934;
DROP TABLE IF EXISTS Comment CASCADE;
DROP TABLE IF EXISTS Invited CASCADE;
DROP TABLE IF EXISTS Event CASCADE;
DROP TABLE IF EXISTS Friends CASCADE;
DROP TABLE IF EXISTS Users CASCADE;

