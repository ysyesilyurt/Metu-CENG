#include <stdio.h>
#include "the2.h"

void test_insert_print(){
    
    int i;
    node* list = init(2);

    printf("---------\n");
    printf("is_empty: %d\n", is_empty(list));
    printf("num_levels: %d\n", num_levels(list));
    printf("num_nodes: %d\n", num_nodes(list));
    printf("---------\n");
    print(list);
    printf("---------\n");

    insert(list, 123, "abc");
    printf("---------\n");
    print(list);
    printf("---------\n");
    printf("---------\n");
    for (i=num_levels(list)-1; i>=0; --i){
        print_level(list, i);
    }
    printf("---------\n");

    insert(list, 234, "cde");
    printf("---------\n");
    print(list);
    printf("---------\n");
    printf("---------\n");
    for (i=num_levels(list)-1; i>=0; --i){
        print_level(list, i);
        printf("\n");
    }
    printf("---------\n");

    insert(list, 345, "wer");
    printf("---------\n");
    print(list);
    printf("---------\n");
    printf("---------\n");
    for (i=num_levels(list)-1; i>=0; --i){
        print_level(list, i);
        printf("\n");
    }
    printf("---------\n");

    insert(list, 456, "rqe");
    printf("---------\n");
    print(list);
    printf("---------\n");
    printf("---------\n");
    for (i=num_levels(list)-1; i>=0; --i){
        print_level(list, i);
        printf("\n");
    }
    printf("---------\n");

    insert(list, 567, "rre");
    printf("---------\n");
    printf("is_empty: %d\n", is_empty(list));
    printf("num_levels: %d\n", num_levels(list));
    printf("num_nodes: %d\n", num_nodes(list));
    printf("---------\n");
    print(list);
    printf("---------\n");
    printf("---------\n");
    for (i=num_levels(list)-1; i>=0; --i){
        print_level(list, i);
        printf("\n");
    }
    printf("---------\n");

    
    insert(list, 678, "yey");
    insert(list, 789, "rtr");
    insert(list, 890, "htv");
    insert(list, 901, "bgh");
    insert(list, 912, "bnm");

    printf("---------\n");
    printf("is_empty: %d\n", is_empty(list));
    printf("num_levels: %d\n", num_levels(list));
    printf("num_nodes: %d\n", num_nodes(list));
    printf("---------\n");
    print(list);
    printf("---------\n");
    printf("---------\n");
    for (i=num_levels(list)-1; i>=0; --i){
        print_level(list, i);
        printf("\n");
    }
    printf("---------\n");
    printf("---------\n");
    print(list);
    printf("---------\n");
    printf("---------\n");
    for (i=num_levels(list)-1; i>=0; --i){
        print_level(list, i);
        printf("\n");
    }
    printf("---------\n");
    printf("---------\n");
    
}

void test_insert_update(){

    int i;
    node* list = init(3);

    insert(list, 1, "ilk");
    insert(list, 12, "bnm");
    insert(list, 123, "abcty");
    insert(list, 234, "cdehg");
    insert(list, 345, "werf");
    insert(list, 456, "rqe");
    insert(list, 567, "rr");
    insert(list, 678, "y");
    insert(list, 789, "rtrd");
    insert(list, 890, "htv");
    insert(list, 901, "bghdf");
    
    printf("\n");
    print(list);
    printf("\n");
    for (i=num_levels(list)-1; i>=0; --i){
        print_level(list, i);
        printf("\n");
    }
    printf("\n");

    insert(list, 789, "abc");
    print(list);
    printf("\n");
    insert(list, 890, "abc");
    print(list);
    printf("\n");

    for (i=num_levels(list)-1; i>=0; --i){
        print_level(list, i);
        printf("\n");
    }
    printf("\n");
}


void test_branch(int b){

    int i;
    node* list = init(b);

    insert(list, 1, "ilk");
    insert(list, 12, "bnm");
    insert(list, 123, "abcty");
    insert(list, 234, "cdehg");
    insert(list, 345, "werf");
    insert(list, 456, "rqe");
    insert(list, 567, "rr");
    insert(list, 678, "y");
    insert(list, 789, "rtrd");
    insert(list, 890, "htv");
    insert(list, 901, "bghdf");
    
    printf("\n");
    print(list);
    printf("\n");
    for (i=num_levels(list)-1; i>=0; --i){
        print_level(list, i);
        printf("\n");
    }
    printf("\n");
}

