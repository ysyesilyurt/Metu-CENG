-- This query uses a temporary table named "year_pubcounts". Its creation script and insertion scripts are given in task_3_temp.sql file.
select
	concat(cast(ypc1.year as varchar), '-' , cast(ypc10.year + 1 as varchar)) as decade,
	(ypc1.pubCount + ypc2.pubCount + ypc3.pubCount + ypc4.pubCount + ypc5.pubCount + ypc6.pubCount + ypc7.pubCount + ypc8.pubCount + ypc9.pubCount + ypc10.pubCount) as total
from
	year_pubcounts ypc1, year_pubcounts ypc2,
	year_pubcounts ypc3, year_pubcounts ypc4,
	year_pubcounts ypc5, year_pubcounts ypc6,
	year_pubcounts ypc7, year_pubcounts ypc8,
	year_pubcounts ypc9, year_pubcounts ypc10
where
	ypc2.year - ypc1.year = 1 and
	ypc3.year - ypc1.year = 2 and
	ypc4.year - ypc1.year = 3 and
	ypc5.year - ypc1.year = 4 and
	ypc6.year - ypc1.year = 5 and
	ypc7.year - ypc1.year = 6 and
	ypc8.year - ypc1.year = 7 and
	ypc9.year - ypc1.year = 8 and
	ypc10.year - ypc1.year = 9
order by 
	decade;