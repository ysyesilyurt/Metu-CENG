import java.awt.EventQueue;
import java.util.ArrayList;
public class CengLibrary {
	
private static Integer order;
	
	private static String fileName;
	private static Integer guiOptions;
	
	private static Boolean guiEnabled;
	
	private static LibraryTree libraryTree;
	private static CengGUI window;

	
	private static Boolean wrapNodes = true;
	private static Boolean packFrame = false;
	
	public static void main(String[] args) throws Exception
	{		
			
		if(args.length <2)
		{
			throw new Exception("Usage : java CengLibrary -order- -guiOptions- (-guiFileName-) ");			
		}		
		
		order = Integer.parseInt(args[0]);
		guiOptions = Integer.parseInt(args[1]);
		
		if(args.length == 2 && guiOptions!=0)
		{
			throw new Exception("In order to use GUI, provide an input file");			
		}
		
		if(guiOptions>0 && guiOptions<4) {
			guiEnabled=true;
			fileName = args[2];
		}
		else if (guiOptions==0) guiEnabled=false;
		else 
		{
			throw new Exception("Invalid GUI Options Value");			
		}		
		
		libraryTree = new LibraryTree(order); 
				
		Integer orderN = 2 * order + 1; // N-based order, for GUI purposes only.

		CengGUI.orderN = orderN;
		
		if(guiEnabled)
		{
			EventQueue.invokeLater(new Runnable()
			{
				public void run() 
				{
					try 
					{
						window = new CengGUI(guiOptions);
						window.show();
					} 
					catch (Exception e) 
					{
						e.printStackTrace();
					}
				}
			});
		}

		/* A way of bulk loading, but not really. Useful for big tree print testing.
		for(int i = 1; i < 100; i++)
		{
			CengBook testBook = new CengBook(i, (i+1)/2, "test", "test");

			CengLibrary.addBook(testBook);
		}
		*/
		
		LibraryParser.startParsingCommandLine();
	}
	
	public static void addBook(CengBook book)
	{
		libraryTree.addBook(book);
		
		if(guiEnabled)
		{
			if(window == null)
			{
				System.out.println("Err: Window is not initialized yet.");
				
				return;
			}
			
			window.modelNeedsUpdate(guiOptions, libraryTree.primaryRoot, libraryTree.secondaryRoot);
		}
	}

	public static void searchBook(Integer key)
	{
		libraryTree.searchBook(key);
	
	}
	
	public static void printPrimary()
	{
		libraryTree.printPrimaryLibrary();
		
		if(guiEnabled)
		{
			window.modelNeedsUpdate(guiOptions, libraryTree.primaryRoot, libraryTree.secondaryRoot);
		}
	}
	
	public static void printSecondary()
	{
		libraryTree.printSecondaryLibrary();
		
		if(guiEnabled)
		{
			window.modelNeedsUpdate(guiOptions, libraryTree.primaryRoot, libraryTree.secondaryRoot);
		}
	}
	
	public static void setPrimaryRoot(LibraryNode newRoot)
	{
		libraryTree.primaryRoot=newRoot;
		
	}
	
	public static void setSecondaryRoot(LibraryNode newRoot)
	{
		libraryTree.secondaryRoot=newRoot;
		
	}
	
	public static String getFilenameToParse()
	{
		return CengLibrary.fileName;
	}
	
	public static Boolean shouldWrap()
	{
		return CengLibrary.wrapNodes;
	}
	
	public static Boolean shouldPack()
	{
		return CengLibrary.packFrame;
	}
}

	

