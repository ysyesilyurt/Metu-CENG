#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "the2.h"

int branch_factor(node *list){
    return list->key/1000;
}


node *init(int branch){
    node *head=malloc(sizeof(node));
    node *level0=malloc(sizeof(node));
    head->key=branch*1000;
    head->down=level0;
    head->next=NULL;
    level0->key=0;
    level0->next=NULL;
    level0->down=NULL;
    return head;
}


void clear(node *list){
    node *temp,*temp2,*level=list->down;
    node *curr;
    while (level)
    {
        curr=level->next;
        while (curr)
        {
            temp=curr->next;
            free(curr);
            curr=temp;
        }
        temp2=level->down;
        free(level);
        level=temp2;
    }
    free(list);
    return;
}


int is_empty(node *list){
    node *level1;
    level1=list->down;
    if(level1->next==NULL && level1->down==NULL)
        return 1;
    else
        return 0;
}


int num_levels(node *list){
    node *level;
    int count=0;
    level=list->down;
    if(is_empty(list))
        return 1;
    else
    {
        while(level)
        {
            count++;
            level=level->down;
        }
    }
    return count;
}


int num_nodes(node *list){
    return list->key%1000;
}


node *insert(node *list, int key, char *value){
    node *newnode,*newlevel,*head=list,*ret,*temp,*level,*go=list,*curr,*curr1,*curr2,*level2;
    int numberofnodes=1+num_nodes(head),branch=branch_factor(head),power=0,oldp;
    if(!find(go,key))
    {
        list->key+=1;
        newnode=malloc(sizeof(node));
        if(!newnode)
            return NULL;
        strncpy(newnode->value,value,V_SIZE);
        newnode->key=key;
        newnode->next=NULL;
        newnode->down=NULL;
        if(numberofnodes>999)
            return NULL;
        if(is_empty(head))
        {
            temp=head->down;
            temp->next=newnode;
            return newnode;
        }
        else if(numberofnodes%branch!=0)
        {
            while (head->down)
                head=head->down;
            temp=head;
            while (head->next)
            {
                head=head->next;
                if(head->key>newnode->key)
                {
                    temp->next=newnode;
                    newnode->next=head;
                    ret=temp->next;
                    break;
                }
                else if(head->key<newnode->key && !(head->next))
                {
                    head->next=newnode;
                    ret=head->next;
                    break;
                }
                temp=temp->next;
            }
            return ret;
        }
        else
        {
            while (1)
            {
                if(numberofnodes%branch!=0)
                    break;
                numberofnodes/=branch;
                power++;
            }
            oldp=power;
            temp=head->down;
            for (;power > 0;--power) {
                if (-power >= temp->key)
                    break;
                else {
                    newlevel = malloc(sizeof(node));
                    if (!newlevel)
                        return NULL;
                    head->down = newlevel;
                    newlevel->key = -power;
                    newlevel->next = NULL;
                    newlevel->down = temp;
                    head = head->down;
                }
            }
            level=list->down;
            while (1)
            {
                if(level->key==-oldp)
                    break;
                level=level->down;
            }
            while (level)
            {
                newnode=malloc(sizeof(node));
                if(!newnode)
                    return NULL;
                strncpy(newnode->value,value,V_SIZE);
                newnode->key=key;
                newnode->next=NULL;
                newnode->down=NULL;
                if(numberofnodes>999)
                    return NULL;
                curr=level->next;
                temp=level;
                while (curr)
                {
                    if(curr->key>newnode->key)
                    {
                        temp->next=newnode;
                        newnode->next=curr;
                        ret=temp->next;
                        break;
                    }
                    else if(curr->key<newnode->key && !(curr->next))
                    {
                        curr->next=newnode;
                        ret=curr->next;
                        break;
                    }
                    curr=curr->next;
                    temp=temp->next;
                }
                if(!level->next)
                {
                    level->next=newnode;
                    ret=level->next;
                }
                level=level->down;
            }
            level=list->down;
            while (1)
            {
                if(level->key==-oldp)
                    break;
                level=level->down;
            }
            if(level->down)
            {
                level2=level->down;
                while (level2)
                {
                    curr1=level->next;
                    curr2=level2->next;
                    while (curr1)
                    {
                        if(curr2->key==curr1->key)
                        {
                            curr1->down=curr2;
                            curr1=curr1->next;
                            curr2=curr2->next;
                        }
                        else
                            curr2=curr2->next;
                    }
                    level2=level2->down;
                    level=level->down;
                }
            }
        }
    }
    else
    {
        temp=find(go,key);
        strncpy(temp->value,value,V_SIZE);
        while (temp->down)
        {
            temp=temp->down;
            strncpy(temp->value,value,V_SIZE);
        }
        ret=temp;
    }
    return ret;
}


