// Implements a dictionary's functionality
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of words in dictionary
int numberWords = 0;

// Number of buckets in hash table
const unsigned int N = 150000;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Convert word to lowercase
    char str[LENGTH + 1];
    strcpy(str, word);
    for (int i = 0; str[i]; i++)
    {
        str[i] = tolower(str[i]);
    }
    // Get index of word for fast search
    int index = hash(str);

    // Search for word in table linked list
    for (node *cursor = table[index]; cursor != NULL; cursor = cursor->next)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

/*
    djb2 hash function by: Dan Bernstein
    source: http://www.cse.yorku.ca/~oz/hash.html
*/
// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *word++))
    {
        hash = ((hash << 5) + hash) + c;   /* hash * 33 + c */
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *file = fopen(dictionary, "r");

    // Return false if can't open dictionary
    if (file == NULL)
    {
        return false;
    }
    int index;
    // Variable to store dictionary word
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        // Allocate memory
        node *n = malloc(sizeof(node));

        // Check if memory there is memory available
        if (n == NULL)
        {
            return false;
        }
        // Convert word to lowercase
        for (int i = 0; word[i]; i++)
        {
            word[i] = tolower(word[i]);
        }
        // Copy dictionary word into linked list
        strcpy(n->word, word);
        n->next = NULL;

        // Get table index base on hash function
        index = hash(n->word);

        // Check if table is empty
        if (table[index] == NULL)
        {
            // Link table to n
            table[index] = n;
            ++numberWords;
        }
        // If not empty chain the table
        else
        {
            // Point where table is pointing to
            n->next = table[index];
            // Point table to n(insert new word to front of linked list)
            table[index] = n;
            ++numberWords;
        }
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (numberWords == 0)
    {
        return 0;
    }
    return numberWords;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; ++i)
    {
        while (table[i] != NULL)
        {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
    }
    return true;
}
