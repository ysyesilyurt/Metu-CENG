public class CengBook 
{
	private Integer key;
	
	private String name;
	private String author;
	private Integer year;
	
	public CengBook(Integer key, String name, String author, Integer year)
	{
		this.key = key;
		this.name = name;
		this.author = author;
		this.year = year;
	}
	
	// Getters
	
	public Integer key()
	{
		return key;
	}
	public String name()
	{
		return name;
	}
	public String author()
	{
		return author;
	}
	public Integer year()
	{
		return year;
	}
	
	// GUI method - do not modify
	public String fullName()
	{
		return "" + key() + "|" + year() + "|" + name() + "|" + author();
	}
	
	// DO NOT ADD SETTERS
}
