#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
	size_t V, E;
	size_t i, j;
	unsigned short *W;

	if (argc < 2)
		return 1;

	srand(time(0));

	V = atol(argv[1]);
	E = atol(argv[2]);
	W = calloc(V*V, sizeof *W);
	printf("%zu %zu\n", V, E);
	for (i = 1; i < V; i++)
		W[(i-1)*V+i] = rand() % 65535 + 1;
	E -= V-1;
	while (E--) {
		do {
			i = rand() % (V-1);
			j = i+1 + rand() % (V-1-i);
		} while (W[i*V+j] != 0);
		W[i*V+j] = rand() % 65535 + 1;
	}
	for (i = 0; i < V; i++)
		for (j = 0; j < V; j++)
			if (W[i*V+j] != 0)
				printf("%zu %zu %d\n", i, j, W[i*V+j]);
	return 0;
}
