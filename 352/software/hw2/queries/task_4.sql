-- Create table for ActiveAuthors table 
create table if not exists ActiveAuthors(name text);

-- Insertion into ActiveAuthors table according to given conditions
insert into ActiveAuthors(name)
select
	distinct a.name
from 
	author a, authored aed, publication p
where
	a.author_id = aed.author_id and aed.author_id = p.pub_id and p.year in (2018, 2019, 2020);

-- Creation of insert_to_activeauthors function to ensure a new row inserted to ActiveAuthors when Authored_Insertion_To_ActiveAuthors trigger gets triggered
CREATE FUNCTION insert_to_activeauthors() 
	RETURNS trigger AS 
	$trigger_bound$
		begin
			if (
					(
					select
						p.year
					from
						publication p
					where
						p.pub_id = NEW.pub_id
					)
					in (2018, 2019, 2020) 
			   ) then
		    insert into ActiveAuthors(name)
			select
				a.name
			from 
				author a
			where
				a.author_id = new.author_id and a.name not in (
																select
																	name
																from 
																	activeauthors
															   );	
	    	END IF;
 		RETURN NEW;
		END;
	$trigger_bound$
LANGUAGE plpgsql;

-- Creation of Authored_Insertion_To_ActiveAuthors trigger
CREATE TRIGGER Authored_Insertion_To_ActiveAuthors
	AFTER INSERT ON authored
	FOR EACH ROW
    EXECUTE PROCEDURE insert_to_activeauthors();

	