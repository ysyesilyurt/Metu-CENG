#include "Article.h"

/*#############################
#               NOTE!         #
#    Please don't forget to   #
#     check PDF. Functions     #
#    may have more detailed   #
#     tasks which are not     #
#       mentioned here.       #
#############################*/

Article::Article( int table_size,int h1_param, int h2_param )
{
    n = 0;
    Article::table_size = table_size;
    Article::h1_param = h1_param;
    Article::h2_param = h2_param;
    table = new std::pair<std::string, int>[table_size];
    for (int i = 0; i < table_size; ++i) {
        table[i] = std::make_pair(EMPTY_KEY,EMPTY_INDEX);
    }
}

Article::~Article()
{
    table_size = 0;
    n = 0;
    h1_param = 0;
    h2_param = 0;
    delete [] table;
}

int Article::get( std::string key, int nth, std::vector<int> &path ) const
{
    int occurence = 0,flag = 0,i = 0;
    while(true)
    {
        int hash = hash_function(key,i);

        if (flag)//check for first cell
            path.push_back(hash);

        if(table[hash].first == key)
        {
            occurence++;
            if(occurence == nth)
                return table[hash].second;
            i++;
            flag = 1;
        }

        else if(table[hash].second == EMPTY_INDEX)
            return -1;
        else if(i>=table_size-1)
            return -1;

        else
        {
            i++;
            flag = 1;
        }
    }
}

int Article::insert( std::string key, int original_index )
{
    if(getLoadFactor()>MAX_LOAD_FACTOR)
        expand_table();

    int countofProbing = 0,flag = 0,i = 0;
    while(true)
    {
        int hash = hash_function(key,i);

        if (flag != 0)//check for first cell
            countofProbing++;

        if(table[hash].first == EMPTY_KEY)
        {
            table[hash] = std::make_pair(key,original_index);
            n++;
            break;
        }

        else if(table[hash].first == key)
        {
            if(original_index < table[hash].second)
            {
                int neworgi_index = table[hash].second;
                table[hash].second = original_index;
                original_index = neworgi_index;
            }
        }
        i++;
        flag = 1;
    }
    return countofProbing;
}

int Article::remove( std::string key, int nth )
{
    int occurence = 0,i = 0;
    while(true)
    {
        int hash = hash_function(key,i);

        if(table[hash].first == key)
        {
            occurence++;
            if(occurence == nth)
            {
                table[hash] = std::make_pair(EMPTY_KEY,MARKED_INDEX);
                n--;
                return i;
            }
        }

        else if(table[hash].second == EMPTY_INDEX)
            return -1;

        else if(i>=table_size-1)
            return -1;

        i++;
    }
}

double Article::getLoadFactor() const
{
    return (double)n/table_size;
}

void Article::getAllWordsFromFile( std::string filepath )
{
    std::ifstream file ;
    std::string wrd ;
    int orgi_index = 1;

    file.open(filepath.c_str());

    while(file >> wrd) {
        insert(wrd, orgi_index);
        orgi_index++;
    }

    file.close();
}

void Article::expand_table()
{
    int oldtablesize = table_size;
    table_size = nextPrimeAfter(2*table_size);
    h2_param = firstPrimeBefore(table_size);
    std::pair<std::string, int>* oldtable = table;
    table = new std::pair<std::string, int>[table_size];
    n = 0;
    for (int i = 0; i < table_size; ++i) {
        table[i] = std::make_pair(EMPTY_KEY,EMPTY_INDEX);
    }
    for (int i = 0; i < oldtablesize ; ++i) {
        if(oldtable[i].second != EMPTY_INDEX) {
            insert(oldtable[i].first, oldtable[i].second);
        }
    }

    delete [] oldtable;
}

int Article::hash_function( std::string& key, int i ) const
{
    int convertedKey = convertStrToInt(key);
    return ( h1(convertedKey) + i*h2(convertedKey) ) % table_size;
}

int Article::h1( int key ) const
{
    int popcount = 0;
    while(key!=0)
    {
        if(key%2) {
            popcount++;
            key /= 2;
        }
        else
            key/=2;
    }
    int res = h1_param * popcount;
    return res;
}

int Article::h2( int key ) const
{
    int modofKey = key % h2_param;
    int res = h2_param - modofKey;
    return res;
}

