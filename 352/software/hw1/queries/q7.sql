select 
	ac.airline_name, (allFromBostonCancelled.countCanc * 100.) / allFromBoston.countAll as percentage
from
	airline_codes ac,
	(
		select
			fr.airline_code, count(*) as countAll
		from
			flight_reports fr 
		where
			origin_city_name like 'Boston%'
		group by
			fr.airline_code 
	) as allFromBoston,
	(
		select
			fr.airline_code, count(*) as countCanc
		from
			flight_reports fr 
		where
			origin_city_name like 'Boston%'
				and
			is_cancelled = 1
		group by
			fr.airline_code 
	) as allFromBostonCancelled
where
	allFromBoston.airline_code = allFromBostonCancelled.airline_code
		and
	ac.airline_code = allFromBoston.airline_code
		and
	(allFromBostonCancelled.countCanc * 100.) / allFromBoston.countAll > 10
order by
	percentage desc
 	
