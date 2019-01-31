#include "Article.h"

int main()
{
	Article article(7, 3112327, 3);
	
	std::cout << "----------------" << std::endl;
	article.getAllWordsFromFile("test3.txt");
	std::cout << "----------------" << std::endl;
	article.printTable();
	std::cout << "----------------" << std::endl;
	std::cout << article.getLoadFactor() << std::endl;

	return 0;
}
