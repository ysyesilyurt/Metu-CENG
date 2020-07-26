select
	a.name as author_name, cnts.numPubs as pub_count
from 
	author a, (
				select
					a.author_id, count(*) as numPubs
				from
					authored a 
				group by
					a.author_id 
				having
					count(*) >= 150 and count(*) < 200
			  ) as cnts
where 
	a.author_id = cnts.author_id
order by
	cnts.numPubs asc, a.name asc;