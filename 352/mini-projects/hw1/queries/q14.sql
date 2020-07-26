select
	res.year, w2.weekday_name, cr.reason_desc as reason, res.frequency as number_of_cancellations
from
	weekdays w2, cancellation_reasons cr, (
		select
			fr.year, fr.weekday_id, fr.cancellation_reason, count(*) as frequency
		from
			flight_reports fr 
		where
			is_cancelled = 1
		group by
			fr.year, fr.weekday_id, fr.cancellation_reason
	) as res
where
	w2.weekday_id = res.weekday_id
		and
	cr.reason_code = res.cancellation_reason
		and
	res.frequency = (
					select
						max(tempFreq.frequency)
					from
						(
							select
								fr.year, fr.weekday_id, fr.cancellation_reason, count(*) as frequency
							from
								flight_reports fr 
							where
								is_cancelled = 1
							group by
								fr.year, fr.weekday_id, fr.cancellation_reason
						) as tempFreq
					where
						tempFreq.year = res.year 
							and 
						tempFreq.weekday_id = res.weekday_id 
					group by
						tempFreq.year, tempFreq.weekday_id
					)
order by
	year asc, case 
				  when weekday_name = 'Monday' then 1
	              when weekday_name = 'Tuesday' then 2
	              when weekday_name = 'Wednesday' then 3
	              when weekday_name = 'Thursday' then 4
  	              when weekday_name = 'Friday' then 5
  	              when weekday_name = 'Saturday' then 6
	              else 7
	         end asc
	

