#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define	SIZE 	15


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
void edge_remove_begin(struct graph* this, uint8_t origin, uint8_t destiny);
uint8_t showMenu();
/***********************************/

int main(void) {
	struct graph this;
	uint8_t origin, destiny, weight;
	uint8_t op;
	uint8_t op2;

	/* Fist we inilialize the table. */
	graph_init(&this);

	edge_add(&this, 4, 2, 1);
	vertex_iterate(&this, 4);
	edge_add(&this, 4, 5, 1);
	vertex_iterate(&this, 4);
	edge_add(&this, 4, 3, 1);
	vertex_iterate(&this, 4);
	edge_add(&this, 4, 4, 1);
	vertex_iterate(&this, 4);
	edge_add(&this, 4, 7, 1);
	vertex_iterate(&this, 4);
	edge_add(&this, 4, 6, 1);
	vertex_iterate(&this, 4);
	printf("Removing edge [4]...\n");
	edge_remove(&this, 4, 4);
	vertex_iterate(&this, 4);
	edge_add(&this, 4, 15, 1);
	vertex_iterate(&this, 4);
	printf("Removing edge [6]...\n");
	edge_remove(&this, 4, 6);
	vertex_iterate(&this, 4);
	printf("Removing edge [2]...\n");
	edge_remove(&this, 4, 2);
	vertex_iterate(&this, 4);
	printf("***********");
	printf("\n\nAdding another vertex, [3] with edges 4, 10, 100 e 13:\n");
	edge_add(&this, 3, 4, 1);
	edge_add(&this, 3, 10, 1);
	edge_add(&this, 3, 100, 1);
	edge_add(&this, 3, 13, 2);
	vertex_iterate(&this, 3);
	printf("Removing edge [100]...\n");
	edge_remove(&this, 3, 100);
	vertex_iterate(&this, 3);
	printf("\n\nTry it yourself at main():\nGoodbye!\n\n");

	// do {
	// 	op = showMenu();
	// 	printf("%i\n", op);

	// 	switch(op){
	// 		case 1:
	// 			printf("\n-->What is the origin? -> ");
	// 			scanf("%i", &origin);
	// 			printf("\n-->What is the destiny? -> ");
	// 			scanf("%i", &destiny);
	// 			printf("\n-->What is his weight? -> ");
	// 			scanf("%i", &weight);
	// 			edge_add(&this, origin, destiny, weight);
	// 			printf("\n\n->Done... Weight %i Edge added from [%i] to [%i]", weight, origin, destiny);
	// 			break;

	// 		case 2:
	// 			printf("\n\n-->What is the vertex? -> ");
	// 			scanf("%i%*c", &origin);
	// 			vertex_iterate(&this, origin);
	// 			break;

	// 		case 3:
	// 			printf("\n-->What is the origin? -> ");
	// 			scanf("%i", &origin);
	// 			printf("\n-->What is the destiny? -> ");
	// 			scanf("%i", &destiny);
	// 			edge_remove_begin(&this, origin, destiny);
	// 			printf("\n\n->Done... First edge deleted. Print to verify.");
	// 			break;

	// 		case 4:
	// 			printf("\n->This may not work correctly...");
	// 			printf("\n-->Feeling lucky? y/n");
	// 			scanf("%c", &op2);
	// 			do{
	// 				if(op2 == 'n' || op2 == 'N')
	// 					break;
	// 				else if(op2 == 'y' || op2 == 'Y'){
	// 					printf("\n-->What is the origin? -> ");
	// 					scanf("%i", &origin);
	// 					printf("\n-->What is the destiny? -> ");
	// 					scanf("%i", &destiny);
	// 					edge_remove(&this, origin, destiny);
	// 				}
	// 			}while(op2 != 'n' || op2 != 'N' || op2 != 'y' || op2 != 'Y');
	// 			break;

	// 		case 0:
	// 			printf("\nGoodbye!\n");
	// 			break;

	// 		default:
	// 			printf("\nInvalid option.");
	// 			break;
	// 	}
	// }while(op != 0);
}


/* showMenu(): shows a menu to the program instead of doing it hard coded
 * in the main().
 *
 */
// uint8_t showMenu(){
// 	uint8_t op, op2;

// 	printf("\n------------------- Graph Creator v1.0 -------------------\n\n");
// 	printf("[1] - Add a new vertex.\n");
// 	printf("[2] - Print edges.\n");
// 	printf("[3] - Remove edge at the begining of the list.\n");
// 	printf("[4] - Remove a given edge. [in construction]\n");
// 	printf("[0] - Exit.\n\n");
// 	printf("Option -> ");
// 	scanf("%i", &op);
// 	op2 = op;

// 	return op2;
// }

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
 * @this: 		pointer to the table.
 * @origin:		origin of the vertex.
 * @destiny:	destiny of the vertex.
 * @weight:		weight of the vertex.
 */
void edge_add(struct graph* this, uint8_t origin, uint8_t destiny, uint8_t weight) {
	struct edge* newEdge;

	newEdge = malloc(sizeof(struct edge));
	newEdge->origin = origin;
	newEdge->destiny = destiny;
	newEdge->weight = weight;
	newEdge->next = this->tab[origin].head;
	this->tab[origin].head = newEdge;

	return;
}

/* edge_remove(): remove a edge (node) of a given vertex (at the table).
 *
 * @this: 		pointer to the table.
 * @origin:		origin of the vertex.
 * @destiny:	destiny of the vertex.
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
 * @this: 		pointer to the table.
 * @origin:		the vertex that we want to iterate.
 */
void vertex_iterate(struct graph* this, uint8_t origin) {
	struct edge* iterator;
	iterator = this->tab[origin].head;

	/* PARANOIAC: Verifies if is there any edge. */
	if(iterator){
		printf("Vertex [%i] edges :: ", origin);
		while(iterator->next){
		 	printf("[%i]-", iterator->destiny);
		 	iterator = iterator->next;
		}

		/* If there is edges and don't print none of them that means 
		 * there is only one edge, so lets print it.
		 * This last print is also used to print the last vertex, once 
		 * the "while" statement doesn't prints the last one - (20/09/14)
		 */
		printf("[%i]\n", iterator->destiny);
		return;		/* We don't need to finish this. */
	}
	else
		printf("There is no edges at the vertex [%i]\n", origin);

	return;
}

/* edge_remove_begin(): remove vertices at the begining of the list.
 * @*this:		pointer to the table.
 * @origin:		origin of the edge.
 * @destiny:	destiny of the edge.
 */
void edge_remove_begin(struct graph* this, uint8_t origin, uint8_t destiny) {
	struct edge* remEdge;
	struct edge* remEdge2;

	/* Check if is there any edge in this vertex. */
	if(this->tab[origin].head){
		/* Check if is at the first node. */
		if(remEdge->destiny == destiny) {
				this->tab[origin].head = this->tab[origin].head->next;
				remEdge->next = 0;
				free(remEdge);
				return;
		}
		else{
			printf("The vertex [%i] isn't at the begining of the list.\n", destiny);
			printf("You should try print the list first ;)\n");			
		}	
	}
	/* If the code arrive here means that the edge doesn't exist. */
	printf("The edge that came from [%i] and goes to [%i] doesn't exist.\n", origin, destiny);

	return;
}
