#ifndef ADJLIST_H
#define ADJLIST_H

#include <stdio.h>

struct edge {
	int src, dst;
	int weight;
};

struct graph {
	size_t V; /* number of vertexes */
	size_t E; /* number of edges */
	size_t *outdeg;
	struct edge **adjlist;
};

extern struct graph *new_graph(size_t V, size_t E);
extern struct edge *add_edge(struct graph *G, struct edge e);
extern struct graph *read_graph(FILE *f);
extern struct graph *read_und_graph(FILE *f);
extern void write_graph(const struct graph *G, FILE *f);
extern void write_und_graph(const struct graph *G, FILE *f);
extern void free_graph(struct graph *G);

#endif /* ADJLIST_H */
