#include<stdio.h>
#include<stddef.h>
#define mymalloc

char mallocs[25000];

struct block{
	
	size_t size;
	char status;
	struct block *prev;
	struct block *next;
};

struct block *base;

void *Mymalloc(size_t size);

void split(size_t size,struct block *temp);

void initialize();

void printMalloc();

void myfree();


