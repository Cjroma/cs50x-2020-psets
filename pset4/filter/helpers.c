#include "helpers.h"
#include <math.h>

// Check if edge is exceed
float exceed(float GX, float GY);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float avg;
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            avg = (((float)image[i][j].rgbtBlue + (float)image[i][j].rgbtGreen + (float)image[i][j].rgbtRed) / 3);
            image[i][j].rgbtBlue  = round(avg);
            image[i][j].rgbtGreen  = round(avg);
            image[i][j].rgbtRed  = round(avg);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int tempR = 0;
    int tempG = 0;
    int tempB = 0;
    for (int i = 0; i < height; ++i)
    {
        // Swap pixel's index to create reflection filter
        for (int j = 0; j < width / 2; ++j)
        {
            tempR = image[i][j].rgbtRed;
            tempG = image[i][j].rgbtGreen;
            tempB = image[i][j].rgbtBlue;
            image[i][j].rgbtRed = image[i][(width - 1) - j].rgbtRed;
            image[i][j].rgbtGreen = image[i][(width - 1) - j].rgbtGreen;
            image[i][j].rgbtBlue = image[i][(width - 1) - j].rgbtBlue;
            image[i][(width - 1) - j].rgbtRed = tempR;
            image[i][(width - 1) - j].rgbtGreen = tempG;
            image[i][(width - 1) - j].rgbtBlue  = tempB;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE cpyImage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            cpyImage[i][j] = image[i][j];
        }
    }
    float avg;
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (i == 0)
            {
                // Blur top-left corner of the image
                if (j == 0)
                {
                    avg = (((float)cpyImage[i][j].rgbtRed + (float)cpyImage[i][j + 1].rgbtRed + (float)cpyImage[i + 1][j].rgbtRed +
                            (float)cpyImage[i + 1][j + 1].rgbtRed) / 4);
                    image[i][j].rgbtRed  = round(avg);
                    avg = (((float)cpyImage[i][j].rgbtGreen + (float)cpyImage[i][j + 1].rgbtGreen + (float)cpyImage[i + 1][j].rgbtGreen +
                            (float)cpyImage[i + 1][j + 1].rgbtGreen) / 4);
                    image[i][j].rgbtGreen  = round(avg);
                    avg = (((float)cpyImage[i][j].rgbtBlue + (float)cpyImage[i][j + 1].rgbtBlue + (float)cpyImage[i + 1][j].rgbtBlue +
                            (float)cpyImage[i + 1][j + 1].rgbtBlue) / 4);
                    image[i][j].rgbtBlue  = round(avg);
                }
                // Blur top-right corner of the image
                else if (j == width - 1)
                {
                    avg = (((float)cpyImage[i][j - 1].rgbtRed + (float)cpyImage[i][j].rgbtRed + (float)cpyImage[i + 1][j - 1].rgbtRed +
                            (float)cpyImage[i + 1][j].rgbtRed) / 4);
                    image[i][j].rgbtRed  = round(avg);
                    avg = (((float)cpyImage[i][j - 1].rgbtGreen + (float)cpyImage[i][j].rgbtGreen + (float)cpyImage[i + 1][j - 1].rgbtGreen +
                            (float)cpyImage[i + 1][j].rgbtGreen) / 4);
                    image[i][j].rgbtGreen  = round(avg);
                    avg = (((float)cpyImage[i][j - 1].rgbtBlue + (float)cpyImage[i][j].rgbtBlue + (float)cpyImage[i + 1][j - 1].rgbtBlue +
                            (float)cpyImage[i + 1][j].rgbtBlue) / 4);
                    image[i][j].rgbtBlue  = round(avg);
                }
                // Blur top edge of the image
                else
                {
                    avg = (((float)cpyImage[i][j - 1].rgbtRed + (float)cpyImage[i][j].rgbtRed + (float)cpyImage[i][j + 1].rgbtRed +
                            (float)cpyImage[i + 1][j - 1].rgbtRed + (float)cpyImage[i + 1][j].rgbtRed + (float)cpyImage[i + 1][j + 1].rgbtRed) / 6);
                    image[i][j].rgbtRed  = round(avg);
                    avg = (((float)cpyImage[i][j - 1].rgbtGreen + (float)cpyImage[i][j].rgbtGreen + (float)cpyImage[i][j + 1].rgbtGreen +
                            (float)cpyImage[i + 1][j - 1].rgbtGreen + (float)cpyImage[i + 1][j].rgbtGreen + (float)cpyImage[i + 1][j + 1].rgbtGreen) / 6);
                    image[i][j].rgbtGreen  = round(avg);
                    avg = (((float)cpyImage[i][j - 1].rgbtBlue + (float)cpyImage[i][j].rgbtBlue + (float)cpyImage[i][j + 1].rgbtBlue +
                            (float)cpyImage[i + 1][j - 1].rgbtBlue + (float)cpyImage[i + 1][j].rgbtBlue + (float)cpyImage[i + 1][j + 1].rgbtBlue) / 6);
                    image[i][j].rgbtBlue  = round(avg);
                }
            }
            else if (i == height - 1)
            {
                // Blur bottom-left corner of the image
                if (j == 0)
                {
                    avg = (((float)cpyImage[i - 1][j].rgbtRed + (float)cpyImage[i - 1][j + 1].rgbtRed + (float)cpyImage[i][j].rgbtRed +
                            (float)cpyImage[i][j + 1].rgbtRed) / 4);
                    image[i][j].rgbtRed  = round(avg);
                    avg = (((float)cpyImage[i - 1][j].rgbtGreen + (float)cpyImage[i - 1][j + 1].rgbtGreen + (float)cpyImage[i][j].rgbtGreen +
                            (float)cpyImage[i][j + 1].rgbtGreen) / 4);
                    image[i][j].rgbtGreen  = round(avg);
                    avg = (((float)cpyImage[i - 1][j].rgbtBlue + (float)cpyImage[i - 1][j + 1].rgbtBlue + (float)cpyImage[i][j].rgbtBlue +
                            (float)cpyImage[i][j + 1].rgbtBlue) / 4);
                    image[i][j].rgbtBlue  = round(avg);
                }
                // Blur bottom-right corner of the image
                else if (j == width - 1)
                {
                    avg = (((float)cpyImage[i - 1][j - 1].rgbtRed + (float)cpyImage[i - 1][j].rgbtRed + (float)cpyImage[i][j - 1].rgbtRed +
                            (float)cpyImage[i][j].rgbtRed) / 4);
                    image[i][j].rgbtRed  = round(avg);
                    avg = (((float)cpyImage[i - 1][j - 1].rgbtGreen + (float)cpyImage[i - 1][j].rgbtGreen + (float)cpyImage[i][j - 1].rgbtGreen +
                            (float)cpyImage[i][j].rgbtGreen) / 4);
                    image[i][j].rgbtGreen  = round(avg);
                    avg = (((float)cpyImage[i - 1][j - 1].rgbtBlue + (float)cpyImage[i - 1][j].rgbtBlue + (float)cpyImage[i][j - 1].rgbtBlue +
                            (float)cpyImage[i][j].rgbtBlue) / 4);
                    image[i][j].rgbtBlue  = round(avg);
                }
                // Blur bottom edge of the image
                else
                {
                    avg = (((float)cpyImage[i - 1][j - 1].rgbtRed + (float)cpyImage[i - 1][j].rgbtRed + (float)cpyImage[i - 1][j + 1].rgbtRed +
                            (float)cpyImage[i][j - 1].rgbtRed + (float)cpyImage[i][j].rgbtRed + (float)cpyImage[i][j + 1].rgbtRed) / 6);
                    image[i][j].rgbtRed  = round(avg);
                    avg = (((float)cpyImage[i - 1][j - 1].rgbtGreen + (float)cpyImage[i - 1][j].rgbtGreen + (float)cpyImage[i - 1][j + 1].rgbtGreen +
                            (float)cpyImage[i][j - 1].rgbtGreen + (float)cpyImage[i][j].rgbtGreen + (float)cpyImage[i][j + 1].rgbtGreen) / 6);
                    image[i][j].rgbtGreen  = round(avg);
                    avg = (((float)cpyImage[i - 1][j - 1].rgbtBlue + (float)cpyImage[i - 1][j].rgbtBlue + (float)cpyImage[i - 1][j + 1].rgbtBlue +
                            (float)cpyImage[i][j - 1].rgbtBlue + (float)cpyImage[i][j].rgbtBlue + (float)cpyImage[i][j + 1].rgbtBlue) / 6);
                    image[i][j].rgbtBlue  = round(avg);
                }
            }
            // Blur left edge of the image
            else if (j == 0)
            {
                avg = (((float)cpyImage[i - 1][j].rgbtRed + (float)cpyImage[i - 1][j + 1].rgbtRed + (float)cpyImage[i][j].rgbtRed +
                        (float)cpyImage[i][j + 1].rgbtRed + (float)cpyImage[i + 1][j].rgbtRed + (float)cpyImage[i + 1][j + 1].rgbtRed) / 6);
                image[i][j].rgbtRed  = round(avg);
                avg = (((float)cpyImage[i - 1][j].rgbtGreen + (float)cpyImage[i - 1][j + 1].rgbtGreen + (float)cpyImage[i][j].rgbtGreen +
                        (float)cpyImage[i][j + 1].rgbtGreen + (float)cpyImage[i + 1][j].rgbtGreen + (float)cpyImage[i + 1][j + 1].rgbtGreen) / 6);
                image[i][j].rgbtGreen  = round(avg);
                avg = (((float)cpyImage[i - 1][j].rgbtBlue + (float)cpyImage[i - 1][j + 1].rgbtBlue + (float)cpyImage[i][j].rgbtBlue +
                        (float)cpyImage[i][j + 1].rgbtBlue + (float)cpyImage[i + 1][j].rgbtBlue + (float)cpyImage[i + 1][j + 1].rgbtBlue) / 6);
                image[i][j].rgbtBlue  = round(avg);
            }
            // Blur right edge of the image
            else if (j == width - 1)
            {
                avg = (((float)cpyImage[i - 1][j - 1].rgbtRed + (float)cpyImage[i - 1][j].rgbtRed + (float)cpyImage[i][j - 1].rgbtRed +
                        (float)cpyImage[i][j].rgbtRed + (float)cpyImage[i + 1][j - 1].rgbtRed + (float)cpyImage[i + 1][j].rgbtRed) / 6);
                image[i][j].rgbtRed  = round(avg);
                avg = (((float)cpyImage[i - 1][j - 1].rgbtGreen + (float)cpyImage[i - 1][j].rgbtGreen + (float)cpyImage[i][j - 1].rgbtGreen +
                        (float)cpyImage[i][j].rgbtGreen + (float)cpyImage[i + 1][j - 1].rgbtGreen + (float)cpyImage[i + 1][j].rgbtGreen) / 6);
                image[i][j].rgbtGreen  = round(avg);
                avg = (((float)cpyImage[i - 1][j - 1].rgbtBlue + (float)cpyImage[i - 1][j].rgbtBlue + (float)cpyImage[i][j - 1].rgbtBlue +
                        (float)cpyImage[i][j].rgbtBlue + (float)cpyImage[i + 1][j - 1].rgbtBlue + (float)cpyImage[i + 1][j].rgbtBlue) / 6);
                image[i][j].rgbtBlue  = round(avg);
            }
            // Blur middle of the image
            else
            {
                avg = (((float)cpyImage[i - 1][j - 1].rgbtRed + (float)cpyImage[i - 1][j].rgbtRed + (float)cpyImage[i - 1][j + 1].rgbtRed +
                        (float)cpyImage[i][j - 1].rgbtRed + (float)cpyImage[i][j].rgbtRed + (float)cpyImage[i][j + 1].rgbtRed +
                        (float)cpyImage[i + 1][j - 1].rgbtRed + (float)cpyImage[i + 1][j].rgbtRed + (float)cpyImage[i + 1][j + 1].rgbtRed) / 9);
                image[i][j].rgbtRed  = round(avg);
                avg = (((float)cpyImage[i - 1][j - 1].rgbtGreen + (float)cpyImage[i - 1][j].rgbtGreen + (float)cpyImage[i - 1][j + 1].rgbtGreen +
                        (float)cpyImage[i][j - 1].rgbtGreen + (float)cpyImage[i][j].rgbtGreen + (float)cpyImage[i][j + 1].rgbtGreen +
                        (float)cpyImage[i + 1][j - 1].rgbtGreen + (float)cpyImage[i + 1][j].rgbtGreen + (float)cpyImage[i + 1][j + 1].rgbtGreen) / 9);
                image[i][j].rgbtGreen  = round(avg);
                avg = (((float)cpyImage[i - 1][j - 1].rgbtBlue + (float)cpyImage[i - 1][j].rgbtBlue + (float)cpyImage[i - 1][j + 1].rgbtBlue +
                        (float)cpyImage[i][j - 1].rgbtBlue + (float)cpyImage[i][j].rgbtBlue + (float)cpyImage[i][j + 1].rgbtBlue +
                        (float)cpyImage[i + 1][j - 1].rgbtBlue + (float)cpyImage[i + 1][j].rgbtBlue + (float)cpyImage[i + 1][j + 1].rgbtBlue) / 9);
                image[i][j].rgbtBlue  = round(avg);
            }
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE cpyImage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            cpyImage[i][j] = image[i][j];
        }
    }
    float GX = 0;
    float GY = 0;
    float edge = 0;
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (i == 0)
            {
                // Detect top-left corner of the image
                if (j == 0)
                {
                    GX = (((float)(cpyImage[i][j + 1].rgbtRed * 2) + (float)cpyImage[i + 1][j + 1].rgbtRed));
                    GY = (((float)(cpyImage[i + 1][j].rgbtRed * 2) + (float)cpyImage[i + 1][j + 1].rgbtRed));

                    image[i][j].rgbtRed  = exceed(GX, GY);

                    GX = (((float)(cpyImage[i][j + 1].rgbtGreen * 2) + (float)cpyImage[i + 1][j + 1].rgbtGreen));
                    GY = (((float)(cpyImage[i + 1][j].rgbtGreen * 2) + (float)cpyImage[i + 1][j + 1].rgbtGreen));

                    image[i][j].rgbtGreen  = exceed(GX, GY);

                    GX = (((float)(cpyImage[i][j + 1].rgbtBlue * 2) + (float)cpyImage[i + 1][j + 1].rgbtBlue));
                    GY = (((float)(cpyImage[i + 1][j].rgbtBlue * 2) + (float)cpyImage[i + 1][j + 1].rgbtBlue));

                    image[i][j].rgbtBlue  = exceed(GX, GY);
                }
                // Detect top-right corner of the image
                else if (j == width - 1)
                {
                    GX = (((float)(cpyImage[i][j - 1].rgbtRed * -2) + (float)(cpyImage[i + 1][j - 1].rgbtRed * -1)));
                    GY = (((float)cpyImage[i + 1][j - 1].rgbtRed + (float)(cpyImage[i + 1][j].rgbtRed * 2)));

                    image[i][j].rgbtRed  = exceed(GX, GY);

                    GX = (((float)(cpyImage[i][j - 1].rgbtGreen * -2) + (float)(cpyImage[i + 1][j - 1].rgbtGreen * -1)));
                    GY = (((float)cpyImage[i + 1][j - 1].rgbtGreen + (float)(cpyImage[i + 1][j].rgbtGreen * 2)));

                    image[i][j].rgbtGreen  = exceed(GX, GY);

                    GX = (((float)(cpyImage[i][j - 1].rgbtBlue * -2) + (float)(cpyImage[i + 1][j - 1].rgbtBlue * -1)));
                    GY = (((float)cpyImage[i + 1][j - 1].rgbtBlue + (float)(cpyImage[i + 1][j].rgbtBlue * 2)));

                    image[i][j].rgbtBlue  = exceed(GX, GY);
                }
                // Detect top edge of the image
                else
                {
                    GX = (((float)(cpyImage[i][j - 1].rgbtRed * -2) + (float)(cpyImage[i][j + 1].rgbtRed * 2) +
                           (float)(cpyImage[i + 1][j - 1].rgbtRed * -1) + (float)cpyImage[i + 1][j + 1].rgbtRed));
                    GY = (((float)cpyImage[i + 1][j - 1].rgbtRed + (float)(cpyImage[i + 1][j].rgbtRed * 2) +
                           (float)cpyImage[i + 1][j + 1].rgbtRed));

                    image[i][j].rgbtRed  = exceed(GX, GY);

                    GX = (((float)(cpyImage[i][j - 1].rgbtGreen * -2) + (float)(cpyImage[i][j + 1].rgbtGreen * 2) +
                           (float)(cpyImage[i + 1][j - 1].rgbtGreen * -1) + (float)cpyImage[i + 1][j + 1].rgbtGreen));
                    GY = (((float)cpyImage[i + 1][j - 1].rgbtGreen + (float)(cpyImage[i + 1][j].rgbtGreen * 2) +
                           (float)cpyImage[i + 1][j + 1].rgbtGreen));

                    image[i][j].rgbtGreen  = exceed(GX, GY);

                    GX = (((float)(cpyImage[i][j - 1].rgbtBlue * -2) + (float)(cpyImage[i][j + 1].rgbtBlue * 2) +
                           (float)(cpyImage[i + 1][j - 1].rgbtBlue * -1) + (float)cpyImage[i + 1][j + 1].rgbtBlue));
                    GY = (((float)cpyImage[i + 1][j - 1].rgbtBlue + (float)(cpyImage[i + 1][j].rgbtBlue * 2) +
                           (float)cpyImage[i + 1][j + 1].rgbtBlue));

                    image[i][j].rgbtBlue  = exceed(GX, GY);
                }
            }
            else if (i == height - 1)
            {
                // Detect bottom-left corner of the image
                if (j == 0)
                {
                    GX = (((float)cpyImage[i - 1][j + 1].rgbtRed + (float)(cpyImage[i][j + 1].rgbtRed * 2)));
                    GY = (((float)(cpyImage[i - 1][j].rgbtRed * -2) + (float)(cpyImage[i - 1][j + 1].rgbtRed * -1)));

                    image[i][j].rgbtRed  = exceed(GX, GY);

                    GX = (((float)cpyImage[i - 1][j + 1].rgbtGreen + (float)(cpyImage[i][j + 1].rgbtGreen * 2)));
                    GY = (((float)(cpyImage[i - 1][j].rgbtGreen * -2) + (float)(cpyImage[i - 1][j + 1].rgbtGreen * -1)));

                    image[i][j].rgbtGreen  = exceed(GX, GY);

                    GX = (((float)cpyImage[i - 1][j + 1].rgbtBlue + (float)(cpyImage[i][j + 1].rgbtBlue * 2)));
                    GY = (((float)(cpyImage[i - 1][j].rgbtBlue * -2) + (float)(cpyImage[i - 1][j + 1].rgbtBlue * -1)));

                    image[i][j].rgbtBlue  = exceed(GX, GY);
                }
                // Detect bottom-right corner of the image
                else if (j == width - 1)
                {
                    GX = (((float)(cpyImage[i - 1][j - 1].rgbtRed * -1) + (float)(cpyImage[i][j - 1].rgbtRed * -2)));
                    GY = (((float)(cpyImage[i - 1][j - 1].rgbtRed * -1) + (float)(cpyImage[i - 1][j].rgbtRed * -2)));

                    image[i][j].rgbtRed  = exceed(GX, GY);

                    GX = (((float)(cpyImage[i - 1][j - 1].rgbtGreen * -1) + (float)(cpyImage[i][j - 1].rgbtGreen * -2)));
                    GY = (((float)(cpyImage[i - 1][j - 1].rgbtGreen * -1) + (float)(cpyImage[i - 1][j].rgbtGreen * -2)));

                    image[i][j].rgbtGreen  = exceed(GX, GY);

                    GX = (((float)(cpyImage[i - 1][j - 1].rgbtBlue * -1) + (float)(cpyImage[i][j - 1].rgbtBlue * -2)));
                    GY = (((float)(cpyImage[i - 1][j - 1].rgbtBlue * -1) + (float)(cpyImage[i - 1][j].rgbtBlue * -2)));

                    image[i][j].rgbtBlue  = exceed(GX, GY);
                }
                // Detect bottom edge of the image
                else
                {
                    GX = (((float)(cpyImage[i - 1][j - 1].rgbtRed * -1) + (float)cpyImage[i - 1][j + 1].rgbtRed +
                           (float)(cpyImage[i][j - 1].rgbtRed * -2) + (float)(cpyImage[i][j + 1].rgbtRed * 2)));
                    GY = (((float)(cpyImage[i - 1][j - 1].rgbtRed * -1) + (float)(cpyImage[i - 1][j].rgbtRed * -2) +
                           (float)(cpyImage[i - 1][j + 1].rgbtRed * -1)));

                    image[i][j].rgbtRed  = exceed(GX, GY);

                    GX = (((float)(cpyImage[i - 1][j - 1].rgbtGreen * -1) + (float)cpyImage[i - 1][j + 1].rgbtGreen +
                           (float)(cpyImage[i][j - 1].rgbtGreen * -2) + (float)(cpyImage[i][j + 1].rgbtGreen * 2)));
                    GY = (((float)(cpyImage[i - 1][j - 1].rgbtGreen * -1) + (float)(cpyImage[i - 1][j].rgbtGreen * -2) +
                           (float)(cpyImage[i - 1][j + 1].rgbtGreen * -1)));

                    image[i][j].rgbtGreen  = exceed(GX, GY);

                    GX = (((float)(cpyImage[i - 1][j - 1].rgbtBlue * -1) + (float)cpyImage[i - 1][j + 1].rgbtBlue +
                           (float)(cpyImage[i][j - 1].rgbtBlue * -2) + (float)(cpyImage[i][j + 1].rgbtBlue * 2)));
                    GY = (((float)(cpyImage[i - 1][j - 1].rgbtBlue * -1) + (float)(cpyImage[i - 1][j].rgbtBlue * -2) +
                           (float)(cpyImage[i - 1][j + 1].rgbtBlue * -1)));

                    image[i][j].rgbtBlue  = exceed(GX, GY);
                }
            }
            // Detect left edge of the image
            else if (j == 0)
            {
                GX = (((float)cpyImage[i - 1][j + 1].rgbtRed + (float)(cpyImage[i][j + 1].rgbtRed * 2) + (float)cpyImage[i + 1][j + 1].rgbtRed));
                GY = (((float)(cpyImage[i - 1][j].rgbtRed * -2) + (float)(cpyImage[i - 1][j + 1].rgbtRed * -1) +
                       (float)(cpyImage[i + 1][j].rgbtRed * 2) + (float)cpyImage[i + 1][j + 1].rgbtRed));

                image[i][j].rgbtRed  = exceed(GX, GY);

                GX = (((float)cpyImage[i - 1][j + 1].rgbtGreen + (float)(cpyImage[i][j + 1].rgbtGreen * 2) +
                       (float)cpyImage[i + 1][j + 1].rgbtGreen));
                GY = (((float)(cpyImage[i - 1][j].rgbtGreen * -2) + (float)(cpyImage[i - 1][j + 1].rgbtGreen * -1) +
                       (float)(cpyImage[i + 1][j].rgbtGreen * 2) + (float)cpyImage[i + 1][j + 1].rgbtGreen));

                image[i][j].rgbtGreen  = exceed(GX, GY);

                GX = (((float)cpyImage[i - 1][j + 1].rgbtBlue + (float)(cpyImage[i][j + 1].rgbtBlue * 2) +
                       (float)cpyImage[i + 1][j + 1].rgbtBlue));
                GY = (((float)(cpyImage[i - 1][j].rgbtBlue * -2) + (float)(cpyImage[i - 1][j + 1].rgbtBlue * -1) +
                       (float)(cpyImage[i + 1][j].rgbtBlue * 2) + (float)cpyImage[i + 1][j + 1].rgbtBlue));

                image[i][j].rgbtBlue  = exceed(GX, GY);
            }
            // Detect right edge of the image
            else if (j == width - 1)
            {
                GX = (((float)(cpyImage[i - 1][j - 1].rgbtRed * -1) + (float)(cpyImage[i][j - 1].rgbtRed * -2) +
                       (float)(cpyImage[i + 1][j - 1].rgbtRed * -1)));
                GY = (((float)(cpyImage[i - 1][j - 1].rgbtRed * -1) + (float)(cpyImage[i - 1][j].rgbtRed * -2) +
                       (float)cpyImage[i + 1][j - 1].rgbtRed + (float)(cpyImage[i + 1][j].rgbtRed * 2)));

                image[i][j].rgbtRed  = exceed(GX, GY);

                GX = (((float)(cpyImage[i - 1][j - 1].rgbtGreen * -1) + (float)(cpyImage[i][j - 1].rgbtGreen * -2) +
                       (float)(cpyImage[i + 1][j - 1].rgbtGreen * -1)));
                GY = (((float)(cpyImage[i - 1][j - 1].rgbtGreen * -1) + (float)(cpyImage[i - 1][j].rgbtGreen * -2) +
                       (float)cpyImage[i + 1][j - 1].rgbtGreen + (float)(cpyImage[i + 1][j].rgbtGreen * 2)));

                image[i][j].rgbtGreen  = exceed(GX, GY);

                GX = (((float)(cpyImage[i - 1][j - 1].rgbtBlue * -1) + (float)(cpyImage[i][j - 1].rgbtBlue * -2) +
                       (float)(cpyImage[i + 1][j - 1].rgbtBlue * -1)));
                GY = (((float)(cpyImage[i - 1][j - 1].rgbtBlue * -1) + (float)(cpyImage[i - 1][j].rgbtBlue * -2) +
                       (float)cpyImage[i + 1][j - 1].rgbtBlue + (float)(cpyImage[i + 1][j].rgbtBlue * 2)));

                image[i][j].rgbtBlue  = exceed(GX, GY);
            }
            // Detect edges in middle of the image
            else
            {
                GX = (((float)(cpyImage[i - 1][j - 1].rgbtRed * -1) + (float)cpyImage[i - 1][j + 1].rgbtRed +
                       (float)(cpyImage[i][j - 1].rgbtRed * -2) + (float)(cpyImage[i][j + 1].rgbtRed * 2) +
                       (float)(cpyImage[i + 1][j - 1].rgbtRed * -1) + (float)cpyImage[i + 1][j + 1].rgbtRed));
                GY = (((float)(cpyImage[i - 1][j - 1].rgbtRed * -1) + (float)(cpyImage[i - 1][j].rgbtRed * -2) +
                       (float)(cpyImage[i - 1][j + 1].rgbtRed * -1) + (float)cpyImage[i + 1][j - 1].rgbtRed +
                       (float)(cpyImage[i + 1][j].rgbtRed * 2) + (float)cpyImage[i + 1][j + 1].rgbtRed));

                image[i][j].rgbtRed  = exceed(GX, GY);

                GX = (((float)(cpyImage[i - 1][j - 1].rgbtGreen * -1) + (float)cpyImage[i - 1][j + 1].rgbtGreen +
                       (float)(cpyImage[i][j - 1].rgbtGreen * -2) + (float)(cpyImage[i][j + 1].rgbtGreen * 2) +
                       (float)(cpyImage[i + 1][j - 1].rgbtGreen * -1) + (float)cpyImage[i + 1][j + 1].rgbtGreen));
                GY = (((float)(cpyImage[i - 1][j - 1].rgbtGreen * -1) + (float)(cpyImage[i - 1][j].rgbtGreen * -2) +
                       (float)(cpyImage[i - 1][j + 1].rgbtGreen * -1) + (float)cpyImage[i + 1][j - 1].rgbtGreen +
                       (float)(cpyImage[i + 1][j].rgbtGreen * 2) + (float)cpyImage[i + 1][j + 1].rgbtGreen));

                image[i][j].rgbtGreen  = exceed(GX, GY);

                GX = (((float)(cpyImage[i - 1][j - 1].rgbtBlue * -1) + (float)cpyImage[i - 1][j + 1].rgbtBlue +
                       (float)(cpyImage[i][j - 1].rgbtBlue * -2) + (float)(cpyImage[i][j + 1].rgbtBlue * 2) +
                       (float)(cpyImage[i + 1][j - 1].rgbtBlue * -1) + (float)cpyImage[i + 1][j + 1].rgbtBlue));
                GY = (((float)(cpyImage[i - 1][j - 1].rgbtBlue * -1) + (float)(cpyImage[i - 1][j].rgbtBlue * -2) +
                       (float)(cpyImage[i - 1][j + 1].rgbtBlue * -1) + (float)cpyImage[i + 1][j - 1].rgbtBlue +
                       (float)(cpyImage[i + 1][j].rgbtBlue * 2) + (float)cpyImage[i + 1][j + 1].rgbtBlue));

                image[i][j].rgbtBlue  = exceed(GX, GY);
            }
        }
    }
    return;
}

float exceed(float GX, float GY)
{
    if (round(sqrt((GX * GX) + (GY * GY))) > 255)
    {
        return 255;
    }
    else
    {
       return round(sqrt((GX * GX) + (GY * GY)));
    }
}