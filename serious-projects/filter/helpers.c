#include "helpers.h"
#include "stdio.h"
#include "math.h"
#include "stdlib.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE grayShade;
    const int bmpBytes = 54 + (height * width) * 3;
    float floatRGB;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            floatRGB = image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed;
            grayShade = round(floatRGB / 3);
            image[i][j].rgbtBlue = grayShade;
            image[i][j].rgbtGreen = grayShade;
            image[i][j].rgbtRed = grayShade;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaBlue;
    float sepiaGreen;
    float sepiaRed;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sepiaBlue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);
            sepiaGreen = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            sepiaRed = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE auxiliarImage[height][width * 3];
    float widthFloat = width;
    float reference = widthFloat / 2;
    int intReference = reference;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width * 3; j++)
        {
            auxiliarImage[i][j] = image[i][j / 3].rgbtBlue;
            auxiliarImage[i][j + 1] = image[i][j / 3].rgbtGreen;
            auxiliarImage[i][j + 2] = image[i][j / 3].rgbtRed;
            j += 2;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < intReference; j++)
        {
            int distance = fabs(((reference - j) * 2));

            auxiliarImage[i][((j + distance) * 3) - 3] = image[i][j + distance - 1].rgbtBlue;
            auxiliarImage[i][((j + distance) * 3) - 2] = image[i][j + distance - 1].rgbtGreen;
            auxiliarImage[i][((j + distance) * 3) - 1] = image[i][j + distance - 1].rgbtRed;

            image[i][j + distance - 1].rgbtBlue = image[i][j].rgbtBlue;
            image[i][j + distance - 1].rgbtGreen = image[i][j].rgbtGreen;
            image[i][j + distance - 1].rgbtRed = image[i][j].rgbtRed;

            image[i][j].rgbtBlue = auxiliarImage[i][((distance + j) * 3) -3];
            image[i][j].rgbtGreen = auxiliarImage[i][((distance + j) * 3) - 2];
            image[i][j].rgbtRed = auxiliarImage[i][((distance + j) * 3) - 1];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE auxiliarImage[height][width];
    float floatRGB;
    int average;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            auxiliarImage[i][j].rgbtBlue = image[i][j].rgbtBlue;
            auxiliarImage[i][j].rgbtGreen = image[i][j].rgbtGreen;
            auxiliarImage[i][j].rgbtRed = image[i][j].rgbtRed;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 && j == 0)
            {
                floatRGB = auxiliarImage[i][j].rgbtBlue + auxiliarImage[i][j + 1].rgbtBlue + auxiliarImage[i + 1][j].rgbtBlue + auxiliarImage[i + 1][j + 1].rgbtBlue;
                average = round(floatRGB / 4);
                image[i][j].rgbtBlue = average;

                floatRGB = auxiliarImage[i][j].rgbtGreen + auxiliarImage[i][j + 1].rgbtGreen + auxiliarImage[i + 1][j].rgbtGreen + auxiliarImage[i + 1][j + 1].rgbtGreen;
                average = round(floatRGB / 4);
                image[i][j].rgbtGreen = average;

                floatRGB = auxiliarImage[i][j].rgbtRed + auxiliarImage[i][j + 1].rgbtRed + auxiliarImage[i + 1][j].rgbtRed + auxiliarImage[i + 1][j + 1].rgbtRed;
                average = round(floatRGB / 4);
                image[i][j].rgbtRed = average;
            }
            else if (i == height - 1 && j == width - 1)
            {
                floatRGB = auxiliarImage[i][j].rgbtBlue + auxiliarImage[i][j - 1].rgbtBlue + auxiliarImage[i - 1][j].rgbtBlue + auxiliarImage[i - 1][j - 1].rgbtBlue;
                average = round(floatRGB / 4);
                image[i][j].rgbtBlue = average;

                floatRGB = auxiliarImage[i][j].rgbtGreen + auxiliarImage[i][j - 1].rgbtGreen + auxiliarImage[i - 1][j].rgbtGreen + auxiliarImage[i - 1][j - 1].rgbtGreen;
                average = round(floatRGB / 4);
                image[i][j].rgbtGreen = average;

                floatRGB = auxiliarImage[i][j].rgbtRed + auxiliarImage[i][j - 1].rgbtRed + auxiliarImage[i - 1][j].rgbtRed + auxiliarImage[i - 1][j - 1].rgbtRed;
                average = round(floatRGB / 4);
                image[i][j].rgbtRed = average;
            }
            else if (i == 0 && j == width - 1)
            {
                floatRGB = auxiliarImage[i][j].rgbtBlue + auxiliarImage[i][j - 1].rgbtBlue + auxiliarImage[i + 1][j].rgbtBlue + auxiliarImage[i + 1][j - 1].rgbtBlue;
                average = round(floatRGB / 4);
                image[i][j].rgbtBlue = average;

                floatRGB = auxiliarImage[i][j].rgbtGreen + auxiliarImage[i][j - 1].rgbtGreen + auxiliarImage[i + 1][j].rgbtGreen + auxiliarImage[i + 1][j - 1].rgbtGreen;
                average = round(floatRGB / 4);
                image[i][j].rgbtGreen = average;

                floatRGB = auxiliarImage[i][j].rgbtRed + auxiliarImage[i][j - 1].rgbtRed + auxiliarImage[i + 1][j].rgbtRed + auxiliarImage[i + 1][j - 1].rgbtRed;
                average = round(floatRGB / 4);
                image[i][j].rgbtRed = average;
            }
            else if (i == height - 1 && j == 0)
            {
                floatRGB = auxiliarImage[i][j].rgbtBlue + auxiliarImage[i][j + 1].rgbtBlue + auxiliarImage[i - 1][j].rgbtBlue + auxiliarImage[i - 1][j + 1].rgbtBlue;
                average = round(floatRGB / 4);
                image[i][j].rgbtBlue = average;

                floatRGB = auxiliarImage[i][j].rgbtGreen + auxiliarImage[i][j + 1].rgbtGreen + auxiliarImage[i - 1][j].rgbtGreen + auxiliarImage[i - 1][j + 1].rgbtGreen;
                average = round(floatRGB / 4);
                image[i][j].rgbtGreen = average;

                floatRGB = auxiliarImage[i][j].rgbtRed + auxiliarImage[i][j + 1].rgbtRed + auxiliarImage[i - 1][j].rgbtRed + auxiliarImage[i - 1][j + 1].rgbtRed;
                average = round(floatRGB / 4);
                image[i][j].rgbtRed = average;
            }
            else if (i == 0)
            {
                floatRGB = auxiliarImage[i][j].rgbtBlue + auxiliarImage[i][j - 1].rgbtBlue + auxiliarImage[i][j + 1].rgbtBlue + auxiliarImage[i + 1][j - 1].rgbtBlue + auxiliarImage[i + 1][j].rgbtBlue + auxiliarImage[i + 1][j + 1].rgbtBlue;
                average = round(floatRGB / 6);
                image[i][j].rgbtBlue = average;

                floatRGB = auxiliarImage[i][j].rgbtGreen + auxiliarImage[i][j - 1].rgbtGreen + auxiliarImage[i][j + 1].rgbtGreen + auxiliarImage[i + 1][j - 1].rgbtGreen + auxiliarImage[i + 1][j].rgbtGreen + auxiliarImage[i + 1][j + 1].rgbtGreen;
                average = round(floatRGB / 6);
                image[i][j].rgbtGreen = average;

                floatRGB = auxiliarImage[i][j].rgbtRed + auxiliarImage[i][j - 1].rgbtRed + auxiliarImage[i][j + 1].rgbtRed + auxiliarImage[i + 1][j - 1].rgbtRed + auxiliarImage[i + 1][j].rgbtRed + auxiliarImage[i + 1][j + 1].rgbtRed;
                average = round(floatRGB / 6);
                image[i][j].rgbtRed = average;
            }
            else if (j == 0)
            {
                floatRGB = auxiliarImage[i][j].rgbtBlue + auxiliarImage[i - 1][j].rgbtBlue + auxiliarImage[i + 1][j].rgbtBlue + auxiliarImage[i - 1][j + 1].rgbtBlue + auxiliarImage[i][j + 1].rgbtBlue + auxiliarImage[i + 1][j + 1].rgbtBlue;
                average = round(floatRGB / 6);
                image[i][j].rgbtBlue = average;

                floatRGB = auxiliarImage[i][j].rgbtGreen + auxiliarImage[i - 1][j].rgbtGreen + auxiliarImage[i + 1][j].rgbtGreen + auxiliarImage[i - 1][j + 1].rgbtGreen + auxiliarImage[i][j + 1].rgbtGreen + auxiliarImage[i + 1][j + 1].rgbtGreen;
                average = round(floatRGB / 6);
                image[i][j].rgbtGreen = average;

                floatRGB = auxiliarImage[i][j].rgbtRed + auxiliarImage[i - 1][j].rgbtRed + auxiliarImage[i + 1][j].rgbtRed + auxiliarImage[i - 1][j + 1].rgbtRed + auxiliarImage[i][j + 1].rgbtRed + auxiliarImage[i + 1][j + 1].rgbtRed;
                average = round(floatRGB / 6);
                image[i][j].rgbtRed = average;
            }
            else if (i == height - 1)
            {
                floatRGB = auxiliarImage[i][j].rgbtBlue + auxiliarImage[i][j - 1].rgbtBlue + auxiliarImage[i][j + 1].rgbtBlue + auxiliarImage[i - 1][j - 1].rgbtBlue + auxiliarImage[i - 1][j].rgbtBlue + auxiliarImage[i - 1][j + 1].rgbtBlue;
                average = round(floatRGB / 6);
                image[i][j].rgbtBlue = average;

                floatRGB = auxiliarImage[i][j].rgbtGreen + auxiliarImage[i][j - 1].rgbtGreen + auxiliarImage[i][j + 1].rgbtGreen + auxiliarImage[i - 1][j - 1].rgbtGreen + auxiliarImage[i - 1][j].rgbtGreen + auxiliarImage[i - 1][j + 1].rgbtGreen;
                average = round(floatRGB / 6);
                image[i][j].rgbtGreen = average;

                floatRGB = auxiliarImage[i][j].rgbtRed + auxiliarImage[i][j - 1].rgbtRed + auxiliarImage[i][j + 1].rgbtRed + auxiliarImage[i - 1][j - 1].rgbtRed + auxiliarImage[i - 1][j].rgbtRed + auxiliarImage[i - 1][j + 1].rgbtRed;
                average = round(floatRGB / 6);
                image[i][j].rgbtRed = average;
            }
            else if (j == width - 1)
            {
                floatRGB = auxiliarImage[i][j].rgbtBlue + auxiliarImage[i - 1][j].rgbtBlue + auxiliarImage[i + 1][j].rgbtBlue + auxiliarImage[i - 1][j - 1].rgbtBlue + auxiliarImage[i][j - 1].rgbtBlue + auxiliarImage[i + 1][j - 1].rgbtBlue;
                average = round(floatRGB / 6);
                image[i][j].rgbtBlue = average;

                floatRGB = auxiliarImage[i][j].rgbtGreen + auxiliarImage[i - 1][j].rgbtGreen + auxiliarImage[i + 1][j].rgbtGreen + auxiliarImage[i - 1][j - 1].rgbtGreen + auxiliarImage[i][j - 1].rgbtGreen + auxiliarImage[i + 1][j - 1].rgbtGreen;
                average = round(floatRGB / 6);
                image[i][j].rgbtGreen = average;

                floatRGB = auxiliarImage[i][j].rgbtRed + auxiliarImage[i - 1][j].rgbtRed + auxiliarImage[i + 1][j].rgbtRed + auxiliarImage[i - 1][j - 1].rgbtRed + auxiliarImage[i][j - 1].rgbtRed + auxiliarImage[i + 1][j - 1].rgbtRed;
                average = round(floatRGB / 6);
                image[i][j].rgbtRed = average;
            }
            else
            {
                floatRGB = auxiliarImage[i][j].rgbtBlue + auxiliarImage[i - 1][j - 1].rgbtBlue + auxiliarImage[i - 1][j].rgbtBlue + auxiliarImage[i - 1][j + 1].rgbtBlue + auxiliarImage[i][j - 1].rgbtBlue + auxiliarImage[i][j + 1].rgbtBlue + auxiliarImage[i + 1][j - 1].rgbtBlue + auxiliarImage[i + 1][j].rgbtBlue + auxiliarImage[i + 1][j + 1].rgbtBlue;
                average = round(floatRGB / 9);
                image[i][j].rgbtBlue = average;

                floatRGB = auxiliarImage[i][j].rgbtGreen + auxiliarImage[i - 1][j - 1].rgbtGreen + auxiliarImage[i - 1][j].rgbtGreen + auxiliarImage[i - 1][j + 1].rgbtGreen + auxiliarImage[i][j - 1].rgbtGreen + auxiliarImage[i][j + 1].rgbtGreen + auxiliarImage[i + 1][j - 1].rgbtGreen + auxiliarImage[i + 1][j].rgbtGreen + auxiliarImage[i + 1][j + 1].rgbtGreen;
                average = round(floatRGB / 9);
                image[i][j].rgbtGreen = average;

                floatRGB = auxiliarImage[i][j].rgbtRed + auxiliarImage[i - 1][j - 1].rgbtRed + auxiliarImage[i - 1][j].rgbtRed + auxiliarImage[i - 1][j + 1].rgbtRed + auxiliarImage[i][j - 1].rgbtRed + auxiliarImage[i][j + 1].rgbtRed + auxiliarImage[i + 1][j - 1].rgbtRed + auxiliarImage[i + 1][j].rgbtRed + auxiliarImage[i + 1][j + 1].rgbtRed;
                average = round(floatRGB / 9);
                image[i][j].rgbtRed = average;
            }
        }
    }
    return;
}