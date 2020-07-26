-- This query uses a temporary table named "author_collaboratives". Its creation script and insertion script are given in task_3_temp.sql file.
select
	a.name, resTable.numOfCollabs as collab_count
from
	author a, (		
				select
					author_id_1, count(*) numOfCollabs
				from
					author_collaboratives
				group by
					author_id_1
			  ) as resTable
where
	a.author_id = resTable.author_id_1
order by
	collab_count desc, a.name asc
limit
	1000;