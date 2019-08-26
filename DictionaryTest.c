//Sidney Robinson
//Simrobin 1643731
//CMPS12B/M
//DictionaryClient.c

#include "Dictionary.h"
/*
 * test the hash table
 */
//Place with a main to test the hash table and the hash table functions
//Personal playground for testing edge cases
int
main () {
 
    const int tableSize = 12;	// set to 101 in assignment description

    char *sites[] =  {
	"Clash",
	"Promiscuous",
	"Home",
	"In my place",
	"LowRider",
	"Jackie",
	"Head"};


    HashTableObj  *H;
    int i;

    // you can make this hash table size anything you like that is a prime but the example
    // results will be different based on the has table size.
   H = newHashTable(tableSize);

    for (i=0; i< 7; i++) {
        insert(H, sites[i]);
    }
	printHashTable(stdout, H);
	
	delete(H,"Clash");
	delete(H,"Home");
	printHashTable(stdout, H);
	delete(H,"Jackie");
	delete(H,"LowRider");
	printHashTable(stdout, H);
	delete(H,"Head");
	delete(H,"In my place");
	printHashTable(stdout, H);
	deleteHashTable(H);
	printHashTable(stdout, H);
	deleteHashTable(H);
	printHashTable(stdout, H);
	printHashTable(stdout, H);
   //When putting this through valgrind there is an issue whee it has 20mallocs 20frees but
   //a tiny amount of bytes are lost upon exit
}


