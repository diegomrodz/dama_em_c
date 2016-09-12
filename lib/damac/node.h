#ifndef FILE_NODE
#define FILE_NODE

#include "damac/board.h"
#include "damac/piece.h"

typedef struct Node Node;

struct Node
{
	Board* state;
	Node* parent;
	Node* next_nodes;
	int next_nodes_count;
	int cost;
	int depth;
	int fitness;
};

void init_node(Board*, Node* node, Node* parent);

void set_fitness(Node*, PieceColor);

void set_next_nodes(Node*, PieceColor);

#endif