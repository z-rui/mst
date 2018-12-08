#include "adjlist.h"

#include <stdio.h>
#include <stdlib.h>

struct graph *new_graph(size_t V, size_t E)
{
	struct graph *G;

	G = malloc(sizeof *G);
	if (G == NULL)
		goto fail0;
	G->V = V;
	G->E = E;
	G->outdeg = calloc(G->V, sizeof *G->outdeg);
	G->adjlist = calloc(G->V, sizeof *G->adjlist);
	if (G->outdeg == NULL || G->adjlist == NULL)
		goto fail1;
	return G;
fail1:
	free(G->outdeg);
	free(G->adjlist);
	free(G);
fail0:
	return NULL;
}

struct edge *add_edge(struct graph *G, struct edge e)
{
	size_t x;

	x = G->outdeg[e.src];
	if ((x & (x-1)) == 0) {
		struct edge *newlist;

		newlist = realloc(G->adjlist[e.src], ((x) ? 2*x : 1) * sizeof *G->adjlist[0]);
		if (newlist == NULL)
			return NULL;
		G->adjlist[e.src] = newlist;
	}
	G->adjlist[e.src][x] = e;
	++G->outdeg[e.src];
	return &G->adjlist[e.src][x];
}

struct graph *read_graph(FILE *f)
{
	struct graph *G;
	size_t V, E;
	size_t i;

	if (fscanf(f, "%zu%zu", &V, &E) != 2)
		goto fail0;
	G = new_graph(V, E);
	if (G == NULL)
		goto fail0;
	for (i = 0; i < E; i++) {
		struct edge e;

		if (fscanf(f, "%d%d%d", &e.src, &e.dst, &e.weight) != 3)
			goto fail1;
		if (add_edge(G, e) == NULL)
			goto fail1;
	}
	return G;
fail1:
	free_graph(G);
fail0:
	return NULL;
}

struct graph *read_und_graph(FILE *f)
{
	struct graph *G;
	size_t V, E;
	size_t i;

	if (fscanf(f, "%zu%zu", &V, &E) != 2)
		goto fail0;
	G = new_graph(V, 2*E);
	if (G == NULL)
		goto fail0;
	for (i = 0; i < E; i++) {
		struct edge e;
		int tmp;

		if (fscanf(f, "%d%d%d", &e.src, &e.dst, &e.weight) != 3)
			goto fail1;
		if (add_edge(G, e) == NULL)
			goto fail1;
		tmp = e.src;
		e.src = e.dst;
		e.dst = tmp;
		if (add_edge(G, e) == NULL)
			goto fail1;
	}
	return G;
fail1:
	free_graph(G);
fail0:
	return NULL;
}

void write_graph(const struct graph *G, FILE *f)
{
	size_t i, j;

	fprintf(f, "%zu %zu\n", G->V, G->E);
	for (i = 0; i < G->V; i++) {
		struct edge *e;

		e = G->adjlist[i];
		for (j = 0; j < G->outdeg[i]; j++, e++)
			fprintf(f, "%d %d %d\n", e->src, e->dst, e->weight);
	}
}

void write_und_graph(const struct graph *G, FILE *f)
{
	size_t i, j;

	fprintf(f, "%zu %zu\n", G->V, G->E/2);
	for (i = 0; i < G->V; i++) {
		struct edge *e;

		e = G->adjlist[i];
		for (j = 0; j < G->outdeg[i]; j++, e++)
			if (e->src <= e->dst)
				fprintf(f, "%d %d %d\n", e->src, e->dst, e->weight);
	}
}

void free_graph(struct graph *G)
{
	size_t i;

	for (i = 0; i < G->V; i++)
		free(G->adjlist[i]);
	free(G->outdeg);
	free(G->adjlist);
	free(G);
}
