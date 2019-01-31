import java.util.ArrayList;
import java.util.Stack;

@SuppressWarnings("Duplicates")

public class LibraryTree {

	public LibraryNode primaryRoot;		//root of the primary B+ tree
	public LibraryNode secondaryRoot;	//root of the secondary B+ tree
	public LibraryTree(Integer order)
	{
		LibraryNode.order = order;
		primaryRoot = new LibraryNodeLeaf(null);
		primaryRoot.level = 0;
		secondaryRoot = new LibraryNodeLeaf(null);
		secondaryRoot.level = 0;
	}

	// add methods to fill both primary and secondary tree
	public void addBook(CengBook book) {

		// Primary B+Tree
		LibraryNodeLeaf leafToInsert = findIndexPrimary(book.key());
		ArrayList<CengBook> booksOfLeaf = leafToInsert.getbooks();
		Integer indexToInsert = -1;

		for (int i = 0; i < leafToInsert.bookCount() ; i++) {
			if (booksOfLeaf.get(i).key() > book.key())
			{
				indexToInsert = i;
				break;
			}
		}
		if (indexToInsert == -1)
			indexToInsert = leafToInsert.bookCount();

		// Insert book to the tree
		leafToInsert.addBook(indexToInsert, book);

		// if leaf is a root
		if (leafToInsert.getParent() == null) {

			/* if overflow in root (leaf) */
			if (leafToInsert.bookCount() == (2 * LibraryNode.order) + 1)
			{
				LibraryNodePrimaryIndex newRoot = new LibraryNodePrimaryIndex(null);
				LibraryNodeLeaf newNode = new LibraryNodeLeaf(newRoot);
				for (int index = LibraryNode.order, j = 0 ; index < leafToInsert.bookCount() ; index++,j++)
					newNode.addBook(j,leafToInsert.bookAtIndex(index));
				leafToInsert.getbooks().subList(LibraryNode.order, leafToInsert.getbooks().size()).clear();
				leafToInsert.setParent(newRoot);
				newRoot.addKey(0, newNode.bookAtIndex(0).key());
				newRoot.addChild(0, leafToInsert);
				newRoot.addChild(1, newNode);
				primaryRoot = newRoot;
			}
		}

		// leaf is not root
		else {

			/* if overflow in node (leaf) */
			if (leafToInsert.bookCount() == (2 * LibraryNode.order) + 1)
			{
				// Divide node into two and fill them
				LibraryNode parent = leafToInsert.getParent();
				LibraryNodeLeaf newNode = new LibraryNodeLeaf(parent);
				for (int index = LibraryNode.order, j = 0 ; index < leafToInsert.bookCount() ; index++,j++)
					newNode.addBook(j,leafToInsert.bookAtIndex(index));
				// Remove additional items from old leaf node
				leafToInsert.getbooks().subList(LibraryNode.order, leafToInsert.getbooks().size()).clear();
				// leafToInsert.setParent(parent);

				// Add new leaf node to its Internal parent node
				Integer keyToUp = newNode.bookKeyAtIndex(0);
				boolean isSet = false;
				for (int i = 0; i < ((LibraryNodePrimaryIndex)parent).keyCount(); i++) {
					if (((LibraryNodePrimaryIndex)parent).keyAtIndex(i) > keyToUp)
					{
						((LibraryNodePrimaryIndex)parent).addKey(i, keyToUp);
						// parent.addChild(i, leafToInsert);
						((LibraryNodePrimaryIndex)parent).addChild(i + 1, newNode);
						isSet = true;
						break;
					}
				}
				if (!isSet)
				{
					((LibraryNodePrimaryIndex)parent).addKey(keyToUp);
					// ((LibraryNodePrimaryIndex)parent).addChild(((LibraryNodePrimaryIndex)parent).keyCount(), leafToInsert);
					((LibraryNodePrimaryIndex)parent).addChild(newNode);
				}

				// check if overflow exists in leaf's Internal parent node
				LibraryNode nextParent;
				while (((LibraryNodePrimaryIndex)parent).keyCount() == (2 * LibraryNode.order) + 1)
				{
					isSet = false;

					// Fetch parent of the Internal parent node
					nextParent = parent.getParent();

					// if Internal parent node is root
					if (nextParent == null)
					{
						LibraryNodePrimaryIndex newRoot = new LibraryNodePrimaryIndex(null);
						// Create a new internal node
						LibraryNodePrimaryIndex newInternalNode = new LibraryNodePrimaryIndex(newRoot);
						// Fill new internal node
						for (int index = LibraryNode.order + 1, j = 0 ; index < ((LibraryNodePrimaryIndex)parent).keyCount() ; index++,j++)
						{
							// Here, parent refers to old internal node (sibling of newInternalNode)
							newInternalNode.addKey(j,((LibraryNodePrimaryIndex)parent).keyAtIndex(index));
							newInternalNode.addChild(j,((LibraryNodePrimaryIndex)parent).getChildrenAt(index));
							((LibraryNodePrimaryIndex)parent).getChildrenAt(index).setParent(newInternalNode);
						}
						newInternalNode.addChild(newInternalNode.keyCount(),((LibraryNodePrimaryIndex)parent).getChildrenAt(((LibraryNodePrimaryIndex)parent).keyCount()));
						((LibraryNodePrimaryIndex)parent).getChildrenAt(((LibraryNodePrimaryIndex)parent).keyCount()).setParent(newInternalNode);

						keyToUp = ((LibraryNodePrimaryIndex)parent).keyAtIndex(LibraryNode.order);

						// Remove additional items from old internal node
						((LibraryNodePrimaryIndex)parent).getAllKeys().subList(LibraryNode.order, ((LibraryNodePrimaryIndex)parent).getAllKeys().size()).clear();
						((LibraryNodePrimaryIndex)parent).getAllChildren().subList(LibraryNode.order + 1, ((LibraryNodePrimaryIndex)parent).getAllChildren().size()).clear();

						// Bind both Internal parent nodes to the new Root
						newRoot.addKey(0, keyToUp);
						newRoot.addChild(0, parent);
						parent.setParent(newRoot);
						newRoot.addChild(1, newInternalNode);
						primaryRoot = newRoot;
						break;
					}

					// if Internal parent node is an ordinary index node
					else
					{
						// Create a new internal node
						LibraryNodePrimaryIndex newInternalNode = new LibraryNodePrimaryIndex(nextParent);
						// Fill new internal node
						for (int index = LibraryNode.order + 1, j = 0 ; index < ((LibraryNodePrimaryIndex)parent).keyCount() ; index++,j++)
						{
							// Here, parent refers to old internal node (sibling of newInternalNode)
							newInternalNode.addKey(j,((LibraryNodePrimaryIndex)parent).keyAtIndex(index));
							newInternalNode.addChild(j,((LibraryNodePrimaryIndex)parent).getChildrenAt(index));
							((LibraryNodePrimaryIndex)parent).getChildrenAt(index).setParent(newInternalNode);
						}
						newInternalNode.addChild(newInternalNode.keyCount(),((LibraryNodePrimaryIndex)parent).getChildrenAt(((LibraryNodePrimaryIndex)parent).keyCount()));
						((LibraryNodePrimaryIndex)parent).getChildrenAt(((LibraryNodePrimaryIndex)parent).keyCount()).setParent(newInternalNode);

						keyToUp = ((LibraryNodePrimaryIndex)parent).keyAtIndex(LibraryNode.order);

						// Remove additional items from old internal node
						((LibraryNodePrimaryIndex)parent).getAllKeys().subList(LibraryNode.order, ((LibraryNodePrimaryIndex)parent).getAllKeys().size()).clear();
						((LibraryNodePrimaryIndex)parent).getAllChildren().subList(LibraryNode.order + 1, ((LibraryNodePrimaryIndex)parent).getAllChildren().size()).clear();

						// Add new Internal parent node to its Internal parent node
						for (int i = 0; i < ((LibraryNodePrimaryIndex)nextParent).keyCount(); i++) {
							if (((LibraryNodePrimaryIndex)nextParent).keyAtIndex(i) > keyToUp)
							{
								((LibraryNodePrimaryIndex)nextParent).addKey(i, keyToUp);
								((LibraryNodePrimaryIndex)nextParent).addChild(i, parent);
								// Need to set child since we are adding child to start and it was pointing to "parent"
								((LibraryNodePrimaryIndex)nextParent).setChild(i + 1, newInternalNode);
								isSet = true;
								break;
							}
						}
						if (!isSet)
						{

							((LibraryNodePrimaryIndex)nextParent).addKey(keyToUp);
							// No Need to set child since we are adding child to the end and it was pointing nothing
							// ((LibraryNodePrimaryIndex)nextParent).setChild(((LibraryNodePrimaryIndex)nextParent).keyCount(),parent);
							((LibraryNodePrimaryIndex)nextParent).addChild(newInternalNode);
						}
						parent = nextParent;
					}
				}
			}
		}

		// Secondary B+Tree
		LibraryNodeLeaf leafToInsertSec = findIndexSecondary(book.year(),book.key());
		ArrayList<CengBook> booksOfLeafSec = leafToInsertSec.getbooks();
		Integer indexToInsertSec = -1;

		for (int i = 0; i < leafToInsertSec.bookCount() ; i++) {
			// if years are equal
			if (booksOfLeafSec.get(i).year() == book.year())
			{
				// greater or equal to keys are to the right
				if (booksOfLeafSec.get(i).key() >= book.key())
				{
					indexToInsertSec = i;
					break;
				}
				// lower keys are to the left
				else
				{
					if (i != 0)
					{
						indexToInsertSec = i - 1;
						break;
					}
					else
					{
						indexToInsertSec = i;
						break;
					}
				}
			}
			// if entry can be sorted according to year
			else if (booksOfLeafSec.get(i).year() > book.year())
			{
				indexToInsertSec = i;
				break;
			}
		}

		if (indexToInsertSec == -1)
			indexToInsertSec = leafToInsertSec.bookCount();

		// Insert book to the tree
		leafToInsertSec.addBook(indexToInsertSec, book);

		// if leaf is a root
		if (leafToInsertSec.getParent() == null) {

			/* if overflow in root (leaf) */
			if (leafToInsertSec.bookCount() == (2 * LibraryNode.order) + 1)
			{
				LibraryNodeSecondaryIndex newRoot = new LibraryNodeSecondaryIndex(null);
				LibraryNodeLeaf newNode = new LibraryNodeLeaf(newRoot);
				for (int index = LibraryNode.order, j = 0 ; index < leafToInsertSec.bookCount() ; index++,j++)
					newNode.addBook(j,leafToInsertSec.bookAtIndex(index));
				leafToInsertSec.getbooks().subList(LibraryNode.order, leafToInsertSec.getbooks().size()).clear();
				leafToInsertSec.setParent(newRoot);
				newRoot.addYear(0, newNode.bookAtIndex(0).year());
				newRoot.addKey(0, newNode.bookAtIndex(0).key());
				newRoot.addChild(0, leafToInsertSec);
				newRoot.addChild(1, newNode);
				secondaryRoot = newRoot;
			}
		}

		// leaf is not root
		else {

			/* if overflow in node (leaf) */
			if (leafToInsertSec.bookCount() == (2 * LibraryNode.order) + 1)
			{
				// Divide node into two and fill them
				LibraryNode parent = leafToInsertSec.getParent();
				LibraryNodeLeaf newNode = new LibraryNodeLeaf(parent);
				for (int index = LibraryNode.order, j = 0 ; index < leafToInsertSec.bookCount() ; index++,j++)
					newNode.addBook(j,leafToInsertSec.bookAtIndex(index));
				// Remove additional items from old leaf node
				leafToInsertSec.getbooks().subList(LibraryNode.order, leafToInsertSec.getbooks().size()).clear();
				// leafToInsertSec.setParent(parent);

				// Add new leaf node to its Internal parent node
				Integer yearToUp = newNode.bookYearAtIndex(0);
				Integer keyToUp = newNode.bookKeyAtIndex(0);
				boolean isSet = false;
				for (int i = 0; i < ((LibraryNodeSecondaryIndex)parent).keyCount(); i++) {
					if (((LibraryNodeSecondaryIndex)parent).yearAtIndex(i) == yearToUp)
					{
						// greater or equal to keys are to the right
						if (((LibraryNodeSecondaryIndex)parent).keyAtIndex(i) >= keyToUp)
						{
							((LibraryNodeSecondaryIndex)parent).addYear(i, yearToUp);
							((LibraryNodeSecondaryIndex)parent).addKey(i, keyToUp);
							// parent.addChild(i, leafToInsertSec);
							((LibraryNodeSecondaryIndex)parent).addChild(i + 1, newNode);
							isSet = true;
							break;
						}
						// lower keys are to the left
						else
						{
							if (i != 0)
							{
								((LibraryNodeSecondaryIndex)parent).addYear(i-1, yearToUp);
								((LibraryNodeSecondaryIndex)parent).addKey(i-1, keyToUp);
								// parent.addChild(i, leafToInsertSec);
								((LibraryNodeSecondaryIndex)parent).addChild(i, newNode);
								isSet = true;
								break;
							}
							else
							{
								((LibraryNodeSecondaryIndex)parent).addYear(i, yearToUp);
								((LibraryNodeSecondaryIndex)parent).addKey(i, keyToUp);
								// parent.addChild(i, leafToInsertSec);
								((LibraryNodeSecondaryIndex)parent).addChild(i + 1, newNode);
								isSet = true;
								break;
							}
						}
					}
					// if entry can be sorted according to year
					else if (((LibraryNodeSecondaryIndex)parent).yearAtIndex(i) > yearToUp)
					{
						((LibraryNodeSecondaryIndex)parent).addYear(i, yearToUp);
						((LibraryNodeSecondaryIndex)parent).addKey(i, keyToUp);
						// parent.addChild(i, leafToInsertSec);
						((LibraryNodeSecondaryIndex)parent).addChild(i + 1, newNode);
						isSet = true;
						break;
					}
				}
				if (!isSet)
				{
					((LibraryNodeSecondaryIndex)parent).addYear(yearToUp);
					((LibraryNodeSecondaryIndex)parent).addKey(keyToUp);
					// ((LibraryNodeSecondaryIndex)parent).addChild(((LibraryNodeSecondaryIndex)parent).keyCount(), leafToInsertSec);
					((LibraryNodeSecondaryIndex)parent).addChild(newNode);
				}

				// check if overflow exists in leaf's Internal parent node
				LibraryNode nextParent;
				while (((LibraryNodeSecondaryIndex)parent).keyCount() == (2 * LibraryNode.order) + 1)
				{
					isSet = false;

					// Fetch parent of the Internal parent node
					nextParent = parent.getParent();

					// if Internal parent node is root
					if (nextParent == null)
					{
						LibraryNodeSecondaryIndex newRoot = new LibraryNodeSecondaryIndex(null);
						// Create a new internal node
						LibraryNodeSecondaryIndex newInternalNode = new LibraryNodeSecondaryIndex(newRoot);
						// Fill new internal node
						for (int index = LibraryNode.order + 1, j = 0 ; index < ((LibraryNodeSecondaryIndex)parent).keyCount() ; index++,j++)
						{
							// Here, parent refers to old internal node (sibling of newInternalNode)
							newInternalNode.addYear(j,((LibraryNodeSecondaryIndex)parent).yearAtIndex(index));
							newInternalNode.addKey(j,((LibraryNodeSecondaryIndex)parent).keyAtIndex(index));
							newInternalNode.addChild(j,((LibraryNodeSecondaryIndex)parent).getChildrenAt(index));
							((LibraryNodeSecondaryIndex)parent).getChildrenAt(index).setParent(newInternalNode);
						}
						newInternalNode.addChild(newInternalNode.keyCount(),((LibraryNodeSecondaryIndex)parent).getChildrenAt(((LibraryNodeSecondaryIndex)parent).keyCount()));
						((LibraryNodeSecondaryIndex)parent).getChildrenAt(((LibraryNodeSecondaryIndex)parent).keyCount()).setParent(newInternalNode);

						yearToUp = ((LibraryNodeSecondaryIndex)parent).yearAtIndex(LibraryNode.order);
						keyToUp = ((LibraryNodeSecondaryIndex)parent).keyAtIndex(LibraryNode.order);

						// Remove additional items from old internal node
						((LibraryNodeSecondaryIndex)parent).getAllYears().subList(LibraryNode.order, ((LibraryNodeSecondaryIndex)parent).getAllYears().size()).clear();
						((LibraryNodeSecondaryIndex)parent).getAllKeys().subList(LibraryNode.order, ((LibraryNodeSecondaryIndex)parent).getAllKeys().size()).clear();
						((LibraryNodeSecondaryIndex)parent).getAllChildren().subList(LibraryNode.order + 1, ((LibraryNodeSecondaryIndex)parent).getAllChildren().size()).clear();

						// Bind both Internal parent nodes to the new Root
						newRoot.addYear(0, yearToUp);
						newRoot.addKey(0, keyToUp);
						newRoot.addChild(0, parent);
						parent.setParent(newRoot);
						newRoot.addChild(1, newInternalNode);
						secondaryRoot = newRoot;
						break;
					}

					// if Internal parent node is an ordinary index node
					else
					{
						// Create a new internal node
						LibraryNodeSecondaryIndex newInternalNode = new LibraryNodeSecondaryIndex(nextParent);
						// Fill new internal node
						for (int index = LibraryNode.order + 1, j = 0 ; index < ((LibraryNodeSecondaryIndex)parent).keyCount() ; index++,j++)
						{
							// Here, parent refers to old internal node (sibling of newInternalNode)
							newInternalNode.addYear(j,((LibraryNodeSecondaryIndex)parent).yearAtIndex(index));
							newInternalNode.addKey(j,((LibraryNodeSecondaryIndex)parent).keyAtIndex(index));
							newInternalNode.addChild(j,((LibraryNodeSecondaryIndex)parent).getChildrenAt(index));
							((LibraryNodeSecondaryIndex)parent).getChildrenAt(index).setParent(newInternalNode);
						}
						newInternalNode.addChild(newInternalNode.keyCount(),((LibraryNodeSecondaryIndex)parent).getChildrenAt(((LibraryNodeSecondaryIndex)parent).keyCount()));
						((LibraryNodeSecondaryIndex)parent).getChildrenAt(((LibraryNodeSecondaryIndex)parent).keyCount()).setParent(newInternalNode);

						yearToUp = ((LibraryNodeSecondaryIndex)parent).yearAtIndex(LibraryNode.order);
						keyToUp = ((LibraryNodeSecondaryIndex)parent).keyAtIndex(LibraryNode.order);

						// Remove additional items from old internal node
						((LibraryNodeSecondaryIndex)parent).getAllYears().subList(LibraryNode.order, ((LibraryNodeSecondaryIndex)parent).getAllYears().size()).clear();
						((LibraryNodeSecondaryIndex)parent).getAllKeys().subList(LibraryNode.order, ((LibraryNodeSecondaryIndex)parent).getAllKeys().size()).clear();
						((LibraryNodeSecondaryIndex)parent).getAllChildren().subList(LibraryNode.order + 1, ((LibraryNodeSecondaryIndex)parent).getAllChildren().size()).clear();

						// Add new Internal parent node to its Internal parent node
						for (int i = 0; i < ((LibraryNodeSecondaryIndex)nextParent).keyCount(); i++) {
							// if years are equal
							if (((LibraryNodeSecondaryIndex)nextParent).yearAtIndex(i) == yearToUp)
							{
								// greater or equal to keys are to the right
								if (((LibraryNodeSecondaryIndex)nextParent).keyAtIndex(i) >= keyToUp)
								{
									((LibraryNodeSecondaryIndex)nextParent).addYear(i, yearToUp);
									((LibraryNodeSecondaryIndex)nextParent).addKey(i, keyToUp);
									((LibraryNodeSecondaryIndex)nextParent).addChild(i, parent);
									((LibraryNodeSecondaryIndex)nextParent).setChild(i + 1, newInternalNode);
									isSet = true;
									break;
								}
								// lower keys are to the left
								else
								{
									if (i != 0)
									{
										((LibraryNodeSecondaryIndex)nextParent).addYear(i - 1, yearToUp);
										((LibraryNodeSecondaryIndex)nextParent).addKey(i - 1, keyToUp);
										((LibraryNodeSecondaryIndex)nextParent).addChild(i - 1, parent);
										((LibraryNodeSecondaryIndex)nextParent).setChild(i, newInternalNode);
										isSet = true;
										break;
									}
									else
									{
										((LibraryNodeSecondaryIndex)nextParent).addYear(i, yearToUp);
										((LibraryNodeSecondaryIndex)nextParent).addKey(i, keyToUp);
										((LibraryNodeSecondaryIndex)nextParent).addChild(i, parent);
										((LibraryNodeSecondaryIndex)nextParent).setChild(i + 1, newInternalNode);
										isSet = true;
										break;
									}
								}
							}
							// if entry can be sorted according to year
							else if (((LibraryNodeSecondaryIndex)nextParent).yearAtIndex(i) > yearToUp)
							{
								((LibraryNodeSecondaryIndex)nextParent).addYear(i, yearToUp);
								((LibraryNodeSecondaryIndex)nextParent).addKey(i, keyToUp);
								((LibraryNodeSecondaryIndex)nextParent).addChild(i, parent);
								// Need to set child since we are adding child to start and it was pointing to "parent"
								((LibraryNodeSecondaryIndex)nextParent).setChild(i + 1, newInternalNode);
								isSet = true;
								break;
							}
						}
						if (!isSet)
						{
							((LibraryNodeSecondaryIndex)nextParent).addYear(yearToUp);
							((LibraryNodeSecondaryIndex)nextParent).addKey(keyToUp);
							// No Need to set child since we are adding child to the end and it was pointing nothing
							// ((LibraryNodeSecondaryIndex)nextParent).setChild(((LibraryNodeSecondaryIndex)nextParent).keyCount(),parent);
							((LibraryNodeSecondaryIndex)nextParent).addChild(newInternalNode);
						}
						parent = nextParent;
					}
				}
			}
		}
	}

