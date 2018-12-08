#include "heapq.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int less(void *h, size_t i, size_t j)
{
	int *data;

	data = (int *) h;
	return data[i] < data[j];
}

static void swap(void *h, size_t i, size_t j)
{
	int *data;
	int tmp;

	data = (int *) h;
	tmp = data[i];
	data[i] = data[j];
	data[j] = tmp;
}

/* heap sort */
int main()
{
	int *data;
	int n, i;

	if (scanf("%d", &n) != 1)
		return 1;
	data = malloc(n * sizeof *data);
	for (i = 0; i < n; i++)
		if (scanf("%d", &data[i]) != 1)
			return 1;
	heap_init(data, n, less, swap);
	for (i = 0; i < n; i++) {
		printf("%d ", data[0]);
		heap_pop(data, n-i, less, swap);
	}
	putchar('\n');
	free(data);
	return 0;
}
