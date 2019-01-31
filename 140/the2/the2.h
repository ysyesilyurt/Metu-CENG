#ifndef _THE_2_
#define _THE_2_

/*
    an augmented sorted linked list implementation
    for faster insert, remove and search methods
    uses multiple levels of linked lists
    each level starts with a dummy node
    dummy node at the beginning of the top layer
    keeps the node count as its key so that we can have deterministic updates
    if remainder is zero for BRANCH^i than insert adds the node to level i
*/


/* max nodes at the lowest level 10^K_SIZE-1*/
#define LIMIT 1000

/* for printfs */
/* 3 digit keys */
#define K_SIZE 3
/* 5 char values */
#define V_SIZE 5

/*  node struct holds a key value pair
        keys are unique
    a pointer to next node at the same level
    a pointer to lower level node
        that contains the same key value pair
*/
typedef struct node{
    int key;
    char value[V_SIZE];
    struct node *next;
    struct node *down;
} node;

/* initializes and returns the dummy head of a new linked list */
node *init(int branch);

/* deletes the list, deallocates all memory */
void clear(node *list);

/*
returns 1 is the linked list contains no elements
returns 0 otherwise
*/
int is_empty(node *list);

/*
returns the number of levels in the list
*/
int num_levels(node *list);

/*
returns the number of nodes in the lowest level of the list
*/
int num_nodes(node *list);

/*
inserts a new node with the given key and value
updates value if key exists, allocates a new node otherwise
returns the node pointer on success, NULL on failure
*/
node *insert(node *list, int key, char *value);

/*
removes the node with the given key from the list
returns 1 on success: node deleted
returns 0 on failure: key does not exists
*/
int delete(node *list, int key);

/*
finds the node with the given key in the list
returns the pointer on success: node found
    this is not the lowest level node
returns NULL on failure: key does not exists
*/
node *find(node *list, int key);

/*
prints the path to the node with the given key
prints keys as integers and the followed paths as next:' > ' or down:' v '
*/
void path(node *list, int key);

/*
prints the contents of the list
a single line with key:values pairs for each level
*/
void print(node *list);

/* print only the given level */
void print_level(node *list, int level);


#endif
