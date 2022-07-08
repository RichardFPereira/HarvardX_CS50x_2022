#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//Defines the size of each block of information (512 Bytes)
const int jpgSize = 512;

int main(int argc, char *argv[])
{
    //Variable to receive the jpg data and recover the image into a new file
    unsigned char buffer[jpgSize];

    //Counter to track when a image is found
    int imageCount = 0;

    //String to track the number of images we've found
    char fileName[] = "000.jpg";

    //Condition to check if the user typed the correct command-line with the name of the program and the forensic image
    if (argc != 2)
    {
        printf("The command-line should have only one argument.(Exemple: ./recover IMAGE)\n");
        return 1;
    }

    //Open the forensic image file in reading mode and declare a pointer to our output
    FILE *forensicImage = fopen(argv[1], "r");
    FILE *outputImage = NULL;

    //Check if the input file isn't empty
    if (forensicImage == NULL)
    {
        printf("The file isn't working.\n");
        return 1;
    }
    else
    {
        //Read blocks of 512 Bytes in our input file
        while (fread(buffer, 1, jpgSize, forensicImage) == jpgSize)
        {

            //Check if the header is equivalent with a jpg header
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] >= 0xe0 && buffer[3] <= 0xef))
            {
                //If it's a jpg, write the file name to the file position
                sprintf(fileName, "%03i.jpg", imageCount);

                //Open the output file in writing mode and give the name of curent imagem number
                outputImage = fopen(fileName, "w");

                //Track the correct number to current jpg image
                imageCount++;
            }
            //Check if the created file is valid to use
            if (outputImage != NULL)
            {
                //Write the jpg data found in a new output
                fwrite(buffer, sizeof(char), 512, outputImage);
            }
        }
    }
    //Close files
    fclose(forensicImage);
    fclose(outputImage);
    return 0;
}