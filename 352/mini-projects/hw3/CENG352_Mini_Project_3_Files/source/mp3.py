import psycopg2

from config import read_config
from customer import Customer
from messages import *

POSTGRESQL_CONFIG_FILE_NAME = "database.cfg"

"""
    Connects to PostgreSQL database and returns connection object.
"""


def connect_to_db():
    db_conn_params = read_config(filename=POSTGRESQL_CONFIG_FILE_NAME, section="postgresql")
    conn = psycopg2.connect(**db_conn_params)
    conn.autocommit = False
    return conn


"""
    Splits given command string by spaces and trims each token.
    Returns token list.
"""


def tokenize_command(command):
    tokens = command.split(" ")
    return [t.strip() for t in tokens]


"""
    Prints list of available commands of the software.
"""


def help():
    # prints the choices for commands and parameters
    print("\n*** Please enter one of the following commands ***")
    print("> help")
    print("> sign_up <email> <password> <first_name> <last_name> <plan_id>")
    print("> sign_in <email> <password>")
    print("> sign_out")
    print("> show_plans")
    print("> show_subscription")
    print("> subscribe <plan_id>")
    print("> watched_movies <movie_id_1> <movie_id_2> <movie_id_3> ... <movie_id_n>")
    print("> search_for_movies <keyword_1> <keyword_2> <keyword_3> ... <keyword_n>")
    print("> suggest_movies")
    print("> quit")


def sign_up(conn, email, password, first_name, last_name, plan_id):
    """
        Saves customer with given details.
        - Return type is a tuple, 1st element is a boolean and 2nd element is the response message from messages.py.
        - If the operation is successful, commit changes and return tuple (True, CMD_EXECUTION_SUCCESS).
        - If any exception occurs; rollback, do nothing on the database and return tuple (False, CMD_EXECUTION_FAILED).
    """
    try:
        cursor = conn.cursor()
        cursor.execute("SELECT email FROM customer WHERE email = %s;", (email,))
        if cursor.fetchone() is not None:
            # Fail if customer already exists in the db (somehow)
            return False, CMD_EXECUTION_FAILED
        cursor.execute("""
                    INSERT INTO customer (email, password, first_name, last_name, session_count, plan_id)
                    VALUES (%s, %s, %s, %s, %s, %s);
                    """,
                       (email, password, first_name, last_name, 0, plan_id))
        conn.commit()
        cursor.close()
        return True, CMD_EXECUTION_SUCCESS
    except Exception as e:
        return False, CMD_EXECUTION_FAILED


def sign_in(conn, email, password):
    """
        Retrieves customer information if email and password is correct and customer's session_count < max_parallel_sessions.
        - Return type is a tuple, 1st element is a customer object and 2nd element is the response message from messages.py.
        - If email or password is wrong, return tuple (None, USER_SIGNIN_FAILED).
        - If session_count < max_parallel_sessions, commit changes (increment session_count) and return tuple (customer, CMD_EXECUTION_SUCCESS).
        - If session_count >= max_parallel_sessions, return tuple (None, USER_ALL_SESSIONS_ARE_USED).
        - If any exception occurs; rollback, do nothing on the database and return tuple (None, USER_SIGNIN_FAILED).
    """
    try:
        cursor = conn.cursor()
        cursor.execute("SELECT customer_id, email, first_name, last_name, session_count, plan_id "
                       "FROM customer "
                       "WHERE email = %s AND password = %s;",
                       (email, password))
        queryCustomer = cursor.fetchone()
        if queryCustomer is None:
            return None, USER_SIGNIN_FAILED

        cursor.execute("SELECT max_parallel_sessions "
                       "FROM plan "
                       "WHERE plan_id = %s;",
                       (queryCustomer[5],))
        queryCustomerPlan = cursor.fetchone()

        if queryCustomer[4] >= queryCustomerPlan[0]:
            return None, USER_ALL_SESSIONS_ARE_USED
        else:
            cursor.execute("""
                        UPDATE customer
                        SET session_count = session_count + 1
                        WHERE email = %s;
                        """,
                           (email,))
            conn.commit()
            cursor.close()
            return Customer(queryCustomer[0], queryCustomer[1], queryCustomer[2], queryCustomer[3],
                            queryCustomer[4], queryCustomer[5]), CMD_EXECUTION_SUCCESS
    except Exception as e:
        return None, USER_SIGNIN_FAILED


