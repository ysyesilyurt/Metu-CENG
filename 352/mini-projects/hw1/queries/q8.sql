select
	distinct fr.plane_tail_number, fr.airline_code as first_owner, fr2.airline_code as second_owner 
from
	(
		(
			select distinct 
				hng1.plane_tail_number, hng1.airline_code,
				hng1.year, hng1.month, hng1.day
			from
				flight_reports hng1
		) as fr
		
		inner join
		
		(
			select distinct
				hng2.plane_tail_number, hng2.airline_code, 
				hng2.year, hng2.month, hng2.day
			from
				flight_reports hng2
		) as fr2
		on fr.plane_tail_number = fr2.plane_tail_number 
	)
where
	fr.airline_code != fr2.airline_code 
		and
	(
		fr.year < fr2.year
			or
		(fr.year = fr2.year and fr.month < fr2.month)
			or
		(fr.year < fr2.year and fr.month = fr2.month and fr.day < fr2.day)	
	)
order by
	plane_tail_number asc, first_owner asc, second_owner asc