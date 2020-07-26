select
	res.plane_tail_number, res.year, avg(res.numOFNonCancFlightsPerDay) as daily_avg
from
	(
		select
			fr.plane_tail_number, fr.year, count(*) numOFNonCancFlightsPerDay
		from
			flight_reports fr 
		where
			is_cancelled = 0
		group by 
			fr.plane_tail_number, fr.year, fr.month, fr.day
	) as res
group by
	res.plane_tail_number, res.year
having
	avg(res.numOFNonCancFlightsPerDay) > 5
order by
	plane_tail_number asc, year asc