def sign_out(conn, customer):
    """
        Signs out from given customer's account.
        - Return type is a tuple, 1st element is a boolean and 2nd element is the response message from messages.py.
        - Decrement session_count of the customer in the database.
        - If the operation is successful, commit changes and return tuple (True, CMD_EXECUTION_SUCCESS).
        - If any exception occurs; rollback, do nothing on the database and return tuple (False, CMD_EXECUTION_FAILED).
    """
    try:
        cursor = conn.cursor()
        cursor.execute("SELECT customer_id "
                       "FROM customer "
                       "WHERE customer_id = %s;",
                       (customer.customer_id,))
        queryCustomer = cursor.fetchone()
        if queryCustomer is None or queryCustomer[0] == 0:
            # Fail if such a customer dne or his/her session count is 0 somehow
            return False, CMD_EXECUTION_FAILED

        cursor.execute("""
                    UPDATE customer
                    SET session_count = session_count - 1
                    WHERE customer_id = %s;
                    """,
                       (customer.customer_id,))
        conn.commit()
        cursor.close()
        return True, CMD_EXECUTION_SUCCESS
    except Exception as e:
        return False, CMD_EXECUTION_FAILED


def quit(conn, customer):
    """
        Quits from program.
        - Return type is a tuple, 1st element is a boolean and 2nd element is the response message from messages.py.
        - Remember to sign authenticated user out first.
        - If the operation is successful, commit changes and return tuple (True, CMD_EXECUTION_SUCCESS).
        - If any exception occurs; rollback, do nothing on the database and return tuple (False, CMD_EXECUTION_FAILED).
    """
    if customer is not None:
        res, msg = sign_out(conn, customer)
        if res:
            return True, CMD_EXECUTION_SUCCESS
        else:
            return False, CMD_EXECUTION_FAILED
    return True, CMD_EXECUTION_SUCCESS


def show_plans(conn):
    """
        Retrieves all available plans and prints them.
        - Return type is a tuple, 1st element is a boolean and 2nd element is the response message from messages.py.
        - If the operation is successful; print available plans and return tuple (True, CMD_EXECUTION_SUCCESS).
        - If any exception occurs; return tuple (False, CMD_EXECUTION_FAILED).

        Output should be like:
        #|Name|Resolution|Max Sessions|Monthly Fee
        1|Basic|720P|2|30
        2|Advanced|1080P|4|50
        3|Premium|4K|10|90
    """
    try:
        cursor = conn.cursor()
        cursor.execute("SELECT plan_id, plan_name, resolution, max_parallel_sessions, monthly_fee FROM plan;")
        queryPlans = cursor.fetchall()
        if queryPlans is None:
            # Fail if no plan exists (somehow)
            return False, CMD_EXECUTION_FAILED
        print("#|Name|Resolution|Max Sessions|Monthly Fee")
        for row in queryPlans:
            print("{0}|{1}|{2}|{3}|{4}".format(row[0], row[1], row[2], row[3], row[4]))
        cursor.close()
        return True, CMD_EXECUTION_SUCCESS
    except Exception as e:
        return False, CMD_EXECUTION_FAILED


def show_subscription(conn, customer):
    """
        Retrieves authenticated user's plan and prints it.
        - Return type is a tuple, 1st element is a boolean and 2nd element is the response message from messages.py.
        - If the operation is successful; print the authenticated customer's plan and return tuple (True, CMD_EXECUTION_SUCCESS).
        - If any exception occurs; return tuple (False, CMD_EXECUTION_FAILED).

        Output should be like:
        #|Name|Resolution|Max Sessions|Monthly Fee
        1|Basic|720P|2|30
    """
    try:
        cursor = conn.cursor()
        cursor.execute("SELECT plan_id "
                       "FROM customer "
                       "WHERE customer_id = %s",
                       (customer.customer_id,))
        queryCustomerPlanId = cursor.fetchall()
        if queryCustomerPlanId is None:
            # Fail if no such customer exists (somehow)
            return False, CMD_EXECUTION_FAILED
        else:
            cursor.execute("SELECT plan_id, plan_name, resolution, max_parallel_sessions, monthly_fee "
                           "FROM plan "
                           "WHERE plan_id = %s",
                           (queryCustomerPlanId[0],))
            queryPlan = cursor.fetchone()
            if queryPlan is None:
                # Fail if no such plan exists
                return False, CMD_EXECUTION_FAILED
            print("#|Name|Resolution|Max Sessions|Monthly Fee")
            print("{0}|{1}|{2}|{3}|{4}".format(queryPlan[0], queryPlan[1], queryPlan[2], queryPlan[3], queryPlan[4]))
            cursor.close()
            return True, CMD_EXECUTION_SUCCESS
    except Exception as e:
        return False, CMD_EXECUTION_FAILED


