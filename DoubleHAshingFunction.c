/* **************** DoubleHAshingFunction.c **************** */
/*
 * The code herein is: Copyright Pavel Teixeira, 2014
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to me, my contact is below.
 * This Copyright give me the intellectual right but does not protect free
 * redistribution of source.
 *
 *     	email:  	galactuzprime[at]gmail.com
 *					gal[dot]prime[dot]kr[at]gmail[dot]com
 *
 *		Blog: 		http://codilandjourney.wordpress.com/
 *		Twitter:	https://twitter.com/Galactuz_Prime
 *		Linkedin:	https://www.linkedin.com/pub/pavel-teixeira/63/b79/1b8
 *
 *
 * The primary maintainer for this code is Pavel Teixeira
 *
 *
 */
/*
 * *** Building a Hash Table with Double Hashing Function. ***
 *
 *	This code create a hash table with the double hashing
 *	function and simulate her. It was implemented for the purpose of 
 *  study of hashing for my course degree and anyone can use it as long as
 *	follow the GNU terms of use.
 *
 *	The source output was "hard coded" in the main function, but you can always do a better 
 *	thing, right? I also recommend that you pay attention on the hastab_delete()
 * 	since it doesn't really delete a value on the table, so, read the hastab_delete() documentation
 *	above his implementation before using it.
 *
 *	@Possible bug:	Trying to add a contact in a node that was deleted before.
 *
 *	@Last Update: 	06/09/2014
 *
 @*/

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
  
#define SIZE 100
#define LEN 50

struct node {
	uint8_t name[LEN];
	uint8_t email[LEN];
	uint8_t mobile[LEN];
	int8_t flag;
};

struct hashmap {
	struct node *tab[SIZE];
};

/* All functions prototype */
void hashtab_put (struct hashmap *this, uint8_t *name, uint8_t *email, uint8_t *mobile);
uint16_t hashtab_get (struct hashmap *this, uint8_t *name);
void hashtab_iterate (struct hashmap *this, uint16_t key);
void hastab_delete (struct hashmap *this, uint8_t *name);
void hashtab_init (struct hashmap *this);
uint16_t h(uint8_t *s, uint8_t i);
uint16_t h1(uint8_t *s);
uint16_t h2(uint8_t *s);



int main (void) {
	struct hashmap this;
	struct node n;
	uint16_t no, ch;

	/* Debbuging code */
	// ch = h("nAderson Ferreira", 1);
	// printf("h = %d\n", ch);
	// printf("h1 = %d\n", h1("nAderson Ferreira"));
	// printf("h2 = %d\n", h2("nAderson Ferreira"));

	hashtab_init(&this);
	hashtab_put (&this, "Pavel Teixeira", "monkey1@gmail.com", "99392893");
	hashtab_put (&this, "Saturnino Mateus", "monkey2@gmail.com", "91094428");
	hashtab_put (&this, "Anderson Ferreira", "monkey3@gmail.com", "91888483");
	hashtab_put (&this, "nAderson Ferreira", "monkey4@gmail.com", "91888483");
	hashtab_put (&this, "Marco Casaroli", "monkey5@gmail.com", "91443242");


	no = hashtab_get (&this, "Anderson Ferreira");
	if (no)
	  	hashtab_iterate (&this, no);
	else
		printf("Name not found...\n");

	hastab_delete (&this, "Anderson Ferreira");
	printf("\n::::::::::::::::::::::::\n");

	no = hashtab_get (&this, "Anderson Ferreira");
	if (no)
	  	hashtab_iterate (&this, no);
	else
		printf("Name not found...\n");


	return 0;
}




/* Implementation of all Functions */
/*
 * This function add a nem contact to  the table, you
 * only need to pass his values.
 *
 * @this  : the pointer to the hashtable.
 * @name  : the name of your contact.
 * @email : Duh
 * @mobile: really?
 */
void hashtab_put (struct hashmap *this, uint8_t *name, uint8_t *email, uint8_t *mobile) {

	uint8_t i;
	uint16_t key;
	struct node *n;
	
	key = h(name, i);

	for (i = 0; i <= SIZE; i++) {
		
		/* 
		 *	Let's allocate memmory and inilialize the node values. 
		 *	This will be possible only if the pointer of that position
		 * 	is empty (NULL) or if it was remoded (flag = -1).
		 *	Please, verify the second condition, i'm a little tired now.
		 */
		if (!this->tab[key] || this->tab[key]->flag == -1) {
			printf("Key created for %s: %d\n", name, key);
			printf("A team of highly trained Monkeys are allocating the memmory for you...\n\n\n");
			n = malloc(sizeof(struct node));
			strncpy(n->name, name, LEN-1);
			strncpy(n->email, email, LEN-1);
			strncpy(n->mobile, mobile, LEN-1);
			n->flag = 1;
			n->name[LEN-1] = 0;
			n->email[LEN-1] = 0;
			n->mobile[LEN-1] = 0;
			this->tab[key] = n;
			return;
		}
		else {
			i = i + 1;
			printf ("We couldn't add %s \nthis hash function is weak\nor maybe the table is full.\nLet's try again!!\n", name);
		}
		key = h(name, i);
	}
	printf("The leader of the Monkeys told me that the table is full... Believe me, he is allways right... Please, pay for a new one...\n");
}

