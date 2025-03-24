#include <stdio.h>
#include <stdlib.h>

struct memory_block{
	int size;
	int proc_size;
	int is_free;
	struct memory_block* next_block;
};
struct memory_block* head = NULL;

void create_memory(int size){
	struct memory_block* new_block = (struct memory_block*) malloc(sizeof(struct memory_block));
	new_block->size = size;
	new_block->is_free = 1;
	if (head==NULL){
		head=new_block;
		new_block->next_block = NULL;
	}
	else{
		new_block->next_block = head;
		head=new_block;
	}
}

int allocate_memory(int block_size){
	struct memory_block* ptr = head;
	struct memory_block* bestfit_memory = NULL;
	
	while(ptr){
		if(ptr->is_free && ptr->size>=block_size){
			if (bestfit_memory == NULL || ptr->size < bestfit_memory->size){
				bestfit_memory = ptr;
			}
		}
		ptr = ptr->next_block;
	}
	
	if(bestfit_memory){
		bestfit_memory->is_free = 0;
		bestfit_memory->proc_size = block_size;
		return 1;
	}
	else{
		return 0;	
	}
}

void print_memory(){
	struct memory_block* ptr = head;
	while(ptr){
		printf("Block Size: %d Process Size:%d, Status: %s\n", ptr->size,ptr->proc_size,(ptr->is_free ? "Free" : "Allocated"));
        	ptr = ptr->next_block;
	}
}
void main(){
	create_memory(100);
	create_memory(500);
	create_memory(250);
	create_memory(50);
	create_memory(600);
	int ch = 1,size;
	
	while(ch){
		printf("Enter the size of the memory to be allocated");
		scanf("%d",&size);
		if(allocate_memory(size))
			printf("The memory has been successfully allocated.\n");
		else
			printf("error, not enough space.\n");
		print_memory();
		printf("Enter 1 to continue, To exit enter 0");
		scanf("%d",&ch);
	}
	
}
