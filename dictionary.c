// Implements a dictionary's functionality
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

int count = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 5381;


// Hash table
node *table[N];


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int x = hash(word); //obtain hash value

    for (node *cursor = table[x]; cursor != NULL; cursor = cursor->next) {
        if(strcasecmp(cursor->word, word)) {
            return true;
        }
    }
    return false;
}


// Hashes word to a number by djb2
unsigned int hash(const char *word)
{
    unsigned int hash = 5381;
    int c;

    while ((c = *word++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    if(hash < N) {
        return hash;
    } else {
        return hash % N;
    }

}


// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //1. open the file

    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    //2. read strings from the file
    char w [LENGTH + 1];
    //int count = 0;
    while (fscanf(file, "%s", w) == 1) //w is a char array where you going to read the word into
    {
        puts(w);
        count++;

        //3. create a new node for each word
        node *n = malloc (sizeof(node)); //allocate memory
        if(n == NULL)
        {
            return false;
        }
        strcpy (n->word, w); //copy the word into the space in memenory (node has 2 elements, WORD and NODE)
        n->next = NULL; //to set the next pointer

        //4. insert the node into the hash table
        int x = hash(n->word);

        //5. insert the node into the hashtable
        n->next = table[x];
        table[x] = n;
    }
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
   return count;
}


// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }

    return true;
}