void test_delete(){

    int i;
    node* list = init(2);

    insert(list, 1, "ilk");
    insert(list, 12, "bnm");
    insert(list, 123, "abcty");
    insert(list, 234, "cdehg");
    insert(list, 345, "werf");
    insert(list, 456, "rqe");
    insert(list, 567, "rr");
    insert(list, 678, "y");
    insert(list, 789, "rtrd");
    insert(list, 890, "htv");
    insert(list, 901, "bghdf");
    
    printf("\n");

    print(list);
    printf("\n");

    delete(list, 123);
    print(list);
    printf("\n");

    delete(list, 345);
    delete(list, 890);
    delete(list, 456);
    i = delete(list, 1);
    if (i)
        printf("Removed node 1\n");
    else
        printf("This is an error\n");
    printf("\n");

    print(list);
    printf("\n");
    for (i=num_levels(list)-1; i>=0; --i){
        print_level(list, i);
        printf("\n");
    }
    printf("\n");

    i = delete(list, 1);
    if (i)
        printf("This is an error\n");
    else
        printf("Key does not exist\n");
    printf("\n");

    print(list);


}

void test_delete_2(){
    
    node* list = init(2);

    printf("new list\n");
    print(list);
    printf("\n");

    insert(list, 123, "abc");
    insert(list, 234, "cde");
    insert(list, 345, "wer");
    insert(list, 456, "rqe");
    insert(list, 567, "rre");
    insert(list, 678, "yey");
    insert(list, 789, "rtr");
    insert(list, 890, "htv");
    insert(list, 901, "bgh");
    insert(list, 912, "bnm");

    printf("after inserting 10 items\n");
    print(list);
    printf("\n");

    delete(list, 123);
    printf("after deleting 123\n");
    print(list);
    printf("\n");
    delete(list, 234);
    printf("after deleting 234\n");
    print(list);
    printf("\n");

    delete(list, 890);
    printf("after deleting 890\n");
    print(list);
    printf("\n");
    delete(list, 912);
    printf("after deleting 912\n");
    print(list);
    printf("\n");

    
    delete(list, 456);
    delete(list, 567);
    delete(list, 678);
    printf("after deleting 3 more\n");
    print(list);
    printf("\n");

    delete(list, 789);
    delete(list, 901);
    delete(list, 345);
    
    printf("after deleting all\n");
    print(list);
    printf("\n");


}

void test_find(){

    int i;
    int nodes[8] = {234, 1, 678, 789, 901, -1, 555, -100};
    node *n;
    node* list = init(2);

    insert(list, 1, "ilk");
    insert(list, 12, "bnm");
    insert(list, 123, "abcty");
    insert(list, 234, "cdehg");
    insert(list, 345, "werf");
    insert(list, 456, "rqe");
    insert(list, 567, "rr");
    insert(list, 678, "y");
    insert(list, 789, "rtrd");
    insert(list, 890, "htv");
    insert(list, 901, "bghdf");
    
    printf("\n");

    print(list);
    printf("\n");

    for (i=0; i<8; i++){
        n = find(list, nodes[i]);
        if (n){
            /* printed memory address may differ */
            printf("Found node %d:%s at %p \n", n->key, n->value, (void*)n);
        }
        else
            printf("Cannot find node %d\n", nodes[i]);
    }
    printf("\n");

    for (i=0; i<8; i++){
        path(list, nodes[i]);
    }
    printf("\n");

}

void test_clear(){

    /*
    valgrind is installed on ineks
    on terminal, after compiling your code, run:
    ---
    valgrind --error-exitcode=1 --leak-check=full ./the2
    ---
    it will show if there are blocks of memory not freed
    there may be different number of allocations depending on your implementation
    ---
    echo $?
    ---
    will print 0 if no leaks, 1 if there are leaks ($? is the return value of the last command)
    */
    node* list = init(2);

    printf("new list\n");
    print(list);
    printf("\n");

    insert(list, 123, "abc");
    insert(list, 234, "cde");
    insert(list, 345, "wer");
    insert(list, 456, "rqe");
    insert(list, 567, "rre");
    insert(list, 678, "yey");
    insert(list, 789, "rtr");
    insert(list, 890, "htv");
    insert(list, 901, "bgh");
    insert(list, 912, "bnm");

    print(list);
    printf("\n");

    clear(list);
}

int main(int argc, char *argv[]){

    /* test_insert_print();*/

    /* test_insert_update(); */


    /*
    test_branch(2);
    test_branch(3);
    test_branch(4);
    */

    /* 
    test_delete(); 
    test_delete_2();
    */

    /* test_find(); */

    test_clear();

    return 0;
}