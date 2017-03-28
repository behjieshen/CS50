// resize bmp file according to the factor given
       
// include necessary header files       
#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

// main function
int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }
    
    // convert 2nd argument into an integer
    int n = atoi(argv[1]);
    
    // make sure that n is within range 
    if(n < 0 || n > 100)
    {
        printf("n must a positive integer below 100.\n");
        return 1;
    }
    
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // create custom bitmap file headers
    BITMAPFILEHEADER bfresize = bf;
    BITMAPINFOHEADER biresize = bi;
    
    // change biWidth & biHeight according to the new factor
    biresize.biWidth = bi.biWidth * n;
    biresize.biHeight = bi.biHeight * n;
    
    // set paddings
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int resizePadding = (4 - (biresize.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // change biSizeImage (includes height * (width(bytes) + resizepadding))
    biresize.biSizeImage = (biresize.biWidth * sizeof(RGBTRIPLE) + resizePadding) * abs(biresize.biHeight);
    
    // change biSize (the entire file of the bitmap)
    bfresize.bfSize = biresize.biSizeImage + sizeof(bf) + sizeof(bi);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bfresize, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&biresize, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over height of the old bitmap (We will print multiple times later, therefore we don't need to use the new height)
    for (int i = 0; i < abs(bi.biHeight); i++)
    {
        for(int j = 0; j < n; j++)
        {
            // if this is not the first time printing
            if(j != 0)
            {
                // set offset in bytes as 1 pixel = 3 bytes(RGB)
                long offset = bi.biWidth * sizeof(RGBTRIPLE);
                // move backward to the beginning to resize vertically
                fseek(inptr, -(offset), SEEK_CUR);
            }
            // iterate over old pixels (We will print multiple times later as well)
            for (int k = 0; k < bi.biWidth; k++)
            {
                // temporary storage
                RGBTRIPLE triple;
        
                // read RGB triple from infile once
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                
                // write n times of RGB triple to outfile 
                for(int l = 0; l < n; l++)
                {
                    // write to the outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            // add necessary padding
            for (int m = 0; m < resizePadding; m++)
            {
                // print black pixel
                fputc(0x00, outptr);
            }
        }
        // skip over padding
        fseek(inptr, padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // end program
    return 0;
}
