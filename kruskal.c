#include "heapq.h"
#include "adjlist.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static int less(void *h, size_t i, size_t j)
{
	struct edge *edges;

	edges = (struct edge *) h;
	return edges[i].weight < edges[j].weight;
}

static void swap(void *h, size_t i, size_t j)
{
	struct edge *edges;
	struct edge tmp;

	edges = (struct edge *) h;

	tmp = edges[i];
	edges[i] = edges[j];
	edges[j] = tmp;
}

static void set_init(int set[], size_t n)
{
	while (n-- > 0)
		set[n] = n;
}

static int find(int set[], int x)
{
	return (set[x] == x) ? x : (set[x] = find(set, set[x]));
}

void kruskal_mst(size_t V, size_t E, struct edge *edges)
{
	int *set;
	size_t i;
	long total_weight = 0;

	set = malloc(V * sizeof *set);
	set_init(set, V);

	heap_init(edges, E, less, swap);
	for (i = 0; i < V-1; ) {
		struct edge e;
		int s_src, s_dst;

		e = edges[0];
		heap_pop(edges, E--, less, swap);
		s_src = find(set, e.src);
		s_dst = find(set, e.dst);
		if (s_src != s_dst) {
			set[s_src] = s_dst;
			//printf("%d-%d:\t%d\n", e.src, e.dst, e.weight);
			total_weight += e.weight;
			i++;
		}
	}
	printf("total weight = %ld\n", total_weight);
	free(set);
}

int main()
{
	clock_t start, stop;
	size_t V, E;
	size_t i;
	struct edge *edges;

	if (scanf("%zu%zu", &V, &E) != 2)
		return 1;
	edges = malloc(E * sizeof *edges);
	for (i = 0; i < E; i++) {
		struct edge *e;

		e = &edges[i];
		if (scanf("%d%d%d", &e->src, &e->dst, &e->weight) != 3)
			return 1;
	}
	start = clock();
	kruskal_mst(V, E, edges);
	stop = clock();
	free(edges);
	printf("time = %fms\n", 1e3*(stop-start)/CLOCKS_PER_SEC);
	return 0;
}
