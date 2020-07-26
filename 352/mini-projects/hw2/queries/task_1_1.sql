select 
	p.pub_type, count(p.pub_type) as total_pubs_of_type
from 
	Pub p
group by 
	p.pub_type
order by 
	total_pubs_of_type desc;