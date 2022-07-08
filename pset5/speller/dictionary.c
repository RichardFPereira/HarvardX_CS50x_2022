// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

int totalWords = 0;

FILE *file;

// Uses a sum of the numbers to each letter times 45 max letters in one word (26 * 70 = 1170)
const unsigned int N = 1170;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Creates an index to the word and a temporary table to that index
    int hashIndex = hash(word);
    node *tempTable;
    tempTable = table[hashIndex];

    //Verifies if the word is in table.word (dictionary) and return true
    while (tempTable != NULL)
    {
        if (strcasecmp(tempTable->word, word) == 0)
        {
            return true;
        }
        tempTable = tempTable->next;
    }

    //Retur false if the word isn't in dictionary
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int i = 0, index = 0;

    //Loop through the string letter by letter checking each value and adding them up
    for (i = 0; i < strlen(word); i++)
    {
        if (toupper(word[i]) - 65 >= 0 && toupper(word[i]) - 65 < 25)
        {
            index = index + (toupper(word[i]) - 65);
        }
    }
    return index;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    file = fopen(dictionary, "r");

    char actualWord[LENGTH + 1];

    //If the file is empty, close the file and return false
    if (file == NULL)
    {
        fclose(file);
        return false;
    }

    // Read word by word and allocate memory to a new word
    while (fscanf(file, "%s", actualWord) != EOF)
    {
        node *newWord = malloc(sizeof(node));
        {
            if (newWord == NULL)
            {
                return false;
            }
            // Copy the string to a new node
            strcpy(newWord->word, actualWord);
            newWord->next = NULL;

            // Look inside the hash to see if it's null and put a new word there
            // If it's not null include the new word in the end of the hash
            int hashIndex = hash(actualWord);
            if (table[hashIndex] == NULL)
            {
                table[hashIndex] = newWord;
            }
            else
            {
                newWord->next = table[hashIndex];
                table[hashIndex] = newWord;
            }
        }
        // Count the words in dictionary
        totalWords++;
    }
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Return the size of dictionary
    return totalWords;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *head = table[i];
        node *cursor = head;
        node *tmp = cursor;

        // Free memory hash by hash without loosing track of the next hash
        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    //Close the dictionary file
    fclose(file);
    return true;
}