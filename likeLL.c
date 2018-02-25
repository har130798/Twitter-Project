/* */

#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
#include"commentLL.c"

typedef struct likedby
{
    char data[20];
    struct likedby * next;
}likedby;

void insertLikeName(char * data, likedby ** head)
{
    likedby * temp;
    temp = (likedby *)malloc(sizeof(likedby));
    strcpy(temp->data, data);

    if(head == NULL)
    {
        temp -> next = NULL;
        (*head) = temp;
    }

    else
    {
        temp -> next = (*head);
        (*head) = temp;
    }
}

int containsLikeName(char * key, likedby ** head)
{
    likedby * temp = (*head);
    int i = 0;

    for(; temp != NULL; temp = temp -> next)
    {
        if(!strcmp(key, temp -> data))
        {
            return i;
        }
        i++;
    }

    return -1;
}

int sizeOfLiked(likedby ** head)
{
    likedby * temp = (*head);
    int i = 0;

    for(; temp != NULL; temp = temp -> next)
    {
        i++;
    }

    return i;
}

void printLikeNames(likedby ** head)
{
    likedby * temp = (*head);
    if(temp == NULL) printf("No one has liked this tweet.\n\n");
    else
    {
        for(; temp != NULL; temp = temp -> next)
        {
            printf("\t\t%s\n", temp -> data);
        }
    }
}

void deleteLikeName(likedby ** head)
{
    likedby * temp1 = (*head);
    likedby * temp2 = (*head);

    if(temp1 == NULL) printf("-->No Likes\n\n");
    else if(temp1 -> next != NULL)
    {
        for(; temp1 -> next != NULL; temp1 = temp1 -> next){}
        for(; temp2 -> next != temp1; temp2 = temp2 -> next){}

        temp2 -> next = NULL;

        printf("****Successfully deleted %d at the tail****\n", temp1 -> data);
        free(temp1);
    }
    else
    {
        (*head) = NULL;
        printf("****Successfully deleted %d the head****\n", temp1 -> data);
    }
}

