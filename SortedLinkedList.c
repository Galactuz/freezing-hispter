#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#define SIZE 15
/***********************************/
struct edge {
	uint8_t origin;
	uint8_t destiny;
	uint8_t weight;
	struct edge* next;
};

struct vertex {
	uint8_t number;
	struct edge* head;
};

struct graph {
	struct vertex tab[SIZE];
};

/* Functions prototypes */
void edge_add(struct graph* this, uint8_t origin, uint8_t destiny, uint8_t weight);
void edge_remove(struct graph* this, uint8_t origin, uint8_t destiny);
void vertex_iterate(struct graph* this, uint8_t origin);
void graph_init(struct graph* this);

/***********************************/
int main(void) {
	struct graph this;
	uint8_t origin, destiny, weight;
	uint8_t op;
	uint8_t op2;
	
	/* Fist we inilialize the table. */
	graph_init(&this);

	edge_add(&this, 4, 2, 3);
	edge_add(&this, 4, 5, 1);
	edge_add(&this, 4, 7, 5);
	vertex_iterate(&this, 4);

	// edge_add(&this, 4, 5, 1);
	// vertex_iterate(&this, 4);

	// edge_add(&this, 4, 3, 1);
	// vertex_iterate(&this, 4);

	// edge_add(&this, 4, 4, 1);
	// vertex_iterate(&this, 4);

	return 0;	
}

/* graph_init(): initialize all the table that will store
* the vertex and his edges.
*
* @this: pointer to the table.
*/
void graph_init(struct graph* this) {
	int i;

	for(i = 0; i < SIZE; i++)
		this->tab[i].head = 0;
}

/* edge_add(): add a new edge (node) to a given vertex (at the table).
* so each table index represent a vertex and all the values of
* his linked list is a edge of that vertex.
*
* @this: pointer to the table.
* @origin: origin of the vertex.
* @destiny: destiny of the vertex.
* @weight: weight of the vertex.
*/
void edge_add(struct graph* this, uint8_t origin, uint8_t destiny, uint8_t weight) {

	struct edge *p;
	struct edge *b;
	struct edge *q;

	p = this->tab[origin].head;

	printf("I am adding\n");
	/* Check if the list is empty */
	if(!this->tab[origin].head){
		b = malloc(sizeof(struct edge));
		b->origin = origin;
		b->destiny = destiny;
		b->weight = weight;
		b->next = 0;
		this->tab[origin].head = b;

		return;
	}

	/* Check if should be added at the first position. */
	if (this->tab[origin].head->weight > weight){
		b = malloc(sizeof(struct edge));
		b->origin = origin;
		b->destiny = destiny;
		b->weight = weight;
		b->next = this->tab[origin].head;

		this->tab[origin].head = b;
		return;
	}

	else{
		p = this->tab[origin].head;
		q = this->tab[origin].head;
		b = malloc(sizeof(struct edge));
		b->origin = origin;
		b->destiny = destiny;
		b->weight = weight;

		while(p->next){
			if (p->weight < weight){
				q = p;
				p = p->next;
			}
			else {
				b->next = p;
				q->next = b;
				return;
			}
		}

		/* If whe arrive here it means that the value is bigger than all of the list. */
		p->next = b;
		b->next = 0;
	}

	return;
}

/* edge_remove(): remove a edge (node) of a given vertex (at the table).
*
* @this: pointer to the table.
* @origin: origin of the vertex.
* @destiny: destiny of the vertex.
*/
void edge_remove(struct graph* this, uint8_t origin, uint8_t destiny) {
	struct edge* remEdge;
	struct edge* remEdge2;
	struct edge* remEdge3;
	remEdge = this->tab[origin].head;
	remEdge2 = this->tab[origin].head;
	remEdge3 = this->tab[origin].head;
	
	/* Check if is there any edge in this vertex. */
	if(this->tab[origin].head){
		/* Check if is at the first node. */
		if(remEdge->destiny == destiny) {
			this->tab[origin].head = this->tab[origin].head->next;
			remEdge->next = 0;
			free(remEdge);
			return;
		}

		/* Whe didn't find at the first node, so let's make a linear search... */

		while((remEdge->next->next != 0)) {
			if(remEdge->destiny == destiny) {
				remEdge3 = remEdge2->next;
				remEdge = remEdge->next;
				remEdge2->next = remEdge;
				remEdge3->next = 0;
				free(remEdge3);
				return;
			}

			/* Verifies if is the current node. */
			else if(remEdge->destiny == destiny) {
				remEdge2 = remEdge->next;
				remEdge->next = remEdge->next->next;
				remEdge2->next = 0;
				free(remEdge2);
			}

			remEdge2 = remEdge;
			remEdge = remEdge->next;
		}

		/* PARANOIAC CHECK TO SEE IF IS AT THE LAST NODE. */
		if(remEdge->next->destiny == destiny){
			remEdge3 = remEdge->next;
			remEdge->next = 0;
			free(remEdge3);
			return;
		}

		/* PARANOIAC CHECK TO SEE IF IS AT THE PENULTIMATE NODE. */
		else if((remEdge->destiny == destiny)) {
			//printf("penultimo: %d\n", remEdge->destiny);
			//printf("ultimo: %d\n", remEdge->next->destiny);
			remEdge3 = remEdge2->next;
			remEdge = remEdge->next;
			remEdge2->next = remEdge;
			remEdge3->next = 0;
			free(remEdge3);
			return;
		}
	}

	/* If the code arrive here means that the edge doesn't exist. */
	printf("The edge that came from [%i] and goes to [%i] don't exist.\n", origin, destiny);
	
	return;
}

/* vertex_iterate(): prints all the edges of an specific vertex.
*
* @this: pointer to the table.
* @origin: the vertex that we want to iterate.
*/
void vertex_iterate(struct graph* this, uint8_t origin) {
	struct edge* iterator;
	iterator = this->tab[origin].head;
	
	/* PARANOIAC: Verifies if is there any edge. */
	if(iterator){
		printf("Vertex [%i] all weights sorted :: ", origin);
		while(iterator->next){
			printf("[%i]-", iterator->weight);
			iterator = iterator->next;
		}

		/* If there is edges and don't print none of them that means
		* there is only one edge, so lets print it.
		* This last print is also used to print the last vertex, once
		* the "while" statement doesn't prints the last one - (20/09/14)
		*/
		printf("[%i]\n", iterator->weight);
		return;	/* We don't need to finish this. */
	}

	else
		printf("There is no edges at the vertex [%i]\n", origin);
	
	return;
}
