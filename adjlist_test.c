#include "adjlist.h"

#include <stdio.h>

int main()
{
	struct graph *G;

	G = read_und_graph(stdin);
	write_graph(G, stdout);
	free_graph(G);
	return 0;
}
