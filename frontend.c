/*Remaining Things TODO:
1. Refactor
2. Change UI (Done till now)
3. Add more features
*/

#ifndef frontend
#define frontend

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"init.c"

char name[20];
consumer * cons = NULL;

void fcopy()
{
    FILE * f1 = fopen("Consumers.txt", "r");
    FILE * f2 = fopen("Consumers.con", "w");
    char str1[20], str2[20];

    while(1)
    {
        fscanf(f1, "%s %s", str1, str2);
        if(!strcmp(str1, "xxxx")) break;
        fprintf(f2, "%s %s\n", str1, str2);
    }
    fprintf(f2, "xxxx\n");
    fclose(f1);
    fclose(f2);
}

void initConsumer()
{
    printf("Hello :D ! Welcome to MartinsTwitter\n");
    FILE * f = fopen("Consumers.con", "r");
    char str1[20], str2[20];
    long size;
    if(f)
    {
        if(f != NULL)
        {
            fseek(f, 0, SEEK_END);
            size = ftell(f);
            if(size == 0) return;
        }
        fseek(f, 0, SEEK_SET);
        while(1)
        {
            fscanf(f, "%s %s", str1, str2);
            if(!strcmp(str1, "xxxx")) break;
            addToConsumerList(str1, str2, &cons);
        }
    }
    fclose(f);
}

void initEncryptConsumer()
{
    printf("Hello :D ! Welcome to MartinsTwitter\n");
    FILE * f = fopen("encryptedConsumers.txt", "r");
    char str1[20], str2[20];
    long size;
    if(f)
    {
        if(f != NULL)
        {
            fseek(f, 0, SEEK_END);
            size = ftell(f);
            if(size == 0) return;
        }
        fseek(f, 0, SEEK_SET);

        while(1)
        {
            fscanf(f, "%s %s", str1, str2);
            if(!strcmp(str1, "xxxx")) break;
            decrypt(str1, str2);
            addToConsumerList(str1, str2, &cons);
        }
        fclose(f);
    }
}

void initTweets()
{
    FILE * f = fopen("Tweets.txt", "r");
    char cname[20], cdate[20], content[431], c;
    char dummy[20] = "dummy";
    int likes, count = 0;
    char str[20];
    consumer * temp;

    if(f)
    {
        long size;
        if(f != NULL)
        {
            fseek(f, 0, SEEK_END);
            size = ftell(f);
            if(size == 0) return;
        }
        fseek(f, 0, SEEK_SET);
        while(1)
        {
            temp = cons;
            fscanf(f, "%s", cname);
            if(!strcmp(cname, "xxxx")) break;
            decrypt(cname, dummy);
            count = containsConsumer(cname, &cons);
            for(; count != 0; count--) temp = temp -> next;
            count = 0;
            while(1)
            {
                count = 0;
                fscanf(f, "%s", cdate);
                if(!strcmp(cdate, "^^^^")) break;
                fscanf(f, "%d", &likes);
                while(1)
                {
                    fscanf(f, "%c", &c);
                    if(c == '|')
                    {
                        content[count] ='\0';
                        break;
                    }
                    if(c >= 33 || c <= 126) content[count++] = c;
                }
                insertAtHead(likes, cdate, content, &(temp ->head));
                while(1)
                {
                    fscanf(f, "%s", str);
                    if(!strcmp(str, "****")) break;
                    insertLikeName(str, &((temp ->head) ->head));
                }
                while(1)
                {
                    count = 0;
                    fscanf(f, "%s", cname);
                    if(!strcmp(cname, "++++")) break;
                    fscanf(f, "%s", cdate);
                    while(1)
                    {
                        fscanf(f, "%c", &c);
                        if(c == '|')
                        {
                            content[count] ='\0';
                            break;
                        }
                        if((c >= 33 || c <= 126) && c != '\n') content[count++] = c;
                    }
                    postComment(content,&((temp ->head) -> comments), cname, cdate);
                }
            }
        }
        fclose(f);
    }
}

void loggedInUI(char * name)
{
    printf("_____________________________________________________________________________________________________________________\n\n");
    printf("                                                                         +------------------------------------------+\n");
    printf("                                                                         |           You are logged in              |\n");
    printf("                                                                         +------------------------------------------+\n");
    printf("                                                                             Name : %s\n\n\n", name);
    printf("\t\t\t\t\t+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n");
    printf("\t\t\t\t\t|          MartinsTwitter         |\n");
    printf("\t\t\t\t\t+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n");
    printf("\t\t\t\t\t|       1 . Enter a tweet         |\n");
    printf("\t\t\t\t\t|_________________________________|\n");
    printf("\t\t\t\t\t|       2 . View my tweets        |\n");
    printf("\t\t\t\t\t|_________________________________|\n");
    printf("\t\t\t\t\t|       3 . View others' tweets   |\n");
    printf("\t\t\t\t\t|_________________________________|\n");
    printf("\t\t\t\t\t|       4 . Delete Account (beta) |\n");
    printf("\t\t\t\t\t|_________________________________|\n");
    printf("\t\t\t\t\t|       5 . Log Out               |\n");
    printf("\t\t\t\t\t|_________________________________|\n");
}

int deleteAccount(char * cname, consumer * head)
{
    fflush(stdin);
    char sure;
    char password[20];
    printf("Are you sure you want to delete your account?\n");
    sure = getchar();
    if(sure == 'n')
    {
        system("cls");
        return;
    }
    else
    {
        int i = containsConsumer(cname, &head);
        consumer * temp = head;
        for(; i != 0; i--){temp = temp -> next;}
        printf("Enter your password\n");
        scanf("%s", password);
        if(!strcmp(password, temp ->password))
        {
            system("cls");
            deleteConsumer(cname, &head);
            printf("Sorry for the inconvenience. Your account has been successfully deleted!\n");
            return 1;
        }
        else
        {
            system("cls");
            printf("ACCESS DENIED!\nREASON : Wrong password\n");
            return 0;
        }
    }
}

