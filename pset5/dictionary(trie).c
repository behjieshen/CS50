/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality. (Trie)
 */

// include necessary header files
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "dictionary.h"

// trie data structure
typedef struct node
{
    bool is_end;
    struct node *children[27];
}
node;

// declare head pointer
node* head;
// make a node pointer to track
node* ptr;
// variable to keep track of the number of words
int word_count = 0;
// declare prototype
void freeEveryNode(node* ptr);

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    ptr = head;
    // iterate the length of the word given
    for(int i = 0; i < strlen(word); i++)
    {
        // calculate letter by subtracting with 97 (max is 25)
        int index = (int)tolower(word[i]) - (int)'a';
        if(strncmp(&word[i], "\'", 1) == 0)
            index = 26;
        // if no corresponding letter is found, return false
        if(ptr->children[index] == NULL)
            return false;
        // else set pointer as child node
        else
            ptr = ptr->children[index];
    }
    return ptr->is_end;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // allocate memory for the head node, else segmentation fault will occur
    head = malloc(sizeof(node));
    // open the specified dictionary file
    FILE* fp = fopen(dictionary, "r");
    // return false to exit if can't open file
    if(fp == NULL)
        return false;
    // while we haven't reach the end of file
    while(!feof(fp))
    {
        ptr = head;
        // create an array to store each character of the word
        char word[LENGTH+1] = {};
        // scan the word from the file and assign it as word
        fscanf(fp, "%s\n", word);
        // iterate over each word
        for(int i = 0; i < strlen(word); i++)
        {
            // create index to store the suitable array index
            int index = (int)tolower(word[i]) - (int)'a';
            // assign letter as 26 if it is an apostrophe
            if(strncmp(&word[i], "\'", 1) == 0)
                index = 26;
            // if there is no value at children[letter]
            if(ptr -> children[index] == NULL)
            {
                ptr->children[index] = malloc(sizeof(node));
            }
            // set pointer as new node
            ptr = ptr->children[index];
        }
        // set node as end when word is end
        ptr->is_end = true;
        // increase word count for size function
        word_count++;
    }
    // close file
    fclose(fp);
    //return true when all words are loaded from the dictionary
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // return word count that is calculated in loaded
    return word_count;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    freeEveryNode(head);
    return true;
}

void freeEveryNode(node* ptr)
{
    for(int i = 0; i < 27; i++)
    {
        if(ptr->children[i] != NULL)
        {
            freeEveryNode(ptr->children[i]);
        }
    }
    free(ptr);
}

/**int main(int argc, char* argv[])
{
    if(argc != 2 || argv[1] == NULL)
    {
        return 1;
    }
    char* second = argv[1];
    load(second);
    printf("good\n");
    return 0;
}**/
