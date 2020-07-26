select
	toAll.year, toAll.airline_code, toBoston.toBostonCount as boston_flight_count,
	(toBoston.toBostonCount * 100.) / toAll.toAllCount as boston_flight_percentage
from
	(
		select
			fr.year, fr.airline_code, count(*) as toBostonCount
		from
			flight_reports fr 
		where
			dest_city_name like 'Boston%'
				and
			is_cancelled = 0
		group by
			fr.year, fr.airline_code 
	) as toBoston,
	(		
		select
			fr.year, fr.airline_code, count(*) as toAllCount
		from
			flight_reports fr 
		where
			is_cancelled = 0
		group by
			fr.year, fr.airline_code 
	) as toAll
where 
	toBoston.year = toAll.year
		and
	toBoston.airline_code = toAll.airline_code
		and 
	(toBoston.toBostonCount * 100.) / toAll.toAllCount > 1
order by
	year asc, airline_code asc