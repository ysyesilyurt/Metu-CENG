select
	ac.airline_name, countRes.flight_count
from
	airline_codes ac, (
		select
			res.airline_code, count(*) as flight_count
		from 
			flight_reports fr2,
				( -- planes that only goes to texas area
					( -- all planes
						select
							fr.plane_tail_number, fr.airline_code 
						from
							flight_reports fr 
						where
							fr.dest_wac_id = (  
												select 
													wac.wac_id 
												from
													world_area_codes wac
												where
													wac.wac_name = 'Texas'
											  )
					)
							
					except
					
					( -- all planes that goes anywhere but texas
						select
							fr.plane_tail_number, fr.airline_code 
						from
							flight_reports fr 
						where
							fr.dest_wac_id != (  
												select 
													wac.wac_id 
												from
													world_area_codes wac
												where
													wac.wac_name = 'Texas'
											  )
					)
				) as res
		where
			fr2.plane_tail_number = res.plane_tail_number
		group by
			res.airline_code
	) as countRes
where 
	ac.airline_code = countRes.airline_code
order by
	airline_name asc