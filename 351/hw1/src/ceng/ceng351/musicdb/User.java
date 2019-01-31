package ceng.ceng351.musicdb;

public class User {
    
    private int userID;
    private String userName;
    private String email;
    private String password;

    public User(int userID, String name, String email, String password) {
        this.userID = userID;
        this.userName = name;
        this.email = email;
        this.password = password;
    }

    public int getUserID() {
        return userID;
    }

    public void setUserID(int userID) {
        this.userID = userID;
    }

    public String getUserName() {
        return userName;
    }

    public void userName(String name) {
        this.userName = name;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }
    
    @Override
    public String toString() {
        return userID + "\t" + userName + "\t" + email + "\t" + password;
    }
    
    
}
