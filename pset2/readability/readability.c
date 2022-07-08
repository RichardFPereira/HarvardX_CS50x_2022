#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    int count = 0, letters = 0, words = 0, sentences = 0;
    float L = 0, S = 0, grade = 0;
    string text = get_string("Text: ");

    //Count the number of letters in the sentence
    for (int i = 0; i < strlen(text); i++)
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            count++;
        }
    }
    letters = count;

    //Reset 'count' to 1 to count the number of words including the last word
    count = 1;

    //Loop to count the number of spaces to know the number of words
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == ' ')
        {
            count++;
        }
    }
    words = count;

    count = 0;
    //Loop to count the number of sentences based on punctuation marks
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count++;
        }
    }
    sentences = count;

    //Calculate the average numbers of letters per 100 words (L)
    L = (letters * 100.0) / words;
    //Calculate the average number of sentences epr 100 words (S)
    S = (sentences * 100.0) / words;

    //Calculate the grade of the text
    grade = (0.0588 * L) - (0.296 * S) - 15.8;

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }

    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", grade);
    }
    //printf("Letters: %i.\nWords: %i.\nSentences: %i.\n", letters, words, sentences);
}