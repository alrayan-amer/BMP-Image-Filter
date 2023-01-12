#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; ++i){
        for (int j = 0; j < width; ++j){
            int grey = round((image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0);
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = grey;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; ++i){
        for (int j = 0; j < width; ++j){
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;
            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
            if (sepiaRed > 255.0){
                sepiaRed = 255.0;
            }
            if (sepiaGreen > 255.0){
                sepiaGreen = 255.0;
            }
            if (sepiaBlue > 255.0){
                sepiaBlue = 255.0;
            }

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; ++i){
        if (width % 2 == 0){
            for ( int j = 0; j < width / 2; ++j){
                temp[i][j] = image[i][j];
                image[i][j] = image[i][width - (j + 1)];
                image[i][width - (j + 1)] = temp[i][j];
            }
        }
        else if (width % 2 != 0){
            for (int k = 0; k < (width - 1) / 2; ++k){
                temp[i][k] = image[i][k];
                image[i][k] = image[i][width - (k + 1)];
                image[i][width - (k + 1)] = temp[i][k];
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sumBlue = 0;
            float sumGreen = 0;
            float sumRed = 0;
            float count = 0;

            for (int k = -1; k < 2; k++)
            {
                for (int x = -1; x < 2; x++)
                {
                    if (i + k < 0 || i + k > height - 1)
                    {
                        continue;
                    }

                    if (j + x < 0 || j + x > width - 1)
                    {
                        continue;
                    }

                    sumBlue += image[i + k][j + x].rgbtBlue;
                    sumGreen += image[i + k][j + x].rgbtGreen;
                    sumRed += image[i + k][j + x].rgbtRed;
                    count++;
                }
            }

            temp[i][j].rgbtBlue = round(sumBlue / count);
            temp[i][j].rgbtGreen = round(sumGreen / count);
            temp[i][j].rgbtRed = round(sumRed / count);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }

    }

    return;
}
