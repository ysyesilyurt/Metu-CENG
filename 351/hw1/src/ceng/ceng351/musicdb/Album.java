package ceng.ceng351.musicdb;

public class Album {
    //The default way to store a date in a MySQL database is by using DATE. 
    //The proper format of a DATE is: YYYY-MM-DD.
    
    private int albumID;
    private String title;
    private String albumGenre;
    private double albumRating;
    private String releaseDate;
    private int artistID;

    public Album(int albumID, String title, String albumGenre, double albumRating, String releaseDate, int artistID) {
        this.albumID = albumID;
        this.title = title;
        this.albumGenre = albumGenre;
        this.albumRating = albumRating;
        this.releaseDate = releaseDate;
        this.artistID = artistID;
    }

    public int getAlbumID() {
        return albumID;
    }

    public void setAlbumID(int albumID) {
        this.albumID = albumID;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getAlbumGenre() {
        return albumGenre;
    }

    public void setAlbumGenre(String albumGenre) {
        this.albumGenre = albumGenre;
    }

    public double getAlbumRating() {
        return albumRating;
    }

    public void setAlbumRating(double albumRating) {
        this.albumRating = albumRating;
    }

    public String getReleaseDate() {
        return releaseDate;
    }

    public void setReleaseDate(String releaseDate) {
        this.releaseDate = releaseDate;
    }

    public int getArtistID() {
        return artistID;
    }

    public void setArtistID(int artistID) {
        this.artistID = artistID;
    }
    
    @Override
    public String toString() {
        return albumID + "\t" + title + "\t" + albumGenre + "\t" + albumRating + "\t" + releaseDate + "\t" + artistID;
    }
    
}
