import java.awt.Color;

import javax.swing.JLabel;

@SuppressWarnings("serial")
public class GUISecondaryLeafNode extends GUITreeNode
{	
	public GUISecondaryLeafNode(LibraryNode node)
	{		
		super(node);

		this.setBackground(Color.pink);

		LibraryNodeLeaf castNode = (LibraryNodeLeaf)node;
		
		for(int i = 0; i < castNode.bookCount(); i++)
		{
			if(i >= this.labels.size())
			{
				System.out.println("Book count is greater than label count.");
				
				return;
			}
			
 			Integer year = castNode.bookYearAtIndex(i);
			Integer key = castNode.bookKeyAtIndex(i); 			
			String yearString = "" + year + "|" + key;
			
			JLabel correspondingLabel = this.labels.get(i);
			
			correspondingLabel.setText(yearString);
			correspondingLabel.repaint();
		}
	}
	
	
}
