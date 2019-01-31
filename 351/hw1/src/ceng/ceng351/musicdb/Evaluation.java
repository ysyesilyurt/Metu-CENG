package ceng.ceng351.musicdb;

import ceng.ceng351.musicdb.QueryResult.ArtistNameNumberOfSongsResult;
import ceng.ceng351.musicdb.QueryResult.ArtistNameSongNameGenreRatingResult;
import ceng.ceng351.musicdb.QueryResult.UserIdUserNameNumberOfSongsResult;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Vector;


public class Evaluation {

    private static String user = "e2259166"; // TODO: Your userName
    private static String password = "b30a2423"; //  TODO: Your password
    private static String host = "144.122.71.57"; // host name
    private static String database = "db2259166"; // TODO: Your database name
    private static int port = 8084; // port
    
    private static Connection connection = null;
    
    
    public static void connect() {
		
        String url = "jdbc:mysql://" + host + ":" + port + "/" + database;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection =  DriverManager.getConnection(url, user, password);
        } 
        catch (SQLException | ClassNotFoundException e) {
            e.printStackTrace();
        } 
    }
    
    public static void disconnect() {
		
        if (connection != null) {
            try {
                connection.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }
    
    public static void addInputTitle(String title, BufferedWriter bufferedWriter) throws IOException {
        bufferedWriter.write("*** " + title + " ***" + System.getProperty("line.separator"));
    }
    
    public static void printAllTables(BufferedWriter bufferedWriter) throws IOException {
		
        String sql1 = "show tables";
        String sql2 = "describe ";

        Vector<String> tables = new Vector<>();

        try
        {
            // Execute query
            Statement st = connection.createStatement();
            ResultSet rs = st.executeQuery(sql1);

            // Process the result set
            while(rs.next()) {
                tables.add(rs.getString(1));
            }

            for(int i=0; i < tables.size(); i++) {
                rs = st.executeQuery(sql2 + tables.get(i));

                // Print table name
                bufferedWriter.write("--- " + tables.get(i) + " ---" + System.getProperty("line.separator"));

                // Print field names and types
                while(rs.next()) {
                        bufferedWriter.write(rs.getString(1) + " " + rs.getString(2) + System.getProperty("line.separator"));
                }

                bufferedWriter.write(System.getProperty("line.separator"));
            }

        } catch (SQLException e) {
            printException(e);
        }
    }
    
    private static void printException(SQLException ex) {
        System.out.println(ex.getMessage() + "\n");
    }
	
    public static void printLine(String result, BufferedWriter bufferedWriter) throws IOException {
        bufferedWriter.write(result + System.getProperty("line.separator"));
    }

    public static void addDivider(BufferedWriter bufferedWriter) throws IOException {
        bufferedWriter.write( System.getProperty("line.separator")+ "--------------------------------------------------------------" + System.getProperty("line.separator"));
    }
    

    public static void main(String[] args) {

       int numberofInsertions = 0;
       int numberofTablesCreated = 0;
       int numberofTablesDropped = 0;

       /***********************************************************/
       // TODO While running on your local machine, change musicdbDirectory accordingly
       String musicdbDirectory = "src" + System.getProperty("file.separator") +
                       "ceng" + System.getProperty("file.separator") +
                       "ceng351" + System.getProperty("file.separator") +
                       "musicdb";
       /***********************************************************/

       FileWriter fileWriter = null;
       BufferedWriter bufferedWriter = null;

       //Connect to the database
       connect();

       // Create MUSICDB object
       MUSICDB musicDB = null;
       
       double avgRating = 3.94;
       String artistName = "Adele";
       String releaseDate = "2017-01-01";
       String userName1 = "Ercan Bolukbasi";
       String userName2 = "Firat Cekinel";
       String userName3 = "Alperen Dalkiran";
       String songName = "Strangers in the Night";

       try {
            // Create MUSICDB object and initialize
            musicDB = new MUSICDB();
            musicDB.initialize();

            /***********************************************************/
            /*************Create File Writer starts*********************/
            /***********************************************************/
            fileWriter = FileOperations.createFileWriter(musicdbDirectory + System.getProperty("file.separator") + "output" + System.getProperty("file.separator") + "Output.txt");
            bufferedWriter =  new BufferedWriter(fileWriter);
            /***********************************************************/
            /*************Create File Writer ends***********************/
            /***********************************************************/

            /***********************************************************/
            /*************Drop tables starts****************************/
            /***********************************************************/
            addDivider(bufferedWriter);
            addInputTitle("Drop tables", bufferedWriter);
            numberofTablesDropped = 0;

            // Drop tables
            try {
                numberofTablesDropped = musicDB.dropTables();
            } catch(Exception e) {
                e.printStackTrace();
            }

            // Check if tables are dropped
            printLine("Dropped " + numberofTablesDropped + " tables.", bufferedWriter);

            addDivider(bufferedWriter);
            /***********************************************************/
            /*************Drop tables ends******************************/
            /***********************************************************/

            /***********************************************************/
            /*******************Create tables starts********************/
            /***********************************************************/
            addDivider(bufferedWriter);
            addInputTitle("Create tables",bufferedWriter);
            numberofTablesCreated = 0;

            // Create Tables
            try {
                numberofTablesCreated = musicDB.createTables();

                // Check if tables are created
                printLine("Created " + numberofTablesCreated + " tables.", bufferedWriter);

            } catch(Exception e) {
                printLine("Q3.1: Exception occured: \n\n" + e.toString(),bufferedWriter);
            }

            addDivider(bufferedWriter);
            /***********************************************************/
            /*******************Create tables ends**********************/
            /***********************************************************/

            /***********************************************************/
            /*******************Insert INTO User starts**********/
            /***********************************************************/
            addDivider(bufferedWriter);
            addInputTitle("Insert into User",bufferedWriter);
            //insert User
            numberofInsertions = 0;
            User[] users = FileOperations.readUserFile(musicdbDirectory + 
                            System.getProperty("file.separator") + "data" + System.getProperty("file.separator") +
                            "Test_UserFile.txt");

            numberofInsertions = musicDB.insertUser(users);
            printLine( numberofInsertions + " users are inserted.",bufferedWriter);
            addDivider(bufferedWriter);
            /***********************************************************/
            /*******************Insert INTO User ends************/
            /***********************************************************/
            
            
            /***********************************************************/
            /*******************Insert INTO Artist starts*****************/
            /***********************************************************/
            addDivider(bufferedWriter);
            addInputTitle("Insert into Artist",bufferedWriter);
            //insert Artist
            numberofInsertions = 0;
            Artist[] artists = FileOperations.readArtistFile( musicdbDirectory + System.getProperty("file.separator") 
                    + "data" + System.getProperty("file.separator") + "Test_ArtistFile.txt");

            numberofInsertions = musicDB.insertArtist(artists);
            printLine( numberofInsertions + " artists are inserted.",bufferedWriter);
            addDivider(bufferedWriter);
            /***********************************************************/
            /*******************Insert INTO Artist ends*******************/
            /***********************************************************/


            /***********************************************************/
            /*******************Insert INTO Album starts**********/
            /***********************************************************/
            addDivider(bufferedWriter);
            addInputTitle("Insert into Album",bufferedWriter);
            //insert Album
            numberofInsertions = 0;
            Album[] albums = FileOperations.readAlbumFile(musicdbDirectory + 
                            System.getProperty("file.separator") + "data" + System.getProperty("file.separator") +
                            "Test_AlbumFile.txt");

            numberofInsertions = musicDB.insertAlbum(albums);
            printLine( numberofInsertions + " albums are inserted.", bufferedWriter);
            addDivider(bufferedWriter);
            /***********************************************************/
            /*******************Insert INTO Album ends************/
            /***********************************************************/


            /***********************************************************/
            /*******************Insert INTO Song starts*************/
            /***********************************************************/
            addDivider(bufferedWriter);
            addInputTitle("Insert into Song",bufferedWriter);
            //insert Song
            numberofInsertions = 0;
            Song[] songs = FileOperations.readSongFile(musicdbDirectory + 
                            System.getProperty("file.separator") + "data" + System.getProperty("file.separator") +
                            "Test_SongFile.txt");

            numberofInsertions = musicDB.insertSong(songs);
            printLine(numberofInsertions + " songs are inserted.",bufferedWriter);
            addDivider(bufferedWriter);
            /***********************************************************/
            /*******************Insert INTO Song ends***************/
            /***********************************************************/
            
            /***********************************************************/
            /*******************Insert INTO Song starts*************/
            /***********************************************************/
            addDivider(bufferedWriter);
            addInputTitle("Insert into Listens",bufferedWriter);
            //insert Song
            numberofInsertions = 0;
            Listen[] listens = FileOperations.readListenFile(musicdbDirectory + 
                            System.getProperty("file.separator") + "data" + System.getProperty("file.separator") +
                            "Test_ListenFile.txt");

            numberofInsertions = musicDB.insertListen(listens);
            printLine(numberofInsertions + " listens are inserted.",bufferedWriter);
            addDivider(bufferedWriter);
            /***********************************************************/
            /*******************Insert INTO Song ends***************/
            /***********************************************************/
            
            /***********************************************************/
            /***********************************************************/
            /***********************************************************/
            addDivider(bufferedWriter);
            addInputTitle("List songs which have the highest rating",bufferedWriter);
            try {

                QueryResult.ArtistNameSongNameGenreRatingResult[] artistNameSongNameGenreRatingResultArray = musicDB.getHighestRatedSongs();

                //Header Line
                printLine("ArtistName" + "\t" + "SongName" + "\t" + "Genre" + "\t" + "Rating",bufferedWriter);

                if(artistNameSongNameGenreRatingResultArray != null) {
                    for(ArtistNameSongNameGenreRatingResult artistNameSongNameGenreRatingResult : artistNameSongNameGenreRatingResultArray){
                        printLine(artistNameSongNameGenreRatingResult.toString(),bufferedWriter);	
                    }	
                }


            } catch(Exception e) {
                printLine("Q3.3: Exception occured: \n\n" + e.toString(),bufferedWriter);
            }
            addDivider(bufferedWriter);
            /***********************************************************/
            /***********************************************************/
            /***********************************************************/
            
            /***********************************************************/
            /***********************************************************/
            /***********************************************************/
            addDivider(bufferedWriter);
            addInputTitle("Find the most recent album for a given artist ",bufferedWriter);
            try {

                QueryResult.TitleReleaseDateRatingResult titleReleaseDateRatingResult = musicDB.getMostRecentAlbum(artistName);

                //Header Line
                printLine("Title" + "\t" + "ReleaseDate" + "\t" + "AlbumRating",bufferedWriter);

                if(titleReleaseDateRatingResult != null) {
                    printLine(titleReleaseDateRatingResult.toString(),bufferedWriter);	
                }


            } catch(Exception e) {
                printLine("Q3.4: Exception occured: \n\n" + e.toString(),bufferedWriter);
            }
            addDivider(bufferedWriter);
            /***********************************************************/
            /***********************************************************/
            /***********************************************************/
   
            /***********************************************************/
            /***********************************************************/
            /***********************************************************/
            addDivider(bufferedWriter);
            addInputTitle("List songs that are listened by both users whose usernames are given",bufferedWriter);
            try {

                QueryResult.ArtistNameSongNameGenreRatingResult[] artistNameSongNameGenreRatingResultArray = musicDB.getCommonSongs(userName1, userName2);

                //Header Line
                printLine("ArtistName" + "\t" + "SongName" + "\t" + "Genre" + "\t" + "Rating",bufferedWriter);
                
                if(artistNameSongNameGenreRatingResultArray != null) {
                    for(ArtistNameSongNameGenreRatingResult artistNameSongNameGenreRatingResult : artistNameSongNameGenreRatingResultArray){
                        printLine(artistNameSongNameGenreRatingResult.toString(),bufferedWriter);	
                    }
                }

            } catch(Exception e) {
                printLine("Q3.5: Exception occured: \n\n" + e.toString(),bufferedWriter);
            }

            addDivider(bufferedWriter);
            /***********************************************************/
            /***********************************************************/
            /***********************************************************/
            
            
            /***********************************************************/
            /***********************************************************/
            /***********************************************************/
            addDivider(bufferedWriter);
            addInputTitle("List artists and number of times his/her songs have been listened by the given user",bufferedWriter);
            try {

                QueryResult.ArtistNameNumberOfSongsResult[] artistNameNumberOfSongsResultArray = musicDB.getNumberOfTimesSongsListenedByUser(userName3);

                //Header Line
                printLine("ArtistName" + "\t" + "NumberofListenedSongs",bufferedWriter);

                if(artistNameNumberOfSongsResultArray != null) {
                    for(ArtistNameNumberOfSongsResult artistNameNumberOfSongsResult : artistNameNumberOfSongsResultArray){
                        printLine(artistNameNumberOfSongsResult.toString(),bufferedWriter);	
                    }
                }

            } catch(Exception e) {
                printLine("Q3.6: Exception occured: \n\n" + e.toString(),bufferedWriter);
            }
            addDivider(bufferedWriter);
            /***********************************************************/
            /***********************************************************/
            /***********************************************************/

            /***********************************************************/
            /***********************************************************/
            /***********************************************************/
            addDivider(bufferedWriter);
            addInputTitle("List users who have listened all songs of a given artist",bufferedWriter);
            try {

                User[] userArray = musicDB.getUsersWhoListenedAllSongs(artistName);

                //Header Line
                printLine("UserID" + "\t" + "UserName" + "\t" + "Email" + "\t" + "Password", bufferedWriter);

                for(User user : userArray){
                    printLine(user.toString(),bufferedWriter);	
                }


            } catch(Exception e) {
                printLine("Q3.7: Exception occured: \n\n" + e.toString(),bufferedWriter);
            }
            addDivider(bufferedWriter);
            /***********************************************************/
            /***********************************************************/
            /***********************************************************/
            
            /***********************************************************/
            /***********************************************************/
            /***********************************************************/
            addDivider(bufferedWriter);
            addInputTitle("List users and number of songs listened by this user such that none of these songs are listened by any other user",bufferedWriter);
            try {

                QueryResult.UserIdUserNameNumberOfSongsResult[] userIdUserNameNumberOfSongsResultArray = musicDB.getUserIDUserNameNumberOfSongsNotListenedByAnyone();

                //Header Line
                printLine("UserID" + "\t" + "UserName" + "\t" + "NumberofSongs", bufferedWriter);

                for(UserIdUserNameNumberOfSongsResult userIdUserNameNumberOfSongsResult : userIdUserNameNumberOfSongsResultArray){
                    printLine(userIdUserNameNumberOfSongsResult.toString(),bufferedWriter);	
                }

            } catch(Exception e) {
                printLine("Q3.8: Exception occured: \n\n" + e.toString(),bufferedWriter);
            }
            addDivider(bufferedWriter);
            /***********************************************************/
            /***********************************************************/
            /***********************************************************/
            
            /***********************************************************/
            /***********************************************************/
            /***********************************************************/
            addDivider(bufferedWriter);
            addInputTitle("List artists who have sung pop music at least once and whose average rating of all songs is greater than the given rating",bufferedWriter);

            try {

                Artist[] artistArray = musicDB.getArtistSingingPopGreaterAverageRating(avgRating);

                //Header Line
                printLine("ArtistID" + "\t" + "ArtistName", bufferedWriter);
                
                if (artistArray != null) {
                    for(Artist artist : artistArray){
                        printLine(artist.toString(),bufferedWriter);	
                    }
                }

            } catch(Exception e) {
                printLine("Q3.9: Exception occured: \n\n" + e.toString(),bufferedWriter);
            }
            addDivider(bufferedWriter);
            /***********************************************************/
            /***********************************************************/
            /***********************************************************/
            
            /***********************************************************/
            /***********************************************************/
            /***********************************************************/
            addDivider(bufferedWriter);
            addInputTitle("Retrieve songs with the lowest rating in pop category, in case of more than one song exist, retrieve the least listened ones",bufferedWriter);
            try {

                Song[] songArray = musicDB.retrieveLowestRatedAndLeastNumberOfListenedSongs();

                //Header Line
                printLine("SongID" + "\t" + "songName" + "\t" + "Rating" + "\t" + "Genre" + "\t" + "ArtistID" + "\t" + "AlbumID", bufferedWriter);

                if (songArray != null) {
                    for (Song song : songArray) {
                        printLine(song.toString(),bufferedWriter);	
                    }
                }

            } catch(Exception e) {
                printLine("Q3.10: Exception occured: \n\n" + e.toString(),bufferedWriter);
            }
            addDivider(bufferedWriter);
            /***********************************************************/
            /***********************************************************/
            /***********************************************************/
            
            /***********************************************************/
            /***********************************************************/
            /***********************************************************/
            addDivider(bufferedWriter);
            addInputTitle("Multiply rating of the album by 1.5 whose releaseDate is after for a given date",bufferedWriter);
            try {
                
                int numberofChanged = musicDB.multiplyRatingOfAlbum(releaseDate);
		printLine( numberofChanged + " rows are changed.", bufferedWriter);

            } catch(Exception e) {
                printLine("Q3.11: Exception occured: \n\n" + e.toString(),bufferedWriter);
            }
            addDivider(bufferedWriter);
            /***********************************************************/
            /***********************************************************/
            /***********************************************************/

            /***********************************************************/
            /***********************************************************/
            /***********************************************************/
            addDivider(bufferedWriter);
            addInputTitle("Delete the song with the given song name",bufferedWriter);
            try {
                
                Song song = musicDB.deleteSong(songName);

                //Header Line
                printLine("SongID" + "\t" + "songName" + "\t" + "Rating" + "\t" + "Genre" + "\t" + "ArtistID" + "\t" + "AlbumID", bufferedWriter);

                if (song != null) {
                    printLine(song.toString(),bufferedWriter);	
                }
            } catch(Exception e) {
                printLine("Q3.12: Exception occured: \n\n" + e.toString(),bufferedWriter);
            }
            addDivider(bufferedWriter);
            /***********************************************************/
            /***********************************************************/
            /***********************************************************/

       } catch (IOException e) {
               e.printStackTrace();
       } finally {
           try {
                //Close Writer
                if (bufferedWriter != null) {
                    bufferedWriter.close();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
            //Close Connection
            disconnect();
       }
    }
    
}
