#include "heapq.h"

void heap_up(void *h, size_t i,
	int (*less)(void *, size_t, size_t),
	void (*swap)(void *, size_t, size_t))
{
	size_t j;

	while (i > 0) {
		j = (i-1) / 2;
		if (!less(h, i, j))
			break;
		swap(h, i, j);
		i = j;
	}
}

void heap_down(void *h, size_t n, size_t i,
	int (*less)(void *, size_t, size_t),
	void (*swap)(void *, size_t, size_t))
{
	size_t j;

	while ((j = 2*i + 1) < n) {
		if (j+1 < n && less(h, j+1, j))
			++j;
		if (!less(h, j, i))
			break;
		swap(h, i, j);
		i = j;
	}
}

void heap_pop(void *h, size_t n,
	int (*less)(void *, size_t, size_t),
	void (*swap)(void *, size_t, size_t))
{
	swap(h, 0, n-1);
	heap_down(h, n-1, 0, less, swap);
}

void heap_init(void *h, size_t n,
	int (*less)(void *, size_t, size_t),
	void (*swap)(void *, size_t, size_t))
{
	size_t i;

	for (i = n/2; i > 0; i--)
		heap_down(h, n, i-1, less, swap);
}
