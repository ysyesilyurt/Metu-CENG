select
	fr2.plane_tail_number, avg(fr2.flight_distance / fr2.flight_time) as avg_speed
from
	flight_reports fr2 ,
	(
		(
			select
				fr.plane_tail_number
			from
				flight_reports fr 
			where
				 fr.year = 2016 
				 	and
				 fr.month = 1 
				 	and 
			 	 fr.is_cancelled = 0
		)
		
		except
		
		(
			select
				fr.plane_tail_number
			from
				flight_reports fr 
			where
				 fr.year = 2016 
				 	and
				 (fr.weekday_id != 6 and fr.weekday_id != 7)
				 	and
				 fr.month = 1 
			 		and
			 	fr.is_cancelled = 0
		)
	) as res
where
	fr2.plane_tail_number = res.plane_tail_number
		and
	fr2.year = 2016 
	 	and
	fr2.month = 1 
group by
	fr2.plane_tail_number
order by
	avg_speed desc
	