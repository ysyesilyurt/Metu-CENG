-- This query uses a temporary table named "author_counts_by_year". Its creation script and insertion script are given in task_3_temp.sql file.
select 
	yearMax.year, a.name, yearMax.maxPubInThatYear as count
from
	author a, author_counts_by_year acby, (
											select
												acby2.year, max(acby2.pubCount) maxPubInThatYear
											from 
												author_counts_by_year acby2
											group by
												acby2.year	
										  ) as yearMax
where
	a.author_id = acby.author_id and 
	acby.year = yearMax.year and 
	acby.pubCount = yearMax.maxPubInThatYear
order by
	yearMax.year asc, a.name asc;
									 
									 
									 
									 
									 
									 
									 
									 
									 
									 