/*
 * This function dosn't really delete the key at the table
 * instead, it assigns -1 to the flag at the contact structure.
 *
 * @this: the pointer to the hashtable.
 * @name: the name that you're looking for.
 */
void hastab_delete (struct hashmap *this, uint8_t *name) {

	uint8_t i = 0;
	uint16_t key;

	do {
		key = h(name, i);

		/*	
		 *	Now let's check if is there something at this new position (key).
		 *	If you don't chech this the core will be in a loop forever because
		 *	to strcmp() works the name must be setted, wright champs? :P
		 *	This bug was related on 04/09/2014 and does not return any compilation
		 *	error. The code will run normally untill you use an invalid name.
		 */
		if (!this->tab[key]) {
			printf("The name [%s] that you are trying to find isn't here...\ntry annother one!\n", name);
			return;
		}
		
		/* 
		 *	If the name exist at the table and is simmilar to the one you're looking
		 * 	for then we will change his flag to -1 to say that it was deleted. 
		 */
		else if (!strcmp(this->tab[key]->name, name)){
			this->tab[key]->flag = -1;	
			return;
		}

		i++;
	}while ((this->tab[key]->name != 0) || i <= SIZE);

	return;
}

/*
 * This function is uded to search for a contact at the table 
 * by the name.
 *
 * @this: the pointer to the hashtable.
 * @name: the name that you're looking for.
 */
uint16_t hashtab_get (struct hashmap *this, uint8_t *name) {

	uint8_t i = 0, j;
	uint16_t key;

	for(j=0; j<SIZE; j++) {

		key = h(name, j);
		printf("Looking for %s[%d] on table...\n", name, key);

		//Check if table is empty or not
		if(this->tab[key]->name) {
			if (this->tab[key]->flag == -1) {
				printf("This contact was removed...\n");
				return 0;
			}
				
			else if(!strcmp(this->tab[key]->name, name)) 
				return key;
		}
		
		else {
			printf("A team of highly trained Monkeys couldn't find %s.\n I told you they were experts on that.", name);
			return 0;	
		}			
	}
}

/*
 * Once you have the pointer at the table and the key to index
 * your values you'll be glab to use this function to iterate
 * all the informations of that node.
 *
 * @this: the pointer to the hashtable.
 * @name: the name that you're looking for.
 */
void hashtab_iterate (struct hashmap *this, uint16_t key) {
	
	if (this->tab[key]->flag == -1)
		return;

	printf("Name\t: %s\n", this->tab[key]->name);
	printf("Email\t: %s\n", this->tab[key]->email);
	printf("Mobile\t: %s\n", this->tab[key]->mobile);

	return;
}

void hashtab_init (struct hashmap *this) {
	uint8_t i;
	
	//for (i = 0; i <= SIZE; i++)
	//	this->tab[i] = 0;

	/* PATCH 06/2014 
	 * This line does the same thing, but is much more elegant :P
	 */
	this->tab[SIZE] = 0;

}

/*
 * This function is the first part of the double hash function, i like
 * to do things by parts, ok?
 * 
 * @s: is the string that will be calculated.
 */  
uint16_t h1(uint8_t *s) {
    
    uint32_t key = 0;
    uint16_t i;
    
    for (i=0; i<strlen(s); i++)
        key += s[i];

    return key % SIZE;
}

/*
 * This function the second part of the double hash function.
 *
 * @s: is the string that will be calculated.
 */
uint16_t h2(uint8_t *s) {
	
	uint32_t key = 0;
	uint16_t i;
	
	for (i=0; i<strlen(s); i++)
		key += s[i];

	return (1 + (key % (SIZE - 1)));
}

uint16_t h(uint8_t *s, uint8_t i) {
	
	uint16_t key;

	/* I'm assigning my hash function to the key, as i told you
	 * i like doing things by parts as you see my h1 e h2.
	 */
	key = ((h1(s) + (i * h2(s))) % SIZE);

	return key;
}

