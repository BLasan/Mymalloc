#include<stdio.h>
#include<stddef.h>
#include "mymalloc.h"


void initialize(){
	base=(struct block*)mallocs;
	base->next=NULL;          //initially consider as whole block is free
	base->prev=NULL;
	base->status='f';
	base->size=25000-sizeof(struct block);                             
    
}

void split(size_t size,struct block *temp){
	
	struct block *free=(void *)(temp)+size+sizeof(struct block);                  //point to the next available block in the array
    size_t remain=temp->size-(size+sizeof(struct block));                   //remaining size         
   
  	
    temp->size=size;
    temp->status='a';                                                        //mark as allocated
    temp->prev=temp->prev;
    free->next=temp->next;
    temp->next=free;
    free->status='f';                                                 //mark the next block as free after splitting
    free->size=remain;
    free->prev=temp;
    
}

void *Mymalloc(size_t size){

	if(!base){                                             //initially if there's no allocation
			initialize();
	}

	
	void *result;
	struct block *curr;
	curr=base;
	while(curr->next!=NULL){
		
		
		if(curr->size>=size&&curr->status=='f')                            //finding the suitable slot
		break;
		curr=curr->next;
		
	}
    if(size==0)                                //if the size is zero then no allocation
    return curr-sizeof(mallocs);
	if(curr->size==size){                        //no need splitting
		
		curr->size=size;
		curr->status='a';
		curr->next=curr->next;
		curr->prev=curr->prev;
	
		result=(void *)(curr)+sizeof(struct block);
		return result;
		
	}
	
	else if(curr->size>size){                              //need splitting
		
		split(size,curr);
	
		result=(void *)(curr)+sizeof(struct block);
		return result;
	}
	
	else if(curr->size<size){
			printf("Not enough memory\n");                               //if no space
			return NULL;
	}

}

void myfree(void* ptr){
	
	 void *temp3=(void *)ptr-sizeof(struct block);                        //return to the address of the first slot of the block 
	 
	 struct block *temper=(struct block *)temp3;                 

	
	 if((ptr>=(void *)mallocs)&&(ptr<=((void *)mallocs+25000))){                     //if given reference is valid
	 	
	 	if(temper==base){                                 //given reference is the first slot
	 		
	 		if(temper->next->status=='f'){                          //if the adjacent block is free
	 			
	 			temper->size=temper->size+temper->next->size+sizeof(struct block);
				if(temper->next->next!=NULL)  
	 			temper->next->next->prev=temper;
	 			temper->next=temper->next->next;                              //merge the two blocks        
				          
	 			temper->status='f';
	 			
			 }
			 else if(temper->next->status=='a'){                         //adjacent block is allocated
			    temper->size=temper->size;
			 	temper->status='f';                                    //no need to merge
			 }
		 }
		 else{
		
		
	    if(temper->prev->status=='f'&&temper->next->status=='f'&&temper->prev!=NULL){        //given reference not the first slot and check the previous and next blocks are free 
       
           temper->prev->size=temper->prev->size+temper->size+temper->next->size+2*sizeof(struct block);     //add the sizes of metadata of two processes
           
	    	temper->prev->next=temper->next->next;                         //merge three blocks
			if(temper->next->next!=NULL)                                        
	    	temper->next->next->prev=temper->prev;
	    	
		}
		
		else if(temper->next->status=='f'){       
		    temper->size=temper->size+temper->next->size+sizeof(struct block);    //addd the size of meta data
			if(temper->next->next!=NULL)          
			temper->next->next->prev=temper;               
		    temper->prev->next=temper;
			temper->next=temper->next->next;                       //if only the next block is free
		    
		    
		}
		    
		else if(temper->prev->status=='f'){                                                     //if only the previous block is free
	
		temper->prev->size=temper->prev->size+temper->size+sizeof(struct block);                             
		temper->prev->next=temper->next;
		
		temper->next->prev=temper->prev;
			
	}
	
	else{                                                       //if there's no free block
		temper->status='f';
		temper->size=temper->size;                                         
	}
	
	temper->status='f';
	
	 }
	 printf("DONE\n");
	
}

   
	      else      {                                                //if invalid reference
	     printf("Error\n");
	      return ;
          }
	

  if(base->next==NULL){                                         //free the memory pool after using the memory
     printMalloc();                                     
    base=NULL;
	printf("Free Memory\n");
	}
	
}
void printMalloc(){
	
	struct block *printer=base;
    while(printer!=NULL){
    	printf("%p(%c)(%u)->",printer,printer->status,printer->size);
    	printer=printer->next;
	}
	printf("\n");
	printf("----------------------------------------------------------------------\n");
}