def watched_movies(conn, customer, movie_ids):
    """
        Insert customer-movie relationships to Watched table if not exists in Watched table.
        - Return type is a tuple, 1st element is a boolean and 2nd element is the response message from messages.py.
        - If a customer-movie relationship already exists, do nothing on the database and return (True, CMD_EXECUTION_SUCCESS).
        - If the operation is successful, commit changes and return tuple (True, CMD_EXECUTION_SUCCESS).
        - If any one of the movie ids is incorrect; rollback, do nothing on the database and return tuple (False, CMD_EXECUTION_FAILED).
        - If any exception occurs; rollback, do nothing on the database and return tuple (False, CMD_EXECUTION_FAILED).
    """
    try:
        customerWatchedMovies = set()
        cursor = conn.cursor()
        cursor.execute("SELECT movie_id "
                       "FROM watched "
                       "WHERE customer_id = %s",
                       (customer.customer_id,))
        queryCustomerWatchedMovies = cursor.fetchall()
        for row in queryCustomerWatchedMovies:
            customerWatchedMovies.add(row[0])

        for movie_id in movie_ids:
            if movie_id not in customerWatchedMovies:
                cursor.execute("SELECT movie_id "
                               "FROM movies "
                               "WHERE movie_id = %s",
                               (movie_id,))
                queryMovie = cursor.fetchone()
                if queryMovie is None:
                    # Fail if no such movie exists
                    return False, CMD_EXECUTION_FAILED
                else:
                    cursor.execute("""
                                INSERT INTO watched (customer_id, movie_id)
                                VALUES (%s, %s);
                                """,
                                   (customer.customer_id, movie_id))
        conn.commit()
        cursor.close()
        return True, CMD_EXECUTION_SUCCESS
    except Exception as e:
        return False, CMD_EXECUTION_FAILED


def subscribe(conn, customer, plan_id):
    """
        Subscribe authenticated customer to new plan.
        - Return type is a tuple, 1st element is a customer object and 2nd element is the response message from messages.py.
        - If target plan does not exist on the database, return tuple (None, SUBSCRIBE_PLAN_NOT_FOUND).
        - If the new plan's max_parallel_sessions < current plan's max_parallel_sessions, return tuple (None, SUBSCRIBE_MAX_PARALLEL_SESSIONS_UNAVAILABLE).
        - If the operation is successful, commit changes and return tuple (customer, CMD_EXECUTION_SUCCESS).
        - If any exception occurs; rollback, do nothing on the database and return tuple (None, CMD_EXECUTION_FAILED).
    """
    try:
        cursor = conn.cursor()
        cursor.execute("SELECT customer_id "
                       "FROM customer "
                       "WHERE customer_id = %s",
                       (customer.customer_id,))
        queryCustomer = cursor.fetchone()
        if queryCustomer is None:
            # Fail if no such customer exists (somehow)
            return None, CMD_EXECUTION_FAILED
        else:
            cursor.execute("SELECT max_parallel_sessions "
                           "FROM plan "
                           "WHERE plan_id = %s",
                           (plan_id,))
            queryNewPlanMaxSessions = cursor.fetchone()
            if queryNewPlanMaxSessions is None:
                # Fail if no such plan exists
                return None, SUBSCRIBE_PLAN_NOT_FOUND
            else:
                cursor.execute("SELECT max_parallel_sessions "
                               "FROM plan "
                               "WHERE plan_id = %s",
                               (customer.plan_id,))
                queryOldPlanMaxSessions = cursor.fetchone()
                if queryOldPlanMaxSessions is None:
                    # Fail if no such plan of customer exists (somehow)
                    return None, CMD_EXECUTION_FAILED
                else:
                    if queryNewPlanMaxSessions[0] < queryOldPlanMaxSessions[0]:
                        return None, SUBSCRIBE_MAX_PARALLEL_SESSIONS_UNAVAILABLE
                    else:
                        cursor.execute("""
                                    UPDATE customer
                                    SET plan_id = %s
                                    WHERE customer_id = %s;
                                    """,
                                       (plan_id, customer.customer_id))
                        conn.commit()
                        cursor.close()
                        customer.plan_id = plan_id
                        return customer, CMD_EXECUTION_SUCCESS
    except Exception as e:
        return False, CMD_EXECUTION_FAILED


