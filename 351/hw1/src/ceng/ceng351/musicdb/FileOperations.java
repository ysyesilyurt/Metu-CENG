package ceng.ceng351.musicdb;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.sql.Timestamp;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;


public class FileOperations {

    public static FileWriter createFileWriter( String path) throws IOException {
        File f = new File( path);

        FileWriter fileWriter = null;

        if( f.isDirectory() && !f.exists())
            f.mkdirs();
        else if( !f.isDirectory() && !f.getParentFile().exists())
            f.getParentFile().mkdirs();

        if( !f.isDirectory() && f.exists())
            f.delete();

        fileWriter = new FileWriter( f, false);

        return fileWriter;
    }

    public static User[] readUserFile(String pathToFile){

        FileReader fileReader = null;
        BufferedReader bufferedReader = null; 

        String strLine;

        List<User> userList = new ArrayList<>();
        User[] userArray = null;
        
        try {

            fileReader = new FileReader(pathToFile);
            bufferedReader = new BufferedReader(fileReader);

            //example strline
            //userID	name    email   password

            while((strLine = bufferedReader.readLine())!=null) {

                //parse strLine
                String[] words = strLine.split("\t");
                
                if (words.length < 4) {
                    System.out.println("There is a problem in User File Reading phase");
                } 
                else {
                    int userID = Integer.parseInt(words[0]);
                    String name = words[1];
                    String email = words[2];
                    String password = words[3];


                    User user = new User(userID, name, email, password);
                    userList.add(user);
                }

            }//End of while

            //Close bufferedReader
            bufferedReader.close();

            userArray = new User[userList.size()];
            userList.toArray(userArray);

        } 
        catch (IOException e) {
            e.printStackTrace();
        }
        
        return userArray;
    }
    
    public static Song[] readSongFile(String pathToFile) {
        
        FileReader fileReader = null;
        BufferedReader bufferedReader = null; 
        String strLine;
        List<Song> songList = new ArrayList<>();
        Song[] songArray = null;
        
        try {
            fileReader = new FileReader(pathToFile);
            bufferedReader = new BufferedReader(fileReader);

            //example strline
            //userID	name    email   password
            while((strLine = bufferedReader.readLine())!=null){

                //parse strLine
                String[] words = strLine.split("\t");
                
                if (words.length < 6) {
                    System.out.println("There is a problem in Song File Reading phase");
                } 
                else {
                    int songID = Integer.parseInt(words[0]);
                    String name = words[1];
                    String genre = words[2];
                    double rating = Double.parseDouble(words[3]);
                    int artistID = Integer.parseInt(words[4]);
                    int albumID = Integer.parseInt(words[5]);

                    Song song = new Song(songID, name, genre, rating, artistID, albumID);
                    songList.add(song);
                }

            }//End of while

            //Close bufferedReader
            bufferedReader.close();

            songArray = new Song[songList.size()];
            songList.toArray(songArray);

        } 
        catch (IOException e) {
            e.printStackTrace();
        }

        return songArray;

    }
    
    public static Artist[] readArtistFile(String pathToFile){

        FileReader fileReader = null;
        BufferedReader bufferedReader = null; 

        String strLine;

        List<Artist> artistList = new ArrayList<>();
        Artist[] artistArray = null;
        
        try {

            fileReader = new FileReader(pathToFile);
            bufferedReader = new BufferedReader(fileReader);

            //example strline
            //artistID	name

            while((strLine = bufferedReader.readLine())!=null) {

                //parse strLine
                String[] words = strLine.split("\t");
                
                if (words.length < 2) {
                    System.out.println("There is a problem in Artist File Reading phase");
                } 
                else {
                    int artistID = Integer.parseInt(words[0]);
                    String name = words[1];

                    Artist artist = new Artist(artistID, name);
                    artistList.add(artist);
                }

            }//End of while

            //Close bufferedReader
            bufferedReader.close();

            artistArray = new Artist[artistList.size()];
            artistList.toArray(artistArray);

        }
        catch (IOException e) {
            e.printStackTrace();
        }
        
        return artistArray;
    }
    
    public static Album[] readAlbumFile(String pathToFile){

        FileReader fileReader = null;
        BufferedReader bufferedReader = null; 
        String strLine;

        List<Album> albumList = new ArrayList<>();
        Album[] albumArray = null;
        
        try {

            fileReader = new FileReader(pathToFile);
            bufferedReader = new BufferedReader(fileReader);

            //example strline
            //albumID	name    genre   rating  releaseDate artistID
            while((strLine = bufferedReader.readLine())!=null) {

                //parse strLine
                String[] words = strLine.split("\t");
                
                if (words.length < 6) {
                    System.out.println("There is a problem in Album File Reading phase");
                } 
                else {
                    int albumID = Integer.parseInt(words[0]);
                    String name = words[1];
                    String genre = words[2];
                    double rating = Double.parseDouble(words[3]);
                    String releaseDate = words[4];
                    int artistID = Integer.parseInt(words[5]);


                    Album album = new Album(albumID, name, genre, rating, releaseDate, artistID);
                    albumList.add(album);
                }

            }//End of while

            //Close bufferedReader
            bufferedReader.close();

            albumArray = new Album[albumList.size()];
            albumList.toArray(albumArray);

        }
        catch (IOException e) {
            e.printStackTrace();
        }
        
        return albumArray;
    }
    
    public static Listen[] readListenFile(String pathToFile){

        FileReader fileReader = null;
        BufferedReader bufferedReader = null; 
        String strLine;

        List<Listen> listenList = new ArrayList<>();
        Listen[] listenArray = null;
        
        try {

            fileReader = new FileReader(pathToFile);
            bufferedReader = new BufferedReader(fileReader);

            //example strline
            //userID	songID    lastListenTime   listenCount
            while((strLine = bufferedReader.readLine())!=null) {

                //parse strLine
                String[] words = strLine.split("\t");
                
                if (words.length < 4) {
                    System.out.println("There is a problem in Listen File Reading phase");
                } 
                else {
                    int userID = Integer.parseInt(words[0]);
                    int songID = Integer.parseInt(words[1]);
                    
                    SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                    Date date = dateFormat.parse(words[2]);
                    Timestamp lastListenTime = new Timestamp(date.getTime());
                    
                    int listenCount = Integer.parseInt(words[3]);


                    Listen listen = new Listen(userID, songID, lastListenTime, listenCount);
                    listenList.add(listen);
                }

            }//End of while

            //Close bufferedReader
            bufferedReader.close();

            listenArray = new Listen[listenList.size()];
            listenList.toArray(listenArray);

        }  
        catch (IOException | ParseException e) {
            e.printStackTrace();
        }
        
        return listenArray;
    }

}
