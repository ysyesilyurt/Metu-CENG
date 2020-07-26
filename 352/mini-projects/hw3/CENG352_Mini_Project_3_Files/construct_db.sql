create table if not exists Customer (customer_id serial primary key, email text, password text, first_name text, last_name text, session_count int, plan_id int);
create table if not exists Plan (plan_id serial primary key, plan_name text, resolution text, max_parallel_sessions int, monthly_fee int);


create table if not exists Actors (actor_id text, actor_name text, birth_year int, death_year int, gender text);
create table if not exists Directors (director_id text, director_name text);
create table if not exists Directed (movie_id text, director_id text);
create table if not exists Genres (movie_id text, genre_name text);
create table if not exists Casts (movie_id text, actor_id text, "characters" text);
create table if not exists Movies (movie_id text, title text, movie_year int, rating decimal, votes int);
create table if not exists Watched (customer_id integer, movie_id text);


alter table customer add constraint customer_email_uniquekey unique (email);
alter table actors add primary key (actor_id);
alter table directors add primary key (director_id);
alter table movies add primary key (movie_id);



/* these inserted values are for testing purposes, you can play with the database as much as you want. */ 
insert into Plan(plan_name, resolution, max_parallel_sessions, monthly_fee) 
values 
	('Basic', '720P', 2, 30),
	('Advanced', '1080P', 4, 50),
	('Premium', '4K', 10, 90);
	

insert into Customer(email, password, first_name, last_name, session_count, plan_id) 
values 
	('cj@mp3.com','pass123','Carl','Johnson', 0, 1),
	('ryder@mp3.com','pass123','Lance','Wilson', 0, 2),
	('bigsmoke@mp3.com','pass123','Melvin','Harris', 0, 3);