	public CengBook searchBook(Integer key) {

		LibraryNode node = primaryRoot;
		boolean cont;

		while (node.getType() == LibraryNodeType.Internal)
		{
			System.out.println("<index>");
			for (int i = 0; i < ((LibraryNodePrimaryIndex) node).keyCount(); i++) {
				System.out.println(((LibraryNodePrimaryIndex) node).keyAtIndex(i));
			}
			System.out.println("</index>");
			cont = false;
			for (int i = 0; i < ((LibraryNodePrimaryIndex) node).keyCount() ; i++) {
				// if ith key is greater than our key, then i is the index of next child
				if (((LibraryNodePrimaryIndex) node).keyAtIndex(i) > key)
				{
					node = ((LibraryNodePrimaryIndex) node).getChildrenAt(i);
					cont = true;
					break;
				}
			}
			if (!cont)
				node = ((LibraryNodePrimaryIndex) node).getChildrenAt(((LibraryNodePrimaryIndex) node).keyCount());
		}
		for (int i = 0; i < ((LibraryNodeLeaf) node).bookCount(); i++) {
			if (((LibraryNodeLeaf) node).bookKeyAtIndex(i) == key)
			{
				System.out.println("<data>");
				System.out.print("<record>");
				System.out.print(((LibraryNodeLeaf) node).bookAtIndex(i).key());
				System.out.print("|");
				System.out.print(((LibraryNodeLeaf) node).bookAtIndex(i).year());
				System.out.print("|");
				System.out.print(((LibraryNodeLeaf) node).bookAtIndex(i).name());
				System.out.print("|");
				System.out.print(((LibraryNodeLeaf) node).bookAtIndex(i).author());
				System.out.print("</record>\n");
				System.out.println("</data>");
				return (((LibraryNodeLeaf) node).bookAtIndex(i));
			}
		}
		System.out.print("No match for ");
		System.out.println(key);
		return null;
	}

