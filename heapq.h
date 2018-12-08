#ifndef HEAPQ_H
#define HEAPQ_H

#include <stddef.h>

extern void heap_up(void *, size_t,
	int (*)(void *, size_t, size_t),
	void (*)(void *, size_t, size_t));
extern void heap_down(void *, size_t, size_t,
	int (*)(void *, size_t, size_t),
	void (*)(void *, size_t, size_t));
/* heap_push is the same as heap_up */
extern void heap_pop(void *, size_t,
	int (*)(void *, size_t, size_t),
	void (*)(void *, size_t, size_t));
extern void heap_init(void *, size_t,
	int (*)(void *, size_t, size_t),
	void (*)(void *, size_t, size_t));

#endif /* HEAPQ_H */
