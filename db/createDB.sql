CREATE TABLE Comment (c_id  SERIAL NOT NULL, id_c_event int4 NOT NULL, author_id int8 NOT NULL, content varchar(255), c_date timestamp, PRIMARY KEY (c_id));
CREATE TABLE Invited (id_event int4 NOT NULL, id_i_user int8 NOT NULL, attended bool, PRIMARY KEY (id_event, id_i_user));
CREATE TABLE Event (e_id  SERIAL NOT NULL, descript varchar(255), id_founder int8 NOT NULL, title varchar(255), location varchar(255), start_date timestamp, how_long int4, PRIMARY KEY (e_id));
CREATE TABLE Friends (person_id int8 NOT NULL, friend_id int8 NOT NULL, PRIMARY KEY (person_id, friend_id));
CREATE TABLE Users (u_id  BIGSERIAL NOT NULL, email varchar(255), first_name varchar(255), last_name varchar(255), gender char(1), PRIMARY KEY (u_id));
ALTER TABLE Invited ADD CONSTRAINT FKInvited634451 FOREIGN KEY (id_event) REFERENCES Event (e_id) ON DELETE Cascade;
ALTER TABLE Invited ADD CONSTRAINT FKInvited563501 FOREIGN KEY (id_i_user) REFERENCES Users (u_id) ON DELETE Cascade;
ALTER TABLE Event ADD CONSTRAINT FKEvent342052 FOREIGN KEY (id_founder) REFERENCES Users (u_id) ON DELETE Cascade;
ALTER TABLE Friends ADD CONSTRAINT FKFriends869808 FOREIGN KEY (friend_id) REFERENCES Users (u_id) ON DELETE Cascade;
ALTER TABLE Friends ADD CONSTRAINT FKFriends354266 FOREIGN KEY (person_id) REFERENCES Users (u_id) ON DELETE Cascade;
ALTER TABLE Comment ADD CONSTRAINT FKComment63934 FOREIGN KEY (id_c_event) REFERENCES Event (e_id) ON DELETE Cascade;