int delete(node *list, int key){
    node *head=list,*target,*level,*temp,*dummy=list;
    if(!find(list,key))
        return 0;
    else
    {
        list->key-=1;
        level=head->down;
        while (level)
        {
            target=level->next;
            temp=level;
            while (target)
            {
                if(target->key==key)
                {
                    temp->next=target->next;
                    free(target);
                }
                target=target->next;
                temp=temp->next;
            }
            level=level->down;
        }
        while(dummy->down)
        {
            target=dummy->down;
            if(num_levels(list)==1)
                break;
            else if(!target->next)
            {
                temp=target->down;
                free(target);
                dummy->down=temp;
            }
            dummy=dummy->down;
        }
    }
    return 1;
}


node *find(node *list, int key){
    node *curr,*level,*head=list,*temp;
    if(is_empty(head))
        return NULL;
    else
    {
        level=head->down;
        while (level)
        {
            curr=level->next;
            temp=level;
            while (curr)
            {
                if(curr->key==key)
                    return curr;
                else if(curr->key>key)
                    break;
                else
                {
                    curr=curr->next;
                    temp=temp->next;
                    continue;
                }
            }
            level=temp->down;
            continue;
        }
    }
    return NULL;
}


void print(node *list){
    node *head=list,*curr,*temp2,*temp=list;
    int i;
    printf("%3d      ", num_nodes(head));
    for (i = 0; i < num_levels(head); ++i) {
        printf(" %d",i);
    }
    printf("\n");
    printf("         ");
    for (i = 0; i < num_levels(head); ++i) {
        printf(" +");
    }
    printf(" -\n");
    while (head->down)
        head=head->down;
    curr=head->next;
    while (curr)
    {
        printf("%3d:%5s",curr->key,curr->value);
        temp2=find(temp,curr->key);
        for (;temp2; temp2=temp2->down) {
            printf(" +");
        }
        printf("\n");
        curr=curr->next;
    }
}


void print_level(node *list, int level){
    node *lvl,*lvl2,*head=list,*curr,*curr1,*curr2;
    lvl2=lvl=head->down;
    if(-level==lvl->key)
    {
        curr=lvl;
        while (curr)
        {
            printf("%3d:%5s -> ",curr->key,curr->value);
            curr=curr->next;
        }
        printf("\n");
    }
    else
    {
        while (1)
        {
            if(-(level)==lvl->key)
                break;
            lvl=lvl->down;
        }
        while (1)
        {
            if(-(level+1)==lvl2->key)
                break;
            lvl2=lvl2->down;
        }
        curr1=lvl->next;
        curr2=lvl2->next;
        printf("             ");
        while (curr2)
        {
            if(curr1->key==curr2->key)
            {
                printf("%3d:%5s -> ",curr2->key,curr2->value);
                curr1=curr1->next;
                curr2=curr2->next;
            }
            else
            {
                printf("             ");
                curr1=curr1->next;
            }
        }
        printf("\n");
        curr1=lvl->next;
        curr2=lvl2->next;
        printf("             ");
        while (curr2)
        {
            if(curr1->key==curr2->key)
            {
                printf("   |         ");
                curr1=curr1->next;
                curr2=curr2->next;
            }
            else
            {
                printf("             ");
                curr1=curr1->next;
            }
        }
        printf("\n");
        curr1=lvl;
        while (curr1)
        {
            printf("%3d:%5s -> ",curr1->key,curr1->value);
            curr1=curr1->next;
        }
        printf("\n");
    }
}


void path(node *list, int key){
    node *head=list,*level,*curr,*temp;
    int flag=0;
    printf("%d",head->key);
    level=head->down;
    printf(" v %3d",level->key);
    while (level)
    {
        curr=level->next;
        temp=level;
        while (curr)
        {
            if(curr->key==key)
            {
                printf(" > %3d:%5s",curr->key,curr->value);
                flag=1;
                break;
            }
            else if(curr->key>key)
                break;
            else
            {
                printf(" > %3d",curr->key);
                curr=curr->next;
                temp=temp->next;
                continue;
            }
        }
        if(flag==1)
            break;
        else
        {
            level=temp->down;
            printf(" v %3d",level->key);
        }
    }
    printf("\n");
}