	public void printPrimaryLibrary() {

		Stack<LibraryNode> itemStack = new Stack<LibraryNode>();
		LibraryNode pTreeRoot = primaryRoot;

		itemStack.add(pTreeRoot);

		while (!itemStack.isEmpty())
		{
			LibraryNode node = itemStack.pop();
			// if node is an internal node
			if (node.getType() == LibraryNodeType.Internal)
			{
				// push all children to stack, from left to right
				ArrayList<LibraryNode> children = ((LibraryNodePrimaryIndex) node).getAllChildren();
				for (int i = children.size() - 1; i >= 0 ; i--)
					itemStack.add(children.get(i));

				// print keys all keys on this internal node
				System.out.println("<index>");
				for (int i = 0; i < ((LibraryNodePrimaryIndex) node).keyCount() ; i++)
					System.out.println(((LibraryNodePrimaryIndex) node).keyAtIndex(i));
				System.out.println("</index>");
			}

			else if (node.getType() == LibraryNodeType.Leaf)
			{
				// print all books, from left to right
				System.out.println("<data>");
				for (int i = 0; i < ((LibraryNodeLeaf) node).bookCount() ; i++)
				{
					System.out.print("<record>");
					System.out.print(((LibraryNodeLeaf) node).bookAtIndex(i).key());
					System.out.print("|");
					System.out.print(((LibraryNodeLeaf) node).bookAtIndex(i).year());
					System.out.print("|");
					System.out.print(((LibraryNodeLeaf) node).bookAtIndex(i).name());
					System.out.print("|");
					System.out.print(((LibraryNodeLeaf) node).bookAtIndex(i).author());
					System.out.print("</record>\n");
				}
				System.out.println("</data>");
			}
		}

	}

