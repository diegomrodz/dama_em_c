#include "damac/node.h"
#include "damac/board.h"
#include "damac/heuristic.h"
#include <stddef.h>
#include <stdlib.h>

void init_node(Board* board, Node* node, Node* parent) 
{
	node->state = board;

	if (parent == NULL) 
	{
		node->cost = 0;
		node->depth = 1;
		node->parent = NULL;
	}
	else 
	{
		node->cost = parent->cost + 1;
		node->depth = parent->depth + 1;
		node->parent = parent;
	}

	node->next_nodes_count = 0;
	node->next_nodes = calloc(DAMAC_PIECES_QTD, sizeof(Node));
}

void set_fitness(Node* node, PieceColor color) 
{
	simple_score(node, color);
}

void set_next_nodes(Node* node, PieceColor color)
{
	Piece piece;
	Piece* neighbor;
	Piece* actual;
	Node* aux;
	int i;
	int is_valid_move;

	for (i = 0; node->state->pieces_left; i += 1) 
	{
		if (node->state->pieces[i].color == color) 
		{
			piece = node->state->pieces[i];

			neighbor = get_piece(node->state, piece.x + 1, piece.y + 1);

			is_valid_move = 1;

			if (neighbor != NULL) 
			{
				if ( ! can_eat_piece(node->state, &piece, neighbor)) 
				{
					is_valid_move = 0;
				}
			}
			else 
			{
				if ( ! can_move_piece(node->state, &piece, piece.x + 1, piece.y + 1)) 
				{
					is_valid_move = 0;
				}
			}

			if (is_valid_move) 
			{
				aux = &node->next_nodes[node->next_nodes_count];

				init_node(node->state, aux, node);

				if (neighbor != NULL) 
				{
					eat_piece(aux->state, &piece, neighbor);
				}
				else 
				{
					actual = get_piece(aux->state, piece.x, piece.y);

					move_piece(actual, piece.x + 1, piece.y + 1);
				}

				set_fitness(aux, color);

				node->next_nodes_count += 1;
			}

			neighbor = get_piece(node->state, piece.x - 1, piece.y - 1);

			is_valid_move = 1;

			if (neighbor != NULL) 
			{
				if ( ! can_eat_piece(node->state, &piece, neighbor)) 
				{
					is_valid_move = 0;
				}
			}
			else 
			{
				if ( ! can_move_piece(node->state, &piece, piece.x - 1, piece.y - 1)) 
				{
					is_valid_move = 0;
				}
			}

			if (is_valid_move) 
			{
				aux = &node->next_nodes[node->next_nodes_count];

				init_node(node->state, aux, node);

				if (neighbor != NULL) 
				{
					eat_piece(aux->state, &piece, neighbor);
				}
				else 
				{
					actual = get_piece(aux->state, piece.x, piece.y);

					move_piece(actual, piece.x + 1, piece.y + 1);
				}

				set_fitness(aux, color);

				node->next_nodes_count += 1;
			}

			neighbor = get_piece(node->state, piece.x + 1, piece.y - 1);

			is_valid_move = 1;

			if (neighbor != NULL) 
			{
				if ( ! can_eat_piece(node->state, &piece, neighbor)) 
				{
					is_valid_move = 0;
				}
			}
			else 
			{
				if ( ! can_move_piece(node->state, &piece, piece.x + 1, piece.y - 1)) 
				{
					is_valid_move = 0;
				}
			}

			if (is_valid_move) 
			{
				aux = &node->next_nodes[node->next_nodes_count];

				init_node(node->state, aux, node);

				if (neighbor != NULL) 
				{
					eat_piece(aux->state, &piece, neighbor);
				}
				else 
				{
					actual = get_piece(aux->state, piece.x, piece.y);

					move_piece(actual, piece.x + 1, piece.y + 1);
				}

				set_fitness(aux, color);

				node->next_nodes_count += 1;
			}

			neighbor = get_piece(node->state, piece.x - 1, piece.y + 1);

			is_valid_move = 1;

			if (neighbor != NULL) 
			{
				if ( ! can_eat_piece(node->state, &piece, neighbor)) 
				{
					is_valid_move = 0;
				}
			}
			else 
			{
				if ( ! can_move_piece(node->state, &piece, piece.x - 1, piece.y + 1)) 
				{
					is_valid_move = 0;
				}
			}

			if (is_valid_move) 
			{
				aux = &node->next_nodes[node->next_nodes_count];

				init_node(node->state, aux, node);

				if (neighbor != NULL) 
				{
					eat_piece(aux->state, &piece, neighbor);
				}
				else 
				{
					actual = get_piece(aux->state, piece.x, piece.y);

					move_piece(actual, piece.x + 1, piece.y + 1);
				}

				set_fitness(aux, color);

				node->next_nodes_count += 1;
			}
		}
	}
}