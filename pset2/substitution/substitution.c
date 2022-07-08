#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

//Global variables declaration to be used inside main and inside other functions
int check = 0, count = 0;
char holder;

int verifyCommandLine();
int verifyKeyLength();
int verifyOnlyLetters();
int verifyNoRepeat();

//Main function declared with argc and argv to receive values
int main(int argc, string argv[])
{
    check = verifyCommandLine(argc);

    //The check variable is utilized many times to ensure some conditions, this one is to garantee that the user put two arguments in the command line
    if (check == 1)
    {
        printf("The command should be a single command-line argument, not more not less.\n");
        return 1;
    }
    else
    {
        string key = argv[1];
        int length = strlen(key);

        //Check if the second argument (argv) is a string with 26 characters
        check = verifyKeyLength(length);

        if (check == 1)
        {
            printf("The key must contains 26 letters.\n");
            return 1;
        }
        else
        {
            //Verify if the key has only letters
            check = verifyOnlyLetters(key);

            if (check == 1)
            {
                printf("The key must have only letters.\n");
                return 1;
            }
            else
            {
                //Verify if the key has only non-repeated letters
                check = verifyNoRepeat(key);

                if (check == 1)
                {
                    printf("The key must have non-repeated letters.\n");
                    return 1;
                }
                else
                {
                    string text = get_string("plaintext:  ");
                    string cipher = text;

                    for (int i = 0; i < strlen(text); i++)
                    {
                        //Verify if the symbol is a letter between lowercase 'a' and lowercase 'z'
                        if (text[i] >= 'a' && text[i] <= 'z')
                        {
                            count = 0;
                            //'holder' variable receives the letter and will be used to count it's position in alphaet
                            for (holder = text[i]; holder != 'a'; holder --)
                            {
                                count ++;
                            }
                            //Switch the original letter with it's equivalent in the 'key' and maintain the output in lowercase
                            cipher[i] = tolower(key[count]);
                        }
                        //Verfify if the symbol is a letter between uppercase 'A' and uppercase 'Z'
                        else if (text[i] >= 'A' && text[i] <= 'Z')
                        {
                            count = 0;
                            //
                            for (holder = text[i]; holder != 'A'; holder --)
                            {
                                count ++;
                            }
                            //Switch the original letter with it's equivalent in the 'key' and maintain the ouput in uppercase
                            cipher[i] = toupper(key[count]);
                        }
                        else
                        {
                            //If the input isn't a letter, it'll keep it to the output value
                            cipher[i] = text[i];
                        }
                    }
                    printf("ciphertext: %s\n", cipher);
                }
            }
        }
    }
}

//It'll verify if the user just typed the command line with only one key
int verifyCommandLine(argc)
{
    if (argc != 2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//Verify if the key length has 26 characters
int verifyKeyLength(length)
{
    if (length == 26)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

//Verify if the user typed only letters in the key
int verifyOnlyLetters(string key)
{
    check = 0;
    for (int i = 0; i < 26; i ++)
    {
        if ((key[i] >= 'a' && key[i] <= 'z') || (key[i] >= 'A' && key[i] <= 'Z'))
        {

        }
        else
        {
            check = 1;
            break;
        }
    }
    if (check == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

//Verify if the key command doesn't have repeated letters
int verifyNoRepeat(string key)
{
    check = 0;
    char c;
    for (int i = 0; i < 26; i++)
    {
        c = key[i];
        if (i > 0)
        {
            for (int j = (i - 1); j >= 0; j--)
            {
                if (c == key[j])
                {
                    check = 1;
                    break;
                }
            }
        }
    }
    if (check == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}