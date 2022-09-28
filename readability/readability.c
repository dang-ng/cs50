#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>


int main(void)
{
    string text = get_string("Text: ");

    int length = strlen(text);
//count letters ***************************************
    int letters = 0;
    for (int i = 0; i <= length; i++)
    {
        if (isalnum(text[i]))
        {
            letters++;
        }
        else
        {
            continue;
        }
    }

//count words ***************************************
    int words = 0;
    for (int i = 0; i <= length; i++)
    {
        if ((text[i]) == ' ' && (text[i + 1] != ' '))
        {
            words++;
        }
        else
        {
            continue;
        }
    }

//count sentences ***************************************
    int sentences = 0;
    for (int i = 0; i <= length; i++)
    {
        if ((text[i]) == '.' || (text[i] == '!') || (text[i] == '?'))
        {
            sentences++;
        }
        else
        {
            continue;
        }
    }

//summary ***************************************
    // printf("%d letters\n", letters);
    // printf("%d words\n", words+1);
    // printf("%d sentences\n", sentences);
    float L = (float)letters / (words + 1) * 100;
    float S = (float)sentences / (words + 1) * 100;
    float beforeindex = (0.0588 * L) - (0.296 * S) - 15.8;
    int index = round(beforeindex);
    // printf("%.2f\n", L);
    // printf("%.2f\n", S);
    // printf("%.2f\n", beforeindex);
    // printf("%d\n", index);
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", index);
    }
}

