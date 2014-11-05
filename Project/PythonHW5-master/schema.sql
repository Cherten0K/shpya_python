pragma foreign_keys=on;

drop table if exists entries;
drop table if exists users;

create table users (
    login text primary key not null,
    password text not null
);

create table entries (
  id integer primary key autoincrement,
  user integer references users(login),
  title text not null,
  comment text,
  start_date datetime,
  end_date datetime
);
