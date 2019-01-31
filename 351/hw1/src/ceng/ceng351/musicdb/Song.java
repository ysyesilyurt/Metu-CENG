package ceng.ceng351.musicdb;

public class Song {
    
    private int songID;
    private String songName;
    private String genre;
    private double rating;
    private int artistID;
    private int albumID;

    public Song(int songID, String name, String genre, double rating, int artistID, int albumID) {
        this.songID = songID;
        this.songName = name;
        this.genre = genre;
        this.rating = rating;
        this.artistID = artistID;
        this.albumID = albumID;
    }

    public int getSongID() {
        return songID;
    }

    public void setSongID(int songID) {
        this.songID = songID;
    }

    public String getSongName() {
        return songName;
    }

    public void setSongName(String name) {
        this.songName = name;
    }

    public String getGenre() {
        return genre;
    }

    public void setGenre(String genre) {
        this.genre = genre;
    }

    public double getRating() {
        return rating;
    }

    public void setRating(double rating) {
        this.rating = rating;
    }

    public int getArtistID() {
        return artistID;
    }

    public void setArtistID(int artistID) {
        this.artistID = artistID;
    }

    public int getAlbumID() {
        return albumID;
    }

    public void setAlbumID(int albumID) {
        this.albumID = albumID;
    }
    
    @Override
    public String toString() {
        return songID + "\t" + songName + "\t" + genre + "\t" + rating + "\t" + artistID + "\t" + albumID;
    }
}
