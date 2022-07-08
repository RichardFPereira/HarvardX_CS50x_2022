#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    //Verify if player 1 scored higher than player two and print winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else
    {
        //Verify if both words scored iqual and print "Tie!"
        if (score1 == score2)
        {
            printf("Tie!\n");
        }

        //Last case is the player 2 as the winner
        else
        {
            printf("Player 2 wins!\n");
        }
    }
}

//Function to score each player's word
int compute_score(string word)
{
    //Variable total to hold total points and variable score to hold each letter score
    int total = 0, score = 0;

    //For loop to scan each letter of the word using the variable 'i' while it is less than the word lenght
    for (int i = 0; i < strlen(word); i++)
    {
        int letter = word[i];

        //Verify the current letter and see if it's an uppercase letter
        if ((letter > 64) && (letter < 91))
        {
            //If the letter is an uppercase letter will match to its position in the 'POINTS' array
            score = letter - 65;
            score = POINTS[score];
        }

        else
        {
            //Check if the letter is lowercase and convert to it's equivalent uppercase letter and score it
            if ((letter > 96) && (letter < 123))
            {
                letter = letter - 32;
                score = letter - 65;
                score = POINTS[score];
            }
            //If the char isn't a lowercase nor an uppercase letter it's not going to score points
            else
            {
                score = 0;
            }
        }
        total = total + score;
    }
    return total;
}
