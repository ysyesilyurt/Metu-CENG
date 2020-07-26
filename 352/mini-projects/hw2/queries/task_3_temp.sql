----------------------------------------------- TASK_3_4 -----------------------------------------------
-- I have created below temporary table 'year_pubcounts' to be able to keep publication counts by years for task_3_4
-- in my query inside task_3_4.sql, I am using this temporary table to compute the decade counts through the years
create temporary table if not exists year_pubcounts(year int, pubCount int);

-- Below scripts are insertions that need to be done to year_pubcounts temporary table after the creation.
-- First (in direct below) insertion, inserts all data from year 1940 to 2020 accordingly.
insert into year_pubcounts(year, pubCount)
select
	p.year, count(*) as yearPubsCount
from
	publication p
where 
	p.year >= 1940
group by
	p.year;
	
-- The ones below are just padding insertions for handling the year gap between 2020 and 2030, 
-- i.e they just insert records such as 2021, 0 until 2030
insert into year_pubcounts(year, pubCount)
select
	max(ypc.year) + 1, 0
from
	year_pubcounts ypc;
	
insert into year_pubcounts(year, pubCount)
select
	max(ypc.year) + 1, 0
from
	year_pubcounts ypc;

insert into year_pubcounts(year, pubCount)
select
	max(ypc.year) + 1, 0
from
	year_pubcounts ypc;

insert into year_pubcounts(year, pubCount)
select
	max(ypc.year) + 1, 0
from
	year_pubcounts ypc;

insert into year_pubcounts(year, pubCount)
select
	max(ypc.year) + 1, 0
from
	year_pubcounts ypc;

insert into year_pubcounts(year, pubCount)
select
	max(ypc.year) + 1, 0
from
	year_pubcounts ypc;

insert into year_pubcounts(year, pubCount)
select
	max(ypc.year) + 1, 0
from
	year_pubcounts ypc;

insert into year_pubcounts(year, pubCount)
select
	max(ypc.year) + 1, 0
from
	year_pubcounts ypc;

insert into year_pubcounts(year, pubCount)
select
	max(ypc.year) + 1, 0
from
	year_pubcounts ypc;

----------------------------------------------- TASK_3_5 -----------------------------------------------
	
-- I have created below temporary table 'author_collaboratives' to be able to keep distinct 1-to-1 author collaborations in one place for task_3_5.
-- in my query inside task_3_5.sql, I am using this temporary table to group by its first author field and count their corresponding second author field 
-- (which basically gives me the distinct collab count) 
create temporary table if not exists author_collaboratives (author_id_1 int, author_id_2 int);

-- Below statements is the insertion script to author_collaboratives temporary table
insert into author_collaboratives(author_id_1, author_id_2)
select 
	distinct a1.author_id , a2.author_id 
from
	authored a1, authored a2 
where
	a1.author_id != a2.author_id and a1.pub_id = a2.pub_id;
	
----------------------------------------------- TASK_3_6 -----------------------------------------------
	
-- I have created below temporary table 'author_counts_by_year' to be able to keep publication counts of distinct authors by years for task_3_6.
-- in my query inside task_3_6.sql, I am using this temporary table to group by year and get the max pubCount in that year
create temporary table if not exists author_counts_by_year (author_id int, year int, pubCount int);

-- Below statements is the insertion script to author_counts_by_year temporary table
insert into author_counts_by_year(author_id, year, pubCount)
select
	a.author_id, p.year, count(*)
from
	authored a, publication p
where
	a.pub_id = p.pub_id and p.year >= 1940 and p.year <= 1990
group by 
	a.author_id, p.year;

	
	
