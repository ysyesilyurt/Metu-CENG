#include "Article.h"

/*###############################
#   DO NOT MODIFY THIS FILE     #
# THIS FILE CONSISTS OF HELPER  #
# FUNCTIONS FOR YOUR TASKS AND  #
# A PRINT FUNCTION THAT CREATES #
#  A TABLE WHICH HAS YOUR HASH  #
#         TABLE DATA            #
###############################*/

/* Checks if integer n is prime or not */
bool Article::isPrime( int n ) const
{
    if( n%2 == 0 ) return false;
    for( int i=3; i*i<=n; i+=2 )
        if( n%i == 0 )
            return false;
    return true;
}
/* Finds the first prime number just after
    integer n */
int Article::nextPrimeAfter( int n ) const
{
    for( int i=n+1; ; i++ )
        if( isPrime(i) )
            return i;
}

/* Finds the first prime number just before
    integer n */
int Article::firstPrimeBefore (int n) const
{
    for( int i=n-1; ; i-- )
        if( isPrime(i) )
            return i;
}

/* Converts given string to an integer that 
	is used in hashing functions */
int Article::convertStrToInt( const std::string &key ) const
{
	int tableIndex = 0, convertedKey = 0;
	int length = key.length();
	
	int r=length-1,l=0;
	int m = (l+r)/2;
	convertedKey += ( ((0xfe)/26)*(((unsigned int)key[l])-'a') + 1 );
	convertedKey += ( ((0xfe)/26)*(((unsigned int)key[r])-'a') + 1 )*37;
	convertedKey += ( ((0xfe)/26)*(((unsigned int)key[m])-'a') + 1 )*37*37;
	
	return convertedKey;
}

/* Prints hash table data in a table shaped
     format */
void Article::printTable() const
{
    int nameMaxLength = 0, temp = 0;
    int maxIndex = 0, maxIndexLength = 0;
    int blankDiff = 0, indexLength = 0;
    
    for (int i = 0; i < table_size; i++)
    {
        if (table[i].first.length() > nameMaxLength)
            nameMaxLength = table[i].first.length();
        if (table[i].second > maxIndex)
            maxIndex = table[i].second;
    }
    if (maxIndex <= 0)
    {
    	nameMaxLength = 5;
    	maxIndex = 999;
    }
    temp = maxIndex;
    while (temp != 0)
    {
        temp /= 10;
        maxIndexLength++;
    }
    std::cout << "|";
    for (int i = 0; i < nameMaxLength + maxIndexLength + 5; ++i)
        std::cout << "-";
    if (maxIndexLength < 2)
        std::cout << "-";
    std::cout << "|" << std::endl;
    
    std::cout << "| ";
    for (int i = 0; i < (nameMaxLength - 1)/2; ++i)
        std::cout << " ";
    std::cout << "K";
    for (int i = 0; i < (nameMaxLength - 1)/2; ++i)
        std::cout << " ";
    if ((nameMaxLength - 1) %2 != 0)
        std::cout << " ";
    std::cout << " | ";
    for (int i = 0; i < (maxIndexLength - 1)/2; ++i)
        std::cout << " ";
    if ((maxIndexLength - 1) % 2 != 0)
        std::cout << " ";
    std::cout << "I";
    if (maxIndexLength < 2)
        std::cout << " ";
    for (int i = 0; i < (maxIndexLength - 1)/2; ++i)
        std::cout << " ";
    std::cout << " |" << std::endl;
    
    std::cout << "|";
    for (int i = 0; i < nameMaxLength + maxIndexLength + 5; ++i)
        std::cout << "-";
    if (maxIndexLength < 2)
        std::cout << "-";
    std::cout << "|" << std::endl;
    
    for (int i = 0; i < table_size; i++)
    {
        indexLength = 0;
        blankDiff = nameMaxLength - table[i].first.length();
        
        std::cout << "|";
        
        for (int j = 0; j < (blankDiff/2) + 1; j++)
            std::cout << " ";
        std::cout << table[i].first;
        for (int j = 0; j < (blankDiff/2) + 1; j++)
            std::cout << " ";
        if (blankDiff % 2 != 0)
            std::cout << " ";
        std::cout << "|";
        
        temp = table[i].second;
        while(temp != 0)
        {
            temp /= 10;
            indexLength++;
        }
        blankDiff = maxIndexLength - indexLength;

        for (int j = 0; j < (blankDiff/2) + 1; j++)
            std::cout << " ";
        std::cout << table[i].second;
        for (int j = 0; j < blankDiff/2; j++)
            std::cout << " ";
        if (table[i].second > 0)
            std::cout << " ";
        if (table[i].second == -1 && (maxIndexLength % 2 != 0 && maxIndexLength < 2))
            std::cout << " ";
        else if (table[i].second == -1 && maxIndexLength % 2 == 0)
            std::cout << " ";
        if (blankDiff % 2 != 0 && table[i].second > 0)
            std::cout << " ";
        if (table[i].second > 0 && maxIndexLength < 2)
            std::cout << " ";
        if (table[i].second == -99 && (maxIndexLength % 2 != 0 && maxIndexLength > 1))
            std::cout << " ";
        std::cout << "|" << std::endl;
        
        std::cout << "|";
        for (int i = 0; i < nameMaxLength + maxIndexLength + 5; ++i)
            std::cout << "-";
        if (maxIndexLength < 2)
            std::cout << "-";
        std::cout << "|" << std::endl;
    }
}
