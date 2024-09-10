#include <math.h>
#include <stdio.h>

#include "helpers.h"

// This is my code //

// Prototypes

void validation(int *b, int *g, int *r);
void swap(int *a, int *b);
int averageBox(int height, int width, RGBTRIPLE image[height][width], int i, int j, char colour);
float kernelSum(int gxValue, int gyValue);
int sobelOperator(int height, int width, RGBTRIPLE copy[height][width], int i, int j, char colour);

int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}}; // x Kernel
int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}}; // y Kernel

/*
--- Greyscale ---
If RGB == 0x00 (0) the pixel is black
If RGB == oxff (255) the pixel is white
So, as long as the values of RGB are all the same, it will have varying shades of grey along the
spectrum The closer it is to 0, the darker. And the closer to 255, the whiter it will be

So we must convert each value of RGB to the same one. But to -what- value? If the original values
were high, then the converted values should all also be high. And the other way around. To ensure
that the brightness is the same in general, we can make it so the new identical value for RGB is the
average of the red, green adn blue original values
--- Greyscale ---
*/

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // We store the original RGB values
            int b = image[i][j].rgbtBlue;
            int g = image[i][j].rgbtGreen;
            int r = image[i][j].rgbtRed;
            // Average them
            int avg = round((b + g + r) / 3.0);
            // Update them to the new ones; a shade of grey
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

/*
--- Sepia ---
Sepia filter makes imagines look old-fashioned, converting them into red-brown tones
We can do this by taking the original pixels and converting the values based on the original values
There are already algorithms out there to do this. We will use one of them. It basically takes the
original RGB values and adds to them a certain pre-defined value

It is possible that the resulting values go over 255. In such cases, we should cap them to 255.
--- Sepia ---
*/

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // We store the original RGB values
            int b = image[i][j].rgbtBlue;
            int g = image[i][j].rgbtGreen;
            int r = image[i][j].rgbtRed;
            // Conversion to sepia values
            int sepiaBlue = round(.272 * r + .534 * g + .131 * b);
            int sepiaGreen = round(.349 * r + .686 * g + .168 * b);
            int sepiaRed = round(.393 * r + .769 * g + .189 * b);
            // Validation
            validation(&sepiaBlue, &sepiaGreen, &sepiaRed);
            // Update them to the new ones; a shade of grey
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}

/*
--- Reflection ---
A reflection is the result of placing the original image in front of a mirror, moving the pixels
around. Therefore, any pixels on the left side of the image should end up on the right, and
viceversa.

The original pixels are still present. But they are to be rearranged.
--- Reflection ---
*/

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Swap
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
/*
--- Blur ---
You can blur an imagine in various ways. The algorithm used in this case is called "box blur". It
takes each pixel and, for each colour value, gives it a new one by averaging the color values of
neighbouring pixels.

We do this by creating a 3x3 box around the pixel to be modified.

A copy of image is necessary so as to the new values do not affect the blurring
--- Blur ---
*/
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // We create an exact copy of the original image to work with it
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    // Now we need to read from copy, but write in image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int blurredBlue = averageBox(height, width, copy, i, j, 'B');
            int blurredGreen = averageBox(height, width, copy, i, j, 'G');
            int blurredRed = averageBox(height, width, copy, i, j, 'R');
            // We make sure that the value is correct
            validation(&blurredBlue, &blurredGreen, &blurredRed);
            image[i][j].rgbtBlue = blurredBlue;
            image[i][j].rgbtGreen = blurredGreen;
            image[i][j].rgbtRed = blurredRed;
        }
    }
    return;
}

void validation(int *b, int *g, int *r)
{
    // < 0 cases are to handle gx and gy negative values
    if (*b > 255)
        *b = 255;
    if (*b < 0)
        *b = 0;
    if (*g > 255)
        *g = 255;
    if (*g < 0)
        *g = 0;
    if (*r > 255)
        *r = 255;
    if (*r < 0)
        *r = 0;
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int averageBox(int height, int width, RGBTRIPLE copy[height][width], int i, int j, char colour)
{
    int sum = 0, count = 0;

    // Bounds
    int startRow = (i - 1 < 0) ? 0 : i - 1;
    int endRow = (i + 1 >= height) ? height - 1 : i + 1;
    int startCol = (j - 1 < 0) ? 0 : j - 1;
    int endCol = (j + 1 >= width) ? width - 1 : j + 1;
    // Here we basically make sure we do not go out of bounds. If we were to go out of bonds
    // either in a row or col, then assign that value to 0

    for (int row = startRow; row <= endRow; row++)
    {
        for (int col = startCol; col <= endCol; col++)
        {
            if (colour == 'B')
            {
                sum += copy[row][col].rgbtBlue;
            }
            else if (colour == 'G')
            {
                sum += copy[row][col].rgbtGreen;
            }
            else if (colour == 'R')
            {
                sum += copy[row][col].rgbtRed;
            }
            count++;
        }
    }
    return round((float) sum / count);
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // We create an exact copy of the original image to work with it
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    // Now we need to read from copy, but write in image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int blueEdges = sobelOperator(height, width, copy, i, j, 'B');
            int greenEdges = sobelOperator(height, width, copy, i, j, 'G');
            int redEdges = sobelOperator(height, width, copy, i, j, 'R');
            validation(&blueEdges, &greenEdges, &redEdges);
            image[i][j].rgbtBlue = blueEdges;
            image[i][j].rgbtGreen = greenEdges;
            image[i][j].rgbtRed = redEdges;
        }
    }
    return;
}

float kernelSum(int gxValue, int gyValue)
{
    // printf("Kernel sum value is %i\n", (int) sqrt(pow(gxValue, 2) + pow(gyValue, 2)));
    return sqrt(pow(gxValue, 2) + pow(gyValue, 2));
}

int sobelOperator(int height, int width, RGBTRIPLE copy[height][width], int i, int j, char colour)
{
    int gxValue = 0, gyValue = 0;

    // Iteration through the 3x3 grid surrounding the pixel in positions i, j
    for (int row = -1; row <= 1; row++)
    {
        for (int col = -1; col <= 1; col++)
        {
            int currentRow = i + row;
            int currentCol = j + col;
            int pixelValue = 0; // We default it to 0 to handle out-of-bonds as per the problem

            // Checking for the values of each colour band
            if (currentRow >= 0 && currentRow < height && currentCol >= 0 && currentCol < width)
            {
                if (colour == 'B')
                {
                    pixelValue = copy[currentRow][currentCol].rgbtBlue;
                }
                else if (colour == 'G')
                {
                    pixelValue = copy[currentRow][currentCol].rgbtGreen;
                }
                else if (colour == 'R')
                {
                    pixelValue = copy[currentRow][currentCol].rgbtRed;
                }
            }
            // We then apply the formula to join gx and gy
            gxValue += pixelValue * gx[row + 1][col + 1];
            gyValue += pixelValue * gy[row + 1][col + 1];
        }
    }
    return round(kernelSum(gxValue, gyValue));
}
