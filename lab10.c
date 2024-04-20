#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
    struct Trie*children[26];
    int count;
};

struct Trie *createTrie()
{
    struct Trie*node=(struct Trie*)malloc(sizeof(struct Trie));
    for(int i=0; i <26; i++){
        node->children[i]=NULL;
    }
    node->count=0;
    return node;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    struct Trie*temp= pTrie;
    for(int i=0; i < strlen(word); i++){
        int index=word[i]-'a';
        if(!temp->children[index]){
            temp->children[index]=createTrie();
        }
        temp=temp->children[index];
    }
    temp->count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    if(pTrie==NULL){
        return 0;
    }
    struct Trie*temp=pTrie;
    for(int i=0; i <strlen(word);i++){
        int index=word[i]-'a';
        if(temp->children[index]==NULL){
            return 0;
        }
        temp=temp->children[index];
    }
    return temp->count;
}


// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if(pTrie!=NULL){
    for(int i=0; i <26; i++){
        if(pTrie->children[i]!=NULL){
        deallocateTrie(pTrie->children[i]);
        }
    }
    free(pTrie);
    }
    return NULL;
}



// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE*fp=fopen(filename, "r");
    int i=0;
    char word[100];
    while(fscanf(fp, "%s", word)!=EOF){
        pInWords[i]=(char*)malloc((strlen(word)+1)*sizeof(char));
        strcpy(pInWords[i], word);
        i++;
    }
    fclose(fp);
    return i;

}

int main(void)
{
	char *inWords[256];

	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);

	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}

	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);

	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}
