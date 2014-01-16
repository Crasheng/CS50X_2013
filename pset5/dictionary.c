/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/
#include<stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "dictionary.h"

bool ind = false ; 
int words = 0 ;
node* root = NULL ;
void de_trie(node* current,int start,int end,node* prev,int no)
{
  //loop iterate over all childerns .. ;
  if(start == end)
  {
    free(current) ;
    prev->childern[no] = NULL ;
    return;
  }
  //check for NULL if dosnot exist follow it ;
    if(current->childern[start] != NULL)
    {
        //to buffering dataa untill read next ....
      prev = current ;
      no =start ;
      current = current->childern[start];
      de_trie(current,0,27,prev,no);	     
    }
    else
    {   
        start++ ;
	de_trie(current,start,27,prev,no);
    }
}


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    //to keep tracking :)
    node* current = root ;
    
    int len = strlen(word) ;
    int i =0 ;
    for(i=0;i<len;i++)
    {
      if(word[i]=='\'')
	if(current->childern[26] != NULL) 
	  current = current->childern[26] ; 
	else 
	  break ;
      else
	if(current->childern[tolower(word[i])-97] != NULL)
	  current=current->childern[tolower(word[i])-97] ;
	else
	  break ; 
    }
    if(i == len && current->is_word == true)
      return true ;
    else 
      return false ;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    FILE* fp = fopen(dictionary,"r");
    if(fp == NULL)
    {
	printf("sorry i can't open it  >>):(<< \n") ;
	return false ;
    }
    char buffer[LENGTH+1];
    root= malloc(sizeof(node )) ;
    for(int i=0; i<27; i++)
        root->childern[i] = NULL ;
    root->is_word = false ;
    node* current = NULL;
    while(fgets(buffer, 46*sizeof(char), fp) != NULL)
    {
        //keep track root
        current = root ;
      
	//make variable to store length of word..
	int length = strlen(buffer)-1 ;
      
	//store in correct string format..
	char* str = buffer ;
	
	//iterate over the word length :)
	for(int i=0; i <= length && str[i] != '\n'; i++)
	{
	    if(str[i] == '\'')
	    {
	        if(current->childern[26] == NULL)
		{
		    node* child = malloc(sizeof(node)) ;
		    for(int i=0; i<27; i++)
		        child->childern[i] = NULL ;
		    child->is_word = false ;
		    current->childern[26] = child ;
		    current = child ;
		}
		else
		    current = current->childern[26];
	    }
	    else if(current->childern[tolower(str[i])-97] == NULL)
	    {
		node* child = malloc(sizeof(node)) ;
		for(int i=0; i<27; i++)
	            child->childern[i] = NULL ;
		child->is_word = false ;
		current->childern			\
		  [tolower(str[i])-97] = child ;
		//keep track nodes
		current = child ;
	    }
	    //if the node pointer pointing to sth..
	    else 
	        current = current->childern	\
		  [tolower(str[i])-97] ;
	}
  
	//indictation that , here's end of some word :)
	current->is_word = true ;
	words++;
    }
    //return .. :)
    ind = true ;
    fclose(fp) ;
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    if(ind == true)
    {
        return words ;
    }
    else
      return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    for(int i=0; i<27; i++ )
    {
        while(root->childern[i] != NULL)
	    de_trie(root,0,27,NULL,0) ;
    }
    free(root);
    return true;
}
