#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int average;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
int maxsepia(value)
{
    if (value > 255)
    {
        value = 255;
    }
    return value;
};

void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            image[i][j].rgbtBlue = maxsepia(sepiaBlue);
            image[i][j].rgbtGreen = maxsepia(sepiaGreen);
            image[i][j].rgbtRed = maxsepia(sepiaRed);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[0][0];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < round(width / 2); j++)
        {
            // if ( width%2==0)
            temp[0][0] = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp[0][0];
        }
    }
    return;
}

// Blur image
// int min (value){
//     if (value<0) value = 0;
//     else if (value>=heigh)
//     return value;
// }

// int blurfunc (height, width, value)
// {
//     image[height][width].rgbtBlue = round((image[min(height-1)][width-1].rgbtBlue + image[height-1][width].rgbtBlue
// + image[height-1][width+1].rgbtBlue + image[height][width-1].rgbtBlue + image[height][width].rgbtBlue
// + image[height][width+1].rgbtBlue + image[height+1][width-1].rgbtBlue + image[height+1][width].rgbtBlue
// + image[height+1][width+1].rgbtBlue)/9.0);
// }

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

// ***********************************************************
    int sumBlue = 0, sumGreen = 0, sumRed = 0;
    float num = 0.0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sumBlue = 0;
            sumGreen = 0;
            sumRed = 0;
            num = 0.0;
            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    if (i + x < 0 || j + y < 0)
                    {
                        continue;
                    }

                    else if (i + x >= height || j + y >= width)
                    {
                        continue;
                    }
                    else
                    {
                        sumBlue += copy[i + x][j + y].rgbtBlue;
                        sumGreen += copy[i + x][j + y].rgbtGreen;
                        sumRed += copy[i + x][j + y].rgbtRed;
                        num ++;
                    }
                }
            }
            image[i][j].rgbtBlue = round(sumBlue / num);
            image[i][j].rgbtGreen = round(sumGreen / num);
            image[i][j].rgbtRed = round(sumRed / num);
        }
    }

    return;
}
