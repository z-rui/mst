CC=gcc

CFLAGS=-Wall -ggdb -O3

# Add -flto, -pg, etc here:
CLFLAGS=
CFLAGS+=$(CLFLAGS)
LDFLAGS+=$(CLFLAGS)

all: heapq_test adjlist_test prim kruskal graphgen

heapq_test: heapq.o heapq_test.o
adjlist_test: adjlist.o adjlist_test.o
prim: prim.o heapq.o adjlist.o
kruskal: kruskal.o heapq.o
graphgen: graphgen.o

adjlist.o: adjlist.c adjlist.h
adjlist_test.o: adjlist_test.c adjlist.h
graphgen.o: graphgen.c
heapq.o: heapq.c heapq.h
heapq_test.o: heapq_test.c heapq.h
kruskal.o: kruskal.c heapq.h adjlist.h
prim.o: prim.c heapq.h adjlist.h

.PHONY: all
