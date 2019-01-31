package ceng.ceng351.musicdb;

import java.sql.Timestamp;

public class Listen {
    
    private int userID;
    private int songID;
    private Timestamp lastListenTime;
    private int listenCount;

    public Listen(int userID, int songID, Timestamp lastListenTime, int listenCount) {
        this.userID = userID;
        this.songID = songID;
        this.lastListenTime = lastListenTime;
        this.listenCount = listenCount;
    }

    public int getUserID() {
        return userID;
    }

    public void setUserID(int userID) {
        this.userID = userID;
    }

    public int getSongID() {
        return songID;
    }

    public void setSongID(int songID) {
        this.songID = songID;
    }

    public Timestamp getLastListenTime() {
        return lastListenTime;
    }

    public void setLastListenTime(Timestamp lastListenTime) {
        this.lastListenTime = lastListenTime;
    }

    public int getListenCount() {
        return listenCount;
    }

    public void setListenCount(int listenCount) {
        this.listenCount = listenCount;
    }
    
    @Override
    public String toString() {
        return userID + "\t" + songID + "\t" + lastListenTime + "\t" + listenCount;
    }
}
