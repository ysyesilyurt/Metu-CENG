select 
	res.weekday_id, w.weekday_name, res.avgs as avg_delay
from weekdays w, (
		select 
			fr.weekday_id, avg(fr.departure_delay + fr.arrival_delay) as avgs
		from 
			flight_reports fr
		where 
			fr.origin_city_name like 'San Francisco%' and fr.dest_city_name like 'Boston%'
		group by 
			fr.weekday_id
		order by 
			avgs asc limit 1
	) as res
where 
	res.weekday_id = w.weekday_id 