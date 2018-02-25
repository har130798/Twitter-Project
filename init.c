/* */
#ifndef init
#define init

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"user.c"

void enterTweet(char * cname, consumer * curr)
{
    char alpha;
    char content[431];
    int count = 0;

    printf("\t\t\t\t+-----------------------------------------------------------------+\n");
    printf("\t\t\t\t|    Type your tweet & type '|' at the end to save your tweet:    |\n");
    printf("\t\t\t\t+-----------------------------------------------------------------+\n");
    printf("\t\t\t\t___________________________________________________________________\n");

    fflush(stdin);
    while(1)
    {
        alpha = getchar();
        if(alpha == '|') break;
        if(count == 430) break;
        content[count++] = alpha;
    }
    fflush(stdin);
    if(count == 0) strcpy(content, "NULLINFO");
    else
    {
        content[count] = '\0';
        count = containsConsumer(cname, &curr);
        consumer * temp = curr;
        for(; count != 0; count--) temp = temp -> next;
        insertAtHead(0, getDateTime(), content, &(temp ->head));
    }
    system("cls");
    if(!strcmp(content, "NULLINFO")) printf("You haven't entered anything!\n");
    else printf("Tweet saved successfully!\n");
}

void viewMyTweet(char * cname, char * username, consumer * curr)
{
    int count;
    char exitChar = 'a';
    count = containsConsumer(cname, &curr);
    consumer * temp = curr;
    for(; count != 0; count--) temp = temp -> next;

    if((temp ->head) != NULL)
        printList(&(temp -> head), cname, username);
    else
    {
        printf("No tweets exist!\n");
        return;
    }
    fflush(stdin);
    system("cls");
}

void viewTweet(consumer * curr, char * username)
{
    char name[20];
    printf("\t\t\t\t\t+------------------------------------+\n");
    printf("\t\t\t\t\t|  Enter the username of the person  |\n");
    printf("\t\t\t\t\t+------------------------------------+\n");
    scanf("%s", name);

    char Tweet[431];
    int count = containsConsumer(name, &curr);

    if(count != -1)
    {
        viewMyTweet(name, username, curr);
    }
    else
    {
        system("cls");
        printf("Name does not exist!\n");
    }
}

#endif