	public void printSecondaryLibrary() {

		Stack<LibraryNode> itemStack = new Stack<LibraryNode>();
		LibraryNode pTreeRoot = secondaryRoot;

		itemStack.add(pTreeRoot);

		while (!itemStack.isEmpty())
		{
			LibraryNode node = itemStack.pop();
			// if node is an internal node
			if (node.getType() == LibraryNodeType.Internal)
			{
				// push all children to stack, from left to right
				ArrayList<LibraryNode> children = ((LibraryNodeSecondaryIndex) node).getAllChildren();
				for (int i = children.size() - 1; i >= 0 ; i--)
					itemStack.add(children.get(i));

				// print keys all keys on this internal node
				System.out.println("<index>");
				for (int i = 0; i < ((LibraryNodeSecondaryIndex) node).keyCount() ; i++)
				{
					System.out.print(((LibraryNodeSecondaryIndex) node).yearAtIndex(i));
					System.out.print("|");
					System.out.print(((LibraryNodeSecondaryIndex) node).keyAtIndex(i));
					System.out.print("\n");
				}
				System.out.println("</index>");
			}

			else if (node.getType() == LibraryNodeType.Leaf)
			{
				// print all books, from left to right
				System.out.println("<data>");
				for (int i = 0; i < ((LibraryNodeLeaf) node).bookCount() ; i++)
				{
					System.out.print("<record>");
					System.out.print(((LibraryNodeLeaf) node).bookAtIndex(i).key());
					System.out.print("|");
					System.out.print(((LibraryNodeLeaf) node).bookAtIndex(i).year());
					System.out.print("|");
					System.out.print(((LibraryNodeLeaf) node).bookAtIndex(i).name());
					System.out.print("|");
					System.out.print(((LibraryNodeLeaf) node).bookAtIndex(i).author());
					System.out.print("</record>\n");
				}
				System.out.println("</data>");
			}
		}
	}

