import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Scanner;

public class LibraryParser 
{	
	public static ArrayList<CengBook> parseBooksFromFile(String filename) 
	{
		ArrayList<CengBook> bookList = new ArrayList<CengBook>();
		Scanner s = null;;
		try {
			s = new Scanner(new File(filename));
		} catch (FileNotFoundException e1) {
			
			e1.printStackTrace();
		}
		String myLine = null;
			while ( s.hasNextLine())
			{
			myLine = s.nextLine();
			String[] array = myLine.split("[|]");
			 Integer key = Integer.parseInt(array[0]);
			 Integer year = Integer.parseInt(array[1]);
			 String name = array[2];
			 String author = array[3];
			 
			 
			 bookList.add(new CengBook(key,name,author,year));
			// Parsing the input file in order to use GUI tables.
			
			}
		return bookList;
	}
	
	public static void startParsingCommandLine() throws IOException
	{
		@SuppressWarnings("resource")
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		boolean running = true;
		String inpLine = null;
		while(running){
			inpLine = reader.readLine();
			String[] array = inpLine.split("[|]");
			String command = array[0];
			if(command.equalsIgnoreCase("add")){
				Integer key = Integer.parseInt(array[1]);
				Integer year = Integer.parseInt(array[2]);
				String name = array[3];
				String author = array[4];
				
				CengLibrary.addBook(new CengBook(key,name,author,year));
			}
			else if(command.equalsIgnoreCase("quit")){
				running = false;
			}
			else if(command.equalsIgnoreCase("search")){
				int key = Integer.parseInt(array[1]);
				CengLibrary.searchBook(key);
			}
			else if(command.equalsIgnoreCase("print1")){
				CengLibrary.printPrimary();
			}
			else if(command.equalsIgnoreCase("print2")){
				CengLibrary.printSecondary();
			}
			
		}
		
		// 
		// There are 5 commands:
		// 1) quit : End the application. Print nothing, call nothing, just terminate.
		// 2) add : Parse and create the book, calls CengLibrary.addBook(newBook)
		// 3) search : Parse the key in primary tree, calls CengLibrary.searchBook(key)
		// 4) print1 : Print the whole primary tree, calls CengLibrary.printPrimary()
		// 4) print2 : Print the whole secondary tree, calls CengLibrary.printSecondary()

		// Commands (quit, add, search1, print1, print2) are case-insensitive.
	}
}