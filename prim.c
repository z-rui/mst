#include "heapq.h"
#include "adjlist.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct heap_node {
	const struct edge *e;
	size_t heap_idx;
};

static int less(void *h, size_t i, size_t j)
{
	struct heap_node **q;

	q = (struct heap_node **) h;
	return q[i]->e->weight < q[j]->e->weight;
}

static void swap(void *h, size_t i, size_t j)
{
	struct heap_node **q;
	struct heap_node *tmp;

	q = (struct heap_node **) h;

	/* swap pointers */
	tmp = q[i];
	q[i] = q[j];
	q[j] = tmp;

	/* fix heap_idx */
	q[i]->heap_idx = i;
	q[j]->heap_idx = j;
}

void prim_mst(struct graph *G)
{
	struct heap_node **q, *v;
	size_t i, j;
	size_t n; /* heap len */
	long total_weight = 0;

	v = calloc(G->V, sizeof *v);
	q = calloc(G->V, sizeof *q);

	(q[0] = &v[0])->heap_idx = 0;  /* enqueue vertex 0 */
	n = 1;
	while (n > 0) {
		i = q[0] - v;
		heap_pop(q, n--, less, swap);
		v[i].heap_idx = (size_t) -1;
		for (j = 0; j < G->outdeg[i]; j++) {
			struct edge *e;
			struct heap_node *node;

			e = &G->adjlist[i][j];
			node = &v[e->dst];
			if (node->heap_idx == (size_t) -1)
				continue;
			if (node->e == NULL) {
				node->e = e;
				(q[n] = node)->heap_idx = n;
				heap_up(q, n++, less, swap);
			} else if (node->e->weight > e->weight) {
				node->e = e;
				heap_up(q, node->heap_idx, less, swap);
			}
		}
	}
	for (i = 1; i < G->V; i++) {
		const struct edge *e;

		e = v[i].e;
		//printf("%d-%d:\t%d\n", e->src, e->dst, e->weight);
		total_weight += e->weight;
	}
	printf("total weight = %ld\n", total_weight);
	free(q);
	free(v);
}

int main()
{
	clock_t start, stop;
	struct graph *G;

	G = read_und_graph(stdin);
	if (G == NULL)
		return 1;
	start = clock();
	prim_mst(G);
	stop = clock();
	free_graph(G);
	printf("time = %fms\n", 1e3*(stop-start)/CLOCKS_PER_SEC);
	return 0;
}
