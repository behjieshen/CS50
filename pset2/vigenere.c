// a program that encrypts messages using Vigenère’s cipher

// include necessary header files
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// main function
int main(int argc, string argv[])
{
    // if second argument is null or there isn't 2 arguments, quit
    if(argv[1] == NULL || argc != 2)
    {
        printf("Usage: vigenere string");
        return 1;
    }
    
    // loop through the string
    for(int i = 0; i < strlen(argv[1]); i++)
    {
        // if it is not a letter, quit
        if(isalpha(argv[1][i]) == false)
        {
            printf("Letters only!");
            return 1;
        }
    }
    
    // initialize variables
    int c;
    int diff;
    
    // store the second argument
    string k = argv[1];
    //store the input string
    string input = GetString();
    
    // if input is not null
    if(input != NULL)
    {
        // loop over input
        for(int i=0, j =0; i < strlen(input); i++, j++)
        {
            // if j is finished, start from 0 again
            if(j == strlen(k)) {
                j = 0;
            }
            
            // if it is not a letter, don't increment j
            if(isalpha(input[i]) == false)
            {
                j -= 1;
            }
            
            // if it is a letter
            if(isalpha(input[i]))
            {
                // if it is a lowercase letter
                if(islower(input[i]))
                {
                    // if the 2nd argument's letter is uppercase, change it to lowercase
                    if(isupper(k[i]))
                        k[j]= tolower(k[j]);
                    // calculate c
                    c = (int)input[i] + k[j] - 97;
                    // while c exceeds "z", calculate c
                    while(c > 122) 
                    {
                        diff = c - 122;
                        c = 96 + diff;
                    }
                }
                
                // if it is a uppercase letter
                else if(isupper(input[i]))
                {
                    // if the 2nd argument's letter is lowercase, change it to uppercase
                    if(islower(k[i]))
                        k[j]= toupper(k[j]);
                    // calculate c
                    c = (int)input[i] + k[j] - 65;
                    // while c exceeds "Z", calculate 
                    while(c > 90) 
                    {
                        diff = c - 90;
                        c = 64 + diff;
                    }
            
                // change back into letter form
                c = (char) c;
            }
            // else, leave it as it is
            else
                c = input[i];
            // print c one by one
            printf("%c", c);
        }
    }
    // print newline
    printf("\n");
    return 0;
}