def search_for_movies(conn, customer, search_text):
    """
        Searches for movies with given search_text.
        - Return type is a tuple, 1st element is a boolean and 2nd element is the response message from messages.py.
        - Print all movies whose titles contain given search_text IN CASE-INSENSITIVE MANNER.
        - If the operation is successful; print movies found and return tuple (True, CMD_EXECUTION_SUCCESS).
        - If any exception occurs; return tuple (False, CMD_EXECUTION_FAILED).

        Output should be like:
        Id|Title|Year|Rating|Votes|Watched
        "tt0147505"|"Sinbad: The Battle of the Dark Knights"|1998|2.2|149|0
        "tt0468569"|"The Dark Knight"|2008|9.0|2021237|1
        "tt1345836"|"The Dark Knight Rises"|2012|8.4|1362116|0
        "tt3153806"|"Masterpiece: Frank Millers The Dark Knight Returns"|2013|7.8|28|0
        "tt4430982"|"Batman: The Dark Knight Beyond"|0|0.0|0|0
        "tt4494606"|"The Dark Knight: Not So Serious"|2009|0.0|0|0
        "tt4498364"|"The Dark Knight: Knightfall - Part One"|2014|0.0|0|0
        "tt4504426"|"The Dark Knight: Knightfall - Part Two"|2014|0.0|0|0
        "tt4504908"|"The Dark Knight: Knightfall - Part Three"|2014|0.0|0|0
        "tt4653714"|"The Dark Knight Falls"|2015|5.4|8|0
        "tt6274696"|"The Dark Knight Returns: An Epic Fan Film"|2016|6.7|38|0
    """
    try:
        cursor = conn.cursor()
        formatted_search_text = search_text.replace('=', '==').replace('%', '=%').replace('_', '=_')
        queryToExecute = "SELECT movie_id, title, movie_year, rating, votes " \
                         "FROM movies " \
                         "WHERE LOWER(title) LIKE LOWER(%(like)s) ESCAPE '=' " \
                         "ORDER BY movie_id;"
        cursor.execute(queryToExecute, dict(like='%' + formatted_search_text + '%'))
        queryMovies = cursor.fetchall()
        print("Id|Title|Year|Rating|Votes|Watched")
        for row in queryMovies:
            cursor.execute("SELECT * "
                           "FROM watched "
                           "WHERE customer_id = %s AND movie_id = %s",
                           (customer.customer_id, row[0]))
            queryCustomerWatchedMovie = cursor.fetchone()
            if queryCustomerWatchedMovie is None:
                print("{0}|{1}|{2}|{3:.1f}|{4}|{5}".format(row[0], row[1], row[2], row[3], row[4], '0'))
            else:
                print("{0}|{1}|{2}|{3:.1f}|{4}|{5}".format(row[0], row[1], row[2], row[3], row[4], '1'))
        cursor.close()
        return True, CMD_EXECUTION_SUCCESS
    except Exception as e:
        print(e)
        return False, CMD_EXECUTION_FAILED

# sign_in cj@mp3.com pass123
# search_for_movies the dark knight
# watched_movies tt0468569 tt0120737 tt0111161 tt0480249


