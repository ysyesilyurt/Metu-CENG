import java.awt.Color;

import java.util.ArrayList;

import javax.swing.JLabel;

@SuppressWarnings("serial")
public class GUIInternalSecondaryNode extends GUITreeNode 
{
	public GUIInternalSecondaryNode(LibraryNode node)
	{
		super(node);
		
		this.setBackground(Color.white);

		LibraryNodeSecondaryIndex castNode = (LibraryNodeSecondaryIndex)node;
		
		for(int i = 0; i < castNode.keyCount(); i++)
		{			
			if(i < this.labels.size())
			{
	 			Integer year = castNode.yearAtIndex(i);
	 			Integer key = castNode.keyAtIndex(i);
				String yearString = "" + year + "|" + key;
				
				JLabel correspondingLabel = this.labels.get(i);
				
				correspondingLabel.setText(yearString);
				
				correspondingLabel.repaint();
			}
			else
			{
				System.out.println("Year count is greater than label count.");
			}
		}
		
		ArrayList<LibraryNode> allChildren = castNode.getAllChildren();
		
		if(allChildren.size() > this.paddings.size())
		{
			System.out.println("Children count is greater than padding count.");
		}
		
		for(int i = 0; i < this.paddings.size(); i++)
		{
			if(i < allChildren.size())
			{
				LibraryNode child = allChildren.get(i);
				
				this.paddings.get(i).setBackground(Color.BLUE);				
			}
		}
		
		this.repaint();
	}
}
