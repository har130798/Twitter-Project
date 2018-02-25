/* */
#ifndef stringLL
#define stringLL

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include"likeLL.c"
#include"commentLL.c"

typedef struct tweet
{
    int likes;
    char content[411];
    char dateTimeofPublish[17];
    struct tweet * next;
    likedby * head;
    comment * comments;
}tweet;

void insertAtHead(int likes, char * cdate, char * content, tweet ** head)
{
    tweet * temp;
    temp = (tweet *)malloc(sizeof(tweet));
    strcpy(temp->content, content);
    temp ->likes = likes;
    strcpy(temp ->dateTimeofPublish, cdate);
    temp ->head = NULL;
    temp ->comments = NULL;

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

int containsKey(char * key, tweet ** head)
{
    tweet * temp = (*head);
    int i = 0;

    for(; temp != NULL; temp = temp -> next)
    {
        if(!strcmp(key, temp -> content))
        {
            return i;
        }
        i++;
    }

    return -1;
}

int sizeOfList(tweet ** head)
{
    tweet * temp = (*head);
    int i = 0;

    for(; temp != NULL; temp = temp -> next)
    {
        i++;
    }

    return i;
}

void tweetUI()
{
    printf("\t\t\t\t\t+------------------------------+\n");
    printf("\t\t\t\t\t|           Options            |\n");
    printf("\t\t\t\t\t+------------------------------+\n");
    printf("\t\t\t\t\t|        1. Like Tweet         |\n");
    printf("\t\t\t\t\t|______________________________|\n");
    printf("\t\t\t\t\t|        2. Comment            |\n");
    printf("\t\t\t\t\t|______________________________|\n");
    printf("\t\t\t\t\t|        3. View Comments      |\n");
    printf("\t\t\t\t\t|______________________________|\n");
    printf("\t\t\t\t\t|        4. View Likes         |\n");
    printf("\t\t\t\t\t|______________________________|\n");
    printf("\t\t\t\t\t|        5. Next Tweet         |\n");
    printf("\t\t\t\t\t|______________________________|\n");
    printf("\t\t\t\t\t|        6. Back to Menu       |\n");
    printf("\t\t\t\t\t|______________________________|\n");
}
void printList(tweet ** head, char * cname, char * username)
{
    tweet * temp = (*head);
    int choice;

    if(temp == NULL) printf("-->List Empty!\n\n");
    else
    {
        while(temp != NULL)
        {
            system("cls");
            printf("+----------------------------------------------------------------------------------------------------------------+\n");
            printf("\t\t\t\t\t%s's tweets\n", cname);
            printf("+----------------------------------------------------------------------------------------------------------------+\n");
            printf("+----------------------------------------------------------------------------------------------------------------+\n");
            printf("\tTIME OF TWEET :\t%s\n", temp ->dateTimeofPublish);
            printf("+----------------------------------------------------------------------------------------------------------------+\n");
            printf("\t\t%s\n\n", temp -> content);
            printf("+----------------------------------------------------------------------------------------------------------------+\n");
            printf("|   LIKES : %d | COMMENTS : %d |\n", temp ->likes, NoOfComments(&(temp ->comments)));
            printf("+----------------------------------------------------------------------------------------------------------------+\n\n");
            tweetUI();
            fflush(stdin);
            scanf("%d", &choice);
            switch(choice)
            {
                case 1: if(containsLikeName(username, &(temp ->head)) == -1)
                        {
                            (temp ->likes) += 1;
                            insertLikeName(username, &(temp ->head));
                        }
                        break;
                case 2: system("cls");
                        enterComment(username, &(temp ->comments));
                        system("pause");
                        break;
                case 3: system("cls");
                        printf("\t\t\t\t\t+------------------------------------+\n");
                        printf("\t\t\t\t\t| People who commented on this tweet |\n");
                        printf("\t\t\t\t\t+------------------------------------+\n");
                        printComments(&(temp ->comments));
                        system("pause");
                        break;
                case 4: system("cls");
                        printf("\t+-----------------------------+\n");
                        printf("\t| People who liked this tweet |\n");
                        printf("\t+-----------------------------+\n");
                        printLikeNames(&(temp ->head));
                        system("pause");
                        break;
                case 5: temp = temp -> next;
                        if(temp == NULL)
                        {
                            system("cls");
                            printf("No more tweets to display\n\n");
                            system("pause");
                            return;
                        }
                        break;
                case 6: return;
                default:system("cls");
                        printf("ERROR : Enter a valid choice\n");
                        system("pause");
                        break;
            }
        }
    }
}

void deleteTail(tweet ** head)
{
    tweet * temp1 = (*head);
    tweet * temp2 = (*head);

    if(temp1 == NULL) printf("-->No elements in the linked list.\n-->Try using void insertAtHead(int, tweet **);\n\n");
    else if(temp1 -> next != NULL)
    {
        for(; temp1 -> next != NULL; temp1 = temp1 -> next){}
        for(; temp2 -> next != temp1; temp2 = temp2 -> next){}

        temp2 -> next = NULL;
        free(temp1);
    }
    else
    {
        (*head) = NULL;
    }
}

void deleteAtKthpos(int k, tweet ** head)
{
    tweet * temp1 = (*head);
    tweet * temp2 = (*head);
    int i;
    if(temp1 == NULL) printf("-->No elements in the linked list.\n-->Try using void insertAtHead(int, tweet **);\n");
    else if(k < sizeOfList(head) && k >= 0 && temp1 -> next != NULL)
    {
        for(i = 0; i < k && temp1 != NULL; i++)
        {
            temp1 = temp1 -> next;
        }
        for(; temp2 -> next != temp1; temp2 = temp2 -> next){}

        temp2 -> next = temp1 -> next;
        free(temp1);
    }
    else if(temp1 -> next == NULL) deleteTail(head);
    else printf("-->Can't delete %dth position when size of list is %d\n-->Try using void deleteTail(tweet **);\n\n", k, sizeOfList(head));
}

#endif
