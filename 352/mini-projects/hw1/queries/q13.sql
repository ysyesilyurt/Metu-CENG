select
	ac.airline_name, flightsOnMonday.hng1 as monday_flights, flightsOnSunday.hng2 as sunday_flights
from
	airline_codes ac,
	(	select
			fr.airline_code, count(*) hng1
		from
			flight_reports fr 
		where
			fr.weekday_id = 1
				and
			is_cancelled = 0
		group by
			fr.airline_code 
	) as flightsOnMonday,
	(
		select
			fr.airline_code, count(*) hng2
		from
			flight_reports fr 
		where
			fr.weekday_id = 7
				and
			is_cancelled = 0
		group by
			fr.airline_code 	
	) as flightsOnSunday
where
	ac.airline_code = flightsOnMonday.airline_code
		and
	flightsOnMonday.airline_code = flightsOnSunday.airline_code
order by
	airline_name asc
	
	