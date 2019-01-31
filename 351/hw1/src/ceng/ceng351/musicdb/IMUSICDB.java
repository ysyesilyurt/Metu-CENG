package ceng.ceng351.musicdb;

public interface IMUSICDB {
    
    /**
    * Place your initialization code inside if required.
    * 
    * <p>
    * This function will be called before all other operations. If your implementation
    * need initialization , necessary operations should be done inside this function. For
    * example, you can set your connection to the database server inside this function.
    */
   public void initialize();
   
   /**
    * Should create the necessary tables when called.
    * 
    * @return the number of tables that are created successfully.
    */
   public int createTables();
   
   /**
    * Should drop the tables if exists when called. 
    * 
    * @return the number of tables are dropped successfully.
    */
   public int dropTables();
   
   /**
    * Should insert an array of Album into the database.
    * 
    * @return Number of rows inserted successfully.
    */
   public int insertAlbum(Album[] albums);

   /**
    * Should insert an array of Artist into the database.
    * 
    * @return Number of rows inserted successfully.
    */
   public int insertArtist(Artist[] artists);

   /**
    * Should insert an array of Song into the database.
    * 
    * @return Number of rows inserted successfully.
    */
   public int insertSong(Song[] songs);

   /**
    * Should insert an array of User into the database.
    * 
    * @return Number of rows inserted successfully.
    */
   public int insertUser(User[] users);
   
   /**
    * Should insert an array of Listen into the database.
    * 
    * @return Number of rows inserted successfully.
    */
   public int insertListen(Listen[] listens);
   
   /**
    * Should return songs with the highest rating
    * 
    * @return ArtistNameSongNameGenreRatingResult[]
    */
   public QueryResult.ArtistNameSongNameGenreRatingResult[] getHighestRatedSongs();
   
   /**
    * Should return the most recent album for the given artistName
    * 
    * @return TitleReleaseDateRatingResult
    */
   public QueryResult.TitleReleaseDateRatingResult getMostRecentAlbum(String artistName);
   
   /**
    * Should return songs that are listened by both userName1 & userName2
    * 
    * @return ArtistNameSongNameGenreRatingResult[]
    */
   public QueryResult.ArtistNameSongNameGenreRatingResult[] getCommonSongs(String userName1, String userName2);
   
   /**
    * Should return artists whose songs are listened by the given user  
    * and number of times his/her songs have been listened by the given user 
    * 
    * @return ArtistNameNumberOfSongsResult[]
    */
   public QueryResult.ArtistNameNumberOfSongsResult[] getNumberOfTimesSongsListenedByUser(String userName);
   
   /**
    * Should return users who have listened all songs of a given artist
    * 
    * @return User[]
    */
   public User[] getUsersWhoListenedAllSongs(String artistName);
   
   /**
    * Should return the userID, userName and number of songs listened by this user such that 
    * none of these songs are listened by any other user.
    * 
    * @return QueryResult.UserIdUserNameNumberOfSongsResult[]
    */
   public QueryResult.UserIdUserNameNumberOfSongsResult[]  getUserIDUserNameNumberOfSongsNotListenedByAnyone();
   
   /**
    * Should return artists who have sung pop music at least once and whose average rating of
    * all songs is greater than the given rating
    * 
    * @return Artist[]
    */
   public Artist[] getArtistSingingPopGreaterAverageRating(double rating);
   
   /**
    * Retrieve songs with the lowest rating in pop category, in case of more than one song exist, 
    * retrieve the least listened ones
    * 
    * @return Song[]
    */
   public Song[] retrieveLowestRatedAndLeastNumberOfListenedSongs();
   
   /**
    * Multiply the rating of the album by 1.5 whose releaseDate is after for a given date
    * 
    * @return the row count for SQL Data Manipulation Language (DML) statements
    */
   public int multiplyRatingOfAlbum(String releaseDate);
   
   /**
    * Delete the song for the given songName
    * 
    * @return Song
    */
   public Song deleteSong(String songName);
   
}
