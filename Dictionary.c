//Sidney Robinson
//Simrobin 1643731
//CMPS12B/M
//Dictionary.c

#include "Dictionary.h"
#include <string.h>
#include <strings.h>
//Pre Implemented Good Provided by Lecturer
// rotate_left() // rotate the bits in an unsigned int
 unsigned int rotate_left(unsigned int value, int shift)
 {    
	int sizeInBits = 8*sizeof(unsigned int);   
	shift = shift & (sizeInBits - 1);    
		if ( shift == 0 )     
		return value;    
 return (value << shift) | (value >> (sizeInBits - shift)); } 
 // pre_hash() // turn a string into an unsigned int 
	unsigned int pre_hash(char* input) { 
	unsigned int result = 0xBAE86554; 
		while (*input) {    
		result ^= *input++;  
		result = rotate_left(result, 5); 
 } return result;
 } 
 // hash() // turns a string into an int in the range 0 to tableSize-1
 int hash(char* key, int tableSize){  
	return pre_hash(key)%tableSize;
 }

//-----------------------------------------------------------------------------------------------------


//Code to declare a new Hash Table with Size implemented by the user
HashTableObj *newHashTable(int size)
{
 // error checking code omitted // we explicitly allocate space for the fixed size element in HashTableObj, // the size element plus the space for the variable size array
 HashTableObj * H;
 H = (HashTableObj *) malloc(sizeof(HashTableObj) + sizeof(bucketList)*size);
 H->size = size;
 int i;
 for(i = 0; i <size ; i++)
 {
	 bucketListObj * hold = NULL;
	 H->bucket[i] = hold;
 }
 return H;
}
//Void command to delete the Entire Hash Table and return a NULL value
void deleteHashTable(HashTableObj * H)
{
	if(H == NULL)
	{
		fprintf(stderr, "error");
		return;
	}
	if(H->size == 0)
	{
		fprintf(stderr, "Size is 0 / Table is empty \n");
		return;
	}
	int i;
	bucketListObj * hold;
	bucketListObj* tmp;
	for(i = 0; i<H->size; i++)
	{
		hold = H->bucket[i];
		if(hold != NULL)
		{
		while(hold->next != NULL)
		{
			hold = hold->next;
			tmp = H->bucket[i];
			strcpy(tmp->item,"");
			tmp->next=NULL;
			free(tmp);
			tmp = NULL;
			H->bucket[i] = hold;
			
			//H->bucket[i] = hold;
		}
		free(H->bucket[i]);
		H->bucket[i] = NULL;
		}
	 hold = NULL;
	}
	free(H);
	H->size = 0;
	H = NULL;
}
//Member command to check whether or not the String already exists within the Hash Map, while it can be
//used it main it find its main purpose within other functions within the documentation as a check for 
//strings to stop repeated insertion
bool member(HashTableObj *H, char *str)
{
	if(H == NULL)
	{
		return false;
	}
	if(strcasecmp(str, "") == 0)
	{
		return false;
	}
	int i;
   // bucketListObj* tmp;
	for(i = 0; i<H->size; i++)
	{
		bucketListObj * hold = H->bucket[i];
		while(hold!=NULL)
		{
			if(strcasecmp(hold->item, str) == 0)
			{
				//printf("great! found the members\n");
				return true;
			}
			hold = hold->next;
		}
		free(hold);
	}
	return false;
}
//Void to populate and insert Items into the hashmap, will stop duplicate inserts as well
void insert(HashTableObj *H, char *str)
{
	if(H==NULL)
	{
		return;
	}
	if(member(H,str) == true)
	{
		fprintf(stderr, "This String Already Exists In The Hash Table");
		return;
	}

	int hashHold  = hash(str, H->size);	
	//bucketListObj * newStr = malloc(sizeof(bucketListObj) + strlen(str)+1);
	char* bigStr = malloc(sizeof(char) * strlen(str)+1);
	//strcpy(newStr->item,bigStr);
    //strcpy(newStr->item,str);
	//leave commneted btw newStr = H->bucket[hashHold - 1];
	if( H->bucket[hashHold] == NULL)
	{
		bucketListObj * newStr = malloc(sizeof(bucketListObj) + strlen(str)+1);
		strcpy(newStr->item,bigStr);
		strcpy(newStr->item,str);
		H->bucket[hashHold] = newStr;
	}
	if(H->bucket[hashHold] != NULL)
	{ 	
		bucketListObj * list = malloc(sizeof(bucketList) + strlen(str)+1);
		bucketListObj * newStr = H->bucket[hashHold];
		strcpy(list->item,bigStr);
		strcpy(list->item,str);
		list->next = newStr;
		H->bucket[hashHold] = list;
		//free(list);
	}	
	free(bigStr);
}
//Searches through the hashmap to delete a specific item from the list
bool delete(HashTableObj *H, char *str)
{
	if(H== NULL)
	{
		fprintf(stderr,"The HEAD is NULL \n");
		return false;
	}
	if(H->size == 0)
	{
		fprintf(stderr,"Everything is empty!");
		return false;
	}
	if(member(H,str)==false)
	{
		fprintf(stderr, "The String does not exist \n");
		return false;
	}
		int i = hash(str, H->size);
		bucketListObj* hold = H->bucket[i];
		//printf("Check");
		while(hold->next != NULL)
		{
		if(strcasecmp(hold->item,H->bucket[i]->item) == 0 &&  strcasecmp(hold->item,str)==0)
		{
			if(hold->next !=NULL)
			{
			H->bucket[i] = hold->next;
			//bucketListObj * temp = hold;
			//free(temp);
			free(hold);
			//printf("great! deleted check 1%s\n", str);
			return true;
			}else
			{
			bucketListObj * temp = H->bucket[i];
			free(temp);
			free(hold);
			//printf("great! deleted  check 2%s\n", str);
			return true;
			}
			
		}
		else if(strcasecmp(hold->item,str) == 0 )
		{
			bucketListObj * temp = malloc(sizeof(bucketListObj) + strlen(str)+1);
			temp = hold;
			if(temp->next != NULL && hold!= NULL)
			{
				free(temp);
				//printf("great! deleted %s\n", str);
				return true;
			}else
			{
				//free(hold);
				//printf("freeD");
				free(temp);
				return true;
			}
				free(temp);
		}
		hold = hold->next;
		}
	
	return false;
}
//Prints out the hash Table to allow visualization and testing
void printHashTable(FILE *out, HashTableObj *H)
{
	int i;
	if(H==NULL)
	{
		fprintf(stderr, "HASH TABLE IS NULL \n");
		return;
	}
	fprintf(out,"Hash table contents\n");
	for(i = 0; i< H->size; i++)
	{
		bucketListObj * hold = H->bucket[i];
		fprintf(out,"bucket %d\n", i);
		while(hold != NULL && hold->next != NULL)
		{
			fprintf(out,"    bucket list item = %s\n",hold->item);
			hold = hold->next;
		}
		
	}
}
