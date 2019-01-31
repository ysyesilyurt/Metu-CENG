#include "Article.h"

void ppp( std::vector<int> & path )
{
	std::cout<<"Path : ";
	for( int i=0; i<path.size(); i++ )
		std::cout<< path[i] << "->";
	std::cout<< "End" << std::endl;
}

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
	
	
	std::cout << std::endl << "---------------- phase 3 -----------------" << std::endl << std::endl;
	
	for( int i=0; i<26; i++ )
	{
		std::cout << "Trying to get \"" << ( std::string(1,'a'+i)) << "\", 1th occurance: " << article.get(( std::string(1,'a'+i)),1,path) << std::endl;
		std::cout << "Length of path for previous query: " << path.size() << std::endl;
		ppp(path);
		path.clear();
	}

	std::cout << "Trying to get \"" << ( std::string(1,'a')) << "\", 2th occurance: " << article.get(( std::string(1,'a')),2,path) << std::endl;
	std::cout << "Length of path for previous query: " << path.size() << std::endl;
	ppp(path);
	path.clear();

	std::cout << std::endl << "---------------- phase 4 -----------------" << std::endl << std::endl;
	
	for( int i=25; i>=0; i-- )
	{
		std::cout << "Removing \"" << ( std::string(1,'a' + i)) << "\", 1st occurance: " << article.remove(( std::string(1,'a' + i)),1) << std::endl;
		
		std::cout << "Trying to get \"" << ( std::string(1,'a' + i)) << "\", 1st occurance: " << article.get(( std::string(1,'a' + i)),1,path) << std::endl;
		std::cout << "Length of path for previous query : " << path.size() << std::endl;
		ppp(path);
		path.clear();
	}

	std::cout << "Trying to get \"" << ( std::string(1,'a')) << "\", 3rd occurance: " << article.get(( std::string(1,'a')),3,path) << std::endl;
	std::cout << "Removing \"" << ( std::string(1,'a')) << "\", 1st occurance: " << article.remove(( std::string(1,'a')),1) << std::endl; 
	std::cout << "Removing \"" << ( std::string(1,'a')) << "\", 1st occurance: " << article.remove(( std::string(1,'a')),1) << std::endl; 

	article.printTable();
	return 0;
}
