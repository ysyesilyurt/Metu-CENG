select
	a.name as author_name, cnts.numPubs as pub_count
from 
	author a, (
				select
					a.author_id, count(*) as numPubs
				from
					authored a, (
									select
										a2.pub_id
									from
										article a2
									where
										a2.journal = 'IEEE Trans. Wireless Communications'
								) as ieeePubs
				where
					a.pub_id = ieeePubs.pub_id and a.author_id not in (
																		select
																			notWantedAuthors.author_id
																		from
																			authored notWantedAuthors, (
																											select
																												tempArticle.pub_id
																											from
																												article tempArticle
																											where
																												tempArticle.journal = 'IEEE Wireless Commun. Letters'
																										) as notWantedIeeePubs
																		where
																			notWantedAuthors.pub_id = notWantedIeeePubs.pub_id
																	  )
				group by
					a.author_id
				having
					count(*) >= 10
			  ) as cnts
where 
	a.author_id = cnts.author_id
order by
	cnts.numPubs desc, a.name asc;