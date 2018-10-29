#include<stdio.h>
#include "mymalloc.h"
int main(){
	
	int *ptr=Mymalloc(0);
	printMalloc();
	int *ptr1=Mymalloc(1000);
	myfree(ptr);
	printMalloc();
}