def suggest_movies(conn, customer):
    """
        Suggests combination of these movies:
            1- Find customer's genres. For each genre, find movies with most number of votes among the movies that the customer didn't watch.

            2- Find top 10 movies with most number of votes and highest rating, such that these movies are released
               after 2010 ( [2010, today) ) and the customer didn't watch these movies.
               (descending order for votes, descending order for rating)

            3- Find top 10 movies with votes higher than the average number of votes of movies that the customer watched.
               Disregard the movies that the customer didn't watch.
               (descending order for votes)

        - Return type is a tuple, 1st element is a boolean and 2nd element is the response message from messages.py.
        - Output format and return format are same with search_for_movies.
        - Order these movies by their movie id, in ascending order at the end.
        - If the operation is successful; print movies suggested and return tuple (True, CMD_EXECUTION_SUCCESS).
        - If any exception occurs; return tuple (False, CMD_EXECUTION_FAILED).
    """
    cursor = conn.cursor()
    try:
        cursor.execute("""
                        -- step1
                        (
                            select distinct
                                mov.movie_id, mov.title, mov.movie_year, mov.rating, mov.votes
                            from 
                                movies mov,
                                    (
                                        select 
                                            max(m2.votes) as maxVotes
                                        from 
                                            genres g2, movies m2,
                                            (
                                                select 
                                                    m.movie_id
                                                from 
                                                    movies m
                                                
                                                except
                                                
                                                select 
                                                    w.movie_id
                                                from 
                                                    watched w
                                                where 
                                                    w.customer_id = %s
                                             ) as moviesThatCustomerDidntWatch,
                                             (
                                                select distinct
                                                    g.genre_name 
                                                from 
                                                    genres g, (				
                                                                select 
                                                                    w.movie_id 
                                                                from 
                                                                    watched w 
                                                                where 
                                                                    w.customer_id = %s
                                                               ) as customerWatchedMovies
                                                where 
                                                    g.movie_id = customerWatchedMovies.movie_id
                                             ) as customerGenres
                                        where 
                                            g2.genre_name = customerGenres.genre_name and 
                                            g2.movie_id = moviesThatCustomerDidntWatch.movie_id and
                                            moviesThatCustomerDidntWatch.movie_id = m2.movie_id
                                        group by 
                                            g2.genre_name 
                                    ) as suggesting_movies
                            where 
                                suggesting_movies.maxVotes = mov.votes
                        )
                        
                        UNION
                        
                        -- step2
                        (
                            select
                                m.movie_id, m.title, m.movie_year, m.rating, m.votes
                            from 
                                movies m,
                                    (
                                        select 
                                            m.movie_id
                                        from 
                                            movies m
                                        
                                        except
                                        
                                        select 
                                            w.movie_id
                                        from 
                                            watched w
                                        where 
                                            w.customer_id = %s
                                    ) as moviesThatCustomerDidntWatch
                            where 
                                m.movie_id = moviesThatCustomerDidntWatch.movie_id and m.movie_year >= 2010
                            order by 
                                m.votes desc, m.rating desc
                            limit
                                10
                        )
                        
                        UNION
                        
                        -- step3
                        (
                            select
                                mov.movie_id, mov.title, mov.movie_year, mov.rating, mov.votes
                            from
                                movies mov,
                                    (
                                        select 
                                            m.movie_id
                                        from 
                                            movies m
                                        
                                        except
                                        
                                        select 
                                            w.movie_id
                                        from 
                                            watched w
                                        where 
                                            w.customer_id = %s
                                    ) as moviesThatCustomerDidntWatch,
                                    (
                                        select 
                                            avg(m.votes) voteAvg
                                        from 
                                            watched w, movies m
                                        where 
                                            w.customer_id = %s and w.movie_id = m.movie_id 
                                        group by 
                                            w.customer_id
                                    ) as customerVoteAvg
                            where
                                mov.movie_id = moviesThatCustomerDidntWatch.movie_id and
                                mov.votes > customerVoteAvg.voteAvg
                            order by
                                mov.votes desc
                            limit
                                10
                        )
                        """, (customer.customer_id, customer.customer_id,
                              customer.customer_id, customer.customer_id, customer.customer_id))
        all_steps_suggestions_combined = cursor.fetchall()
        print("Id|Title|Year|Rating|Votes")
        for movie_row in all_steps_suggestions_combined:
            print("{0}|{1}|{2}|{3:.1f}|{4}".format(movie_row[0], movie_row[1], movie_row[2], movie_row[3], movie_row[4]))
        cursor.close()
        return True, CMD_EXECUTION_SUCCESS
    except Exception as e:
        return False, CMD_EXECUTION_FAILED
