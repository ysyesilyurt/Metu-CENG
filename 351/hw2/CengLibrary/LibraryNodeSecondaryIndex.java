import java.util.ArrayList;

public class LibraryNodeSecondaryIndex extends LibraryNode
{
	private ArrayList<Integer> keys;
	private ArrayList<Integer> years;
	private ArrayList<LibraryNode> children;	
	
	public LibraryNodeSecondaryIndex(LibraryNode parent) 
	{
		super(parent);
		keys = new ArrayList<Integer>();
		years = new ArrayList<Integer>();
		children = new ArrayList<LibraryNode>();
		this.type = LibraryNodeType.Internal;
	}
	
	public LibraryNodeSecondaryIndex(LibraryNode parent, ArrayList<Integer> years, ArrayList<Integer> keys, ArrayList<LibraryNode> children) 
	{
		super(parent);
		this.years = years;
		this.keys = keys;
		this.children = children;
		this.type = LibraryNodeType.Internal;
	}
	
	// GUI Methods - Do not modify
	public ArrayList<LibraryNode> getAllChildren()
	{
		return this.children;
	}
	
	public LibraryNode getChildrenAt(Integer index) {
		
		return this.children.get(index);
	}
	
	public Integer keyCount()
	{
		return this.keys.size();
	}
	public Integer keyAtIndex(Integer index)
	{
		if(index >= this.keyCount() || index < 0)
		{
			return -1;
		}
		else
		{
			return this.keys.get(index);			
		}
	}
	
	public Integer yearAtIndex(Integer index)
	{
		if(index >= this.keyCount() || index < 0)
		{
			return -1;
		}
		else
		{
			return this.years.get(index);			
		}
	}
	
	
	// Extra functions if needed

	public ArrayList<Integer> getAllKeys()
	{
		return this.keys;
	}

	public ArrayList<Integer> getAllYears()
	{
		return this.years;
	}

	public void addKey(Integer index, Integer key)
	{
		keys.add(index,key);
	}

	public void addKey(Integer key)
	{
		keys.add(key);
	}

	public void addChild(Integer index, LibraryNode child)
	{
		children.add(index,child);
	}

	public void addChild(LibraryNode child)
	{
		children.add(child);
	}

	public void addYear(Integer index, Integer year)
	{
		years.add(index,year);
	}

	public void addYear(Integer year)
	{
		years.add(year);
	}

	public void setKey(Integer index, Integer key)
	{
		keys.set(index,key);
	}

	public void setChild(Integer index, LibraryNode child)
	{
		children.set(index,child);
	}

	public void setYear(Integer index, Integer year)
	{
		years.set(index,year);
	}

}