	public LibraryNodeLeaf findIndexPrimary(Integer key) {

		LibraryNode node = primaryRoot;
		boolean cont;

		while (node.getType() == LibraryNodeType.Internal)
		{
			cont = false;
			for (int i = 0; i < ((LibraryNodePrimaryIndex) node).keyCount() ; i++) {
				// if ith key is greater than our key, then i is the index of next child
				if (((LibraryNodePrimaryIndex) node).keyAtIndex(i) > key)
				{
					node = ((LibraryNodePrimaryIndex) node).getChildrenAt(i);
					cont = true;
					break;
				}
			}
			if (!cont)
				node = ((LibraryNodePrimaryIndex) node).getChildrenAt(((LibraryNodePrimaryIndex) node).keyCount());
		}

		return ((LibraryNodeLeaf) node);
	}

	public LibraryNodeLeaf findIndexSecondary(Integer year, Integer key) {

		LibraryNode node = secondaryRoot;
		boolean cont;

		while (node.getType() == LibraryNodeType.Internal)
		{
			cont = false;
			for (int i = 0; i < ((LibraryNodeSecondaryIndex) node).keyCount() ; i++) {
				// if ith key is greater than our key, then i is the index of next child
				if (((LibraryNodeSecondaryIndex) node).yearAtIndex(i) == year)
				{
					if (((LibraryNodeSecondaryIndex) node).keyAtIndex(i) >= key)
					{
						node = ((LibraryNodeSecondaryIndex) node).getChildrenAt(i);
						cont = true;
						break;
					}
					else
						if (i != 0)
						{
							node = ((LibraryNodeSecondaryIndex) node).getChildrenAt(i - 1);
							cont = true;
							break;
						}
						else
						{
							node = ((LibraryNodeSecondaryIndex) node).getChildrenAt(i);
							cont = true;
							break;
						}
				}
				else if (((LibraryNodeSecondaryIndex) node).yearAtIndex(i) > year)
				{
					node = ((LibraryNodeSecondaryIndex) node).getChildrenAt(i);
					cont = true;
					break;
				}
			}

			if (!cont)
				node = ((LibraryNodeSecondaryIndex) node).getChildrenAt(((LibraryNodeSecondaryIndex) node).keyCount());
		}

		return ((LibraryNodeLeaf) node);
	}

}
