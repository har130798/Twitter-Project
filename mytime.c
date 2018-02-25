/* */
#ifndef mytime
#define mytime

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

char * mystrcat(const char * str1, const char * str2, const char delimiter)
{
    int i = 0, j, size;
    char * output;

    if(str1 == NULL && str2 != NULL)
    {
        size = strlen(str2) + 1;

        output = (char *)malloc(size);
        output[i] = delimiter;

        for(j = 0; str2[j] != '\0'; j++)
        {
            output[i+1+j] = str2[j];
        }
        output[i+1+j] = '\0';
    }

    if(str2 == NULL && str1 != NULL)
    {
        size = strlen(str1) + 1;

        output = (char *)malloc(size);
        for(i = 0; str1[i] != '\0'; i++)
        {
            output[i] = str1[i];
        }
        output[i] = delimiter;
        output[i+1] = '\0';

    }

    if(str1 == NULL && str2 == NULL)
    {
        output = NULL;
    }

    if(str1 != NULL && str2 != NULL)
    {
        size = strlen(str1) + strlen(str2) + 1;

        output = (char *)malloc(size);

        for(i = 0; str1[i] != '\0'; i++)
        {
            output[i] = str1[i];
        }
        output[i] = delimiter;

        for(j = 0; str2[j] != '\0'; j++)
        {
            output[i+1+j] = str2[j];
        }
        output[i+1+j] = '\0';

    }

    return output;
}
// Converts int to char
char * i2c(int num)
{
    int temp = num, digits = 0;
    if(num != 0)
        while(temp != 0)
        {
            temp = temp / 10;
            digits++;
        }
    else digits = 1;

    char * output;
    int i, flag = 0, fin;
    if(num < 0)
    {
        output = (char *)malloc((digits+2) * sizeof(char));
        output[0] = '-';
        flag = 1;
        fin = digits+2;
        num *= -1;

    }
    else
    {
        output = (char *)malloc((digits+1) * sizeof(char));
        fin = digits+1;
    }

    for(i = fin-2; i >= flag; i--)
    {
        output[i] = num % 10 + 48;
        num = num / 10;
    }

    output[fin-1] = '\0';

    return output;
}

char * getDate()
{
    time_t t = time(NULL);
    struct tm * tm = localtime(&t);

    char * date;
    date = i2c(tm->tm_mday);
    date = mystrcat(date, i2c(tm->tm_mon + 1), '-');
    date = mystrcat(date, i2c(tm->tm_year + 1900), '-');

    char * Date = (char *)malloc(strlen(date) * sizeof(char));
    Date = date;

    return Date;
}

char * getDateTime()
{
    time_t t = time(NULL);
    struct tm * tm = localtime(&t);

    char * date;
    date = i2c(tm->tm_mday);
    date = mystrcat(date, i2c(tm->tm_mon + 1), '-');
    date = mystrcat(date, i2c(tm->tm_year + 1900), '-');
    char * time;
    time = i2c(tm->tm_hour);
    time = mystrcat(time, i2c(tm->tm_min), ':');

    char * dateTime = (char *)malloc((strlen(time) + strlen(date)) * sizeof(char));
    dateTime = mystrcat(time, date, '~');

    return dateTime;
}

#endif
