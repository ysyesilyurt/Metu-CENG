#include "Article.h"

int main()
{
	std::cout << std::endl << "---------------- phase 1 -----------------" << std::endl << std::endl;
	Article article(7, 3112327, 3);
	std::vector<int> path;
    article.printTable();
	
	std::cout << std::endl << "---------------- phase 2 -----------------" << std::endl << std::endl;
	
	
	for( int i=0; i<26; i++ )
		std::cout << ( std::string(1,'a'+i)) << " is inserted with probe count " << article.insert(std::string(1,'a'+i),i+1) << std::endl;
    std::cout << ( std::string(1,'a')) << " is inserted with probe count " << article.insert(std::string(1,'a'),27) << std::endl;
    
    std::cout << "Table has a load factor of " << article.getLoadFactor() << std::endl << std::endl;
	article.printTable();

	return 0;
}
