/* */
#ifndef user
#define user

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include"stringLL.c"

typedef struct consumer
{
    char name[30];
    char password[10];
    tweet * head;
    struct consumer * next;
    struct consumer * prev;
}consumer;

void addToConsumerList(char * name, char * password, consumer ** head)
{
    consumer * temp;
    temp = (consumer *)malloc(sizeof(consumer));
    strcpy(temp ->name, name);
    strcpy(temp ->password, password);
    temp -> head = NULL;

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

void printConsumer(consumer ** head)
{
    consumer * temp = (*head);

    if(temp == NULL) printf("-->List Empty!\n\n");
    else
    {
        for(; temp != NULL; temp = temp -> next)
        {
            printf("%s %s  from exec\n", temp -> name, temp ->password);
        }
    }
}

int containsConsumer(char * key, consumer ** head)
{
    consumer * temp = (*head);
    int i = 0;

    for(; temp != NULL; temp = temp -> next)
    {
        if(!strcmp(key, temp -> name))
        {
            return i;
        }
        i++;
    }

    return -1;
}

int noOfConsumers(consumer ** head)
{
    consumer * temp = (*head);
    int i = 0;

    for(; temp != NULL; temp = temp -> next)
    {
        i++;
    }

    return i;
}

void deleteConsumer(char * name, consumer ** head)
{
    consumer * temp1 = (*head);
    consumer * temp2 = (*head);
    int i = containsConsumer(name, head);
    int j = i;
    if(temp1 == NULL) printf("-->No elements in the linked list.\n-->Try using void insertAtHead(int, tweet **);\n\n");
    else if(i > 0)
    {
        for(; i != 0; i--){temp1 = temp1 -> next;}
        for(; j != 1; j--){temp2 = temp2 -> next;}
        consumer * temp3 = temp1 -> next;
        temp2 -> next = temp3;
        temp1 ->head = NULL;
        free(temp1);
    }
    else
    {
        temp2 = temp2 -> next;
        (*head) = temp2;
        free(temp1);
    }
}

void saveTweets(consumer ** con)
{
    FILE * f = fopen("Tweets.txt", "w");
    consumer * temp = (*con);
    tweet * t;
    likedby * likedperson;
    comment * commentedData;
    bool flag = false, fl = false;
    while(temp != NULL)
    {
        fl = true;
        t = temp ->head;
        if(t != NULL)
        {
            flag = true;
            fprintf(f, "%s\n", temp ->name);
        }
        while(t != NULL)
        {
            fprintf(f, "%s %d", t ->dateTimeofPublish, t ->likes);
            fprintf(f, "%s|\n", t ->content);
            likedperson = t ->head;
            while(likedperson != NULL)
            {
                fprintf(f, "%s\n", likedperson ->data);
                likedperson = likedperson ->next;
            }
            fprintf(f, "****\n");
            commentedData = t ->comments;
            while(commentedData != NULL)
            {
                fprintf(f, "%s %s\n", commentedData ->name, commentedData ->dateTimePost);
                fprintf(f, "%s|\n", commentedData ->data);
                commentedData = commentedData ->next;
            }
            fprintf(f, "++++\n");
            t = t ->next;
        }
        if(flag)
        {
            flag = false;
            fprintf(f,"^^^^\n");
        }
        temp = temp ->next;
    }
    if(fl) fprintf(f,"xxxx\n");
    fclose(f);
}

void saveAccounts(consumer ** head)
{
    FILE * f = fopen("Consumers.con", "w");
    consumer * temp = (*head);
    while(temp != NULL)
    {
        fprintf(f, "%s %s\n", temp ->name, temp ->password);
        temp = temp ->next;
    }
    fprintf(f,"xxxx\n");
    fclose(f);
    saveTweets(head);
}

void encrypt(char * name, char * password)
{
    int i, size = strlen(name);
    for(i = 0; i < size; i++)
    {
        if(name[i] >= 33 && name[i] <= 119) name[i] = name[i] + 3;
        else name[i] = name[i] - 119 + 32;
    }
    size = strlen(password);
    for(i = 0; i < size; i++)
    {
        if(password[i] >= 33 && password[i] <= 117) password[i] = password[i] + 5;
        else password[i] = password[i] - 117 + 32;
    }
}

void saveEncryptAccounts(consumer ** head)
{
    FILE * f = fopen("encryptedConsumers.txt", "w");
    consumer * temp = (*head);
    while(temp != NULL)
    {
        encrypt(temp ->name, temp ->password);
        fprintf(f, "%s %s\n", temp ->name, temp ->password);
        temp = temp ->next;
    }
    fprintf(f,"xxxx\n");
    fclose(f);
    saveTweets(head);
}
void decrypt(char * name, char * password)
{
    int i, size = strlen(name);
    for(i = 0; i < size; i++)
    {
        if(name[i] >= 36 && name[i] <= 122) name[i] = name[i] - 3;
        else name[i] = name[i] - 35 + 122;
    }
    size = strlen(password);
    for(i = 0; i < size; i++)
    {
        if(password[i] >= 38 && password[i] <= 122) password[i] = password[i] - 5;
        else password[i] = password[i] - 37 + 122;
    }
}
#endif
