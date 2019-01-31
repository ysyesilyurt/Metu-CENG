import java.util.ArrayList;

public class LibraryNodeLeaf extends LibraryNode
{
	private ArrayList<CengBook> books;
	
	public LibraryNodeLeaf(LibraryNode parent) 
	{
		super(parent);
		books = new ArrayList<CengBook>();
		this.type = LibraryNodeType.Leaf;
	}
	
	public LibraryNodeLeaf(LibraryNode parent, ArrayList<CengBook> books ) 
	{
		super(parent);
		this.books = books;
		this.type = LibraryNodeType.Leaf;
	}
	
	public void addBook(int index, CengBook book) {
		
		books.add(index, book);
	}
	
	
	// GUI Methods - Do not modify
	public int bookCount()
	{
		return books.size();
	}
	public Integer bookKeyAtIndex(Integer index)
	{
		if(index >= this.bookCount())
		{
			return -1;
		}
		else
		{
			CengBook book = this.books.get(index);
			
			return book.key();
		}
	}
	
	public Integer bookYearAtIndex(Integer index)
	{
		if(index >= this.bookCount())
		{
			return null;
		}
		else
		{
			CengBook book = this.books.get(index);
			
			return book.year();
		}
	}
	
	public CengBook bookAtIndex(Integer index)
	{
		if(index >= this.bookCount())
		{
			return null;
		}
		else
		{
			return this.books.get(index);
		}
	}
	
	public ArrayList<CengBook> getbooks(){
		return books;
	}
	
	
}