void loggedInMenu(char * name)
{
    int choice;
    while(choice != 5)
    {
        loggedInUI(name);
        scanf("%d", &choice);
        system("cls");
        switch(choice)
        {
            case 1: printf("Selected 1\n");enterTweet(name, cons);break;
            case 2: printf("Selected 2\n");viewMyTweet(name, name, cons);break;
            case 3: printf("Selected 3\n");viewTweet(cons, name);break;
            case 4: printf("Selected 4\n");
                    if(deleteAccount(name, cons))
                    {
                        name = NULL;
                        return;
                    }
                    break;
            case 5: printf("Selected 5\nBye %s. You have logged out!\n", name);
                    name = NULL;
                    break;
            default :system("cls");
                     printf("******ERROR in SELECTION! Please Select valid choice******\n");
                     break;
        }
    }
}

void loginUI()
{
    printf("_____________________________________________________________________________________________________________________\n\n");
    printf("                                                                         +------------------------------------------+\n");
    printf("                                                                         |           You are at login page          |\n");
    printf("                                                                         +------------------------------------------+\n\n\n");
    printf("\t\t\t\t\t+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n");
    printf("\t\t\t\t\t|               MartinsTwitter              |\n");
    printf("\t\t\t\t\t+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n");
    printf("\t\t\t\t\t|      1. Log in to an existing account     |\n");
    printf("\t\t\t\t\t|___________________________________________|\n");
    printf("\t\t\t\t\t|      2. Create an account                 |\n");
    printf("\t\t\t\t\t|___________________________________________|\n");
    printf("\t\t\t\t\t|      3. Quit Program                      |\n");
    printf("\t\t\t\t\t|___________________________________________|\n");
}

int login()
{
    char password[10];
    printf("\t\t\t\t\t+--------------------------------------+\n");
    printf("\t\t\t\t\t|           Enter Account name         |\n");
    printf("\t\t\t\t\t+--------------------------------------+\n");
    fflush(stdin);
    scanf("%s", name);
    int i = containsConsumer(name, &cons);
    if(i == -1)
    {
        system("cls");
        printf("The Account doesn't exist\n");
    }
    else
    {
        consumer * temp = (cons);
        for(; i != 0; i--){temp = temp -> next;}
        fflush(stdin);
        printf("\t\t\t\t\t+--------------------------------------+\n");
        printf("\t\t\t\t\t|           Enter your password        |\n");
        printf("\t\t\t\t\t+--------------------------------------+\n");
        scanf("%s", password);
        if(!strcmp(password, temp ->password))
        {
            return 1;
        }
        else
        {
            printf("\t\t\t\t\t+--------------------------------------+\n");
            printf("\t\t\t\t\t|You must have forgotten your password |\n");
            printf("\t\t\t\t\t+--------------------------------------+\n");
            printf("\t\t\t\t+------------------------------------------------------+\n");
            printf("\t\t\t\t|   You have one more try at the correct password      |\n");
            printf("\t\t\t\t+------------------------------------------------------+\n");
            fflush(stdin);
            printf("\t\t\t\t\t+--------------------------------------+\n");
            printf("\t\t\t\t\t|          Enter your password         |\n");
            printf("\t\t\t\t\t+--------------------------------------+\n");
            scanf("%s", password);
            if(strcmp(password, temp ->password))
            {
                system("cls");
                printf("You seem to have forgotten your password\n");
                printf("You can login when you remember your password :D\n");
                return 0;
            }
            else return 1;
        }
    }
}

int createAccount()
{
    char password[10], pass2[10];
    printf("\t\t\t\t\t+--------------------------------------+\n");
    printf("\t\t\t\t\t|          Enter Account name          |\n");
    printf("\t\t\t\t\t+--------------------------------------+\n");
    scanf("%s", name);
    if(containsConsumer(name, &cons) != -1)
    {
        system("cls");
        printf("Account already exists! Try logging in.\n");
        return 0;
    }
    fflush(stdin);
    printf("\t\t\t\t\t+--------------------------------------+\n");
    printf("\t\t\t\t\t|         Enter your password          |\n");
    printf("\t\t\t\t\t+--------------------------------------+\n");
    scanf("%s", password);
    printf("\t\t\t\t\t+--------------------------------------+\n");
    printf("\t\t\t\t\t|      Enter your password again       |\n");
    printf("\t\t\t\t\t+--------------------------------------+\n");
    scanf("%s", pass2);
    if(!strcmp(password,pass2)) addToConsumerList(name, password, &cons);
    else
    {
        system("cls");
        printf("Passwords didn't match. Try again later. :( \n");
        return 0;
    }
    return 1;
}

void loginMenu()
{
    initEncryptConsumer();
    initTweets();
    int choice;
    while(choice != 3)
    {
        loginUI();
        scanf("%d", &choice);
        system("cls");
        switch(choice)
        {
            case 1: printf("Selected 1\n");
                    if(login())
                    {
                        system("cls");
                        printf("You have logged in successfully\n");
                        loggedInMenu(name);
                    }
                    break;
            case 2: printf("Selected 2\n");
                    if(createAccount())
                    {
                        system("cls");
                        printf("Account created successfully and logged in!\n");
                        loggedInMenu(name);
                    }
                    break;
            case 3: printf("Selected 3\n~Bye\n");saveTweets(&cons);saveEncryptAccounts(&cons);break;
            default :system("cls");
                     printf("******ERROR in SELECTION! Please Select valid choice******\n");
                     break;
        }
    }
}

int main()
{
    loginMenu();
    return 0;
}

#endif
