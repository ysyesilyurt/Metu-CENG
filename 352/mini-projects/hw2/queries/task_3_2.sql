select
	a.name as author_name, cnts.numPubs as pub_count
from 
	author a, (
				select
					a.author_id, count(*) as numPubs
				from
					authored a, (
									select
										a2.pub_id
									from
										article a2
									where
										a2.journal like '%IEEE%'
								) as ieeePubs
				where
					a.pub_id = ieeePubs.pub_id
				group by
					a.author_id 
			  ) as cnts
where 
	a.author_id = cnts.author_id
order by
	cnts.numPubs desc, a.name asc 
limit
	50;