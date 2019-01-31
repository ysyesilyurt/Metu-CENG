import java.awt.Color;

import java.util.ArrayList;

import javax.swing.JLabel;

@SuppressWarnings("serial")
public class GUIInternalPrimaryNode extends GUITreeNode 
{
	public GUIInternalPrimaryNode(LibraryNode node)
	{
		super(node);
		
		this.setBackground(Color.lightGray);

		LibraryNodePrimaryIndex castNode = (LibraryNodePrimaryIndex)node;
		
		for(int i = 0; i < castNode.keyCount(); i++)
		{			
			if(i < this.labels.size())
			{
	 			Integer key = castNode.keyAtIndex(i);
	 			
				String keyString = "" + key;
				
				JLabel correspondingLabel = this.labels.get(i);
				
				correspondingLabel.setText(keyString);
				
				correspondingLabel.repaint();
			}
			else
			{
				System.out.println("Key count is greater than label count.");
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
