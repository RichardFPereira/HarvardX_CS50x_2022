#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float averagePixel;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++) //Two loops concatenated to scan all pixels in the image starting with first row and first column
        {
            averagePixel = ( (float)image[i][j].rgbtBlue + (float)image[i][j].rgbtGreen + (float)image[i][j].rgbtRed) / 3; //Convert each data of RGB to float type,sum them and devide by 3
            averagePixel = round(averagePixel); //Function round used to convert the float value to an integer number
            image[i][j].rgbtBlue = averagePixel; //Using the same value of RGB will turn the pixel gray
            image[i][j].rgbtGreen = averagePixel;
            image[i][j].rgbtRed = averagePixel;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float originalBlue, originalGreen, originalRed, sepiaBlue, sepiaGreen, sepiaRed;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            originalBlue = image[i][j].rgbtBlue; //Get the original value of blue in actual pixel
            originalGreen = image[i][j].rgbtGreen;//Get the original value of green in actual pixel
            originalRed = image[i][j].rgbtRed;//Get the original value of red in actual pixel

            sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue; //Calculation used to pick up the correct "amount" of blue to use in sepia filter
            if (sepiaBlue > 255) //Condition to limit the max value of blue in 255
            {
                sepiaBlue = 255;
            }
            else if (sepiaBlue < 0)
            {
                sepiaBlue = 0; //Condition to limit the min value of blue in 0
            }

            sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue; //Calculation used to pick up the correct "amount" of green to use in sepia filter
            if (sepiaGreen > 255) //Condition to limit the max value of green in 255
            {
                sepiaGreen = 255;
            }
            else if (sepiaGreen < 0)
            {
            sepiaGreen = 0; //Condition to limit the min value of green in 0
            }

            sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue; //Calculation used to pick up the correct "amount" of red to use in sepia filter
            if (sepiaRed > 255) //Condition to limit the max value of red in 255
            {
                sepiaRed = 255;
            }
            else if (sepiaRed < 0)
            {
                sepiaRed = 0; //Condition to limit the min value of red in 0
            }

            sepiaBlue = round(sepiaBlue); //Function round used to convert the float value to an integer number
            sepiaGreen = round(sepiaGreen);
            sepiaRed = round(sepiaRed);

            image[i][j].rgbtBlue = sepiaBlue; //Replacing the original values of RGB with new values of sepia filter
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int count = width - 1;
            temp[i][count - j].rgbtBlue = image[i][j].rgbtBlue; //The values of RGB will be stored in a new array but in the oposite horizontal side to make the reflection filter
            temp[i][count - j].rgbtGreen = image[i][j].rgbtGreen;
            temp[i][count - j].rgbtRed = image[i][j].rgbtRed;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue; //The original array (image[][]) receives the new image horizontaly inverted
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float averageBlue = 0, averageGreen = 0, averageRed = 0; //To blur an image we need to pick up the average between the pixel itself and the nearby pixels and replace the original
    RGBTRIPLE tempArray[height][width]; //To insure all values will be calculated with original values we will place new values in a temporary array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 && j == 0) //Blur top left corner pixel(0,0)
            {
                averageBlue = 0;
                averageGreen = 0;
                averageRed = 0;
                for (int a = 0; a < 2; a++)
                {
                    for (int b = 0; b < 2; b++)
                    {
                        averageBlue += image[a][b].rgbtBlue; //The pixels on the corners only have three neighbors. So we sum its value with the valeu of those three for each color (RGB)
                        averageGreen += image[a][b].rgbtGreen;
                        averageRed += image[a][b].rgbtRed;
                    }
                }

                averageBlue = averageBlue / 4; //Calculate the average between the four values to each RGB color
                averageGreen = averageGreen / 4;
                averageRed = averageRed / 4;
                tempArray[i][j].rgbtBlue = round(averageBlue);//Round the average value and fill the new array with the pixel already blurred
                tempArray[i][j].rgbtGreen = round(averageGreen);
                tempArray[i][j].rgbtRed = round(averageRed);
            }

            else if (i == 0 && j == (width - 1)) //Blur top right corner pixel(0,width-1). Same concept used in top left corner.
            {
                averageBlue = 0;
                averageGreen = 0;
                averageRed = 0;
                for (int a = 0; a < 2; a++)
                {
                    for (int b = 1; b < 3; b++)
                    {
                        averageBlue += image[a][width - b].rgbtBlue;
                        averageGreen += image[a][width - b].rgbtGreen;
                        averageRed += image[a][width - b].rgbtRed;
                    }
                }
                averageBlue = averageBlue / 4;
                averageGreen = averageGreen / 4;
                averageRed = averageRed / 4;
                tempArray[i][j].rgbtBlue = round(averageBlue);
                tempArray[i][j].rgbtGreen = round(averageGreen);
                tempArray[i][j].rgbtRed = round(averageRed);
            }

            else if (i == (height - 1) && j == 0) //Blur bottom left corner pixel (height-1, 0). Same concept used in top left corner.
            {
                averageBlue = 0;
                averageGreen = 0;
                averageRed = 0;
                for (int a = 1; a < 3; a++)
                {
                    for (int b = 0; b < 2; b++)
                    {
                        averageBlue += image[height - a][b].rgbtBlue;
                        averageGreen += image[height - a][b].rgbtGreen;
                        averageRed += image[height - a][b].rgbtRed;
                    }
                }
                averageBlue = averageBlue / 4;
                averageGreen = averageGreen / 4;
                averageRed = averageRed / 4;
                tempArray[i][j].rgbtBlue = round(averageBlue);
                tempArray[i][j].rgbtGreen = round(averageGreen);
                tempArray[i][j].rgbtRed = round(averageRed);
            }

            else if (i == (height - 1) && j == (width - 1)) //Blur bottom right corner pixel (height-1,widht-1). Same concept used in top left corner.
            {
                averageBlue = 0;
                averageGreen = 0;
                averageRed = 0;
                for (int a = 1; a < 3; a++)
                {
                    for (int b = 1; b < 3; b++)
                    {
                        averageBlue += image[height - a][width - b].rgbtBlue;
                        averageGreen += image[height - a][width - b].rgbtGreen;
                        averageRed += image[height - a][width - b].rgbtRed;
                    }
                }
                averageBlue = averageBlue / 4;
                averageGreen = averageGreen / 4;
                averageRed = averageRed / 4;
                tempArray[i][j].rgbtBlue = round(averageBlue);
                tempArray[i][j].rgbtGreen = round(averageGreen);
                tempArray[i][j].rgbtRed = round(averageRed);
            }

            else if (i == 0 && (j > 0 && j < (width - 1))) //Blur first row. The pixels in the first and last row and the first and last column only have 5 neighbors.
            {
                averageBlue = 0;
                averageGreen = 0;
                averageRed = 0;
                for (int a = 0; a < 2; a++)
                {
                    for (int b = -1; b < 2; b++)
                    {
                        averageBlue += image[i + a][j + b].rgbtBlue; //Scan and sum the values of the 5 neighbors with the pixel itself value
                        averageGreen += image[i + a][j + b].rgbtGreen;
                        averageRed += image[i + a][j + b].rgbtRed;
                    }
                }
                averageBlue = averageBlue / 6; //Calculate the average between the six values to each color (RGB)
                averageGreen = averageGreen / 6;
                averageRed = averageRed / 6;
                tempArray[i][j].rgbtBlue = round(averageBlue); //Round the average value and fill the new array with the pixel already blurred
                tempArray[i][j].rgbtGreen = round(averageGreen);
                tempArray[i][j].rgbtRed = round(averageRed);
            }

            else if ((i > 0 && i < (height - 1)) && j == 0) //Blur first column. Same concept used in the first row.
            {
                averageBlue = 0;
                averageGreen = 0;
                averageRed = 0;
                for (int a = -1; a < 2; a++)
                {
                    for (int  b = 0; b < 2; b++)
                    {
                        averageBlue += image[i + a][j + b].rgbtBlue;
                        averageGreen += image[i + a][j + b].rgbtGreen;
                        averageRed += image[i + a][j + b].rgbtRed;
                    }
                }
                averageBlue = averageBlue / 6;
                averageGreen = averageGreen / 6;
                averageRed = averageRed / 6;
                tempArray[i][j].rgbtBlue = round(averageBlue);
                tempArray[i][j].rgbtGreen = round(averageGreen);
                tempArray[i][j].rgbtRed = round(averageRed);
            }

            else if (i == (height - 1)  && (j > 0 && j < (width - 1))) //Blur last row. Same concept used in the first row.
            {
                averageBlue = 0;
                averageGreen = 0;
                averageRed = 0;
                for (int a = -1; a < 1; a++)
                {
                    for (int b = -1; b < 2; b++)
                    {
                        averageBlue += image[i + a][j + b].rgbtBlue;
                        averageGreen += image[i + a][j + b].rgbtGreen;
                        averageRed += image[i + a][j + b].rgbtRed;
                    }
                }
                averageBlue = averageBlue / 6;
                averageGreen = averageGreen / 6;
                averageRed = averageRed / 6;
                tempArray[i][j].rgbtBlue = round(averageBlue);
                tempArray[i][j].rgbtGreen = round(averageGreen);
                tempArray[i][j].rgbtRed = round(averageRed);
            }

            else if ((i > 0 && i < (height - 1)) && j == (width - 1)) //Blur last column. Same concept used in the first row.
            {
                averageBlue = 0;
                averageGreen = 0;
                averageRed = 0;
                for (int a = -1; a < 2; a++)
                {
                    for (int b = -1; b < 1; b++)
                    {
                        averageBlue += image[i + a][j + b].rgbtBlue;
                        averageGreen += image[i + a][j + b].rgbtGreen;
                        averageRed += image[i + a][j + b].rgbtRed;
                    }
                }
                averageBlue = averageBlue / 6;
                averageGreen = averageGreen / 6;
                averageRed = averageRed / 6;
                tempArray[i][j].rgbtBlue = round(averageBlue);
                tempArray[i][j].rgbtGreen = round(averageGreen);
                tempArray[i][j].rgbtRed = round(averageRed);
            }
            else //If the actual pixel isn't in edges or cornes the pixel will have 8 neighbors.
            {
                averageBlue = 0;
                averageGreen = 0;
                averageRed = 0;
                for (int a = -1; a < 2; a ++)
                {
                    for (int b = -1; b < 2; b++)
                    {
                        averageBlue += image[i + a][j + b].rgbtBlue; //Scan and sum the values of the 8 neighbors with the pixel itself value
                        averageGreen += image[i + a][j + b].rgbtGreen;
                        averageRed += image[i + a][j + b].rgbtRed;
                    }
                }
                averageBlue = round(averageBlue / 9); //Calculate the average between the nine values to each color (RGB)
                averageGreen= round(averageGreen / 9);
                averageRed = round(averageRed / 9);
                tempArray[i][j].rgbtBlue = averageBlue; //Round the average value and fill the new array with the pixel already blurred
                tempArray[i][j].rgbtGreen = averageGreen;
                tempArray[i][j].rgbtRed = averageRed;
            }
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = tempArray[i][j].rgbtBlue; //The original array (image[][]) receives the new blurred image
            image[i][j].rgbtGreen = tempArray[i][j].rgbtGreen;
            image[i][j].rgbtRed = tempArray[i][j].rgbtRed;
        }
    }
    return;
}