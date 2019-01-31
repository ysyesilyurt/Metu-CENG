package ceng.ceng351.musicdb;

import java.sql.*;
import java.util.ArrayList;

public class MUSICDB implements IMUSICDB {

    private static String user = "e2259166";
    private static String password = "b30a2423";
    private static String host = "144.122.71.57";
    private static String database = "db2259166";
    private static int port = 8084;

    private static Connection connection = null;

    @Override
    public void initialize() {
        String url = "jdbc:mysql://" + host + ":" + port + "/" + database;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection =  DriverManager.getConnection(url, user, password);
        }
        catch (SQLException | ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    @Override
    public int createTables() {

        int numberofTablesInserted = 0;

        // user(userID:int, userName:varchar(60), email:varchar(30), password:varchar(30))
        String queryCreateUserTable = "create table if not exists user (" +
                "userID int ," +
                "userName varchar(60) ," +
                "email varchar(30) ," +
                "password varchar(30) ," +
                "primary key (userID))";

        // song(songID:int, songName:varchar(60), genre:varchar(30), rating:double, artistID:int, albumID:int)
        String queryCreateSongTable = "create table if not exists song (" +
                "songID int ," +
                "songName varchar(60) ," +
                "genre varchar(30) ," +
                "rating double ," +
                "artistID int ," +
                "albumID int ," +
                "primary key (songID)," +
                "foreign key (artistID) references artist(artistID) on delete cascade on update cascade," +
                "foreign key (albumID) references album(albumID) on delete cascade on update cascade)";

        // artist(artistID:int, artistName:varchar(60))
        String queryCreateArtistTable = "create table if not exists artist (" +
                "artistID int," +
                "artistName varchar(60)," +
                "primary key (artistID))";

        //album(albumID:int, title:varchar(60), albumGenre:varchar(30), albumRating:double, releaseDate:date, artistID:int)
        String queryCreateAlbumTable = "create table if not exists album (" +
                "albumID int," +
                "title varchar(60)," +
                "albumGenre varchar(30)," +
                "albumRating double," +
                "releaseDate date," +
                "artistID int," +
                "primary key (albumID)," +
                "foreign key (artistID) references artist(artistID) on delete cascade on update cascade)";

        //listen(userID:int, songID:int, lastListenTime:timestamp, listenCount:int)
        String queryCreateListenTable = "create table if not exists listen (" +
                "userID int," +
                "songID int," +
                "lastListenTime timestamp," +
                "listenCount int," +
                "primary key (userID, songID)," +
                "foreign key (userID) references user(userID) on delete cascade on update cascade," +
                "foreign key (songID) references song(songID) on delete cascade on update cascade)";


        try {
            Statement statement = this.connection.createStatement();

            //User Table
            statement.executeUpdate(queryCreateUserTable);
            numberofTablesInserted++;

            //Song Table
            statement.executeUpdate(queryCreateArtistTable);
            numberofTablesInserted++;

            //Artist Table
            statement.executeUpdate(queryCreateAlbumTable);
            numberofTablesInserted++;

            //Album Table
            statement.executeUpdate(queryCreateSongTable);
            numberofTablesInserted++;

            //Listen Table
            statement.executeUpdate(queryCreateListenTable);
            numberofTablesInserted++;

            //close
            statement.close();
        }

        catch (SQLException e) {
            e.printStackTrace();
        }

        return numberofTablesInserted;
    }

    @Override
    public int dropTables() {

        int numberofTablesDropped = 0;

        String queryDropUserTable = "drop table if exists user";

        String queryDropSongTable = "drop table if exists song";

        String queryDropArtistTable = "drop table if exists artist";

        String queryDropAlbumTable = "drop table if exists album";

        String queryDropListenTable = "drop table if exists listen";


        try {
            Statement statement = this.connection.createStatement();

            statement.executeUpdate(queryDropListenTable);
            numberofTablesDropped++;

            statement.executeUpdate(queryDropSongTable);
            numberofTablesDropped++;

            statement.executeUpdate(queryDropAlbumTable);
            numberofTablesDropped++;

            statement.executeUpdate(queryDropArtistTable);
            numberofTablesDropped++;

            statement.executeUpdate(queryDropUserTable);
            numberofTablesDropped++;

            //close
            statement.close();

        } catch (SQLException e) {
            e.printStackTrace();
        }
        return numberofTablesDropped;
    }

    @Override
    public int insertAlbum(Album[] albums) {

        int numberofRowsInserted = 0;

        for (int i = 0; i < albums.length; i++)
        {
            try {
                Album alb = albums[i];

                PreparedStatement stmt=this.connection.prepareStatement("insert into album values(?,?,?,?,?,?)");
                stmt.setInt(1,alb.getAlbumID());
                stmt.setString(2,alb.getTitle());
                stmt.setString(3,alb.getAlbumGenre());
                stmt.setDouble(4,alb.getAlbumRating());
                stmt.setString(5,alb.getReleaseDate());
                stmt.setInt(6,alb.getArtistID());

                stmt.executeUpdate();

                //Close
                stmt.close();
                numberofRowsInserted++;

            }
            catch (SQLException e) {
                e.printStackTrace();
            }
        }

        return numberofRowsInserted;
    }

    @Override
    public int insertArtist(Artist[] artists) {

        int numberofRowsInserted = 0;

        for (int i = 0; i < artists.length; i++)
        {
            try {
                Artist art = artists[i];

                PreparedStatement stmt=this.connection.prepareStatement("insert into artist values(?,?)");
                stmt.setInt(1,art.getArtistID());
                stmt.setString(2,art.getArtistName());

                stmt.executeUpdate();

                //Close
                stmt.close();
                numberofRowsInserted++;

            }
            catch (SQLException e) {
                e.printStackTrace();
            }
        }

        return numberofRowsInserted;
    }

    @Override
    public int insertSong(Song[] songs) {

        int numberofRowsInserted = 0;

        for (int i = 0; i < songs.length; i++)
        {
            try {
                Song son = songs[i];

                PreparedStatement stmt=this.connection.prepareStatement("insert into song values(?,?,?,?,?,?)");
                stmt.setInt(1,son.getSongID());
                stmt.setString(2,son.getSongName());
                stmt.setString(3,son.getGenre());
                stmt.setDouble(4,son.getRating());
                stmt.setInt(5,son.getArtistID());
                stmt.setInt(6,son.getAlbumID());

                stmt.executeUpdate();

                //Close
                stmt.close();
                numberofRowsInserted++;

            }
            catch (SQLException e) {
                e.printStackTrace();
            }
        }

        return numberofRowsInserted;
    }

    @Override
    public int insertUser(User[] users) {

        int numberofRowsInserted = 0;

        for (int i = 0; i < users.length; i++)
        {
            try {
                User use = users[i];

                PreparedStatement stmt=this.connection.prepareStatement("insert into user values(?,?,?,?)");
                stmt.setInt(1,use.getUserID());
                stmt.setString(2,use.getUserName());
                stmt.setString(3,use.getEmail());
                stmt.setString(4,use.getPassword());

                stmt.executeUpdate();

                //Close
                stmt.close();
                numberofRowsInserted++;

            }
            catch (SQLException e) {
                e.printStackTrace();
            }
        }

        return numberofRowsInserted;
    }

    @Override
    public int insertListen(Listen[] listens) {

        int numberofRowsInserted = 0;

        for (int i = 0; i < listens.length; i++)
        {
            try {

                Listen lis = listens[i];

                PreparedStatement stmt=this.connection.prepareStatement("insert into listen values(?,?,?,?)");
                stmt.setInt(1,lis.getUserID());
                stmt.setInt(2,lis.getSongID());
                stmt.setTimestamp(3,lis.getLastListenTime());
                stmt.setInt(4,lis.getListenCount());

                stmt.executeUpdate();

                //Close
                stmt.close();
                numberofRowsInserted++;

            }
            catch (SQLException e) {
                e.printStackTrace();
            }
        }

        return numberofRowsInserted;
    }

    @Override
    public QueryResult.ArtistNameSongNameGenreRatingResult[] getHighestRatedSongs() {

        ResultSet rs;
        ArrayList<QueryResult.ArtistNameSongNameGenreRatingResult> reslist = new ArrayList<>();

        String query = "SELECT DISTINCT A.artistName, S.songName, S.genre, S.rating\n" +
                       "FROM song S, artist A\n" +
                       "WHERE A.artistID = S.artistID AND S.rating = (SELECT MAX(S2.rating) FROM song S2)\n" +
                       "ORDER BY A.artistName ASC;" ;
        try {
            Statement st = this.connection.createStatement();
            rs = st.executeQuery(query);

            while (rs.next()) {

                String artistName = rs.getString("artistName");
                String songName = rs.getString("songName");
                String genre = rs.getString("genre");
                Double rating = rs.getDouble("rating");

                QueryResult.ArtistNameSongNameGenreRatingResult obj = new QueryResult.ArtistNameSongNameGenreRatingResult(artistName, songName, genre, rating);
                reslist.add(obj);
            }

            //Close
            st.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        QueryResult.ArtistNameSongNameGenreRatingResult[] resarray = new QueryResult.ArtistNameSongNameGenreRatingResult[reslist.size()];

        return reslist.toArray(resarray);
    }

    @Override
    public QueryResult.TitleReleaseDateRatingResult getMostRecentAlbum(String artistName) {

        ResultSet rs;
        ArrayList<QueryResult.TitleReleaseDateRatingResult> reslist = new ArrayList<>();

        try {

            PreparedStatement stmt=this.connection.prepareStatement("SELECT DISTINCT ALB.title, ALB.releaseDate, ALB.albumRating \n" +
                                                                        "FROM album ALB, artist ART\n" +
                                                                        "WHERE ART.artistName = ? AND ALB.artistID = ART.artistID\n" +
                                                                        "\t  AND ALB.releaseDate = (SELECT MAX(A.releaseDate) FROM album A WHERE A.artistID = ALB.artistID)");
            stmt.setString(1,artistName);
            rs=stmt.executeQuery();

            rs.next();

            String title = rs.getString("title");
            String releaseDate = rs.getString("releaseDate");
            Double albumRating = rs.getDouble("albumRating");


            QueryResult.TitleReleaseDateRatingResult obj = new QueryResult.TitleReleaseDateRatingResult(title,releaseDate,albumRating);

            reslist.add(obj);


            //Close
            stmt.close();

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return reslist.get(0);
    }

    @Override
    public QueryResult.ArtistNameSongNameGenreRatingResult[] getCommonSongs(String userName1, String userName2) {

        ResultSet rs;
        ArrayList<QueryResult.ArtistNameSongNameGenreRatingResult> reslist = new ArrayList<>();

        try {

            PreparedStatement stmt=this.connection.prepareStatement("SELECT DISTINCT A.artistName, S.songName, S.genre, S.rating\n" +
                    "FROM song S, artist A\n" +
                    "WHERE A.artistID = S.artistID AND S.songID IN\n" +
                    "\t\t\t\t\t\t\t\t\t\t\t(\n" +
                    "\t\t\t\t\t\t\t\t\t\t\t\tSELECT L1.songID\n" +
                    "\t\t\t\t\t\t\t\t\t\t\t\tFROM user U1, listen L1, user U2, listen L2\n" +
                    "\t\t\t\t\t\t\t\t\t\t\t\tWHERE L1.songID=L2.songID\n" +
                    "\t\t\t\t\t\t\t\t\t\t\t\t\t\tAND U1.userID=L1.userID \n" +
                    "\t\t\t\t\t\t\t\t\t\t\t\t\t\tAND U2.userID=L2.userID\n" +
                    "\t\t\t\t\t\t\t\t\t\t\t\t\t\tAND (U1.userName=? AND U2.userName=?)\n" +
                    "\t\t\t\t\t\t\t\t\t\t\t)\t\n" +
                    "ORDER BY S.rating DESC;");

            stmt.setString(1,userName1);
            stmt.setString(2,userName2);
            rs=stmt.executeQuery();

            while(rs.next()){
                String artistName = rs.getString("artistName");
                String songName = rs.getString("songName");
                String genre = rs.getString("genre");
                Double rating = rs.getDouble("rating");

                QueryResult.ArtistNameSongNameGenreRatingResult obj = new QueryResult.ArtistNameSongNameGenreRatingResult(artistName,songName,genre,rating);
                reslist.add(obj);
            }

            //Close
            stmt.close();

        } catch (SQLException e) {
            e.printStackTrace();
        }

        QueryResult.ArtistNameSongNameGenreRatingResult[] resarray = new QueryResult.ArtistNameSongNameGenreRatingResult[reslist.size()];

        return reslist.toArray(resarray);
    }

    @Override
    public QueryResult.ArtistNameNumberOfSongsResult[] getNumberOfTimesSongsListenedByUser(String userName) {

        ResultSet rs;
        ArrayList<QueryResult.ArtistNameNumberOfSongsResult> reslist = new ArrayList<>();

        try {

            PreparedStatement stmt=this.connection.prepareStatement("SELECT DISTINCT A.artistName, SUM(L.listenCount) AS numberOfSongs \n" +
                    "FROM artist A, song S, listen L, user U\n" +
                    "WHERE U.userName = ? AND U.userID = L.userID AND\n" +
                    "\t  L.songID = S.songID AND S.artistID = A.artistID\n" +
                    "GROUP BY A.artistName\n" +
                    "ORDER BY A.artistName ASC;");

            stmt.setString(1,userName);
            rs=stmt.executeQuery();

            while(rs.next()){
                String artistName = rs.getString("artistName");
                Integer numberOfSongs = rs.getInt("numberOfSongs");

                QueryResult.ArtistNameNumberOfSongsResult obj = new QueryResult.ArtistNameNumberOfSongsResult(artistName,numberOfSongs);
                reslist.add(obj);
            }

            //Close
            stmt.close();

        } catch (SQLException e) {
            e.printStackTrace();
        }

        QueryResult.ArtistNameNumberOfSongsResult[] resarray = new QueryResult.ArtistNameNumberOfSongsResult[reslist.size()];

        return reslist.toArray(resarray);
    }

    @Override
    public User[] getUsersWhoListenedAllSongs(String artistName) {

        ResultSet rs;
        ArrayList<User> reslist = new ArrayList<>();

        try {

            PreparedStatement stmt=this.connection.prepareStatement("SELECT DISTINCT U.userID, U.userName, U.email, U.password\n" +
                    "FROM user U\n" +
                    "WHERE NOT EXISTS \n" +
                    "\t\t\t\t(\n" +
                    "\t\t\t\t\tSELECT S.songID -- songs of that artist\n" +
                    "                    FROM artist A, song S\n" +
                    "                    WHERE A.artistName = ? AND S.artistID = A.artistID\n" +
                    "                    \t  AND NOT EXISTS (\n" +
                    "                    \t  \t\t\t\t\tSELECT L.songID -- songs that, this user listened\n" +
                    "\t\t\t\t\t\t                    FROM listen L\n" +
                    "\t\t\t\t\t\t                    WHERE L.songID = S.songID AND L.userID = U.userID\n" +
                    "                    \t  \t\t\t\t )\n" +
                    "                )\n" +
                    "ORDER BY U.userID ASC;");

            stmt.setString(1,artistName);
            rs=stmt.executeQuery();

            while(rs.next()){
                Integer userID = rs.getInt("userID");
                String userName = rs.getString("userName");
                String email = rs.getString("email");
                String password = rs.getString("password");

                User obj = new User(userID,userName,email,password);
                reslist.add(obj);
            }

            //Close
            stmt.close();

        } catch (SQLException e) {
            e.printStackTrace();
        }

        User[] resarray = new User[reslist.size()];

        return reslist.toArray(resarray);
    }

    @Override
    public QueryResult.UserIdUserNameNumberOfSongsResult[] getUserIDUserNameNumberOfSongsNotListenedByAnyone() {

        ResultSet rs;
        ArrayList<QueryResult.UserIdUserNameNumberOfSongsResult> reslist = new ArrayList<>();

        String query = "SELECT DISTINCT U.userID, U.userName, COUNT(L.songID) AS numberOfSongs\n" +
                "FROM user U, listen L\n" +
                "WHERE L.userID = U.userID\n" +
                "\t  AND L.songID NOT IN  (\n" +
                "\t\t\t\t\t\t\tSELECT L2.songID\n" +
                "\t\t\t\t\t\t\tFROM listen L2, user U2\n" +
                "\t\t\t\t\t\t\tWHERE L2.userID = U2.userID AND U2.userID != U.userID\n" +
                "\t\t\t\t\t\t   )\n" +
                "GROUP BY U.userID\n" +
                "ORDER BY U.userID ASC;" ;
        try {
            Statement st = this.connection.createStatement();
            rs = st.executeQuery(query);

            while (rs.next()) {

                Integer userID = rs.getInt("userID");
                String userName = rs.getString("userName");
                Integer numberOfSongs = rs.getInt("numberOfSongs");

                QueryResult.UserIdUserNameNumberOfSongsResult obj = new QueryResult.UserIdUserNameNumberOfSongsResult(userID, userName, numberOfSongs);
                reslist.add(obj);
            }

            //Close
            st.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        QueryResult.UserIdUserNameNumberOfSongsResult[] resarray = new QueryResult.UserIdUserNameNumberOfSongsResult[reslist.size()];

        return reslist.toArray(resarray);
    }

    @Override
    public Artist[] getArtistSingingPopGreaterAverageRating(double rating) {

        ResultSet rs;
        ArrayList<Artist> reslist = new ArrayList<>();

        try {

            PreparedStatement stmt=this.connection.prepareStatement("SELECT DISTINCT A.artistID, A.artistName\n" +
                    "FROM artist A, song S\n" +
                    "WHERE S.artistID = A.artistID AND S.genre = \"pop\"\n" +
                    "\t  AND A.artistID IN (\n" +
                    "\t\t\t\t\t\tSELECT A2.artistID\n" +
                    "                        FROM artist A2, song S2\n" +
                    "                        WHERE S2.artistID = A2.artistID\n" +
                    "\t\t\t\t\t\tGROUP BY A2.artistID\n" +
                    "                        HAVING AVG(S2.rating) > ?" +
                    "                    )\n" +
                    "ORDER BY A.artistID ASC");

            stmt.setDouble(1,rating);
            rs=stmt.executeQuery();

            while(rs.next()){
                Integer artistID = rs.getInt("artistID");
                String artistName = rs.getString("artistName");

                Artist obj = new Artist(artistID,artistName);
                reslist.add(obj);
            }

            //Close
            stmt.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        Artist[] resarray = new Artist[reslist.size()];

        return reslist.toArray(resarray);
    }

    @Override
    public Song[] retrieveLowestRatedAndLeastNumberOfListenedSongs() {

        ResultSet rs;
        ArrayList<Song> reslist = new ArrayList<>();

        String query = "SELECT DISTINCT \n" +
                "    S.songID,\n" +
                "    S.songName,\n" +
                "    S.rating,\n" +
                "    S.genre,\n" +
                "    S.artistID,\n" +
                "    S.albumID\n" +
                "   FROM\n" +
                "    song S,\n" +
                "    (SELECT \n" +
                "        L.songID, SUM(L.listenCount) AS sumcount\n" +
                "    FROM\n" +
                "        listen L\n" +
                "    GROUP BY L.songID) AS Tmp -- Tmp finds sumcount per song independently\n" +
                "   WHERE\n" +
                "    S.songID = Tmp.songID -- If a sumcount is in the result of the subquery, then it is in the final result\n" +
                "        AND Tmp.sumcount IN (SELECT \n" +
                "            MIN(Temp2.sumcount2) -- Find min of the result\n" +
                "        FROM\n" +
                "            (SELECT \n" +
                "                *\n" +
                "            FROM\n" +
                "                song S\n" +
                "            WHERE\n" +
                "                S.genre = 'Pop'\n" +
                "                    AND S.rating = (SELECT \n" +
                "                        MIN(S2.rating)\n" +
                "                    FROM\n" +
                "                        song S2\n" +
                "                    WHERE\n" +
                "                        S2.genre = 'Pop')) AS Temp1, -- Temp1 = Fetch the Pop songs with lowest rating\n" +
                "            (SELECT \n" +
                "                L.songID, SUM(L.listenCount) AS sumcount2\n" +
                "            FROM\n" +
                "                listen L\n" +
                "            GROUP BY L.songID) AS Temp2 -- Temp2 = Bring sumcounts per songs again\n" +
                "        WHERE\n" +
                "            Temp1.songID = Temp2.songID) -- combine Temp1 with Temp2 to find min of the desired songs!!\n" +
                "ORDER BY S.songID ASC;" ;

        try {
            Statement st = this.connection.createStatement();
            rs = st.executeQuery(query);

            while (rs.next()) {
                Integer songID = rs.getInt("songID");
                String songName = rs.getString("songName");
                Double rating = rs.getDouble("rating");
                String genre = rs.getString("genre");
                Integer artistID = rs.getInt("artistID");
                Integer albumID = rs.getInt("albumID");

                Song obj = new Song(songID, songName, genre, rating, artistID, albumID);
                reslist.add(obj);
            }

            //Close
            st.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        Song[] resarray = new Song[reslist.size()];

        return reslist.toArray(resarray);
    }

    @Override
    public int multiplyRatingOfAlbum(String releaseDate) {

        int numberofRowsAffected = 0;

        try {

            PreparedStatement stmt=this.connection.prepareStatement("UPDATE album A\n" +
                    "SET    A.albumRating = A.albumRating * 1.5\n" +
                    "WHERE  A.releaseDate > ?");
            stmt.setString(1,releaseDate);

            numberofRowsAffected=stmt.executeUpdate();

            //close
            stmt.close();

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return numberofRowsAffected;
    }

    @Override
    public Song deleteSong(String songName) {

        ResultSet rs;
        ArrayList<Song> reslist = new ArrayList<>();

        try {

            PreparedStatement stmt=this.connection.prepareStatement("SELECT DISTINCT S.songID, S.songName, S.rating, S.genre, S.artistID, S.albumID\n" +
                    "FROM song S\n" +
                    "WHERE S.songName =?");
            stmt.setString(1,songName);
            rs = stmt.executeQuery();

            rs.next();

            Integer songID = rs.getInt("songID");
            String songname = rs.getString("songName");
            Double rating = rs.getDouble("rating");
            String genre = rs.getString("genre");
            Integer artistID = rs.getInt("artistID");
            Integer albumID = rs.getInt("albumID");

            Song obj = new Song(songID,songname,genre,rating,artistID,albumID);

            try {

                PreparedStatement stmt2=this.connection.prepareStatement("delete from song where songName=?");
                stmt2.setString(1,songName);

                stmt2.executeUpdate();

                //close
                stmt2.close();

            } catch (SQLException e) {
                e.printStackTrace();
            }

            reslist.add(obj);
            //Close
            stmt.close();

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return reslist.get(0);
    }
}
