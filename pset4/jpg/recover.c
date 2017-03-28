// recovers jpeg from corrupted memory file

// include necessary header files
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

// main function
int main(void)
{
    // variable to check if the first jpg is found
    bool foundFirstFile = false;
    // variable to check if the file is stil open for writing
    bool fileIsOpen = false;
    // variable to specify the block of memory for fread
    uint8_t buffer[512];
    // variable to store the number of jpg that it is currently working on
    int jpgCounter = 0;
    // file pointer to specify the outfile
    FILE* outfile;
    
    // file pointer for the raw data
    FILE* data = fopen("card.raw", "r");
    // if it is null, warn the user and exit the program
    if(data == NULL)
    {
        printf("File does not exist\n");
        return 2;
    }
    
    // while there is something to read 
    while(fread(buffer, 1, 512, data) > 0)
    {
        // if it is a jpg file
        if((buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff) && (buffer[3] == 0xe0 || buffer[3] == 0xe1 
        || buffer[3] == 0xe2 || buffer[3] == 0xe3 || buffer[3] == 0xe4 || buffer[3] == 0xe5 || buffer[3] == 0xe6 
        || buffer[3] == 0xe7 || buffer[3] == 0xe8 || buffer[3] == 0xe9 || buffer[3] == 0xea || buffer[3] == 0xeb
        || buffer[3] == 0xec || buffer[3] == 0xed || buffer[3] == 0xee || buffer[3] == 0xef))
        {
            // create an array to store filename
            char name[8];
            sprintf(name, "%03d.jpg", jpgCounter);
            // increase jpg count
            jpgCounter+=1;
            // indicate that the first jpg file is found
            foundFirstFile = true;
            
            // if it is found fileIsOpen is true
            if(foundFirstFile == true)
            {
                fileIsOpen = true;
            }
            
            // close the file if the file is already open
            else if(fileIsOpen) {
                fclose(outfile);
            }
            
            // write to the outfile
            outfile = fopen(name, "w");
            fwrite(buffer, 1, 512, outfile);
        }
        // if a new jpg is not found
        else {
            // write to the existing jpg file if there is any
            if(fileIsOpen)
            {
                fwrite(buffer, 1, 512, outfile);
            }
        }
    }
}
