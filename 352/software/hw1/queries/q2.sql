select 
	counts.airport_code, ac.airport_desc, counts.cancel_count
from 
	airport_codes ac, (
		select 
			fr.origin_airport_code as airport_code, count(*) as cancel_count
		from 
			flight_reports fr
		where 
			fr.cancellation_reason = (
										select
											cr.reason_code 
										from 
											cancellation_reasons cr
										where
											cr.reason_desc like '%Security%'
									 )
		group by 
			fr.origin_airport_code
	) as counts
where 
	counts.airport_code = ac.airport_code 
order by 
	counts.cancel_count desc, counts.airport_code asc
