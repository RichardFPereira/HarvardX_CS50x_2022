#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    FILE *file = fopen("dictionaries/small", "r");
    char word[46];
    int i = 0, index = 0;
    while (fscanf(file, "%s", word) != EOF)
    {
        if(toupper(word[i]) - 'A' >= 0 && toupper(word[i]) - 'A' < 26)
        {
            index = toupper(word[i]) - 65;
            printf("%i\n", index);
        }
    }
    fclose(file);
}