/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality. (HashTable)
 */

// include necessary header files
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "dictionary.h"

// linked list structure
typedef struct node
{
    char word[LENGTH+1];
    struct node* next;
} node;

// the size of the hash table
const int tableSize = 11007;
// variable to keep track of the number of words
int wordCounter = 0;
// create hash table
node* hashTable[tableSize] = {};

// function to return hash index
int hash(const char* word)
{
    // variable to keep track of increment
    int hashIndex = 0;
    // iterate through each letter of word
    for(int i = 0; i < strlen(word); i++)
    {
        // increment hashIndex with the capitalized letters' ASCII values 
        hashIndex += (int)toupper(word[i]);
    }
    // return hashIndex mod tableSize
    return hashIndex % tableSize;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // variable to store the data of hash(word);
    int hashIndex = hash(word);
    // make a node pointer and set it as the start of the index
    node* ptr = hashTable[hashIndex];
    // declare a char array to store lowercased version of word
    char lowerCased[LENGTH+1] = {};
    // iterate through word
    for(int i = 0; i < strlen(word); i++)
    {
        // if it is a capital letter, assign to lowerCased as lowercase letter
        if(isupper(word[i]))
            lowerCased[i] = tolower(word[i]);
        // else copy the letter from word into lowerCased
        else
            lowerCased[i] = word[i];
    }
    // while ptr does not point to NULL
    while(ptr != NULL)
    {
        // if ptr->word and the word is the same, return true
        if(strcmp(ptr->word, lowerCased) == 0)
            return true;
        // move to the next node;
        ptr = ptr->next;
    }
    // return false if the word is not found
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // use a file pointer to open the dictionary for reading purposes
    FILE* fp = fopen(dictionary, "r");
    // if the dictionary does not exist, return false(exit)
    if(fp == NULL)
        return false;
    // while we are not at the end of file
    while(!feof(fp))
    {
        // allocate memory for newNode
        node* newNode = malloc(sizeof(node));
        // scan a word from the dictionary and store it in newNode->word
        fscanf(fp, "%s\n", newNode->word);
        // increase wordCounter by 1
        wordCounter++;
        // variable to store data of hash(newNode->word)
        int hashIndex = hash(newNode->word);
        // if it is the first time assgning to the index
        if(hashTable[hashIndex] == NULL) {
            // set the index as the newNode
            hashTable[hashIndex] = newNode;
            // set newNode next pointer to NULL
            newNode->next = NULL;
        }
        // otherwise
        else {
            // set the next node as the node at the index
            newNode->next = hashTable[hashIndex];
            // set the index to newNode
            hashTable[hashIndex] = newNode;
        }
    }
    // close the file and return true
    fclose(fp);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // return wordCounter
    return wordCounter;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // iterate through the whole tableSize
    for(int i = 0; i < tableSize; i++)
    {
        // create a node pointer at the index
        node* ptr = hashTable[i];
        // while pointer does not equal to NULL
        while(ptr != NULL)
        {
            // create another node temporary for freeing purposes
            node* temp = ptr;
            // set pointer to the next node
            ptr = ptr->next;
            // free temporary
            free(temp);
        }
        // set the index as NULL
        hashTable[i] = NULL;
    }
    // return true(exit)
    return true;
}