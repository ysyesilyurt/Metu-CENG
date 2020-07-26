-- Insertion to Author table
insert into author (name)
select 
	distinct f.field_value
from 
	field f
where
	f.field_name = 'author';

-- Insertion to Publication table
insert into publication (pub_key, title, year)
select 
	f1.pub_key, f1.field_value, CAST(f2.field_value AS int) 
from 
	field f1, field f2
where 
	f1.pub_key = f2.pub_key and f1.field_name = 'title' and f2.field_name = 'year';

-- Insertion to Article table
insert into article (pub_id, journal, month, volume, number)
select
	outerPubs.pub_id, resTableWithArticlePubs.journal, resTableWithArticlePubs.month, resTableWithArticlePubs.volume, resTableWithArticlePubs.number
from 
	publication outerPubs, (
		select 
			articlePubs.pub_key, resTable.journal, resTable.month, resTable.volume, resTable.number 
		from (
				select 
					p.pub_key
				from 
					pub p
				where 
					p.pub_type = 'article'
			 ) as articlePubs
			
			left join
			
			 (
				select 
					firstTwoFields.pub_key, firstTwoFields.journal, firstTwoFields.month, lastTwoFields.volume, lastTwoFields.number
				from (
						select 
							journalTable.pub_key, journalTable.journal, monthTable.month
						from (
								select 
									p.pub_key, f.field_value as journal 
								from
									publication p, field f
								where
									p.pub_key = f.pub_key and f.field_name = 'journal'
							 ) as journalTable 
							 
							 full outer join
							 
							 (
							 	select
							 		p.pub_key, f.field_value as month
								from
									publication p, field f
								where
									p.pub_key = f.pub_key and f.field_name = 'month'
							 ) as monthTable
							 
							 on journalTable.pub_key = monthTable.pub_key
								 
					 ) as firstTwoFields
						
					full outer join
					
					(
						select 
							volumeTable.pub_key, volumeTable.volume, numberTable.number
						from (
								select 
									p.pub_key, f.field_value as volume 
								from
									publication p, field f
								where
									p.pub_key = f.pub_key and f.field_name = 'volume'
							 ) as volumeTable 
							 
							 full outer join
							 
							 (
							 	select
							 		p.pub_key, f.field_value as number
								from
									publication p, field f
								where
									p.pub_key = f.pub_key and f.field_name = 'number'
							 ) as numberTable
							 
							 on volumeTable.pub_key = numberTable.pub_key
					 ) as lastTwoFields
					 
					 on firstTwoFields.pub_key = lastTwoFields.pub_key
			 ) as resTable
			
			 on articlePubs.pub_key = resTable.pub_key
	) as resTableWithArticlePubs
where
	outerPubs.pub_key = resTableWithArticlePubs.pub_key;
	
-- Insertion to Book table
insert into book (pub_id, publisher, isbn)
select 
	p.pub_id, bookPublisher.publisher, bookIsbn.isbn
from 
	publication p,
	(
		(
			select 
				p.pub_key, f.field_value as publisher
			from 
				pub p, field f
			where 
				p.pub_key = f.pub_key and p.pub_type = 'book' and f.field_name = 'publisher'
		) as bookPublisher
		
		full outer join
		
		(
			select 
				p.pub_key, max(f.field_value) as isbn
			from 
				pub p, field f
			where 
				p.pub_key = f.pub_key and p.pub_type = 'book' and f.field_name = 'isbn'
			group by 
				p.pub_key
		) as bookIsbn
		
	 	on bookPublisher.pub_key = bookIsbn.pub_key
	 )
where
	p.pub_key = bookPublisher.pub_key;
	
-- Insertion to Incollection table
insert into incollection (pub_id, book_title, publisher, isbn)
select 
	p.pub_id, resTable.book_title, resTable.publisher, resTable.isbn
from 
	publication p, 
	(
		select 
			titleAndIsbn.pub_key, titleAndIsbn.book_title, incPublisher.publisher, titleAndIsbn.isbn
		from
			(
				select 
					p.pub_key, f.field_value as publisher
				from 
					pub p, field f
				where 
					p.pub_key = f.pub_key and p.pub_type = 'incollection' and f.field_name = 'publisher'
			) as incPublisher
			
			full outer join
			
			(
				select 
					incBookTitle.pub_key, incBookTitle.book_title, incIsbn.isbn
				from (
						select 
							p.pub_key, f.field_value as book_title
						from 
							pub p, field f
						where 
							p.pub_key = f.pub_key and p.pub_type = 'incollection' and f.field_name = 'booktitle'
					) as incBookTitle
					
					full outer join
					
					(
						select 
							p.pub_key, max(f.field_value) as isbn
						from 
							pub p, field f
						where 
							p.pub_key = f.pub_key and p.pub_type = 'incollection' and f.field_name = 'isbn'
						group by 
							p.pub_key
					) as incIsbn
					
				 	on incBookTitle.pub_key = incIsbn.pub_key
			) as titleAndIsbn
			 
			 on incPublisher.pub_key = titleAndIsbn.pub_key
	) as resTable
where
	p.pub_key = resTable.pub_key;

-- Insertion to Inproceedings table
insert into inproceedings (pub_id, book_title, editor)
select 
	p.pub_id, resTable.book_title, resTable.editor
from 
	publication p,
	(
		select 
			inpBookTitle.pub_key, inpBookTitle.book_title, inpEditor.editor
		from (
				select 
					p.pub_key, f.field_value as book_title
				from 
					pub p, field f
				where 
					p.pub_key = f.pub_key and p.pub_type = 'inproceedings' and f.field_name = 'booktitle'
			 ) as inpBookTitle
			
			 full outer join
			
			 (
				select 
					p.pub_key, f.field_value as editor
				from 
					pub p, field f
				where 
					p.pub_key = f.pub_key and p.pub_type = 'inproceedings' and f.field_name = 'editor'
			 ) as inpEditor
			
		 	 on inpBookTitle.pub_key = inpEditor.pub_key
	) as resTable
where 
	p.pub_key = resTable.pub_key;

-- Insertion to Authored table
insert into authored (author_id, pub_id)
select
	distinct a.author_id, p2.pub_id
from
	pub p, field f, author a, publication p2 
where 
	f.field_name = 'author' and f.field_value = a.name and p2.pub_key = p.pub_key and p.pub_key = f.pub_key;
	