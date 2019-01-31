package ceng.ceng351.musicdb;


public class QueryResult {
    
    
    public static class ArtistNameSongNameGenreRatingResult{
	
        String artistName;
        String songName;
        String genre;
        double rating;

        public ArtistNameSongNameGenreRatingResult(
                    String artistName, 
                    String songName, 
                    String genre,
                    double rating) {

            this.artistName = artistName;
            this.songName = songName;
            this.genre = genre;
            this.rating = rating;
        }

        public String toString() {
            return artistName + "\t" + songName + "\t" + genre + "\t" + rating;
        }	
    }
    
    
    public static class TitleReleaseDateRatingResult{
	
        String title;
        String releaseDate;
        double rating;

        public TitleReleaseDateRatingResult(
                    String title, 
                    String releaseDate, 
                    double rating) {

            this.title = title;
            this.releaseDate = releaseDate;
            this.rating = rating;
        }

        public String toString() {
            return title + "\t" + releaseDate + "\t" + rating;
        }	
    }
    
    
    public static class ArtistNameNumberOfSongsResult{
	
        String artistName;
        int numberOfSongs;

        public ArtistNameNumberOfSongsResult(
                String artistName, 
                int numberOfSongs) {

            this.artistName = artistName;
            this.numberOfSongs = numberOfSongs;
        }

        public String toString() {
            return artistName + "\t" + numberOfSongs;
        }	
    }
    
    
    public static class UserIdUserNameNumberOfSongsResult{
	
        int userID;
        String userName;
        int numberOfSongs;

        public UserIdUserNameNumberOfSongsResult(
                int userID,
                String userName, 
                int numberOfSongs) {

            this.userID = userID;
            this.userName = userName;
            this.numberOfSongs = numberOfSongs;
        }

        public String toString() {
            return userID + "\t" + userName + "\t" + numberOfSongs;
        }	
    }
    
}
