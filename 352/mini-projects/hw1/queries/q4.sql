select 
	ac.airline_name
from 
	airline_codes ac, (
		(
			(
				select 
					fr.airline_code
				from 
					flight_reports fr 
				where
						(fr.year = 2018 or fr.year = 2019) 
					and 
						fr.dest_city_name = 'Washington, DC'
					and
						fr.is_cancelled = 0
			)
					
			intersect 
			
			(
				select 
					fr.airline_code
				from 
					flight_reports fr 
				where
						(fr.year = 2018 or fr.year = 2019) 
					and 
						fr.dest_city_name = 'Boston, MA'
					and
						fr.is_cancelled = 0
			)
			
			intersect 
			
			(
				select 
					fr.airline_code
				from 
					flight_reports fr 
				where
						(fr.year = 2018 or fr.year = 2019) 
					and 
						fr.dest_city_name = 'Portland, ME'
					and
						fr.is_cancelled = 0
			)
			
			intersect 
			
			(
				select 
					fr.airline_code
				from 
					flight_reports fr 
				where
						(fr.year = 2018 or fr.year = 2019) 
					and 
						fr.dest_city_name = 'Philadelphia, PA'
					and
						fr.is_cancelled = 0
			)
			
			intersect 
			
			(
				select 
					fr.airline_code
				from 
					flight_reports fr 
				where
						(fr.year = 2018 or fr.year = 2019) 
					and 
						fr.dest_city_name = 'New York, NY'
					and
						fr.is_cancelled = 0
			)
		)
		
		except
		
		(
			(
				select 
					fr.airline_code
				from 
					flight_reports fr 
				where
						(fr.year = 2016 or fr.year = 2017) 
					and 
						fr.dest_city_name = 'Washington, DC'
					and
						fr.is_cancelled = 0
			)
					
			intersect 
			
			(
				select 
					fr.airline_code
				from 
					flight_reports fr 
				where
						(fr.year = 2016 or fr.year = 2017) 
					and 
						fr.dest_city_name = 'Boston, MA'
					and
						fr.is_cancelled = 0
			)
			
			intersect 
			
			(
				select 
					fr.airline_code
				from 
					flight_reports fr 
				where
						(fr.year = 2016 or fr.year = 2017) 
					and 
						fr.dest_city_name = 'Portland, ME'
					and
						fr.is_cancelled = 0
			)
			
			intersect 
			
			(
				select 
					fr.airline_code
				from 
					flight_reports fr 
				where
						(fr.year = 2016 or fr.year = 2017) 
					and 
						fr.dest_city_name = 'Philadelphia, PA'
					and
						fr.is_cancelled = 0
			)
			
			intersect 
			
			(
				select 
					fr.airline_code
				from 
					flight_reports fr 
				where
						(fr.year = 2016 or fr.year = 2017) 
					and 
						fr.dest_city_name = 'New York, NY'
					and
						fr.is_cancelled = 0
			)
		)
		
	) as res
where 
	ac.airline_code = res.airline_code 
order by 
	ac.airline_name asc	
