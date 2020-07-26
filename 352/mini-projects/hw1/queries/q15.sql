select 
	ai.airport_desc
from 
	airport_ids ai,
	(
		select 
			incomingCount.aid, (outgoingCount.outCount + incomingCount.incCount) as traffic
		from
			(
				select 
					fr.origin_airport_id as aid, count(*) as outCount
				from 
					flight_reports fr 
				where 
					fr.is_cancelled = 0
				group by 
					fr.origin_airport_id) as outgoingCount,
			(
				select 
					fr.dest_airport_id as aid, count(*) as incCount
				from 
					flight_reports fr 
				where 
					fr.is_cancelled = 0
				group by 
					fr.dest_airport_id
			) as incomingCount
		where 
			outgoingCount.aid = incomingCount.aid
		order by 
			traffic desc limit 5
	) as res
where 
	res.aid = ai.airport_id
order by
	airport_desc asc