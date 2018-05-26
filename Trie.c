#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "TriePrediction.h"
#define MAX_WORD_LENGTH 1024

void insertString(TrieNode *root, char *str);
void printTrie(TrieNode *root, int useSubtrieFormatting);
void printTrieHelper(TrieNode *root, char *buffer, int k);

int main(int argc, char **argv)
{
    TrieNode *root = buildTrie(argv[1]);
    int num = processInputFile(root, argv[2]);
    //destroyTrie(root);

  	return 0;
}


void printTrie(TrieNode *root, int useSubtrieFormatting)
{
    char buffer[1026];

    if (useSubtrieFormatting)
    {
        strcpy(buffer, "- ");
        printTrieHelper(root, buffer, 2);
    }
    else
    {
        strcpy(buffer, "");
        printTrieHelper(root, buffer, 0);
    }
}

void printTrieHelper(TrieNode *root, char *buffer, int k)
{
	int i;

	if (root == NULL)
		return;

	if (root->count > 0)
    {
        printf("%s (%d)\n", buffer, root->count);
    }

	buffer[k + 1] = '\0';

	for (i = 0; i < 26; i++)
	{
		buffer[k] = 'a' + i;

		printTrieHelper(root->children[i], buffer, k + 1);
	}

	buffer[k] = '\0';
	return;
}

TrieNode *createNode(void)
{
    int i;
    TrieNode *n = malloc(sizeof(TrieNode));

    n->count = 0;
    for (i = 0; i< 26; i++)
        n->children[i] = NULL;
    return n;
}

TrieNode *buildTrie(char *filename)
{
    char buffer[MAX_WORD_LENGTH + 1];
    FILE *ifp = NULL;
    TrieNode *root = NULL;
    root = (struct TrieNode *)malloc(sizeof(struct TrieNode));

    if (root)
    {
        int i;

        root->count = 0;

        for (i = 0; i < 26; i++)
            root->children[i] = NULL;
    }

    if ((ifp = fopen(filename, "r")) == NULL)
    {
        printf("Failed to open file %s\n", filename);
        return NULL;
    }

    while (fscanf(ifp, "%s", buffer) != EOF)
		insertString(root, buffer);

	return root;
}

int processInputFile(TrieNode *root, char *filename)
{
    FILE *ifp = NULL;
    char buffer[MAX_WORD_LENGTH + 1];

    if ((ifp = fopen(filename, "r")) == NULL)
    {
        printf("Failed to open file %s\n", filename);
        return 1;
    }
    while (fscanf(ifp, "%s", buffer) != EOF)
    {
        if(strcmp(buffer, "!"))
        {
            printTrie(root, 1);
        }
        else if (buffer[0] == '@')
        {
            printf("hello");
        }
        else
        {
            printf("%s", buffer);
        }
    }

    return 0;
}

TrieNode *destroyTrie(TrieNode *root)
{
    int i;

    if (root == NULL)
        return NULL;

    if (root->count > 0)
        destroyTrie(root->subtrie);

    for (i = 0; i < 26; i++)
        destroyTrie(root->children[i]);

    free(root);

    return NULL;
}

TrieNode *getNode(TrieNode *root, char *str)
{
    int length = strlen(str);
    int i, index;

    for (i = 0;i < length; i++)
    {
        index = str[i] - 'a';
        if (root->children[index]->count == 0)
            return NULL;

        root = root->children[index];
    }

    return root;
}

void getMostFrequentWord(TrieNode *root, char *str)
{
        return;
}

int containsWord(TrieNode *root, char *str)
{
    int length = strlen(str);
    int i, index;

    for (i = 0;i < length; i++)
    {
        index = str[i] - 'a';
        if (root->children[index]->count == 0)
            return 0;

        root = root->children[index];
    }
    return 1;
}

int prefixCount(TrieNode *root, char *str)
{
    int i, index;
    int length = strlen(str);
    for(i = 0; i < length; i++)
    {
        index = str[i]- 'a';
        root = root->children[index];
    }

    for(i = 0; i < 26; i++)
    {
        if(root->children[i]->count != NULL)
            root = root->children[i];
    }
        return 0;
}

void insertString(TrieNode *root, char *str)
{
    int i, index;
    int len = strlen(str);
    TrieNode *next;

    if (root == NULL)
        root = createNode();

    next = root;

    for (i = 0; i < len; i++)
    {
        if (isalpha(str[i]))
        {
            index = tolower(str[i]) - 'a';

            if (next->children[index] == NULL)
                next->children[index] = createNode();

            next = next->children[index];
        }
    }

    next->count++;

    return;
}
