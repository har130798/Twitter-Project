/* */
#ifndef commentLL
#define commentLL

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include"mytime.c"

typedef struct comment
{
    char name[20];
    char dateTimePost[18];
    char data[400];
    struct comment * next;
}comment;

void postComment(char * data, comment ** head, char * cname, char * cdate)
{
    comment * temp;
    temp = (comment *)malloc(sizeof(comment));
    strcpy(temp->data, data);
    strcpy(temp->name, cname);
    strcpy(temp->dateTimePost, cdate);

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

int hasComment(char * key, comment ** head)
{
    comment * temp = (*head);
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

int NoOfComments(comment ** head)
{
    comment * temp = (*head);
    int i = 0;

    for(; temp != NULL; temp = temp -> next)
    {
        i++;
    }

    return i;
}

void printComments(comment ** head)
{
    comment * temp = (*head);

    if(temp == NULL) printf("NO comments\n\n");
    else
    {
        printf("_____________________________________________________________________________________________________________________\n");
        for(; temp != NULL; temp = temp -> next)
        {
            printf(" %s\t|\tTIME OF COMMENT :\t%s\t|\n", temp ->name, temp ->dateTimePost);
            printf("_____________________________________________________________________________________________________________________\n");
            printf("\t\t%s\n", temp -> data);
            printf("_____________________________________________________________________________________________________________________\n");
        }
    }
}

void enterComment(char * cname, comment ** head)
{
    char alpha;
    char content[431];
    int count = 0;

    printf("\t\t\t\t+-----------------------------------------------------------------+\n");
    printf("\t\t\t\t|  Type your comment & type '|' at the end to save your comment:  |\n");
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
        postComment(content, head, cname, getDateTime());

    }
    system("cls");
    if(!strcmp(content, "NULLINFO")) printf("You haven't entered anything!\n");
    else printf("Comment saved successfully!\n");
}
//int main()
//{
//    comment * p = NULL;
//    postComment("Sample Comment 1", &p, "abc");
//    postComment("Sample Comment 2", &p, "def");
//    postComment("Sample Comment 3", &p, "ghi");
//    postComment("Sample Comment 4", &p, "jkl");
//    printf("%d\n", NoOfComments(&p));
//    printComments(&p);
//    return 0;
//}


#endif
