import java.awt.Color;

import javax.swing.JLabel;

@SuppressWarnings("serial")
public class GUIPrimaryLeafNode extends GUITreeNode
{	
	public GUIPrimaryLeafNode(LibraryNode node)
	{		
		super(node);

		this.setBackground(Color.green);

		LibraryNodeLeaf castNode = (LibraryNodeLeaf)node;
		
		for(int i = 0; i < castNode.bookCount(); i++)
		{
			if(i >= this.labels.size())
			{
				System.out.println("Book count is greater than label count.");
				
				return;
			}
			
 			Integer key = castNode.bookKeyAtIndex(i);
			 			
			String keyString = "" + key;
			
			JLabel correspondingLabel = this.labels.get(i);
			
			correspondingLabel.setText(keyString);
			correspondingLabel.repaint();
		}
	}
	
	
}
