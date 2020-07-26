select
	distinct ac.airline_name, fr2.year, numOfFlightsPerYear.hng2 as total_num_flights, numOfCancelledFlightsPerYear.hng3 as cancelled_flights
from
	flight_reports fr2, airline_codes ac, 
	(
		select
			res.airline_code
		from
			(
				select
					tempRes.airline_code, tempRes.year, avg(tempRes.numOfFlightsPerYear) as tempNums
				from
					(
						select
							fr.airline_code, fr.year, count(*) as numOfFlightsPerYear
						from
							flight_reports fr 
						group by
							fr.airline_code, fr.year, fr.month, fr.day
					) as tempRes
				group by 
					tempRes.airline_code, tempRes.year
				having 
					avg(tempRes.numOfFlightsPerYear) > 2000
			) as res
		group by
			res.airline_code
		having
			count(*) = 4
	) as popularAirlines,
	(
		select
			fr.year, fr.airline_code, count(*) as hng2
		from
			flight_reports fr 
		where
			fr.airline_code in (
								select
									res.airline_code
								from
									(
										select
											tempRes.airline_code, tempRes.year, avg(tempRes.numOfFlightsPerYear) as tempNums
										from
											(
												select
													fr.airline_code, fr.year, count(*) as numOfFlightsPerYear
												from
													flight_reports fr 
												group by
													fr.airline_code, fr.year, fr.month, fr.day
											) as tempRes
										group by 
											tempRes.airline_code, tempRes.year
										having 
											avg(tempRes.numOfFlightsPerYear) > 2000
									) as res
								group by
									res.airline_code
								having
									count(*) = 4
								)
		group by
			fr.year, fr.airline_code 
	) as numOfFlightsPerYear,
	(
		select
			fr.year, fr.airline_code, count(*) as hng3
		from
			flight_reports fr 
		where
			fr.is_cancelled = 1
				and
			fr.airline_code in (
								select
									res.airline_code
								from
									(
										select
											tempRes.airline_code, tempRes.year, avg(tempRes.numOfFlightsPerYear) as tempNums
										from
											(
												select
													fr.airline_code, fr.year, count(*) as numOfFlightsPerYear
												from
													flight_reports fr 
												group by
													fr.airline_code, fr.year, fr.month, fr.day
											) as tempRes
										group by 
											tempRes.airline_code, tempRes.year
										having 
											avg(tempRes.numOfFlightsPerYear) > 2000
									) as res
								group by
									res.airline_code
								having
									count(*) = 4
								)				
		group by
			fr.year, fr.airline_code 
	) as numOfCancelledFlightsPerYear
where
	fr2.airline_code = popularAirlines.airline_code
		and
	fr2.airline_code = numOfFlightsPerYear.airline_code
		and
	fr2.airline_code = numOfCancelledFlightsPerYear.airline_code
		and
	fr2.airline_code = ac.airline_code
		and
	fr2.year = numOfFlightsPerYear.year
		and
	fr2.year = numOfCancelledFlightsPerYear.year
order by
	airline_name asc, year asc
	
	