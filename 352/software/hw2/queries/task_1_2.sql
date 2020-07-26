select 
	fieldsInAllPubTypes.field_name
from
	(
		(
			select 
				f.field_name 
			from 
				field f
			where 
				f.pub_key in (
								 select 
								 	p.pub_key 
								 from 
								 	pub p 
								 where 
								 	p.pub_type = 'article'
			        		 )
		)
			
		intersect
		
		(
			select 
				f.field_name 
			from 
				field f
			where 
				f.pub_key in (
								 select 
								 	p.pub_key 
								 from 
								 	pub p 
								 where 
								 	p.pub_type = 'mastersthesis'
			        		 )
		) 
			
		intersect
		
		(
			select 
				f.field_name 
			from 
				field f
			where 
				f.pub_key in (
								 select 
								 	p.pub_key 
								 from 
								 	pub p 
								 where 
								 	p.pub_type = 'www'
			        		 )
		)
			
		intersect
		
		(
			select 
				f.field_name 
			from 
				field f
			where 
				f.pub_key in (
								 select 
								 	p.pub_key 
								 from 
								 	pub p 
								 where 
								 	p.pub_type = 'book'
			        		 )
		)
			
		intersect
		
		(
			select 
				f.field_name 
			from 
				field f
			where 
				f.pub_key in (
								 select 
								 	p.pub_key 
								 from 
								 	pub p 
								 where 
								 	p.pub_type = 'inproceedings'
			        		 )
		)
			
		intersect
		
		(
			select 
				f.field_name 
			from 
				field f
			where 
				f.pub_key in (
								 select 
								 	p.pub_key 
								 from 
								 	pub p 
								 where 
								 	p.pub_type = 'incollection'
			        		 )
		)
		
		intersect
		
		(
			select 
				f.field_name 
			from 
				field f
			where 
				f.pub_key in (
								 select 
								 	p.pub_key 
								 from 
								 	pub p 
								 where 
								 	p.pub_type = 'proceedings'
			 			     )
		)
	) as fieldsInAllPubTypes
order by
	fieldsInAllPubTypes.field_name;