select 
	ac.airline_name, avgs.airline_code, avgs.avg_delay
from 
	airline_codes ac, (
		select 
			fr.airline_code, avg(fr.departure_delay) as avg_delay
		from 
			flight_reports fr
		where 
			fr.year = '2018' and fr.is_cancelled = 0
		group by 
			fr.airline_code
	) as avgs
where 
	avgs.airline_code = ac.airline_code
order by 
	avgs.avg_delay asc, ac.airline_name asc