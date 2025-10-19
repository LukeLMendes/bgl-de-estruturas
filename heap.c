#ifndef HEAP_C
#define HEAP_C
#include <stdio.h>
#include <stdlib.h>
#include "./pessoa.h"

#define left(i) (2 * i)
#define right(i) (2 * i)+1

typedef struct {
    Pessoa *data;
    size_t size;
    size_t capacity;
} Heap;
#define empty_pq(h) (h->size == 1)

Heap * new_heap() {
    Heap *h = malloc(sizeof(Heap));
    h->data = malloc(sizeof(Pessoa) * 10);
    h->size = 1; // ignorar primeiro indice pra melhorar a formula
    h->capacity = 10;
    return h;
}

void enq_pq(Heap * h, Pessoa p) {
	if (h->size == h->capacity) {
		h->capacity *= 2;
		h->data = realloc(h->data, sizeof(int) * h->capacity);
	}
	h->data[h->size] = p;
	int curr = h->size;
	h->size++;
	while(curr > 1) {
		Pessoa parrent = h->data[curr/2];
		if  (h->data[curr].caso < parrent.caso) {
			Pessoa temp =  parrent;
			h->data[curr/2] = h->data[curr];
			h->data[curr] = temp;
			curr = curr/2;
			continue;
		} 
		break;
	}
}

Pessoa * peek_pq(Heap * h) {
	if (h->size > 1) {
		return &h->data[1];
	}
	return NULL;
}

void deq_pq(Heap * h) {
	Pessoa last = h->data[h->size - 1];
	h->data[h->size - 1].caso = 0;
	h->data[1] = last;
	h->size--;
	int curr = 1;
	while(curr < h->size) {
		Pessoa leftv = h->data[left(curr)];
		Pessoa rightv = h->data[left(curr)];
		int min, max;
		Pessoa minv, maxv;
		min = leftv.caso < rightv.caso ? left(curr) : right(curr);
		max = leftv.caso >= rightv.caso ? left(curr) : right(curr);
		minv = h->data[min];
		maxv = h->data[max];
		
		if (minv.caso > 0 && minv.caso < h->data[curr].caso) {
			Pessoa temp = h->data[curr];
			h->data[curr] = minv;
			h->data[min] = temp;
			curr = min;
			continue;
		}  
		if (maxv.caso > 0 && maxv.caso < h->data[curr].caso) {
			Pessoa temp = h->data[curr];
			h->data[curr] = maxv;
			h->data[max] = temp;
			curr = max;
			continue;
		}
		if (minv.caso > 0 && minv.caso == h->data[curr].caso && minv.hora < h->data[curr].hora) {
			Pessoa temp = h->data[curr];
			h->data[curr] = minv;
			h->data[min] = temp;
			curr = min;
			continue;
		}  
		if (maxv.caso > 0 && maxv.caso == h->data[curr].caso && maxv.hora < h->data[curr].hora) {
			Pessoa temp = h->data[curr];
			h->data[curr] = maxv;
			h->data[max] = temp;
			curr = max;
			continue;
		}
		break;
	}
}

void free_pq(Heap * h) {
	free(h->data);
	free(h);
}

#include "fila.c"

int print_pq(Heap * h, char * to, int n) {
	Fila * f = nova_fila();
	while (!empty_pq(h)) {
		Pessoa * p = peek_pq(h);
		enq_q(f, *p);
		deq_pq(h);
	}
	n = print_q(f, to, n);
	while (!empty_q(f)) {
		Pessoa * p = &f->prim->p;
		enq_pq(h, *p);
		deq_q(f);
	}
	return n;
}
#endif
