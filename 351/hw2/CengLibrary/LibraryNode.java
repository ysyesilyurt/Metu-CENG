import java.awt.Color;
public class LibraryNode {
	
	static protected Integer order;
	private LibraryNode parent;
	protected LibraryNodeType type; // Type needs to be set for proper GUI. Check CengNodeType.java. 

	// GUI Accessors - do not modify
	public Integer level;
	public Color color;
	
	public LibraryNode(LibraryNode parent)
	{
		this.parent = parent;
				
		if (parent != null)
		this.level = parent.level + 1;
		else
			this.level = 0;
	}
	
	// Getters-Setters - Do not modify
	public LibraryNode getParent() 
	{
		return parent;
	}
	
	public void setParent(LibraryNode parent) 
	{
		this.parent = parent;
	}
	
	public LibraryNodeType getType()
	{
		return type;
	}
	
	// GUI Methods - Do not modify
	public Color getColor()
	{
		return this.color;
	}

}
