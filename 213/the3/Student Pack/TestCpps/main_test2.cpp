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
	std::cout << std::endl << "---------------- phase 0 -----------------" << std::endl << std::endl;
	Article article(7, 3112327, 3);
	std::vector<int> path;
	
	std::cout << std::endl << "---------------- phase 1 -----------------" << std::endl << std::endl;
	
	
	for( int i=0; i<26; i++ )
	{
		std::cout << ( std::string(1,'a'+i)) << " is inserted with probe count " << article.insert(std::string(1,'a'+i),i+1) << std::endl;
		std::cout << ( std::string(1,'a'+i)) << " is removed " << article.remove(std::string(1,'a'+i),1) << std::endl;
	}
	
	std::cout << std::endl << "---------------- phase 2 -----------------" << std::endl << std::endl;
	
	for( int i=0; i<26; i++ )
	{
		std::cout << ( std::string(1,'a'+i)) << " is tried to be gotten " << article.get(std::string(1,'a'+i),1,path) << std::endl;
		ppp( path );
		path.clear();
	}
	
	article.printTable();
	return 0;
}
