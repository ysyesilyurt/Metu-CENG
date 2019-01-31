package ceng.ceng351.musicdb;

public class Artist {
    
    private int artistID;
    private String artistName;

    public Artist(int artistID, String name) {
        this.artistID = artistID;
        this.artistName = name;
    }

    public int getArtistID() {
        return artistID;
    }

    public void setArtistID(int artistID) {
        this.artistID = artistID;
    }

    public String getArtistName() {
        return artistName;
    }

    public void setArtistName(String name) {
        this.artistName = name;
    }
    
    @Override
    public String toString() {
        return artistID + "\t" + artistName;
    }
    
}
